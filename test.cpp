#include "src/config.h" // Config    getconfig
#include "src/led.h"    // LED
#include <iostream>     // std::cout std::endl
#include <unistd.h>     // usleep
#define SHOW() std::cout << led0.vget("delay_off") << ' ' << led0.vget("", don) << std::endl;

int main()
{
	Config cfg = getconfig();
	LED led0(0, &cfg);
	led0.set_trigger("timer");
	// needed for the files to be created in time
	usleep(1e5);

	std::string don = led0.get_fname("delay_on");
	std::string doff = led0.get_fname("delay_off");
	SHOW();
	led0.vset("", 100, doff);
	led0.vset("delay_on", 1000);
	SHOW();

	usleep(5e6);
	led0.reset();

	return 0;
}
