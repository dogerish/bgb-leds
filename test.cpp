#include "config.h"
#include "led.h"
#include <iostream>
int main()
{
	Config cfg = getconfig();
	LED led0(0, &cfg);
	std::cout << led0.get_trigger() << std::endl;
	led0.set_trigger("none");
	std::cout << led0.get_trigger() << std::endl;
	led0.set_trigger("timer");
	std::cout << led0.get_trigger() << std::endl;

	return 0;
}
