#include <cannon/cCannonManager.h>
#include <physics/random_helpers.h>
#include <projectile/cBulletProjectile.h>
#include <projectile/cLaserProjectile.h>
#include <projectile/cBallProjectile.h>
#include <projectile/cEnergyProjectile.h>
#include <graphics/graphics.h>

#include <iostream>

config::sProjectilePreset cannon::cCannonManager::GetPreset(eProjectileType& projectileType)
{
	switch (projectileType)
	{
	case ENERGY:
	{
		return this->projectileConfig.energyBallPreset;
		break;
	}
	case LASER:
	{
		return this->projectileConfig.laserPreset;
		break;
	}
	case BALL:
	{
		return this->projectileConfig.cannonBallPreset;
		break;
	}
	default:
		return this->projectileConfig.bulletPreset;
		break;
	}
}

cannon::cCannonManager::cCannonManager(config::sCannonConfiguration cannonConfig, config::sProjectileConfiguration projectileConfig)
{
	this->cannonConfig = cannonConfig;
	this->projectileConfig = projectileConfig;
}

cannon::cCannonManager::~cCannonManager()
{
}

void cannon::cCannonManager::ShootBullet(glm::mat3& axes, nPhysics::cParticle* particle, glm::vec4& cannonVector)
{
	config::sProjectilePreset preset = GetPreset(projectileType);
	//Standard axes
	glm::vec3 vecX(1.0, 0.0, 1.0);
	glm::vec3 vecZ(-1.0, 0.0, 1.0);
	axes = nPhysics::orthonormalBasisWithParams(vecX, vecZ);
	//Standard position
	glm::vec3 position(0.0, 1.1, 0.0);
	//Apply muzzelVelocity
	glm::vec3 velocity = (axes[0] * preset.muzzleVelocity.x) + (axes[1] * preset.muzzleVelocity.y) + (axes[2] * preset.muzzleVelocity.z);
	velocity *= glm::vec3(cannonVector.x, cannonVector.y, cannonVector.z);
	velocity = glm::normalize(velocity);	
	velocity *= 40.f;
	//Set physic attributes
	particle->SetPosition(position);
	particle->SetVelocity(velocity);
	particle->SetDamping(preset.damping);
}

void  cannon::cCannonManager::ShootLaser(glm::mat3& axes, nPhysics::cParticle* particle, glm::vec4& cannonVector)
{
	config::sProjectilePreset preset = GetPreset(projectileType);
	//Standard axes
	glm::vec3 vecX(1.0, 0.0, 1.0);
	glm::vec3 vecZ(-1.0, 0.0, 1.0);
	axes = nPhysics::orthonormalBasisWithParams(vecX, vecZ);
	//Standard position
	glm::vec3 position(0.0, 1.1, 0.0);
	//Apply muzzelVelocity
	glm::vec3 velocity = (axes[0] * preset.muzzleVelocity.x) + (axes[1] * preset.muzzleVelocity.y) + (axes[2] * preset.muzzleVelocity.z);
	velocity *= glm::vec3(cannonVector.x, cannonVector.y, cannonVector.z);
	velocity = glm::normalize(velocity);
	velocity *= 40.f;
	//Set physic attributes
	particle->SetPosition(position);
	particle->SetVelocity(velocity);
	particle->SetDamping(preset.damping);
}

void  cannon::cCannonManager::ShootBall(glm::mat3& axes, nPhysics::cParticle* particle, glm::vec4& cannonVector)
{
	config::sProjectilePreset preset = GetPreset(projectileType);
	//Standard axes
	glm::vec3 vecX(1.0, 0.0, 1.0);
	glm::vec3 vecZ(-1.0, 0.0, 1.0);
	axes = nPhysics::orthonormalBasisWithParams(vecX, vecZ);
	//Standard position
	glm::vec3 position(0.0, 1.1, 0.0);
	//Apply muzzelVelocity
	glm::vec3 velocity = (axes[0] * preset.muzzleVelocity.x) + (axes[1] * preset.muzzleVelocity.y) + (axes[2] * preset.muzzleVelocity.z);
	velocity *= glm::vec3(cannonVector.x, cannonVector.y, cannonVector.z);
	velocity = glm::normalize(velocity);
	velocity *= 40.f;
	//Set physic attributes
	particle->SetPosition(position);
	particle->SetVelocity(velocity);
	particle->SetDamping(preset.damping);
}

void  cannon::cCannonManager::ShootEnergy(glm::mat3& axes, nPhysics::cParticle* particle, glm::vec4& cannonVector)
{
	config::sProjectilePreset preset = GetPreset(projectileType);
	//Standard axes
	glm::vec3 vecX(1.0, 0.0, 1.0);
	glm::vec3 vecZ(-1.0, 0.0, 1.0);
	axes = nPhysics::orthonormalBasisWithParams(vecX, vecZ);
	//Standard position
	glm::vec3 position(0.0, 1.1, 0.0);
	//Apply muzzelVelocity
	glm::vec3 velocity = (axes[0] * preset.muzzleVelocity.x) + (axes[1] * preset.muzzleVelocity.y) + (axes[2] * preset.muzzleVelocity.z);
	velocity *= glm::vec3(cannonVector.x, cannonVector.y, cannonVector.z);
	velocity = glm::normalize(velocity);
	velocity *= 40.f;
	//Set physic attributes
	particle->SetPosition(position);
	particle->SetVelocity(velocity);
	// energy has acceleration
	glm::vec3 acc(1.0, 5.0, 1.0);
	particle->SetAcceleration(acc);
	particle->SetDamping(preset.damping);

}

void cannon::cCannonManager::SetProjectileType(cannon::eProjectileType type)
{
	this->projectileType = type;
}

nPhysics::cParticle* cannon::cCannonManager::SpawnProjectile()
{
	switch (this->projectileType)
	{
	case ENERGY:
	{
		std::cout << "INSTANCE ENERGY BALL" << std::endl;
		nPhysics::cParticle* particle = new projectile::cEnergyProjectile(GetPreset(projectileType).mass, glm::vec3(0.f));
		particle->SetVelocity(GetPreset(projectileType).muzzleVelocity);
		particle->SetDamping(GetPreset(projectileType).damping);
		return particle;
		break;
	}
	case LASER:
	{
		std::cout << "INSTANCE LASER" << std::endl;
		nPhysics::cParticle* particle = new projectile::cLaserProjectile(GetPreset(projectileType).mass, glm::vec3(0.f));
		particle->SetVelocity(GetPreset(projectileType).muzzleVelocity);
		particle->SetDamping(GetPreset(projectileType).damping);
		return particle;
		break;
	}
	case BALL:
	{
		std::cout << "INSTANCE CANNON BALL" << std::endl;
		nPhysics::cParticle* particle = new projectile::cBallProjectile(GetPreset(projectileType).mass, glm::vec3(0.f));
		particle->SetVelocity(GetPreset(projectileType).muzzleVelocity);
		particle->SetDamping(GetPreset(projectileType).damping);
		return particle;
		break;
	}
	default:
		std::cout << "INSTANCE BULLET" << std::endl;
		nPhysics::cParticle* particle = new projectile::cBulletProjectile(GetPreset(projectileType).mass, glm::vec3(0.f));
		particle->SetVelocity(GetPreset(projectileType).muzzleVelocity);
		particle->SetDamping(GetPreset(projectileType).damping);
		return particle;
		break;
	}

}

bool cannon::cCannonManager::ReachedTimeout(float& timeElapsed, nPhysics::cParticle* particle)
{
	config::sProjectilePreset preset = GetPreset(projectileType);
	if (preset.timeLimit == 0) return false;
	return timeElapsed > preset.timeLimit;
}

bool cannon::cCannonManager::ReachedDistanceLimit(glm::vec3& initialPosition, glm::vec3& currentPosition, nPhysics::cParticle* particle)
{
	config::sProjectilePreset preset = GetPreset(projectileType);
	if (preset.distanceLimit == 0) return false;
	glm::vec3 difference = currentPosition - initialPosition;
	return difference.length() > preset.distanceLimit;
}

void cannon::cCannonManager::ApplyVisual(nGraphics::cGraphicsComponent* graphic)
{
	config::sProjectilePreset preset = GetPreset(projectileType);

	//color
	graphic->GetVars()->ModelColor.r = preset.color.r;
	graphic->GetVars()->ModelColor.g = preset.color.g;
	graphic->GetVars()->ModelColor.b = preset.color.b;
	//mesh/texture
	if (preset.textureName != "")
	{
		graphic->GetVars()->TexDiffuse = nGraphics::gTextureManager->GetTextureByName(preset.textureName);
	}
	//scale
	if (preset.size > 1)
	{
		graphic->GetVars()->ModelMatrix = glm::scale(graphic->GetVars()->ModelMatrix, glm::vec3(preset.size, preset.size, preset.size));
	}
}
