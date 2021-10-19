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
		glm::set(graphicsDefinition.Position, 0.0f, -5.5f, 0.0f);
		glm::set(graphicsDefinition.Scale, 5.0f, 1.0f, 5.0f);

	}
	cPlatform::~cPlatform()
	{
	}

	void cPlatform::AddLoadingInfo(nGraphics::sMeshLoadingInfo& loadingInfo)
	{
		loadingInfo.File = "../Assets/box.obj";
		loadingInfo.DoResize = true;
		loadingInfo.Extents = glm::vec3(2.f, 2.f, 2.f);
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
