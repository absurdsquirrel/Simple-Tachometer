volatile bool slow = true;
volatile unsigned long _ticks;
unsigned long ticks, previous;
float rps, rpm;

void setup() {
  Serial.begin(115200);
  previous = 0;
  timer = 0;
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  TIMSK1 |= (1 << TOIE1) | (1 << ICIE1);
  TCCR1B |= (1 << ICNC1) | (0 << ICES1) | (1 << CS12);
  interrupts();
}

ISR(TIMER1_OVF_vect){
  slow = true;
  previous = 0;
}

ISR(TIMER1_CAPT_vect){
  _ticks = TCNT1;
  TCNT1 = 0;
  slow = false;
}

void loop() {
  delay(1000);
  ticks = _ticks;
  if(slow || ticks < 400 || ticks > 10000 || ticks < previous){
    //erroneous readings, ignore
    return;
  } else {
    previous = ticks;
    rps = 62500.00 / ticks;
    rpm = 60 * rps;
    Serial.print(millis()/1000.00);
    Serial.print(" ");
    Serial.println(rps);
  }
}
