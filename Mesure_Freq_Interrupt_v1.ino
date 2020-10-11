class Frequence{
public:
  int64_t tStart, tEnd; // en us
  double frequence; 
  bool mesureFinie; //true si la mesure est finie, false sinon
  Frequence(){
    mesureFinie = false;
    tStart = esp_timer_get_time();
  }
};

const int signal_carre = 33; // a changer
Frequence freqEolienne;


void IRAM_ATTR isr_freq_falling() {
  if(freqEolienne.mesureFinie) {
    freqEolienne.tStart = esp_timer_get_time();
    //Serial.println(freqEolienne.tStart);
  }
  else {
    freqEolienne.tEnd = esp_timer_get_time();
    freqEolienne.frequence = 1.0/(freqEolienne.tEnd - freqEolienne.tStart)*1e6;
    //Serial.println(freqEolienne.frequence);
  }
  freqEolienne.mesureFinie = !freqEolienne.mesureFinie;
  //Serial.println(freqEolienne.tHighEnd);
}

void setup() {
  Serial.begin(115200);
  pinMode(signal_carre, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(signal_carre), isr_freq_falling, FALLING);
}

void loop() {
  Serial.println(freqEolienne.frequence);
  delay(1000);
}
