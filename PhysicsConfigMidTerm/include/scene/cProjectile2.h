#pragma once
#include <graphics/sGraphic.h>
#include <graphics/load/sMeshLoadingInfo.h>
#include <graphics/cGraphicsComponent.h>


namespace scene
{
	//Graphics that represents the laser projectile format
	class cProjectile2
	{
	private:
		nGraphics::sGraphic graphicAssets;
		nGraphics::sGraphicsComponentDef graphicsDefinition;
	public:
		cProjectile2();
		virtual ~cProjectile2();

		void AddLoadingInfo(nGraphics::sMeshLoadingInfo& loadingInfo);
		nGraphics::sGraphicsComponentDef GetGraphicDefinition();
		void SendToTextureManager();
	};
}