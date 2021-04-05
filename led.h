#ifndef LEDCLASS
#define LEDCLASS
// LED class: controls one led

#include "config.h" // Config
#include <string>   // std::string
#include <fstream>  // std::ifstream      std::ofstream
#include <sstream>  // std::ostringstream

class LED
{
	Config* cfg;
	int index;
	// default trigger for this LED
	std::string def;
	// original trigger from initialization
	std::string orig;
	// filename for trigger
	std::string triggerfn;
	// filename for brightness
	std::string bnfn;

	public:
		LED(int, Config*);
		// gets the full file name for in this LED's directory
		// if arg 2 is given, it will return that instead of generating the name
		template<typename T>
		std::string get_fname(T, std::string = "");
		// gets the filename with get_fname and then opens it with its openfs variant
		template<typename T>
		std::ifstream getopen_ifname(T, std::string = "");
		// for std::ofstream
		template<typename T>
		std::ofstream getopen_ofname(T, std::string = "");

		// gets active trigger
		std::string get_trigger();
		// sets the trigger to a new state
		template<typename T>
		void set_trigger(T);
		// resets the trigger to its default state as defined in its cfg
		void reset();
		// restores the trigger to its original state (from when this was instantiated)
		void restore();
		
		// gets the current brightness value
		int get_bn();
		// sets the brightness value
		void set_bn(int);
};

template<typename T>
std::string LED::get_fname(T fn, std::string over)
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
std::ifstream LED::getopen_ifname(T fn, std::string over)
{ return openifs(get_fname(fn, over)); }
template<typename T>
std::ofstream LED::getopen_ofname(T fn, std::string over)
{ return openofs(get_fname(fn, over)); }

template<typename T>
void LED::set_trigger(T newmode)
{
	std::ofstream f = openofs(triggerfn);
	f << newmode;
	f.close();
}

#endif
