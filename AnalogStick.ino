/***********************************************************************************************************************
 *  Intro: A single analog stick.
 *         Arduino reads its raw values, filters(Radial Scaling method) them and
 *         prints to serial port when there is an change.
 *
 *  Board: Arduino Pro Mini (3.3V, 8MHz)
 *
 *  Connections: Type   Pro Mini   Analog Stick
 *               Output   A2         VRx
 *               Output   A3         VRy
 *               Output   VCC        +5V
 *               Output   GND        GND
 *
 **********************************************************************************************************************/

//Radial Scaling Constants
const int rMax = sqrt(2 * pow(512, 2));
const int deadzone = 0.20 * rMax;
const int rScaledMax = rMax / (rMax - deadzone);

int xPrev = 1024;
int yPrev = 1024;


/**********************************************************************************************************************
 *  Static Functions
 *********************************************************************************************************************/
static int stickTranspose(int val) {
  if (val > 512) {
    return val - 511;
  } else if (val < 511) {
    return val - 512;
  } else {
    return 0;
  }
}

static void stickPrint(int *x, int *y, int valx, int valy) {
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

/**********************************************************************************************************************
 *  Setup
 *********************************************************************************************************************/
void setup() {
  Serial.begin(57600);
}

/**********************************************************************************************************************
 *  Main
 *********************************************************************************************************************/
void loop() {
  int xCurr, yCurr, r;

  xCurr = stickTranspose(analogRead(A2));
  delay(100);
  yCurr = stickTranspose(analogRead(A3));
  r = sqrt(pow(xCurr, 2) + pow(yCurr, 2));

  if (r < deadzone) {
    xCurr = 0;
    yCurr = 0;
  } else {
    int rScaled = r / (r - deadzone) ;

    xCurr = rScaledMax / rScaled * xCurr;
    yCurr = rScaledMax / rScaled * yCurr;
  }

  stickPrint(&xPrev, &yPrev, xCurr, yCurr);
}
