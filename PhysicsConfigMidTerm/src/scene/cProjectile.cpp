#include <scene/cProjectile.h>
#include <graphics/sGraphic.h>
#include <graphics/cGraphicsComponent.h>
#include <graphics/graphics.h>

namespace scene
{
	const std::string meshName = "Projectile";

	cProjectile::cProjectile()
	{
		//Define the graphic assets
		this->graphicAssets = nGraphics::sGraphic("bullet", "../Assets/PerforatedMetalPlate.bmp");

		//Set graphic definition
		this->graphicsDefinition.Mesh = meshName;
		//this->graphicsDefinition.TexDiffuse = graphicAssets.name;
		glm::set(this->graphicsDefinition.ModelColor, 1.0f, 1.0f, 1.0f, 1.0f);
		glm::set(this->graphicsDefinition.Position, 0.0f, 1.0f, 0.0f);
		glm::set(this->graphicsDefinition.Scale, 1.0f, 1.0f, 1.0f);
	}
	cProjectile::~cProjectile()
	{
	}
	void cProjectile::AddLoadingInfo(nGraphics::sMeshLoadingInfo& loadingInfo)
	{
		loadingInfo.File = "../Assets/SoccerBall.obj";
		loadingInfo.DoResize = true;
		loadingInfo.Extents = glm::vec3(2.f, 2.f, 2.f);
		loadingInfo.SubMeshes[0].Name = meshName;
	}
	nGraphics::sGraphicsComponentDef cProjectile::GetGraphicDefinition()
	{
		return this->graphicsDefinition;
	}
	void cProjectile::SendToTextureManager()
	{
		nGraphics::gTextureManager->LoadSimple(this->graphicAssets);
	}

}