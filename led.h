#ifndef LEDCLASS
#define LEDCLASS
// LED class; controls one led

#include <string> // def, orig, get_trigger()[return], get_fname()[return]
#include "config.h" // cfg, LED()
#include <fstream> // set_trigger()[f]
#include <sstream> // get_fname()[ret]
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
	std::ofstream f;
	f.open(get_fname(cfg->trigger));
	f << newmode;
	f.close();
}

#endif
