#include <iostream>
#include <fstream> // get_trigger()[f]

// get_trigger()[std::numeric_limits<std::streamsize>::max()]
#include <limits>
#include <ios>

#include <string> // get_trigger()[return, mode]
#include "config.h" // LED(cfg)
#include "led.h"

LED::LED(int index, Config* cfg)
{
	if (index < 0 || index > 3)
	{
		std::cerr << "Failed to create LED: index out of range" << std::endl;
		throw;
	}
	this->index = index;
	this->cfg = cfg;
	// set default and original triggers
	def = &cfg->defaults[index];
	orig = get_trigger();
}

std::string LED::get_trigger()
{
	std::string mode;
	std::ifstream f;
	f.open(get_fname(cfg->trigger));
	// ignore up to '['
	f.ignore(std::numeric_limits<std::streamsize>::max(), '[');
	// then read to ']' to get the active mode
	std::getline(f, mode, ']');
	f.close();

	return mode;
}
