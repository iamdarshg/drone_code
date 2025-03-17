


#include "config.h"
#include "inc/pwm.h"
#include "inc/start_stuff.h"
#include "hdr/hdr_cgu.h"

#include "LPC43xx.h"


static void fpu_enable(void);
static uint32_t pll_start(const uint32_t crystal, const uint32_t frequency);



int main(void){
	volatile uint32_t count, count_max = 10000000;

	fpu_enable();
	pll_start(CRYSTAL, FREQUENCY);

	LPC_GPIO_PORT->DIR[LED_GPIO] |= LED;	// configure GPIO pin as output

	while (1)
	{
		for (count = 0; count < count_max; count++);	// delay
		LED_bb = 1;
		for (count = 0; count < count_max; count++);	// delay
		LED_bb = 0;
	}

	return 0;
}