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
		// gets active trigger
		std::string get_trigger();
		// sets the trigger to a new state
		template<typename T>
		void set_trigger(T);
		// resets the trigger to its default state as defined in its cfg
		void reset();
		// restores the trigger to its original state (from when this was instantiated)
		void restore();


	private:
		// gets the full file name for in this LED's directory
		template<typename T>
		std::string get_fname(const T);
};

// define template functions

template<typename T>
std::string LED::get_fname(const T fn)
{
	std::ostringstream ret;
	ret
	<< cfg->leddir << '/'
	<< cfg->ledpre << index << cfg->ledsuf << '/'
	<< fn;
	return ret.str();
}


template<typename T>
void LED::set_trigger(T newmode)
{
	// open file and write new mode to it
	std::string fn = get_fname(cfg->trigger);
	std::ofstream f(fn);
	if (f.fail()) throw FileOpenError(fn.c_str());
	f << newmode;
	f.close();
}

#endif
