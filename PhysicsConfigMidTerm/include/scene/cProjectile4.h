#pragma once
#include <graphics/sGraphic.h>
#include <graphics/load/sMeshLoadingInfo.h>
#include <graphics/cGraphicsComponent.h>

namespace scene
{
	//Graphics that represents the cloud projectile format
	class cProjectile4
	{
	private:
		nGraphics::sGraphic graphicAssets;
		nGraphics::sGraphicsComponentDef graphicsDefinition;
	public:
		cProjectile4();
		virtual ~cProjectile4();

		void AddLoadingInfo(nGraphics::sMeshLoadingInfo& loadingInfo);
		nGraphics::sGraphicsComponentDef GetGraphicDefinition();
		void SendToTextureManager();
	};

}