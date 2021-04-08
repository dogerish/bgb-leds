#include <csignal>      // signal
#include "src/config.h" // Config
#include "src/led.h"    // LED
#include <cmath>        // sin
#include <unistd.h>     // usleep
#include <stdlib.h>     // srand     rand
#include <time.h>       // time
#include <iostream>     // std::cout std::endl

bool done = false;

// stop on signals
void sig_handler(int signum) { done = true; }

int main()
{
	srand(time(NULL));
	signal(SIGABRT, sig_handler);
	signal(SIGINT, sig_handler);
	signal(SIGTERM, sig_handler);
	// which one is on
	int on = 0;
	Config cfg = getconfig();
	LED* leds[4];

	// initialize LEDs
	for (int i = 0; i < 4; i++)
	{
		leds[i] = new LED(i, &cfg);
		leds[i]->set_trigger("timer");
	}
	usleep(1e6);
	for (int i = 0; i < 4; i++)
	{
		leds[i]->vset("delay_on", rand() % 500 + 500);
		leds[i]->vset("delay_off", rand() % 500 + 500);
		std::cout << leds[i]->vget("delay_on") << ' ' << leds[i]->vget("delay_off") << std::endl;
	}

	while (!done) usleep(1e2);

	for (int i = 0; i < 4; i++)
	{
		leds[i]->reset();
		delete leds[i];
	}

	return 0;
}
