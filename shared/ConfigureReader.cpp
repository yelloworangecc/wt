#include <fstream>
#include <sstream>
#include <string>
#include "ConfigureReader.h"

const int ConfigureReader::MAX_OPTION_NAME_LEN = 127;

ConfigureReader::ConfigureReader(const std::string& path)
	:isLoaded(false)
{
	j = nlohmann::json::object();
	std::ifstream fs(path, std::ifstream::in);
	if (fs.good())
	{
		fs >> j;
		if (fs.good()) isLoaded = true;
	}
}

ConfigureReader::~ConfigureReader()
{
}

ConfigureReader::ERROR_CODE ConfigureReader::locate(const std::string& name, nlohmann::json& child)
{
	if (!isLoaded) return ERROR_LOAD;

	std::istringstream in(name);
	char temp[MAX_OPTION_NAME_LEN + 1];
	child = j;

	while (in.good())
	{
		in.getline(temp, MAX_OPTION_NAME_LEN + 1, '.');//please use getline() instead of get() (if not find '.', the remained charaters will be discarded)
		if (child.find(temp) != child.end())
		{
			child = child[temp];
		}
		else
		{
			child.clear();
			return ERROR_FIND;
		}
	}
	return ERROR_NONE;
}

ConfigureReader::ERROR_CODE ConfigureReader::getOptionValue(const std::string& name,std::string& value)
{
	nlohmann::json child;
	ERROR_CODE ecode = locate(name, child);
	if (ecode == ERROR_NONE) child.get_to(value);
	return ecode;
}

ConfigureReader::ERROR_CODE ConfigureReader::getOptionValue(const std::string& name, int& value)
{
	nlohmann::json child;
	ERROR_CODE ecode = locate(name, child);
	if (ecode == ERROR_NONE) child.get_to(value);
	return ecode;
}