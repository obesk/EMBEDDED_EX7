#ifndef PWM_H
#define PWM_H

enum Direction {
	FORWARD,
	LEFT,
	RIGHT,
	BACKWARD,
	STOP
};

void pwm_init(void);
int comp_duty(int percentage);
void pwm_start(void);
void pwm_stop(void);
void move(enum Direction direction);

#endif
