#include "config.h"
#include "led.h"
#include <iostream>

void showt(LED led) { std::cout << led.get_trigger() << std::endl; }

int main()
{
	Config cfg = getconfig();
	LED led0(0, &cfg);
	led0.set_trigger("none"); showt(led0);
	led0.set_trigger("timer"); showt(led0);
	led0.restore(); showt(led0);
	led0.reset(); showt(led0);

	return 0;
}
