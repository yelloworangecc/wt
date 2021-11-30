#ifndef _CONFIGURE_READER_H_
#define _CONFIGURE_READER_H_
#include <string>
#include "json.hpp"

class ConfigureReader
{
public:

	enum ERROR_CODE
	{
		ERROR_NONE = 0,
		ERROR_LOAD,
		ERROR_FIND

	};

	static const int MAX_OPTION_NAME_LEN;

	ConfigureReader(const std::string& path);
	~ConfigureReader();
	ERROR_CODE locate(const std::string& name, nlohmann::json& jret);
	ERROR_CODE getOptionValue(const std::string& name,std::string& value);
	ERROR_CODE getOptionValue(const std::string& name, int& value);
private:
	nlohmann::json j;
	bool isLoaded;
};
#endif
