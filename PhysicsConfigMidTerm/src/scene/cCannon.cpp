#include <scene/cCannon.h>
#include <graphics/sGraphic.h>
#include <graphics/cGraphicsComponent.h>
#include <graphics/graphics.h>

namespace scene
{
	const std::string meshName = "Cannon";

	cCannon::cCannon()
	{
		//Define the graphic assets
		this->graphicAssets = nGraphics::sGraphic("plate", "../Assets/PerforatedMetalPlate.bmp");

		//Set graphic definition
		this->graphicsDefinition.Mesh = meshName;
		this->graphicsDefinition.TexDiffuse = graphicAssets.name;
		glm::set(this->graphicsDefinition.ModelColor, 1.0f, 1.0f, 1.0f, 1.0f);
		glm::set(this->graphicsDefinition.Position, 0.0f, 1.0f, 0.0f);
		glm::set(this->graphicsDefinition.Scale, 1.0f, 1.0f, 1.0f);
	}
	cCannon::~cCannon()
	{
	}
	void cCannon::AddLoadingInfo(nGraphics::sMeshLoadingInfo& loadingInfo)
	{
		loadingInfo.File = "../Assets/cylinder.obj";
		loadingInfo.DoResize = true;
		loadingInfo.Extents = glm::vec3(2.f, 2.f, 2.f);
		loadingInfo.SubMeshes[0].Name = meshName;
	}
	nGraphics::sGraphicsComponentDef cCannon::GetGraphicDefinition()
	{
		return this->graphicsDefinition;
	}
	void cCannon::SendToTextureManager()
	{
		nGraphics::gTextureManager->LoadSimple(this->graphicAssets);
	}

}