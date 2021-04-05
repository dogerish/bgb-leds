#include <iostream>
#include <fstream>
#include "config.h"
#include "errors.h"

Config<const char*> Config<std::string>::charify()
{
	Config<const char*> cfg;
	cfg.leddir	= leddir.c_str();
	cfg.ledpre	= ledpre.c_str();
	cfg.ledsuf	= ledsuf.c_str();
	cfg.trigger	= trigger.c_str();
	cfg.brightness	= brightness.c_str();

	// do it for each default
	for (int i = 0; i < 4; i++)
		cfg.defaults[i] = defaults[i].c_str();

	return cfg;
}

Config<std::string> getconfig(const char* fn)
{
	Config<std::string> cfg;
	std::ifstream cfgfile(fn);
	if (cfgfile.fail()) throw FileOpenError(fn);

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
