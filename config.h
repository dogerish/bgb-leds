#ifndef CONFIG_STRUCT
#define CONFIG_STRUCT

#include <string>
// hold configuration info
// S is data type to store info as, default std::string
template<typename S>
class Config
{
	public:
		S leddir;
		S ledpre;
		S ledsuf;
		S defaults[4];
		S trigger;
		S brightness;
};
template <>
class Config <std::string>
{
	public:
		std::string leddir;
		std::string ledpre;
		std::string ledsuf;
		std::string defaults[4];
		std::string trigger;
		std::string brightness;
	public:
		// return copy of Config as c_str's
		Config<const char*> charify();
};

// read configuration from fn or config.txt
Config<std::string> getconfig(const char* = "config.txt");

#endif
