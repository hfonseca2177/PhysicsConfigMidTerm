#include <projectile/cBaseProjectile.h>


void projectile::cBaseProjectile::SetPreset(config::sProjectilePreset& preset)
{
	this->preset = preset;
}

config::sProjectilePreset projectile::cBaseProjectile::GetPreset()
{
	return this->preset;
}

bool projectile::cBaseProjectile::ReachedTimeout(float& timeElapsed)
{
	if (this->preset.timeLimit == 0) return false;
	return timeElapsed > this->preset.timeLimit;
}

bool projectile::cBaseProjectile::ReachedDistanceLimit(glm::vec3& initialPosition, glm::vec3& currentPosition)
{
	if (this->preset.distanceLimit == 0) return false;
	glm::vec3 difference = currentPosition - initialPosition;
	return difference.length() > this->preset.distanceLimit;
}

void projectile::cBaseProjectile::ApplyVisual(nGraphics::cGraphicsComponent& graphic)
{
	//color
	graphic.GetVars()->ModelColor.r = this->preset.color.r;
	graphic.GetVars()->ModelColor.g = this->preset.color.g;
	graphic.GetVars()->ModelColor.b = this->preset.color.b;
	//mesh/texture
	if (this->preset.meshName != "")
	{
		graphic.SetDiffuseTexture(this->preset.meshName);
	}
	//scale
	if (this->preset.size > 1)
	{
		//TODO
	}

}
