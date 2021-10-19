#pragma once
#include <extern_includes.h>
#include <string>

namespace config
{
	//Preset configuration for projectiles
	struct sProjectilePreset
	{
		float mass;
		float damping;
		float size;
		float timeLimit;
		float distanceLimit;
		glm::vec3 muzzleVelocity;
		glm::vec3 color;
		std::string meshName;
	};

	//Preset configuration for cannon functionality
	struct sCannonConfiguration
	{
		glm::vec2 pitch;
		glm::vec2 yaw;
	};

	//Program Projectile configurations
	struct sProjectileConfiguration
	{
		sProjectilePreset bulletPreset;
		sProjectilePreset laserPreset;
		sProjectilePreset cannonBallPreset;
		sProjectilePreset energyBallPreset;
	};
}
