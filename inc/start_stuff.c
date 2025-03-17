#include "start_stuff.h"


static uint32_t pll_start(const uint32_t crystal, const uint32_t frequency)
{
	volatile uint32_t count;
	uint32_t m, n, real_frequency, best_m = 0, best_n = 0, best_real_frequency = 0;

	// enable crystal oscillator, crystal < 15MHz - low frequency, crystal >= 15MHz - high frequency
	LPC_CGU->XTAL_OSC_CTRL = crystal < 15000000 ? 0 : CGU_XTAL_OSC_CTRL_HF_Pos;
	for (count = 0; count < 20000; count++);	// delay of at least 100us for crystal to start

	for (n = 1; n <= 4; n++)	// predivider - [1; 4]
		for (m = 1; m <= 256; m++)	// feedback divider (multiplier) [1; 256]
		{
			real_frequency = m * crystal / n;

			// valid output must be in [156MHz; 320MHz] range, update results if they are better what was already found
			if (real_frequency >= 156000000 && real_frequency <= 320000000 && real_frequency <= frequency &&
					real_frequency > best_real_frequency)
			{
				best_m = m;
				best_n = n;
				best_real_frequency = real_frequency;
			}
		}

	if (best_m != 0 && best_n != 0 && best_real_frequency != 0)	// valid settings found?
	{
		// enable PLL1 in direct mode, with autoblock, source - crystal
		LPC_CGU->PLL1_CTRL = CGU_PLL1_CTRL_DIRECT_Msk | CGU_PLL1_CTRL_AUTOBLOCK_Msk | CGU_x_CLK_SEL_CRYSTAL |
				((best_n - 1) << CGU_PLL1_CTRL_NSEL_Pos) | ((best_m - 1) << CGU_PLL1_CTRL_MSEL_Pos);
		while (!CGU_PLL1_STAT_LOCK_bb);	// wait for PLL1 lock
		LPC_CGU->BASE_M4_CLK = CGU_BASE_M4_CLK_AUTOBLOCK_Msk | CGU_x_CLK_SEL_PLL1;	// set base clock of M4 core to PLL1
	}

	return best_real_frequency;
}

static void fpu_enable(void)
{
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
	SCB->CPACR |= ((3UL << 10 * 2)|(3UL << 11 * 2));	// set CP10 and CP11 Full Access
#endif
}