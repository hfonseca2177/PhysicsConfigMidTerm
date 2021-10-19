#pragma once
#include <graphics/sCubeGraphic.h>
#include <graphics/load/sMeshLoadingInfo.h>
#include <graphics/cGraphicsComponent.h>

namespace scene 
{	
	//Graphics for a clear sky representation
	class cClearSky
	{
	private:
		nGraphics::sCubeGraphic graphicAssets;
		nGraphics::sGraphicsComponentDef graphicsDefinition;
	public:
		cClearSky();
		virtual ~cClearSky();

		void AddLoadingInfo(nGraphics::sMeshLoadingInfo& loadingInfo);
		nGraphics::sGraphicsComponentDef GetGraphicDefinition();
		void SendToTextureManager();
	};
}
