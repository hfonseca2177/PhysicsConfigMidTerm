#pragma once
#include <graphics/sGraphic.h>
#include <graphics/load/sMeshLoadingInfo.h>
#include <graphics/cGraphicsComponent.h>


namespace scene
{
	//Graphics that represents the big ball projectile format
	class cProjectile3
	{
	private:
		nGraphics::sGraphic graphicAssets;
		nGraphics::sGraphicsComponentDef graphicsDefinition;
	public:
		cProjectile3();
		virtual ~cProjectile3();

		void AddLoadingInfo(nGraphics::sMeshLoadingInfo& loadingInfo);
		nGraphics::sGraphicsComponentDef GetGraphicDefinition();
		void SendToTextureManager();
	};
}