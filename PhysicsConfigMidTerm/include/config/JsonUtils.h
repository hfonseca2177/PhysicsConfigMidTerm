#pragma once
#include <rapidjson/filereadstream.h>
#include <rapidjson/document.h>
#include <string>

using namespace rapidjson;

//Reads a file from the path and converts to a rapidjson document
Document FromJson(const std::string& filePath);
//Writes the document ovewritting the file
void ToJson(const std::string& filePath, Document& json);
//Checks if the file exists in the given path
bool Exists(const std::string& filePath);