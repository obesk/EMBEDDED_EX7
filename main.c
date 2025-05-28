#include "pwm.h"
#include "timer.h"
#include "xc.h"

void button_init(void) {
	RPINR0bits.INT1R = 0x58; // remapping the interrupt 1 to the T2 button pin
	IFS1bits.INT1IF = 0;	 // resetting flag of interrupt 1
	IEC1bits.INT1IE = 1;	 // enabling interrupt 1
}

void timers_init() {
	IEC0bits.T2IE = 1; // enabling the timer 3interrupt

	IFS0bits.T2IF = 0;
}

int move_forward = 0;

int main(void) {
	INTCON2bits.GIE = 1;

	TRISA = TRISG = ANSELA = ANSELB = ANSELC = ANSELD = ANSELE = ANSELG =
		0x0000;

	pwm_init();
	button_init();
	timers_init();

	move(FORWARD);

	while (1)
		;

	return 0;
}

void __attribute__((__interrupt__, __auto_psv__)) _INT1Interrupt(void) {
	IFS1bits.INT1IF = 0;
	tmr_setup_period(TIMER2, 10);
}

void __attribute__((__interrupt__, no_auto_psv)) _T2Interrupt(void) {
	IFS0bits.T2IF = 0;
	T2CONbits.TON = 0;

	if (move_forward) {
		pwm_start();
	} else {
		pwm_stop();
	}
	move_forward = !move_forward;
}
