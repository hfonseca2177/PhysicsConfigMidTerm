#pragma once
#include <string>
#include <graphics/sGraphic.h>

namespace nGraphics
{
	using namespace std;

	// Common cube Graphic information
	struct sCubeGraphic : public sGraphic 
	{
		string posX;
		string negX;

		string posY;
		string negY;
		
		string negZ;
		string posZ;
		sCubeGraphic()
		{
		}
		sCubeGraphic(string name, string assetFolder, string posX, string negX, string posY, string negY, string posZ, string negZ)
		{
			this->name = name;
			this->assetFolder = assetFolder;
			this->posX = assetFolder + posX;
			this->posY = assetFolder + posY;
			this->posZ = assetFolder + posZ;
			this->negX = assetFolder + negX;
			this->negY = assetFolder + negY;
			this->negZ = assetFolder + negZ;
		}

	};

}