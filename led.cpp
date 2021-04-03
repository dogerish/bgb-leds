#include <iostream>
#include <stdexcept> // throw std::out_of_range
#include <fstream> // get_trigger()[f]

// get_trigger()[std::numeric_limits<std::streamsize>::max()]
#include <limits>
#include <ios>

#include <string> // get_trigger()[return, mode]
#include "config.h" // LED(cfg)
#include "errors.h" // get_trigger()[FileOpenError]
#include "led.h"

LED::LED(int index, Config* cfg)
{
	if (index < 0 || index > 3)
		throw std::out_of_range("LED::index");
	this->index = index;
	this->cfg = cfg;
	// set default and original triggers
	def = &cfg->defaults[index];
	orig = get_trigger();
}

std::string LED::get_trigger()
{
	// holds filename for now
	std::string mode = get_fname(cfg->trigger);
	std::ifstream f(mode);
	if (f.fail()) throw FileOpenError(mode.c_str());
	// ignore up to '['
	f.ignore(std::numeric_limits<std::streamsize>::max(), '[');
	// then read to ']' to get the active mode
	std::getline(f, mode, ']');
	f.close();

	return mode;
}

void LED::reset() { set_trigger(*def); }
void LED::restore() { set_trigger(orig); }
