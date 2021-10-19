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
		this->graphicAssets[0] = nGraphics::sGraphic("bulletTxt", "../Assets/bulletTxt.jpg");
		this->graphicAssets[1] = nGraphics::sGraphic("laserTxt", "../Assets/laserTxt.jpg");
		this->graphicAssets[2] = nGraphics::sGraphic("cannonTxt", "../Assets/cannonTxt.jpg");
		this->graphicAssets[3] = nGraphics::sGraphic("energyTxt", "../Assets/energyTxt.jpg");
		
		//Set graphic definition
		this->graphicsDefinition.Mesh = meshName;
		//this->graphicsDefinition.TexDiffuse = graphicAssets[0].name;
		glm::set(this->graphicsDefinition.ModelColor, 1.0f, 0.0f, 0.0f, 1.0f);
		glm::set(this->graphicsDefinition.Position, 0.0f, 2.0f, 0.0f);
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
		for (size_t i = 0; i < 4; i++)
		{
			nGraphics::gTextureManager->LoadSimple(this->graphicAssets[i]);
		}
	}

}