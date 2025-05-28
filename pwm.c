#include "xc.h"
#include "pwm.h"

// TODO: change this and check if fcy is correct
#define FCY 72000000UL
#define PWM_FREQ 10000UL
#define PWM_PERIOD_TICKS (FCY/PWM_FREQ)

void pwm_init(void) {
	// No sync or trigger source for input caputure
	OC1CON2bits.SYNCSEL = 0x1F;
	OC2CON2bits.SYNCSEL = 0x1F;
	OC3CON2bits.SYNCSEL = 0x1F;
	OC4CON2bits.SYNCSEL = 0x1F;

	// Setting peripheral clock 1/2 of FOSC
	OC1CON1bits.OCTSEL = 7;
	OC2CON1bits.OCTSEL = 7;
	OC3CON1bits.OCTSEL = 7;
	OC4CON1bits.OCTSEL = 7;


	// Setting the period of the PWM
	OC1RS = PWM_PERIOD_TICKS;
	OC2RS = PWM_PERIOD_TICKS; 
	OC3RS = PWM_PERIOD_TICKS; 
	OC4RS = PWM_PERIOD_TICKS; 

	// remapping pins for output compare
    RPOR0bits.RP65R = 0b010000;
    RPOR1bits.RP66R = 0b010001;
    RPOR1bits.RP67R = 0b010010;
    RPOR2bits.RP68R = 0b010011;

	// setting the PWM pins as output
    TRISDbits.TRISD1 = 0;
    TRISDbits.TRISD2 = 0;
    TRISDbits.TRISD3 = 0;
    TRISDbits.TRISD4 = 0;
}

void move(enum Direction direction) {
	switch (direction) {
		case FORWARD:
			OC1R = 0;
			OC2R = comp_duty(50);
			OC3R = 0;
			OC4R = comp_duty(50);
			break;

		case RIGHT:
			OC1R = 0;
			OC2R = comp_duty(100);
			OC3R = 0;
			OC4R = comp_duty(50);
			break;

		case STOP:
			OC1R = 0;
			OC2R = 0;
			OC3R = 0;
			OC4R = 0;
			break;
		default:
			break;
	}

	return;
}

void pwm_start(void) {
	// edge-aligned pwm mode
    OC1CON1bits.OCM = 0b110;
    OC2CON1bits.OCM = 0b110;
    OC3CON1bits.OCM = 0b110;
    OC4CON1bits.OCM = 0b110;
}

void pwm_stop(void) {
    OC1CON1bits.OCM = 0;
    OC2CON1bits.OCM = 0;
    OC3CON1bits.OCM = 0;
    OC4CON1bits.OCM = 0;
}

int comp_duty(int percentage) {  
    return (PWM_PERIOD_TICKS * percentage) / 100;
}

