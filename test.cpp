#include "config.h"
#include "led.h"
#include <iostream>
#include <string>

void showt(LED led, std::string fn = "") { std::cout << led.get_trigger(fn) << std::endl; }

int main()
{
	Config cfg = getconfig();
	LED led0(0, &cfg);
	std::string trigger = led0.get_fname("trigger");
	showt(led0, trigger);
	led0.set_trigger("none", trigger); showt(led0, trigger);
	led0.set_trigger("timer", trigger); showt(led0, trigger);
	led0.restore(trigger); showt(led0, trigger);
	led0.reset(trigger); showt(led0, trigger);

	return 0;
}
