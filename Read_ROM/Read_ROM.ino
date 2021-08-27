//#define TO_MONITOR

int ADDRESS[] = {22, 23, 24, 25, 26, 27, 28, 29,
                 30, 31, 32, 33, 34, 35, 36, 37,
                 38, 39, 40
                };

int DATA[] = {41, 42, 43, 44, 45, 46, 47, 48};

int nCE = 49;
int nOE = 50;

void setAddress(unsigned long int address) {
  unsigned long int t = 0;
  for (int i = 0; i < 19; i++) {
    digitalWrite(ADDRESS[i], (address >> i) & 1);
  }
}

byte readData() {
  byte data = 0;
  for (int i = 0; i < 8; i++) {
    data |= digitalRead(DATA[i]) << i;
  }
  return data;
}

void setup() {

  for (int i = 0; i < 19; i++) {
    pinMode(ADDRESS[i], OUTPUT);
  }

  for (int i = 0; i < 8; i++) {
    pinMode(DATA[i], INPUT);
  }

  pinMode(nCE, OUTPUT);
  pinMode(nOE, OUTPUT);

  digitalWrite(nOE, HIGH);
  digitalWrite(nCE, LOW);


  Serial.begin(115200);
  delay(1000);

  digitalWrite(nOE, LOW);
  delay(1);

  for (unsigned long address = 0; address < 0x80000; address++) {
    setAddress(address);

    digitalWrite(nCE, HIGH);
    delayMicroseconds(10);

    byte data = readData();

    delayMicroseconds(10);
    digitalWrite(nCE, LOW);


#ifdef TO_MONITOR
    Serial.print((data >> 4) & 0x0F, HEX);
    Serial.print(data & 0x0F, HEX);

    Serial.print( ' ' );
    if ((address + 1) % 32 == 0) {
      Serial.print( '\n' );
    }
#else
    Serial.write(data);
    delayMicroseconds(100);
#endif
  }
}

void loop() {
}
