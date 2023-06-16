const int buzzerPin = 9; //Pin Buzzer
const int irPin = 10; //Pin Infra Red
const int trigPin = 11; //Pin Trig Ultrasonik
const int echoPin = 12; //Pin Echo Ultrasonik
const int pompaPin = 13; //Pin Pompa DC

bool tangan = 0;
bool ir = 0;
long duration;
int distance;
int waktuPompa = 1000; //Waktu menyala pompa
int tinggiBotol = 20; //Tinggi botol

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(irPin, INPUT);
  pinMode(pompaPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  
  ir = digitalRead(irPin);

  if (distance < tinggiBotol){
    Serial.println("Tinggi Cairan : "+String(tinggiBotol-distance));
    digitalWrite(buzzerPin, LOW);
    if (ir == 0 && tangan == 0){
      tangan = 1;
      digitalWrite(pompaPin, HIGH);
      Serial.println("Pompa Menyala");
      delay(500);
    } else if (ir == 0 && tangan == 1){
      //tangan = 0;
      digitalWrite(pompaPin, LOW);
      Serial.println("Pompa Mati");
    } else if (ir == 1){
      digitalWrite(pompaPin, LOW);
      Serial.println("Pompa Mati");
      tangan = 0;
    }
  } else {
    Serial.println("Cairan Hand Sanitizer Habis");
    digitalWrite(buzzerPin, HIGH);
  }
  delay(500);
}
