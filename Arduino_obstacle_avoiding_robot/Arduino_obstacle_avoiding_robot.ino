
int E1 = 10; // 1번(A) 모터 Enable
int M1 = 12; // 1번(A) 모터 PWM
int E2 = 11; // 2번(B) 모터 Enable
int M2 = 13; // 2번(B) 모터 PWM
int EchoPin = 9;
int TrigPin = 8;
long duration, distance;

int i;

void Obstacle_Check(); //장애물 확인 함수
void Distance_Measurement(); //거리 측정 함수
void Forward(); //전진 함수
void Backward(); //후진 함수
void Right(); // 우회전 함수
void Left(); // 좌회전 함수
void Stop(); // 정지 함수


void setup()
{
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  Serial.begin(9600); // PC 시리얼 통신 속도
  pinMode(TrigPin, OUTPUT); // 초음파 센서 trigPin 출력
  pinMode(EchoPin, INPUT); // 초음파 센서 echoPin 입력
}

void loop(){
  Forward();
  delay(100);
  Obstacle_Check();
}
//장애물 확인, 회피방향 결정

void Obstacle_Check(){
  int val = random(2);
  Distance_Measurement();

  Serial.println(distance);

  while ( distance < 200 ) {
    if ( val==0) {
      Right();
      delay(400);
    }
    else if(val==1) {
      Left();
      delay(400);
    }
    Distance_Measurement();
  }
}  
    
//거리 감지 함수
void Distance_Measurement() {
  digitalWrite(TrigPin, LOW);
  delay(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  duration = pulseIn(EchoPin, HIGH);
  distance = ((float)(340 * duration) / 1000) / 2;
  delay(5);
}

//방향 제어 함수
void Forward() {
  digitalWrite(M1,HIGH);
  digitalWrite(M2,HIGH);
  analogWrite(E1, 255);  
  analogWrite(E2, 255);
  delay(2);
}

void Right() {
  digitalWrite(M1,HIGH);
  digitalWrite(M2, LOW);
  analogWrite(E1, 255);
  analogWrite(E2, 0);
  delay(2);
}

void Left() {
  digitalWrite(M1,LOW);
  digitalWrite(M2, HIGH);
  analogWrite(E1, 0);
  analogWrite(E2, 255);
  delay(2);
}
