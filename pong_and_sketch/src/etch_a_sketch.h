/*--------------------------------------------------------------------
Name:   Kevin Zhao
Date:   2022, January 19
File:   etch_a_sketch.h

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

void etchSketch(void) {

}