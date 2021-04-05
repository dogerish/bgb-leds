#include <iostream>
#include <stdexcept> // throw std::out_of_range
#include <fstream> // get_trigger()[f]

// get_trigger()[std::numeric_limits<std::streamsize>::max()]
#include <limits>
#include <ios>

#include <string> // get_trigger()[return, mode], get_bn(fn)[std::stoi]
#include "config.h" // LED(cfg)
#include "errors.h" // get_trigger()[FileOpenError]
#include "led.h"

LED::LED(int index, Config<const char*>* cfg)
{
	if (index < 0 || index > 3)
		throw std::out_of_range("LED::index");
	this->index = index;
	this->cfg = cfg;
	// set default and original triggers
	def = cfg->defaults[index];
	orig = get_trigger();
}

std::string LED::get_fname(const char* fn, std::string over)
{
	if (over.length()) return over.c_str();
	std::ostringstream ret;
	ret
	<< cfg->leddir << '/'
	<< cfg->ledpre << index << cfg->ledsuf << '/'
	<< fn;
	return ret.str();
}

std::ifstream LED::getopen_ifname(const char* fn, std::string over)
{ return openifs(get_fname(fn, over).c_str()); }
std::ofstream LED::getopen_ofname(const char* fn, std::string over)
{ return openofs(get_fname(fn, over).c_str()); }


const char* LED::get_trigger(std::string fn)
{
	std::ifstream f = getopen_ifname(cfg->trigger, fn);
	std::string mode;
	// ignore up to '['
	f.ignore(std::numeric_limits<std::streamsize>::max(), '[');
	// then read to ']' to get the active mode
	std::getline(f, mode, ']');
	f.close();

	return mode.c_str();
}
void LED::set_trigger(const char* newmode, std::string fn)
{
	std::ofstream f = getopen_ofname(cfg->trigger, fn);
	f << newmode;
	f.close();
}

void LED::reset(std::string fn) { set_trigger(def, fn); }
void LED::restore(std::string fn) { set_trigger(orig, fn); }

int LED::get_bn(std::string fn)
{
	std::ifstream f = getopen_ifname(cfg->brightness, fn);
	std::string br;
	f >> br;
	f.close();
	return std::stoi(br);
}

void LED::set_bn(int value, std::string fn)
{
	std::ofstream f = getopen_ofname(cfg->brightness, fn);
	f << value;
	f.close();
}
