/*--------------------------------------------------------------------
Name:   Kevin Zhao
Date:   2022, January 19
File:   joystick_lib.h

Purp: 

Doc:  
--------------------------------------------------------------------*/

/*
 * This function leaves the ADC functionality on the whole time. Is that "Free Running"?
 */
void adcInit(void) {
  PRR &= ~(1 << PRADC); // Writing '0' to Power Reduction ADC bit in Power Reduction Register to...?
  ADMUX = (1 << REFS0); // Set ADC reference voltage to external reference and clear all other bits
  ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Enable ADC with 128 prescalar
}

uint16_t readAnalogInput (uint8_t analogPin) {
  uint16_t ADCvalue;
  ADMUX = (ADMUX & 0xF0) | analogPin; // Clears bottom 4 bits and sets mux for appropriate input pin
  ADCSRA |= (1 << ADSC); // Writing '1' to ADC Start Conversion bit in ADC Control and Status Register A
  while(ADCSRA & (1 << ADSC)); // While no ADSC == 1 (i.e ADC conversion no complete)
  ADCvalue = ADC; // Read ADC value and return
  return ADCvalue;
}