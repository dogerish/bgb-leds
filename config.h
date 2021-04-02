#ifndef CONFIG_STRUCT
#define CONFIG_STRUCT

#include <string>
// hold configuration info
struct Config
{
	std::string leddir;
	std::string ledpre;
	std::string ledsuf;
	std::string defaults[4];
	std::string trigger;
	std::string brightness;
};

// read configuration from fn or config.txt
Config getconfig(const char* = "config.txt");

#endif
