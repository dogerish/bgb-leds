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
#include "files.h"
class LED
{
	Config<const char*>* cfg;
	int index;
	// default trigger for this LED
	const char* def;
	// original trigger from initialization
	const char* orig;

	public:
		LED(int, Config<const char*>*);
		// gets the full file name for in this LED's directory
		// if arg 2 is given, it will return that instead of generating the name
		std::string get_fname(const char*, std::string = "");
		// gets the filename with get_fname and then opens it with its openfs variant
		std::ifstream getopen_ifname(const char*, std::string = "");
		// for std::ofstream
		std::ofstream getopen_ofname(const char*, std::string = "");

		// gets active trigger, optional first argument is the filename to read from
		const char* get_trigger(std::string = "");
		// sets the trigger to a new state, optional second argument is filename
		void set_trigger(const char*, std::string = "");
		// resets the trigger to its default state as defined in its cfg
		void reset(std::string = "");
		// restores the trigger to its original state (from when this was instantiated)
		void restore(std::string = "");
		
		// gets the current brightness value, optional first is filename to read from
		int get_bn(std::string = "");
		// sets the brightness value
		void set_bn(int value, std::string = "");
};

#endif
