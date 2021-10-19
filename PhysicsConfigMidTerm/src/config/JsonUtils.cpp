#include <rapidjson/writer.h>
#include <sys/stat.h>
#include <rapidjson/filewritestream.h>
#include <config/JsonUtils.h>

#define _CRT_SECURE_NO_WARNINGS

Document FromJson(const std::string& filePath)
{
	FILE* fp = 0;
	fopen_s(&fp, filePath.c_str(), "rb"); // non-Windows use "r"

	char readBuffer[65536];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));

	Document d;
	d.ParseStream(is);

	fclose(fp);
	return d;
}

void ToJson(const std::string& filePath, Document& json)
{
	FILE* fp = fopen(filePath.c_str(), "wb"); // non-Windows use "w"

	char writeBuffer[65536];
	
	FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));

	Writer<FileWriteStream> writer(os);
	json.Accept(writer);

	fclose(fp);
}

bool Exists(const std::string& filePath)
{
	struct stat buffer;
	return (stat(filePath.c_str(), &buffer) == 0);
}
