const int rMax = sqrt(2 * pow(512, 2));
const int deadzone = 0.25 * rMax;
const int rScaledMax = rMax / (rMax - deadzone);

int x = 1024;
int y = 1024;

static int jsAxis(int val) {
  if (val > 512) {
    return val - 511;
  } else if (val < 511) {
    return val - 512;
  } else {
    return 0;
  }
}

static void printUpdate(int *x, int *y, int valx, int valy) {
  if (*x != valx || *y != valy) {
    if (*x != valx) {
      *x = valx;
    }
    if (*y != valy) {
      *y = valy;
    }
    Serial.print(F("("));
    Serial.print(*x);
    Serial.print(F(","));
    Serial.print(*y);
    Serial.print(F(")"));
    Serial.println();
  }
}

void setup() {
  Serial.begin(57600);
}

void loop() {
  int xCurr, yCurr, r;

  xCurr = jsAxis(analogRead(A2));
  delay(100);
  yCurr = jsAxis(analogRead(A3));
  r = sqrt(pow(xCurr, 2) + pow(yCurr, 2));

  if (r < deadzone) {
    xCurr = 0;
    yCurr = 0;
  } else {
    int rScaled = r / (r - deadzone) ;

    xCurr = rScaledMax / rScaled * xCurr;
    yCurr = rScaledMax / rScaled * yCurr;
  }

  printUpdate(&x, &y, xCurr, yCurr);
}

