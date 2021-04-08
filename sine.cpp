// makes the LEDs follow a sine wave
#include <csignal>      // signal
#include "src/config.h" // Config
#include "src/led.h"    // LED
#include <cmath>        // sin
#include <unistd.h>     // usleep

bool done = false;

// stop on signals
void sig_handler(int signum) { done = true; }

int main()
{
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
		leds[i]->set_trigger("none");
	}

	for (float t = 0; !done; t += M_PI/6)
	{
		leds[on]->set_bn(0);
		on = round((sin(t / 100) + 1) * 1.5);
		leds[on]->set_bn(1);
		usleep(1e2);
	}

	for (int i = 0; i < 4; i++)
	{
		leds[i]->reset();
		delete leds[i];
	}

	return 0;
}
