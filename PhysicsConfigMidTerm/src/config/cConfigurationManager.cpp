#pragma once
#include <string>
#include <vector>
#include "rapidjson/document.h"
#include <rapidjson/writer.h>

#include "rapidjson/filewritestream.h"


#include <config/JsonUtils.h>
#include <config/cConfigurationManager.h>
#include <config/sConfiguration.h>

using namespace rapidjson;

void ReadProjectilePreset(config::sProjectilePreset& projectileConf, Value& preset)
{
	projectileConf.mass = preset["mass"].GetFloat();
	projectileConf.damping = preset["damping"].GetFloat();
	projectileConf.size = preset["size"].GetFloat();
	projectileConf.timeLimit = preset["timeLimit"].GetFloat();
	projectileConf.distanceLimit = preset["distanceLimit"].GetFloat();
	projectileConf.muzzleVelocity.x = preset["muzzleVelocity"]["x"].GetFloat();
	projectileConf.muzzleVelocity.y = preset["muzzleVelocity"]["y"].GetFloat();
	projectileConf.muzzleVelocity.z = preset["muzzleVelocity"]["z"].GetFloat();
	projectileConf.color.r = preset["color"]["r"].GetFloat();
	projectileConf.color.g = preset["color"]["g"].GetFloat();
	projectileConf.color.b = preset["color"]["b"].GetFloat();
	projectileConf.textureName = preset["textureName"].GetString();
}

void config::cConfigurationManager::LoadProjectileConfig()
{
	Document configFile = FromJson(this->particlesConfigFileName);
	this->projectileConfig = config::sProjectileConfiguration();
	Value& conf = configFile["configuration"];
	ReadProjectilePreset(this->projectileConfig.bulletPreset, conf["bulletPreset"]);
	ReadProjectilePreset(this->projectileConfig.laserPreset, conf["laserPreset"]);
	ReadProjectilePreset(this->projectileConfig.cannonBallPreset, conf["cannonBallPreset"]);
	ReadProjectilePreset(this->projectileConfig.energyBallPreset, conf["energyBallPreset"]);
}

void config::cConfigurationManager::LoadCannonConfig()
{
	Document configFile = FromJson(this->cannonConfigFileName);
	this->cannonConfig = config::sCannonConfiguration();
	Value& conf = configFile["configuration"];
	this->cannonConfig.pitch.x = conf["pitch"]["min"].GetFloat();
	this->cannonConfig.pitch.y = conf["pitch"]["max"].GetFloat();
	this->cannonConfig.yaw.x = conf["yaw"]["min"].GetFloat();
	this->cannonConfig.yaw.y = conf["yaw"]["max"].GetFloat();
}

config::sProjectileConfiguration config::cConfigurationManager::GetProjectileConfiguration()
{
	return this->projectileConfig;
}
config::sCannonConfiguration config::cConfigurationManager::GetCannonConfiguration()
{
	return this->cannonConfig;
}


void config::cConfigurationManager::LoadConfiguration()
{
	LoadCannonConfig();
	LoadProjectileConfig();
}
