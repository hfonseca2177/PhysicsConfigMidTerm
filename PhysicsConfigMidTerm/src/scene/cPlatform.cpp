#include <scene/cPlatform.h>
#include <graphics/sGraphic.h>
#include <graphics/cGraphicsComponent.h>
#include <graphics/graphics.h>
namespace scene
{

	const std::string meshName = "platform";

	cPlatform::cPlatform()
	{
		//Define the graphic assets
	    graphicAssets = nGraphics::sGraphic("box", "../Assets/texture.jpg");

		//Set graphic definition	
		graphicsDefinition.Mesh = meshName;
		graphicsDefinition.TexDiffuse = graphicAssets.name;
		glm::set(graphicsDefinition.ModelColor, 1.0f, 1.0f, 1.0f, 1.0f);
		glm::set(graphicsDefinition.Position, 0.0f, -0.2f, 0.0f);
		glm::set(graphicsDefinition.Scale, 1.0f, 1.0f, 1.0f);

	}
	cPlatform::~cPlatform()
	{
	}

	void cPlatform::AddLoadingInfo(nGraphics::sMeshLoadingInfo& loadingInfo)
	{
		loadingInfo.File = "../Assets/box.obj";
		loadingInfo.DoResize = true;
		loadingInfo.Extents = glm::vec3(12.f, 12.f, 12.f);
		loadingInfo.SubMeshes[0].Name = meshName;
	}

	nGraphics::sGraphicsComponentDef cPlatform::GetGraphicDefinition()
	{
		return this->graphicsDefinition;
	}
	void cPlatform::SendToTextureManager()
	{
		nGraphics::gTextureManager->LoadSimple(this->graphicAssets);
	}
}
