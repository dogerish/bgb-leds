#include <iostream>
#include <fstream>
#include "config.h"
#include "errors.h"

Config getconfig(const char* fn)
{
	Config cfg;
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
