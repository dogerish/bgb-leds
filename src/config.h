#ifndef CONFIG_STRUCT
#define CONFIG_STRUCT
// get and hold config data

#include <string>  // std::string   std::getline
#include <fstream> // std::ifstream
#include "files.h" // openifs

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
template<typename T = const char*>
Config getconfig(T fn = "config.txt")
{
	Config cfg;
	std::ifstream cfgfile = openifs(fn);

	std::getline(cfgfile, cfg.leddir);
	std::getline(cfgfile, cfg.ledpre);
	std::getline(cfgfile, cfg.ledsuf);

	// split by spaces
	for (int i = 0; i < 4; i++)
		std::getline(cfgfile, cfg.defaults[i], (i == 3) ? '\n' : ' ');

	std::getline(cfgfile, cfg.trigger);
	std::getline(cfgfile, cfg.brightness);

	return cfg;
}

#endif
