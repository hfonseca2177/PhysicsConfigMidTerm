#pragma once
#include <string>
#include <config/sConfiguration.h>

namespace config
{
	//Configuration Manager that loads the cannon and projectiles configurations 
	class cConfigurationManager
	{
	private:
		const std::string particlesConfigFileName = "config/ProjectileConfig.json";
		const std::string cannonConfigFileName = "config/CannonConfig.json";
		config::sProjectileConfiguration projectileConfig;
		config::sCannonConfiguration cannonConfig;
		void LoadProjectileConfig();
		void LoadCannonConfig();
	public:
		virtual ~cConfigurationManager() {};
		void LoadConfiguration();
		config::sProjectileConfiguration GetProjectileConfiguration();
		config::sCannonConfiguration GetCannonConfiguration();
	};
}