#pragma once
#include <string>

namespace nGraphics
{
	using namespace std;
    //Container for basic graphic information
	struct sGraphic
	{
		string name;
		string assetFolder;

		sGraphic() {}

		sGraphic(string name, string assetFolder)
		{
			this->name = name;
			this->assetFolder = assetFolder;
		}
	};
}