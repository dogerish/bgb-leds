#ifndef LEDCLASS
#define LEDCLASS
// LED class; controls one led

#include <iostream>
#include <signal.h> // raise sigtrap
#include <string> // def, orig, get_fname()[return] set_trigger()[fn]
#include "config.h" // cfg, LED()
#include <fstream> // set_trigger()[f]
#include <sstream> // get_fname()[ret]
#include "errors.h" // set_trigger()[FileOpenError]
class LED
{
	Config* cfg;
	int index;
	// default trigger for this LED
	std::string* def;
	// original trigger from initialization
	std::string orig;

	public:
		LED(int, Config*);
		// gets the full file name for in this LED's directory
		// if `over` is given, it will return that instead of generating the name
		template<typename T>
		std::string get_fname(const T, std::string over = "");
		// gets active trigger, optional first argument is the filename to read from
		std::string get_trigger(std::string = "");
		// sets the trigger to a new state, optional second argument is filename
		template<typename T>
		void set_trigger(T, std::string = "");
		// resets the trigger to its default state as defined in its cfg
		void reset(std::string = "");
		// restores the trigger to its original state (from when this was instantiated)
		void restore(std::string = "");
};

// define template functions

template<typename T>
std::string LED::get_fname(const T fn, std::string over)
{
	if (over.length()) return over;
	std::ostringstream ret;
	ret
	<< cfg->leddir << '/'
	<< cfg->ledpre << index << cfg->ledsuf << '/'
	<< fn;
	return ret.str();
}


template<typename T>
void LED::set_trigger(T newmode, std::string fn)
{
	fn = get_fname(cfg->trigger, fn);
	std::ofstream f(fn);
	if (f.fail()) throw FileOpenError(fn.c_str());
	f << newmode;
	f.close();
}

#endif
