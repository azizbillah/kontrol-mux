

#include <SmartMatrix3.h>



#define COLOR_DEPTH 24                  // known working: 24, 48 - If the sketch uses type `rgb24` directly, COLOR_DEPTH must be 24
const uint8_t kMatrixWidth = 64;        // known working: 32, 64, 96, 128
const uint8_t kMatrixHeight = 32;       // known working: 16, 32, 48, 64
const uint8_t kRefreshDepth = 36;       // known working: 24, 36, 48
const uint8_t kDmaBufferRows = 2;       // known working: 2-4, use 2 to save memory, more to keep from dropping frames and automatically lowering refresh rate
const uint8_t kPanelType = SMARTMATRIX_HUB75_32ROW_MOD16SCAN;   // use SMARTMATRIX_HUB75_16ROW_MOD8SCAN for common 16x32 panels
const uint8_t kMatrixOptions = (SMARTMATRIX_OPTIONS_NONE);      // see http://docs.pixelmatix.com/SmartMatrix for options
const uint8_t kScrollingLayerOptions = (SM_SCROLLING_OPTIONS_NONE);
const uint8_t kIndexedLayerOptions = (SM_INDEXED_OPTIONS_NONE);

SMARTMATRIX_ALLOCATE_BUFFERS(matrix, kMatrixWidth, kMatrixHeight, kRefreshDepth, kDmaBufferRows, kPanelType, kMatrixOptions);
SMARTMATRIX_ALLOCATE_SCROLLING_LAYER(scrollingLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kScrollingLayerOptions);
SMARTMATRIX_ALLOCATE_SCROLLING_LAYER(scrollingLayer2, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kScrollingLayerOptions);
SMARTMATRIX_ALLOCATE_INDEXED_LAYER(indexedLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kIndexedLayerOptions);

const int defaultBrightness = (20*255)/100;        // full (100%) brightness
//const int defaultBrightness = (15*255)/100;       // dim: 15% brightness
const int defaultScrollOffset = 6;
const rgb24 defaultBackgroundColor = {0, 100, 0};



int A_1 = 4;
int B_1 = 5;

//String dataku;
String dt[20];
boolean parsing = false;
int minLength = 0;

char sped[15],heading[15], win[15];
char dis_sped[15],disp_head[15], disp_win[15];

int k;
float d_head;
float d_win;
float d_sped;
String s_heading;
float f_heading=0;
String dataku;



void setup() {
  // put your setup code here, to run once:

  Serial.begin(4800);
 // Serial1.begin(4800);
  pinMode( A_1, OUTPUT);
  pinMode( B_1, OUTPUT);
  digitalWrite(A_1,LOW);
  digitalWrite(B_1, LOW);
  matrix.addLayer(&scrollingLayer);
  matrix.addLayer(&scrollingLayer2);
  matrix.addLayer(&indexedLayer);
  matrix.begin();  
  matrix.setBrightness((30*255)/100);

}

void loop() {
ready_todraw();
  if (parsing) {
    parsingdata();
   // display_data();
    dataku = "";
    parsing = false;


  }



}

void serialEvent1() {
  while (Serial.available()) {
    dataku = readString();
    Serial.print(dataku);
//    if (inChar == '\n') {
//      parsing = true;
//    }
  }
}

void parsingdata()
{
  
  int j = 0;

  dt[j] = "";
  int minLength;
  if (dataku.length() > 70) {
    minLength = 20;
  }
  else                      {
    minLength = 0;
  }
  for (k = 1; k < dataku.length() - minLength ; k++) {
    if ((dataku[k] == '$') || (dataku[k] == ',' ) || (dataku[k] == '*' ) ) {
      j++;
      dt[j] = "";
    }
    else {
      dt[j] = dt[j] + dataku[k];
    }
  }

  if (dt[0]=="GPHDT") {
    //dt[1].toCharArray(heading,15);
      Serial.print(dataku);
   // d_head=dt[1].toFloat();
//    digitalWrite(A_1, HIGH);
//    digitalWrite(B_1, LOW);
    

  }

//  else if (dt[0].charAt(4) == 'V') {
//    //Serial.println(data);
//    dt[1].toCharArray(win,15);
//    //d_win = dt[1].toFloat();
//    digitalWrite(A_1, LOW);
//    digitalWrite(B_1, HIGH);
//  }
//
//  else if (dt[0].charAt(4) == 'W' ) {
//    //d_sped = dt[5].toFloat();
//    dt[1].toCharArray(sped,15); 
//    digitalWrite(A_1, LOW);
//    digitalWrite(B_1, LOW);
//  }
}

void display_data(){
//      sprintf(disp_head, "%d",heading);
//      Serial.print(disp_head);
//      sprintf(tanggalhijriah, "%d %s %d", Hjr_Date, bulanHijriah[Hjr_Month], Hjr_Year);
//      sprintf(tanggalmasehi, "%d %s %d", rTgl, bulanMasehi[rBul], rTah);
 
      indexedLayer.fillScreen(0);
      indexedLayer.drawString(27, 1, 1, sped);
      indexedLayer.drawString(27, 12, 1, disp_head);
      indexedLayer.drawString(27, 22, 1, win);
      indexedLayer.swapBuffers();
  
}
void ready_todraw()

{

      indexedLayer.fillScreen(0);
      indexedLayer.setFont(font6x10);
      indexedLayer.drawString(3, 1, 1, "SPD");
      indexedLayer.drawString(3, 12, 1, "HDT");
      indexedLayer.drawString(3, 22, 1, "WIN");
      indexedLayer.drawString(23, 0, 1, ":");
      indexedLayer.drawString(23, 11, 1, ":");
      indexedLayer.drawString(23, 21, 1, ":");
      indexedLayer.swapBuffers();
  
}
