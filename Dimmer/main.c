#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL  // Adjust if using a different clock frequency
#define PWM_PIN PB3       // Replace with your output pin connected to the dimmable light source

volatile uint8_t dutyCycle = 0;

void pwm_init() {
  // Set Timer/Counter 0 for Fast PWM mode (WGM02:1 = 11)
  TCCR0 |= (1 << WGM00) | (1 << WGM01);
  // Set non-inverting mode (COM01:0 = 10)
  TCCR0 |= (1 << COM01);
  // Set prescaler to 64 (CS02:0 = 011)
  TCCR0 |= (1 << CS01) | (1 << CS00);
  // Set initial duty cycle (0 - 255 for brightness control)
  OCR0 = 0;  // Initial duty cycle is 0
  // Enable Timer/Counter0 overflow interrupt
  TIMSK |= (1 << TOIE0);
}

void adc_init() {
  // Set ADC reference voltage to AVCC
  ADMUX |= (1 << REFS0);
  // Set ADC resolution to 8 bits
  ADMUX |= (1 << ADLAR);
  // Enable ADC and set prescaler to 64 (ADC clock frequency = F_CPU / 64)
  ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1);
}

void adc_start_conversion() {
  // Start ADC conversion on channel 0 (ADC0)
  ADMUX &= 0xF0;  // Clear previous channel selection
  ADCSRA |= (1 << ADSC);
}

ISR(TIMER0_OVF_vect) {
  // Adjust duty cycle based on ADC conversion result
  dutyCycle = ADCH;
  OCR0 = dutyCycle;
}

int main(void) {
  // Set PWM pin as output
  DDRB |= (1 << PWM_PIN);

  pwm_init();
  adc_init();

  sei();  // Enable global interrupts

  while (1) {
    adc_start_conversion();
    _delay_ms(10);  // Delay between ADC conversions
  }

  return 0;
}
