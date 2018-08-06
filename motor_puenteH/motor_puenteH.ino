//Etiquetas para los motores
#define IN1 9  //pwm
#define IN2 8

//etiqueta para cada micro-switch
#define sw0 3
#define sw1 4
#define sw2 5

//valor de cada Micro-Switch
int v0 = digitalRead(sw0);
int v1 = digitalRead(sw1);
int v2 = digitalRead(sw2);

//flags para saber la pocicion del riel
int state;

//Potencia para los motores de 0 a 255
int speed = 150;

void setup()
{
  Serial.begin(9600);
  pinMode (IN1, OUTPUT);    // Input4 conectada al pin 9 pwm
  pinMode (IN2, OUTPUT);    // Input3 conectada al pin 8

  pinMode(sw0, INPUT);
  pinMode(sw1, INPUT);
  pinMode(sw2, INPUT);
}

//Maxima potencia (5v) para los motores hacia adelante
void adelante() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

//Maxima potencia (5v) para los motores hacia atras
void atras() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}

//parar los motores
void parar() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

//Potencia graduada para que los motores giren hacia adelante
void adelanteAnalogo(int speed) {
  analogWrite(IN1, speed);
  digitalWrite(IN2, LOW);
}

//Potencia graduada para que los motores giren hacia adelante
void atrasAnalogo(int speed) {
  analogWrite(IN1, speed);
  digitalWrite(IN2, LOW);
}

void p0() {
  v0 = digitalRead(sw0);
  while (v0 != 1) {
    atras();
    v0 = digitalRead(sw0);
  }
  parar();
  state=0;
  //Serial.println(state);
}

void p1() {
  v1 = digitalRead(sw1);
  while (v1 != 1) {
    adelanteAnalogo(200);
    v1 = digitalRead(sw1);
  }
  parar();
  state=1;
  Serial.println(state);
}

void p2() {
  v2 = digitalRead(sw2);
  while (v2 != 1) {
    adelante();
    v2 = digitalRead(sw2);
  }
  parar();
  state=2;
  Serial.println(state);
}

void loop()
{
  v0 = digitalRead(sw0);
  v1 = digitalRead(sw1);
  v2 = digitalRead(sw2);
  /*
    Serial.print(v0);
    Serial.print(v1);
    Serial.println(v2);
  */

  //Serial ins

  while (Serial.available() > 0) {
    String ins = Serial.readStringUntil("\n");

    if (ins == "RPL1P0") {
      //ir a la pocision 0
      p0();

      //reemplazar por el metodo para mover el dynamixel
      Serial.println("Moviendo dynamixel planta 1");
      delay(3000);
      break;
    }
    else if (ins == "RPL1P1") {
      p0();
      Serial.println("Moviendo dynamixel planta 1");
      delay(3000);
      p2();
      delay(2000);
      break;
    }
    else if (ins == "RPL1P2") {
      p0();
      Serial.println("Moviendo dynamixel planta 2");
      delay(3000);
      p1();
      delay(2000);
      break;
    }
    else if (ins == "RPL1P3") {
      p0();
      Serial.println("Moviendo dynamixel planta 3");
      delay(3000);
      p2();
      delay(2000);
      break;
    }

    else if (ins == "RPL1P4") {
      p0();
      Serial.println("Moviendo dynamixel planta 4");
      delay(3000);
      p1();
      delay(2000);
      break;
    }

    else {
      Serial.println("comando no valido");
      break;
    }
  }
}



