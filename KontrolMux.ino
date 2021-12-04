//#include <Adafruit_GFX.h>
//#include <RGBmatrixPanel.h>

//#define F2(progmem_ptr) (const __FlashStringHelper *)progmem_ptr




//#define CLK 11   // USE THIS ON ARDUINO MEGA
//#define OE   9
//#define LAT 10
//#define A   A0
//#define B   A1
//#define C   A2
//#define D   A3

//RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, true, 64);
//
//
//uint16_t myRED = matrix.Color333(7,0,0);
//uint16_t myGREEN = matrix.Color333(0,7,0);
//uint16_t myBLUE = matrix.Color333(0,0,7);
//uint16_t myWHITE = matrix.Color333(7, 7,7);



int A_1 = 4;
int B_1 = 5;

String data;
String dt[20];
boolean parsing = false;
int minLength = 0;

char heading[15], win[15];

float d_head;
float d_win;

String s_heading;
float f_heading=0;
String dataku;
int textX1 = 14;

int8_t ball[3][4] = {
  {  3,  0,  1,  1 }, // Initial X,Y pos & velocity for 3 bouncy balls
  { 17, 15,  1, -1 },
  { 27,  4, -1,  1 }
};
static const uint16_t PROGMEM ballcolor[3] = {
  0x0080, // Green=1
  0x0002, // Blue=1
  0x1000  // Red=1
};




void setup() {
  // put your setup code here, to run once:
  Serial.begin(4800);
  Serial1.begin(4800);
  pinMode( A_1, OUTPUT);
  pinMode( B_1, OUTPUT);
  digitalWrite(A_1,LOW);
  digitalWrite(B_1, LOW);
 // matrix.begin();
//  matrix.setTextWrap(false); // Allow text to run off right edge
//  matrix.setTextSize(1);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (parsing) {
    parsingdata();
//    display_data();
    data = "";
    parsing = false;


  }

}

void serialEvent1() {
  while (Serial1.available()) {
    char inChar = (char)Serial1.read();
    data += inChar;
    if (inChar == '\n') {
      parsing = true;
    }
  }
}

void parsingdata()
{
  
  int j = 0;
  int k = 0;
  dt[j] = "";
  int minLength;
  if (data.length() > 70) {
    minLength = 20;
  }
  else                      {
    minLength = 0;
  }
  for (k = 1; k < data.length() - minLength ; k++) {
    if ((data[k] == '$') || (data[k] == ',' ) || (data[k] == '*' ) ) {
      j++;
      dt[j] = "";
    }
    else {
      dt[j] = dt[j] + data[k];
    }
  }

  if (dt[0].charAt(4)=='T') {
    //dt[1].toCharArray(heading,15);
    d_head=dt[1].toFloat();
    digitalWrite(A_1, HIGH);
    digitalWrite(B_1, LOW);
  

  }

  else if (dt[0].charAt(4) == 'V') {
    Serial.println(data);
    //dt[1].toCharArray(win,15);
    //d_win = dt[1].toFloat();
    digitalWrite(A_1, LOW);
    digitalWrite(B_1, LOW);
  }

  else if (dt[0] == "GPRMC" ) {
    Serial.println(data);
    digitalWrite(A_1, HIGH);
    digitalWrite(B_1, HIGH);
  }
  else if (dt[0] == "WIMWV" ) {
    Serial.println(data);
    digitalWrite(A_1, LOW);
    digitalWrite(B_1, LOW);
  }





}
/*
void display_data(){
    matrix.fillScreen(matrix.Color333(0, 0, 0));
    matrix.setCursor(3,1);
    matrix.setTextColor(myWHITE);
    matrix.setFont();
    matrix.print("SPD:");
    
    
    
    
    //heading
    matrix.setCursor(3,12);
    matrix.setFont();
    matrix.setTextColor(myWHITE);
    matrix.print("HDG:");
    matrix.setCursor(27,12);
    matrix.setTextColor(myWHITE);
    matrix.setFont();
    matrix.print(d_head);
    //speed
    matrix.setCursor(3,22);
    matrix.setTextColor(myWHITE);
    matrix.setFont();
    matrix.print("WIN:"); 
    matrix.setCursor(27,22);
    matrix.setTextColor(myWHITE);
    matrix.setFont();
    matrix.print(d_win);
    matrix.swapBuffers(false);


  
}
*/
