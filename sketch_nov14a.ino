int DigitPins[4] = { 10, 11, 12, 13 };

// A B C D E F G

int digits[10][7] = {
  { 1, 1, 1, 1, 1, 1, 0 },  // 0
  { 0, 1, 1, 0, 0, 0, 0 },  // 1
  { 1, 1, 0, 1, 1, 0, 1 },  // 2
  { 1, 1, 1, 1, 0, 0, 1 },  // 3
  { 0, 1, 1, 0, 0, 1, 1 },  // 4
  { 1, 0, 1, 1, 0, 1, 1 },  // 5
  { 1, 0, 1, 1, 1, 1, 1 },  // 6
  { 1, 1, 1, 0, 0, 0, 0 },  // 7
  { 1, 1, 1, 1, 1, 1, 1 },  // 8
  { 1, 1, 1, 1, 0, 1, 1 },  // 9
};

int SegmentPins[7] = { 2, 3, 4, 5, 6, 7, 9 };
int DecimalPin = 8;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 7; i++) {
    pinMode(SegmentPins[i], OUTPUT);
  }

  for (int i = 0; i < 4; i++) {
    pinMode(DigitPins[i], OUTPUT);
  }
  pinMode(DecimalPin, OUTPUT);
  digitalWrite(DecimalPin, LOW);
}

void Display(int Index, int Number, bool showdecimal) {
  for (int i = 0; i < 4; i++) {
    digitalWrite(DigitPins[i], HIGH);
  }

  for (int i = 0; i < 7; i++) {
    digitalWrite(SegmentPins[i], digits[Number][i]);
  }

  digitalWrite(DigitPins[Index], LOW);
  digitalWrite(DecimalPin, LOW);

  if (showdecimal) {
    digitalWrite(DecimalPin, HIGH);
  }

  delay(5);
}

String InputNum = " ";

void loop() {
  if (Serial.available()) {
    InputNum = Serial.readString();
  }
  int DigitIndex = 0;

  String Vol = String(analogRead(A0) * (5.0/1023.0), 2);
  Serial.println(Vol);
  InputNum = Vol;

  if (InputNum != " ") {
    for (int i = 0; i < InputNum.length(); i++) {
      int DecimalIndex = InputNum.indexOf('.');

      if (i + 1 == DecimalIndex) {
        Display(DigitIndex, InputNum.charAt(i) - '0', true);
        DigitIndex += 1;
      }
      else if (i != DecimalIndex) {
        Display(DigitIndex, InputNum.charAt(i) - '0', false);
        DigitIndex += 1;
      }
    }
  }
}