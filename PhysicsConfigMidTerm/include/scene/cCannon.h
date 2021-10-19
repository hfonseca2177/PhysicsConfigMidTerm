#pragma once
#include <graphics/sGraphic.h>
#include <graphics/load/sMeshLoadingInfo.h>
#include <graphics/cGraphicsComponent.h>


namespace scene
{
	//Graphics that represents the cannon
	class cCannon
	{
	private:
		nGraphics::sGraphic graphicAssets;
		nGraphics::sGraphicsComponentDef graphicsDefinition;
	public:
		cCannon();
		virtual ~cCannon();

		void AddLoadingInfo(nGraphics::sMeshLoadingInfo& loadingInfo);
		nGraphics::sGraphicsComponentDef GetGraphicDefinition();
		void SendToTextureManager();
	};
}