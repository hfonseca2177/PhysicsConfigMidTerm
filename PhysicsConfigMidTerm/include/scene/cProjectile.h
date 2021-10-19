#pragma once
#include <graphics/sGraphic.h>
#include <graphics/load/sMeshLoadingInfo.h>
#include <graphics/cGraphicsComponent.h>


namespace scene
{
	//Graphics that represents the base projectile
	class cProjectile
	{
	private:
		nGraphics::sGraphic graphicAssets[4];
		nGraphics::sGraphicsComponentDef graphicsDefinition;
	public:
		cProjectile();
		virtual ~cProjectile();

		void AddLoadingInfo(nGraphics::sMeshLoadingInfo& loadingInfo);
		nGraphics::sGraphicsComponentDef GetGraphicDefinition();
		void SendToTextureManager();
	};
}