#include <scene/cProjectile3.h>
#include <graphics/sGraphic.h>
#include <graphics/cGraphicsComponent.h>
#include <graphics/graphics.h>

namespace scene
{
	const std::string meshName = "Projectile3";

	cProjectile3::cProjectile3()
	{
		//Define the graphic assets
		
		this->graphicAssets = nGraphics::sGraphic("cannonTxt", "../Assets/cannonTxt.jpg");
		

		//Set graphic definition
		this->graphicsDefinition.Mesh = meshName;
		this->graphicsDefinition.TexDiffuse = graphicAssets.name;
		glm::set(this->graphicsDefinition.ModelColor, 1.0f, 0.0f, 0.0f, 1.0f);
		glm::set(this->graphicsDefinition.Position, 0.0f, 2.0f, 0.0f);
		glm::set(this->graphicsDefinition.Scale, 1.0f, 1.0f, 1.0f);
	}
	cProjectile3::~cProjectile3()
	{
	}
	void cProjectile3::AddLoadingInfo(nGraphics::sMeshLoadingInfo& loadingInfo)
	{
		loadingInfo.File = "../Assets/SoccerBall.obj";
		loadingInfo.DoResize = true;
		loadingInfo.Extents = glm::vec3(2.f, 2.f, 2.f);
		loadingInfo.SubMeshes[0].Name = meshName;
	}
	nGraphics::sGraphicsComponentDef cProjectile3::GetGraphicDefinition()
	{
		return this->graphicsDefinition;
	}
	void cProjectile3::SendToTextureManager()
	{
		nGraphics::gTextureManager->LoadSimple(this->graphicAssets);
	}

}