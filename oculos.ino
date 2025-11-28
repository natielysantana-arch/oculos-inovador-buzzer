const byte PIN_TRIG = 9;
const byte PIN_ECHO = 10;
const byte PIN_BUZZ = 8;

const int DIST_MAX = 200; 
const int DIST_MIN = 10;  

long medir_cm() {
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  unsigned long dur = pulseIn(PIN_ECHO, HIGH, 30000UL); 
  if (dur == 0) return -1; 
  return dur / 58;        
}

void setup() {
  Serial.begin(9600);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_BUZZ, OUTPUT);
}

void loop() {
  long cm = medir_cm();

  if (cm > 0 && cm <= DIST_MAX) {
    if (cm < DIST_MIN) cm = DIST_MIN; 

    int freq = map(cm, DIST_MAX, DIST_MIN, 500, 3000); 
    int pausa = map(cm, DIST_MAX, DIST_MIN, 600, 100);

    tone(PIN_BUZZ, freq, 80);  
    delay(pausa);
  } else {
    noTone(PIN_BUZZ);
    delay(100);
  } 
  Serial.println(cm);
}
