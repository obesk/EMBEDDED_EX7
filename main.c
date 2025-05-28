#include "pwm.h"
#include "xc.h"

int main(void) {

	ANSELA = ANSELB = ANSELC = ANSELD = ANSELE = ANSELG = 0;
	pwm_init();

	move(FORWARD);

	pwm_start();

	while (1)
		;

	return 0;
}
