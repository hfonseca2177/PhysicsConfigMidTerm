#include <scene/cClearSky.h>
#include <graphics/sCubeGraphic.h>
#include <graphics/cGraphicsComponent.h>
#include <graphics/graphics.h>

namespace scene
{
	cClearSky::cClearSky()
	{
		//Define the graphic assets
		this->graphicAssets = nGraphics::sCubeGraphic("DayLight", "../Assets/daylight_box/",
			"Daylight Box_Front.bmp", "Daylight Box_Back.bmp",
			"Daylight Box_Bottom.bmp", "Daylight Box_Top.bmp",
			"Daylight Box_Right.bmp", "Daylight Box_Left.bmp");
	
		//Set graphic definition
		this->graphicsDefinition.Mesh = graphicAssets.name;
		this->graphicsDefinition.TexCubeMap = graphicAssets.name;
		glm::set(this->graphicsDefinition.ModelColor, 1.0f, 1.0f, 1.0f, 1.0f);
		glm::set(this->graphicsDefinition.Position, 0.0f, 0.0f, 0.0f);
		glm::set(this->graphicsDefinition.Scale, 500.0f, 500.0f, 500.0f);
	}
	cClearSky::~cClearSky()
	{
	}
	void cClearSky::AddLoadingInfo(nGraphics::sMeshLoadingInfo& loadingInfo)
	{	
		loadingInfo.File = "../Assets/daylight_box/Isoshphere_xyz_InvertedNormals.ply";
		loadingInfo.DoResize = false;
		loadingInfo.AddSubMesh(this->graphicAssets.name);
	}
	nGraphics::sGraphicsComponentDef cClearSky::GetGraphicDefinition()
	{
		return this->graphicsDefinition;
	}
	void cClearSky::SendToTextureManager()
	{
		nGraphics::gTextureManager->LoadCube(this->graphicAssets);
	}

}

