volatile bool slow = true;
volatile unsigned long _ticks;
unsigned long ticks, previous;
float rps, rpm;

void setup() {
  Serial.begin(115200);
  previous = 0;
  timer = 0;
  //configure timer interrupts
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  //enable timer interrupts on overflow and input capture pin (D8 on the Nano)
  TIMSK1 |= (1 << TOIE1) | (1 << ICIE1);
  // enable input capture noise canceller (because square waves are noisy) and set edge-select to falling, CS12 for 256 prescaler
  TCCR1B |= (1 << ICNC1) | (0 << ICES1) | (1 << CS12);
  interrupts();
}

ISR(TIMER1_OVF_vect){
  //timer overflowed, reset conditions for measurement
  slow = true;
  previous = 0;
}

ISR(TIMER1_CAPT_vect){
  //input captured
  _ticks = TCNT1;
  TCNT1 = 0;
  slow = false;
}

void loop() {
  //record latest measurement every ~1 second
  delay(1000);
  //get the tick count out of volatile memory so it doesn't change while we're updating the readout
  ticks = _ticks;
  //ignore the readings in these cases:
  //slow -- the timer overflowed while waiting for sensor input; the rpm is too slow to read
  //ticks < 400 -- reading is unrealistically fast for my use-case
  //ticks > 10000 -- readings below this threshold are unreliable
  //ticks < previous -- my use-case expects the target to be slowing down
  if(slow || ticks < 400 || ticks > 10000 || ticks < previous){
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
