
#include "fsl_device_registers.h"
void software_delay(unsigned long delay){while(delay > 0){delay --;}}

volatile int mode = 2; // off by by default
volatile int next_mode = 1; // holds next mode, open by defult

void PORTA_IRQHandler(void) {
NVIC_ClearPendingIRQ(PORTA_IRQn); /* Clear pending interrupts */
GPIOD_PTOR |= 0xFF; /* Toggle */
PORTA_ISFR = (1 << 1); /* Clear ISFR for PORTA, Pin 1*/

//	if (mode == 0){
//		mode = 1; // mode 1 is open
//		GPIOB_PDOR = 0x00;
//	}else if (mode == 1) {
//		GPIOB_PDOR = 0x0F;
//		mode = 0 ; // mode 0 is close
//	}
//	else if( mode == 2 ){
//		mode = 1;
//	}
	mode = next_mode;



}

int duty_25(void){
	FTM3_C6SC = 0x1C; // Output-compare; Set output
	FTM3_C6V = FTM3_CNT + 166; // 250 us
	while(!(FTM3_C6SC & 0x80));
	FTM3_C6SC &= ~(1 << 7);
	FTM3_C6SC = 0x18; // Output-compare; Clear output
	FTM3_C6V = FTM3_CNT + 500; // 750 us
	while(!(FTM3_C6SC & 0x80));
	FTM3_C6SC &= ~(1 << 7);

	return 0;
}

int duty_75(void){
	FTM3_C6SC = 0x1C; // Output-compare; Set output
	FTM3_C6V = FTM3_CNT + 500; // 750 us
	while(!(FTM3_C6SC & 0x80));
	FTM3_C6SC &= ~(1 << 7);
	FTM3_C6SC = 0x18; // Output-compare; Clear output
	FTM3_C6V = FTM3_CNT + 166; // 250 us
	while(!(FTM3_C6SC & 0x80));
	FTM3_C6SC &= ~(1 << 7);

	return 0;
}

int duty_50(void){
	FTM3_C6SC = 0x1C; // Output-compare; Set output
	FTM3_C6V = FTM3_CNT + 333; // 500 us
	while(!(FTM3_C6SC & 0x80));
	FTM3_C6SC &= ~(1 << 7);
	FTM3_C6SC = 0x18; // Output-compare; Clear output
	FTM3_C6V = FTM3_CNT + 333; // 500 us
	while(!(FTM3_C6SC & 0x80));
	FTM3_C6SC &= ~(1 << 7);

	return 0;
}

int duty_0(void){
//	FTM3_C6SC = 0x1C; // Output-compare; Set output
//	FTM3_C6V = FTM3_CNT + 0; // 0 us
//	while(!(FTM3_C6SC & 0x80));
	FTM3_C6SC &= ~(1 << 7);
	FTM3_C6SC = 0x18; // Output-compare; Clear output
	FTM3_C6V = FTM3_CNT + 0; // 1000 us
	while(!(FTM3_C6SC & 0x80));
	FTM3_C6SC &= ~(1 << 7);

	return 0;
}

int duty_100(void){
	FTM3_C6SC = 0x1C; // Output-compare; Set output
	FTM3_C6V = FTM3_CNT + 666; // 1000 us
	while(!(FTM3_C6SC & 0x80));
	FTM3_C6SC &= ~(1 << 7);
	FTM3_C6SC = 0x18; // Output-compare; Clear output
	FTM3_C6V = FTM3_CNT + 0; // 0 us
	while(!(FTM3_C6SC & 0x80));
	FTM3_C6SC &= ~(1 << 7);

	return 0;
}

int percentage(int ticks, int thresh){
	float temp_f = (float)ticks/(float)thresh;
	int pwm_select = temp_f * 100;

	return pwm_select;
}

int buzzer_pwm(int percentage){

		if(percentage <= 25){
			duty_25();
		}
		else if ( (percentage >= 25) & (percentage <= 50)){
			duty_50();
		}
		else if ( (percentage >= 50) & (percentage <= 75)){
			duty_75();
		}
		else if ( percentage > 75){
			duty_100();
		}

	return 0;
}

int main(void)
{
	SIM_SCGC5 |= ( SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTB_MASK);

	// pwm of buzzer

	PORTC_PCR10 = 0x300; // Port C Pin 10 as FTM3_CH6 (ALT3)

	SIM_SCGC3 |= SIM_SCGC3_FTM3_MASK; // FTM3 clock enable
	PORTC_PCR10 = 0x300; // Port C Pin 10 as FTM3_CH6 (ALT3)
	FTM3_MODE = 0x5; // Enable FTM3
	FTM3_MOD = 0xFFFF;
	FTM3_SC = 0x0D; // System clock / 32

	// pins for motor driver

    PORTD_GPCLR = 0x00FF0100; /* Configures Pins 0-7 on Port D to be GPIO */
    GPIOD_PDDR= 0x000000FF; // Output mode

    PORTC_GPCLR = 0x00C0100; /* Configures Pins 2/3 on Port C to be GPIO */
    GPIOC_PDDR= 0x00000000; // input mode

    // port b pins where used as switches for testing ccw/cw timeing

    PORTB_GPCLR = 0x000C0100; /* Configures Pins 2 and 3 on Port B to be GPIO */
    GPIOB_PDDR = 0x000000FF; /* Configures Pins 2 and 3 of port B as output */

    // used for mic interrupt

    PORTA_PCR1 = 0xA0100; ; // Configure PORTA[1] for GPIO
    GPIOA_PDDR |= (0 << 1); /* PORTA[1] input mode */
    PORTA_ISFR = (1 << 1); /* Clear ISFR for PORTA, Pin 1*/
    NVIC_EnableIRQ(PORTA_IRQn); /* Enable interrupts from PORTA */


    // used to store switch val
    uint32_t temp = 0;

    temp = 0;

    unsigned long i ;

    unsigned long time_close = 0; // used to count ticks and figure out time for software delay
    unsigned long time_open  = 0; // used to count ticks and figure out time for software delay

    int close_thresh = 990; // 1100
    int open = 0;
    int close = 0;
    int open_thresh = 980; // 980
    int var = 0; // holds percentage
    unsigned long delay = 10000;


while(1){

    //	temp = GPIOC_PDIR; // this was used to test manually using pins 2/3 on port b as switch

	//	indicator light

	if ( mode == 2) {GPIOB_PDOR = 0x00;}
	else {GPIOB_PDOR = 0x0F;}

	// motor control

	if(mode == 2){
		duty_0();
	}
	else if ((mode == 0) & ( close != close_thresh) ){ // close fast
		var = percentage(close, close_thresh);
		buzzer_pwm(var);

	 	GPIOD_PDOR = 0x3A;
	 	delay = 30000;
	 	software_delay(delay);

		GPIOD_PDOR = 0x39;
	 	delay = 30000;
	 	software_delay(delay);

		GPIOD_PDOR = 0x35;
	 	delay = 30000;
	 	software_delay(delay);

		GPIOD_PDOR = 0x36;
	 	delay = 30000;
	 	software_delay(delay);

		close += 1;
	}
	else if ((mode == 0) & (close >= close_thresh)){
		close = 0;
		next_mode = 1; // next mode is open
		mode = 2;
	}

	else if ((mode == 1) & ( open != open_thresh)){ // open fast
		var = percentage(open, open_thresh);
		buzzer_pwm(var);

		GPIOD_PDOR = 0x36;
		delay = 30000;
		software_delay(delay);

		GPIOD_PDOR = 0x35;
		delay = 30000;
		software_delay(delay);

		GPIOD_PDOR = 0x39;
		delay = 30000;
		software_delay(delay);

		GPIOD_PDOR = 0x3A;
		delay = 30000;
		software_delay(delay);


		open += 1;
	} else if ((mode == 1) & (open >= open_thresh)){
		open = 0;
		next_mode = 0; // next mode is close
		mode = 2;
	}



}

    /* Never leave main */
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
