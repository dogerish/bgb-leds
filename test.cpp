#include "config.h" // Config    getconfig
#include "led.h"    // LED
#include <iostream> // std::cout std::endl
#include <unistd.h> // usleep

int main()
{
	Config cfg = getconfig();
	LED led0(0, &cfg);
	led0.set_trigger("none");
	std::cout << led0.get_trigger() << std::endl;
	std::cout << led0.get_bn() << std::endl;
	usleep(1e6);
	led0.set_bn(1);
	std::cout << led0.get_bn() << std::endl;
	usleep(1e6);
	led0.set_bn(0);
	std::cout << led0.get_bn() << std::endl;
	usleep(1e6);
	led0.reset();

	return 0;
}
