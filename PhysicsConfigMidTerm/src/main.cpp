#include <iostream>
#include <graphics/graphics.h>
#include <input/input.h>
#include <graphics/cCamera.h>
#include <graphics/cameras/c3rdPersonCamera.h>
#include <graphics/cGraphicsComponent.h>
#include <physics/cParticleWorld.h>
#include <physics/particle_force_generators.h>
#include <scene/cClearSky.h>
#include <scene/cPlatform.h>
#include <scene/cCannon.h>
#include <scene/cProjectile.h>
#include <config/cConfigurationManager.h>
#include <cannon/cCannonManager.h>
#include <projectile/cBaseProjectile.h>



// Generate a random number between 0 and 1
float getRandom();

// Generate a random number between zero and a given high value
float getRandom(float high);

// Generate a random number in a given range
float getRandom(float low, float high);

// Returns a vector laying on the x-z plane, randomized in direction and magnitude.
// The output is designed to be linearly independent from the output of getRandomZVector()
glm::vec3 getRandomXVector();

// Returns a vector laying on the x-z plane, randomized in direction and magnitude.
// The output is designed to be linearly independent from the output of getRandomXVector()
glm::vec3 getRandomZVector();

// Determine from the parameters if the particle is currently above the ground.
bool particleIsAboveGround(glm::mat3& axes, float& deltaTime, float& timeElapsed, glm::vec3& position, glm::vec3& velocity);

// Determine from the parameters if the particle is currently moving "up".
bool particleIsMovingUpward(glm::mat3& axes, float& deltaTime, float& timeElapsed, glm::vec3& position, glm::vec3& velocity);

// Perform one single time-step implementing Euler Integration.
//void doTimeStepEuler(glm::mat3& axes, float& deltaTime, float& timeElapsed, glm::vec3& position, glm::vec3& velocity);
// Perform one single time-step implementing Midpoint Integration.
//void doTimeStepMidpoint(glm::mat3& axes, float& deltaTime, float& timeElapsed, glm::vec3& position, glm::vec3& velocity);

glm::mat3 orthonormalBasis(const glm::vec3& xVec, const glm::vec3& zVec);

void mainLoop();

nGraphics::sPerFrameVars PerFrameVars;
nGraphics::c3rdPersonCamera* camera = 0;
nGraphics::cGraphicsComponent* skyboxGraphics;
nGraphics::cGraphicsComponent* platformGraphics;
nGraphics::cGraphicsComponent* cannonGraphics;
nGraphics::cGraphicsComponent* projectilesGraphics;

config::cConfigurationManager* configManager;

int main()
{
	camera = new nGraphics::c3rdPersonCamera();
	nGraphics::SetCamera(camera);
	glm::mat4 identity(1.f);
	camera->SetTargetTransform(identity);

	if (!nGraphics::Init())
	{
		std::cout << "booo graphics didn't start up right" << std::endl;
		system("pause");
		return -1;
	}
	if (!nInput::Init())
	{
		std::cout << "booo inputs didn't start up right" << std::endl;
		system("pause");
		return -1;
	}
	//Load Cannon and Projectiles configurations
	configManager = new config::cConfigurationManager();
	configManager->LoadConfiguration();


	//Instantiate all Shuriken's launch platform scenario graphics component
	scene::cClearSky clearSky = scene::cClearSky();
	scene::cPlatform platform = scene::cPlatform();
	scene::cCannon cannon = scene::cCannon();
	scene::cProjectile projectile = scene::cProjectile();
	
	
	// Loading textures to use with our meshes
	clearSky.SendToTextureManager();
	platform.SendToTextureManager();
	cannon.SendToTextureManager();
	projectile.SendToTextureManager();

	// Loading meshes
	std::vector<nGraphics::sMeshLoadingInfo> infos;
	nGraphics::sMeshLoadingInfo loadingInfo;

	clearSky.AddLoadingInfo(loadingInfo);
	infos.push_back(loadingInfo);
	
	platform.AddLoadingInfo(loadingInfo);
	infos.push_back(loadingInfo);

	cannon.AddLoadingInfo(loadingInfo);
	infos.push_back(loadingInfo);

	projectile.AddLoadingInfo(loadingInfo);
	infos.push_back(loadingInfo);

	if (!nGraphics::gMeshManager->Load(infos))
	{
		std::cout << "booooo failed to load meshes" << std::endl;
		return -1;
	}

	// Create the graphics components

	skyboxGraphics = new nGraphics::cGraphicsComponent(clearSky.GetGraphicDefinition());
	platformGraphics = new nGraphics::cGraphicsComponent(platform.GetGraphicDefinition());
	cannonGraphics = new nGraphics::cGraphicsComponent(cannon.GetGraphicDefinition());
	projectilesGraphics = new nGraphics::cGraphicsComponent(projectile.GetGraphicDefinition());

	// Enter the main loop
	mainLoop();

	// Clean up
	delete platformGraphics;
	delete cannonGraphics;
	delete projectilesGraphics;
	delete skyboxGraphics;
	delete camera;

	nGraphics::Shutdown();

	// all done!
	return 0;
}

//Default particle Setup
//void InitProject1Variables(glm::mat3& axes, nPhysics::cParticle* particle)
//{
//	axes = orthonormalBasis(getRandomXVector(), getRandomZVector());
//	// because our "sphere" has a radius of 1
//	glm::vec3 position(0.0, 1.1f, 0.0);
//	glm::vec3 velocity = (axes[0] * getRandom(-2.f, 2.f)) + (axes[1] * 5.f) + (axes[2] * getRandom(-2.f, 2.f));
//	velocity = glm::normalize(velocity);
//	velocity *= 50.f;
//	particle->SetPosition(position);
//	particle->SetVelocity(velocity);
//}

//Bind projectile particle to the world manager
void AddProjectileToWorld(nPhysics::cParticle* projectile, nPhysics::cParticleGravityGenerator& gravityGenerator,
	nPhysics::cParticleWorld* world, cannon::cCannonManager& cannonManager)
{
	projectile = cannonManager.SpawnProjectile();

	world->AddParticle(projectile);
	
	world->GetForceRegistry()->Register(projectile, &gravityGenerator);
}

// Clean Projectile from world
void CleanProjectile(nPhysics::cParticle* projectile, nPhysics::cParticleWorld* world)
{
	// clean up!
	if (projectile != nullptr)
	{
		world->RemoveParticle(projectile);
		delete projectile;
	}
	
}

//Main program
void mainLoop()
{
	nInput::gInputManager->ClearState();

	nGraphics::Focus();

	bool continueMainLoop = true;

	float previousTime = static_cast<float>(glfwGetTime());

	float fpsFrameCount = 0.f;
	float fpsTimeElapsed = 0.f;

	// BEGIN PROJECT 1 SETUP
	nPhysics::cParticleWorld* world = new nPhysics::cParticleWorld();

	//Shuriken fireworks manager instance
	cannon::cCannonManager cannonManager = cannon::cCannonManager(configManager->GetCannonConfiguration(), configManager->GetProjectileConfiguration());

	nPhysics::cParticleGravityGenerator gravityGenerator(glm::vec3(0.0f, -9.81f, 0.0f));

	//InitWorld(particles, gravityGenerator, world, cannonManager);
	glm::vec3 initialPosition = glm::vec3(0.0f);
	nPhysics::cParticle* projectile = new nPhysics::cParticle(0.0f, initialPosition);

	glm::mat3 axes;
	float timeElapsed = 0;

	bool projectileIsAlive = false;
	

	//cannon controls
	nInput::cKey* oneLeft = nInput::cInputManager::GetInstance()->ListenToKey(nInput::KeyCode::KEY_LEFT);
	nInput::cKey* twoRight = nInput::cInputManager::GetInstance()->ListenToKey(nInput::KeyCode::KEY_RIGHT);
	nInput::cKey* threeUp = nInput::cInputManager::GetInstance()->ListenToKey(nInput::KeyCode::KEY_UP);
	nInput::cKey* threeDown = nInput::cInputManager::GetInstance()->ListenToKey(nInput::KeyCode::KEY_DOWN);
	
	//Listener for the keys 1 2 3 4 respectively for each projectile type
	nInput::cKey* oneKey = nInput::cInputManager::GetInstance()->ListenToKey(nInput::KeyCode::KEY_1);
	nInput::cKey* twoKey = nInput::cInputManager::GetInstance()->ListenToKey(nInput::KeyCode::KEY_2);
	nInput::cKey* threeKey = nInput::cInputManager::GetInstance()->ListenToKey(nInput::KeyCode::KEY_3);
	nInput::cKey* fourKey = nInput::cInputManager::GetInstance()->ListenToKey(nInput::KeyCode::KEY_4);

	

	while (continueMainLoop)
	{
		float currentTime = static_cast<float>(glfwGetTime());
		float deltaTime = currentTime - previousTime;
		previousTime = currentTime;

		// FPS TITLE STUFF
		{
			fpsTimeElapsed += deltaTime;
			fpsFrameCount += 1.0f;
			if (fpsTimeElapsed >= 0.03f)
			{
				std::string fps = std::to_string(fpsFrameCount / fpsTimeElapsed);
				std::string ms = std::to_string(1000.f * fpsTimeElapsed / fpsFrameCount);
				std::string newTitle = "FPS: " + fps + "   MS: " + ms;
				nGraphics::SetWindowTitle(newTitle);
				// reset times and counts
				fpsTimeElapsed = 0.f;
				fpsFrameCount = 0.f;
			}
		}
		
		
		// Continue the simulation so long as the particle is above the ground.
		if (!projectileIsAlive)
		{
			//Fire Bullet
			if (oneKey->IsJustPressed())
			{
				std::cout << "ONE PRESSED - BULLET" << std::endl;
				cannonManager.SetProjectileType(cannon::BULLET);
				CleanProjectile(projectile, world);
				AddProjectileToWorld(projectile, gravityGenerator, world, cannonManager);
				cannonManager.ShootBullet(axes, projectile);
				projectileIsAlive = true;
			}
			//Fire laser
			else if (twoKey->IsJustPressed()) {
				
				std::cout << "TWO PRESSED - LASER" << std::endl;
				cannonManager.SetProjectileType(cannon::LASER);
				CleanProjectile(projectile, world);
				AddProjectileToWorld(projectile, gravityGenerator, world, cannonManager);
				cannonManager.ShootLaser(axes, projectile);
				projectileIsAlive = true;
			}
			//Fire cannon ball
			else if (threeKey->IsJustPressed()) {
				std::cout << "Three PRESSED - CANNON BALL" << std::endl;
				cannonManager.SetProjectileType(cannon::BALL);
				CleanProjectile(projectile, world);
				AddProjectileToWorld(projectile, gravityGenerator, world, cannonManager);
				cannonManager.ShootLaser(axes, projectile);
				projectileIsAlive = true;
			}
			//Replace normal particles for the Shuriken Zeta ones
			else if (fourKey->IsJustPressed()) {
				std::cout << "THREE PRESSED - ENERGY BALL" << std::endl;
				cannonManager.SetProjectileType(cannon::ENERGY);
				CleanProjectile(projectile, world);
				AddProjectileToWorld(projectile, gravityGenerator, world, cannonManager);
				cannonManager.ShootEnergy(axes, projectile);
				projectileIsAlive = true;
			}
		}
		glm::vec3 position = projectile->GetPosition();
		glm::vec3 velocity = projectile->GetVelocity();

		if (projectileIsAlive)
		{
			if(dynamic_cast<projectile::cBaseProjectile*>(projectile)->ReachedTimeout(timeElapsed))
			{
				std::cout << "Projectile Timeout after " << timeElapsed << " seconds with a velocity x=" << velocity.x << "\ty=" << velocity.y << "\tz=" << velocity.z << std::endl;
				projectileIsAlive = false;
			}
			else if (dynamic_cast<projectile::cBaseProjectile*>(projectile)->ReachedDistanceLimit(initialPosition, position))
			{
				std::cout << "Projectile reached a distant limit after " << timeElapsed << " seconds with a velocity x=" << velocity.x << "\ty=" << velocity.y << "\tz=" << velocity.z << std::endl;
				projectileIsAlive = false;
			}
			else if (particleIsAboveGround(axes, deltaTime, timeElapsed, position, velocity))
			{
				if (particleIsMovingUpward(axes, deltaTime, timeElapsed, position, velocity))
				{
					// Let the user know the particle is moving up.
					//std::cout << "going up! \tx=" << position.x << "\ty=" << position.y << "\tz=" << position.z << std::endl;
				}
				else
				{
					// Let the user know the particle is moving down.
					//std::cout << "going down! \tx=" << position.x << "\ty=" << position.y << "\tz=" << position.z << std::endl;
				}
				
				world->TimeStep(deltaTime);
				// Step the simulation forward
				//doTimeStepEuler(axes, deltaTime, timeElapsed, position, velocity, acceleration);
				//doTimeStepMidpoint(axes, deltaTime, timeElapsed, position, velocity, acceleration);
			}
			else
			{
				std::cout << "Impacted after " << timeElapsed << " seconds with a velocity x=" << velocity.x << "\ty=" << velocity.y << "\tz=" << velocity.z << std::endl;
				projectileIsAlive = false;
			}
		}

		// Safety, mostly for first frame
		if (deltaTime == 0.f)
		{
			deltaTime = 0.03f;
		}

		// update the camera
		camera->Update(deltaTime);

		// done with all the updates involving input, so clear it out
		nInput::gInputManager->ClearState();

		// begin setting per-frame vars
		camera->GetEyePosition(PerFrameVars.EyePosition);
		camera->GetViewMatrix(PerFrameVars.ViewMatrix);
		camera->GetProjectionMatrix(PerFrameVars.ProjectionMatrix);
		// end setting per-frame vars

		nGraphics::BeginFrame(PerFrameVars);

		// begin per-item rendering
		skyboxGraphics->Render();
		platformGraphics->Render();
		cannonGraphics->Render();
		// render the projectile
		projectile->GetPosition(position);
		projectilesGraphics->GetVars()->ModelMatrix = glm::translate(glm::mat4(1.0f), position);
		projectilesGraphics->Render();
		
		// end per-item rendering

		nGraphics::EndFrame();

		// Exit conditions: press escape or close the window by the 'x' button
		if (!(nInput::IsKeyUp::Escape() && !nGraphics::WindowShouldClose()))
		{
			continueMainLoop = false;
		}
	}

	//// clean up!
	CleanProjectile(projectile, world);
	projectile = 0;
	delete world;
}

float getRandom()
{
	return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

float getRandom(float high)
{
	return static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / high);
}

float getRandom(float low, float high)
{
	return low + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / (high - low));
}

// Use as-is.  Do not change.
glm::vec3 getRandomXVector()
{
	return glm::vec3(getRandom(0.1f, 1.f), 0.f, getRandom(0.1f, 1.f));
}

// Use as-is.  Do not change.
glm::vec3 getRandomZVector()
{
	return glm::vec3(-getRandom(0.1f, 1.f), 0.f, getRandom(0.1f, 1.f));
}

bool particleIsAboveGround(glm::mat3& axes, float& deltaTime, float& timeElapsed, glm::vec3& position, glm::vec3& velocity)
{
	// TODO: Use the parameters to determine if the particle
	//       is currently above the ground.
	//       Return true if the particle is above the ground, false otherwise.
	return position.y > 1.0f; // because our "sphere" has a radius of 1
}

bool particleIsMovingUpward(glm::mat3& axes, float& deltaTime, float& timeElapsed, glm::vec3& position, glm::vec3& velocity)
{
	// TODO: Use the parameters to determine if the particle
	//       is currently moving upward.
	//       Return true if the particle is above the ground, false otherwise.
	return glm::dot(velocity, axes[1]) > 0;
}

glm::mat3 orthonormalBasis(const glm::vec3& xVec, const glm::vec3& zVec)
{
	// TODO: Generate an orthonormal basis, using xVec and zVec.
	//       The input vectors may be manipulated, however the 
	//       returned axes must essentially be:
	//       x-axis: sourced from xVec
	//       y-axis: generated using math!
	//       z-axis: sourced from zVec

	// Generate y, by crossing z and x.
	glm::vec3 x(xVec);
	glm::vec3 z(zVec);
	glm::vec3 y(glm::cross(z, x));
	// Ensure z is orthogonal to both x and y.
	z = glm::cross(x, y);
	// Normalize everything.
	x = glm::normalize(x);
	y = glm::normalize(y);
	z = glm::normalize(z);
	// Return the result.
	return glm::mat3(x, y, z);
}