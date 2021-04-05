#include "led.h"
#include "config.h"  // Config
#include <exception> // std::out_of_range
#include <string>    // std::string         std::getline  std::stoi
#include "files.h"   // openifs             openofs
#include <fstream>   // std::ifstream       std::ofstream
#include <limits>    // std::numeric_limits
#include <ios>       // std::streamsize

LED::LED(int index, Config* cfg)
{
	if (index < 0 || index > 3) throw std::out_of_range("LED::index");
	this->index = index;
	this->cfg = cfg;
	triggerfn = get_fname(cfg->trigger);
	bnfn = get_fname(cfg->brightness);
	// set default and original triggers
	def = cfg->defaults[index];
	orig = get_trigger();
}

std::string LED::get_trigger()
{
	std::ifstream f = openifs(triggerfn);
	std::string mode;
	// ignore up to '['
	f.ignore(std::numeric_limits<std::streamsize>::max(), '[');
	// then read to ']' to get the active mode
	std::getline(f, mode, ']');
	f.close();

	return mode;
}

void LED::reset() { set_trigger(def); }
void LED::restore() { set_trigger(orig); }

int LED::get_bn()
{
	std::ifstream f = openifs(bnfn);
	std::string tmp;
	f >> tmp;
	f.close();
	return std::stoi(tmp);
}

void LED::set_bn(int value)
{
	std::ofstream f = openofs(bnfn);
	f << value;
	f.close();
}
