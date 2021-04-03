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

std::string LED::get_trigger(std::string fn)
{
	fn = get_fname(cfg->trigger, fn);
	std::string mode;
	std::ifstream f(fn);
	if (f.fail()) throw FileOpenError(fn.c_str());
	// ignore up to '['
	f.ignore(std::numeric_limits<std::streamsize>::max(), '[');
	// then read to ']' to get the active mode
	std::getline(f, mode, ']');
	f.close();

	return mode;
}

void LED::reset(std::string fn) { set_trigger(*def, fn); }
void LED::restore(std::string fn) { set_trigger(orig, fn); }
