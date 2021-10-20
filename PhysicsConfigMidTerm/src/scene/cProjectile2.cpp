#include <scene/cProjectile2.h>
#include <graphics/sGraphic.h>
#include <graphics/cGraphicsComponent.h>
#include <graphics/graphics.h>

namespace scene
{
	const std::string meshName = "Projectile2";

	cProjectile2::cProjectile2()
	{
		//Define the graphic assets
		this->graphicAssets = nGraphics::sGraphic("laserTxt", "../Assets/laserTxt.jpg");

		//Set graphic definition
		this->graphicsDefinition.Mesh = meshName;
		this->graphicsDefinition.TexDiffuse = graphicAssets.name;
		glm::set(this->graphicsDefinition.ModelColor, 0.0f, 0.0f, 1.0f, 0.0f);
		glm::set(this->graphicsDefinition.Position, 0.0f, 2.0f, 0.0f);
		glm::set(this->graphicsDefinition.Scale, 1.0f, 1.0f, 1.0f);
		glm::set(this->graphicsDefinition.TexFactors, 1.0f, 1.0f, 1.0f);
		
	}
	cProjectile2::~cProjectile2()
	{
	}
	void cProjectile2::AddLoadingInfo(nGraphics::sMeshLoadingInfo& loadingInfo)
	{
		loadingInfo.File = "../Assets/cone.ply";
		loadingInfo.DoResize = true;
		loadingInfo.Extents = glm::vec3(2.f, 4.f, 2.f);
		loadingInfo.SubMeshes[0].Name = meshName;
	}
	nGraphics::sGraphicsComponentDef cProjectile2::GetGraphicDefinition()
	{
		return this->graphicsDefinition;
	}
	void cProjectile2::SendToTextureManager()
	{
		nGraphics::gTextureManager->LoadSimple(this->graphicAssets);
	}

}