#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

#define NUMERAL_DDR 	DDRB							///< DDR for controlling individual segments.
#define CONTROL_DDR 	DDRD							///< DDR for controlling individual digits.
#define NUMERAL_PORT 	PORTB							///< Port for controlling individual segments.
#define CONTROL_PORT 	PORTD							///< Port for controlling individual digits.
#define DIGIT1_PIN		PD0								///< Pin controlling first digit of SSD.
#define DIGIT2_PIN		PD1								///< Pin controlling second digit of SSD.
#define DIGIT3_PIN		PD2								///< Pin controlling third digit of SSD.
#define DIGIT4_PIN		PD3								///< Pin controlling fourth digit of SSD.

void PORT_INIT(void);
void DECODE_SSD(uint16_t value);
void DISPLAY_SSD(uint8_t decimalPoint);

uint8_t dig[4];											///< Array to hold individual digits of the value to be displayed.

int main(void){
	PORT_INIT();
	float value = 185.2;								///< Value to be displayed.
	
	uint16_t displayValue = 0;							///< Variable to hold the display value converted to an integer.
	uint8_t decimalPoint = 0;
	
	if(0.001<value && value<0.01){
		decimalPoint = 1;
		displayValue = value*1000;
	}
	else if(0.01<value && value<0.1){
		decimalPoint = 1;
		displayValue = value*1000;
	}
	else if(0.1<value && value<1){
		decimalPoint = 1;
		displayValue = value*1000;
	}
	else if(1<value && value<10){
		decimalPoint = 1;
		displayValue = value*1000;
	}
	else if(10<value && value<100){
		decimalPoint = 2;
		displayValue = value*100;
	}
	else if(100<value && value<1000){
		decimalPoint = 3;
		displayValue = value*10;
	}
	else if(value>1000){
		decimalPoint = 4;
	}
	DECODE_SSD(displayValue);
	
	while(1){
		DISPLAY_SSD(decimalPoint);
	}
}

/*!
 *	@brief Initialize Ports.
 */

void PORT_INIT(void){
	NUMERAL_DDR = 0xFF;
	CONTROL_DDR |= (1<<DIGIT1_PIN)|(1<<DIGIT2_PIN)|(1<<DIGIT3_PIN)|(1<<DIGIT4_PIN);
}

/*!
 *	@brief Decode the value into individual digits.
 *	@param Value to be decoded (uint16_t).
 */

void DECODE_SSD(uint16_t value){
	dig[0] = (value/1000);									///< Save first digit to array.
	dig[1] = (value%1000)/100;								///< Save second digit to array.
	dig[2] = (value%100)/10;								///< Save third digit to array.
	dig[3] = (value%10);									///< Save fourth digit to array.
}

/*!
 *	@brief Display each individual digit on the SSD.
 *	@param Position of decimal point (uint8_t).
 */

void DISPLAY_SSD(uint8_t decimalPoint){
	uint8_t ssd[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};	///< Array to hold values of segments corresponding to each digit.

	if(decimalPoint==1){
		NUMERAL_PORT = ssd[dig[0]] + 0x80;					///< Display first digit with decimal place.
	}
	else{
		NUMERAL_PORT = ssd[dig[0]];						///< Else, display first digit only.
	}
	CONTROL_PORT |= (1<<DIGIT1_PIN);						///< Turn on display of first digit place.
	_delay_ms(1);
	CONTROL_PORT &= ~(1<<DIGIT1_PIN);						///< Turn off display of first digit place.
		
	if(decimalPoint==2){
		NUMERAL_PORT = ssd[dig[1]] + 0x80;					///< Display second digit with decimal place.
	}
	else{
		NUMERAL_PORT = ssd[dig[1]];						///< Else, display second digit only.
	}
	CONTROL_PORT |= (1<<DIGIT2_PIN);						///< Turn on display of second digit place.
	_delay_ms(1);
	CONTROL_PORT &= ~(1<<DIGIT2_PIN);						///< Turn off display of second digit place.
		
	if(decimalPoint==3){
		NUMERAL_PORT = ssd[dig[2]] + 0x80;					///< Display third digit with decimal place.
	}
	else{
		NUMERAL_PORT = ssd[dig[2]];						///< Else, display third digit only.
	}
	CONTROL_PORT |= (1<<DIGIT3_PIN);						///< Turn on display of third digit place.
	_delay_ms(1);
	CONTROL_PORT &= ~(1<<DIGIT3_PIN);						///< Turn off display of third digit place.
		
	if(decimalPoint==4){
		NUMERAL_PORT = ssd[dig[3]] + 0x80;					///< Display fourth digit with decimal place.
	}
	else{
		NUMERAL_PORT = ssd[dig[3]];						///< Else, display fourth digit only.
	}
	CONTROL_PORT |= (1<<DIGIT4_PIN);						///< Turn on display of fourth digit place.
	_delay_ms(1);
	CONTROL_PORT &= ~(1<<DIGIT4_PIN);						///< Turn off display of fourth digit place.
}