#include "config.h"
#include "led.h"
#include <iostream>
#include <string>
#include <unistd.h>

void showt(LED led, std::string fn = "") { std::cout << led.get_trigger(fn) << std::endl; }

int main()
{
	Config<std::string> tmp = getconfig();
	Config<const char*> cfg = tmp.charify();
	LED led0(0, &cfg);
	led0.set_trigger("none");
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
