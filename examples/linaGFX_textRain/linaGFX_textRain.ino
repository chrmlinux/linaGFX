//======================================================================================
// OSC OutPut Wave
//--------------------------------------------------------------------------------------
// date/author    : 2022/05/21 @chrmlinux03
// M5StackC-Plus/M5Atom-Lite/M5StacK ..etc Models with DAC1/DAC2
//======================================================================================
#include <M5StickC.h>
//#define OUTPUTOSC

//===================================================
// https://www.arduinolibraries.info/libraries/three-d
//---------------------------------------------------
// Processes a 3D coordinate matrix to generate 2D coordinates.
//===================================================
#include <ThreeD.hpp>
#include "mdl.h"
static ThreeD td;
#define DRAW_LIMIT (1000 * 10)

//===================================================
// https://github.com/chrmlinux/linaGFX
//---------------------------------------------------
// Draw a line segment and one number on the memory
//===================================================
#include <driver/dac.h>
#include <linaGFX.hpp>
static linaGFX fb;
#define FB_WIDTH   (80)
#define FB_HEIGHT  (80)
#define FB_DEPTH   (8)
#define FB_FSIZE   (8)
#define LEDPIN    (10)
uint16_t _w; // width
uint16_t _h; // height
uint16_t _hw; // half width
uint16_t _hh; // half height

//===================================================
// draw pixel
//===================================================
void setupDot(void) {
  dac_output_enable(DAC_CHANNEL_1); // pin25
  dac_output_enable(DAC_CHANNEL_2); // pin26
}
void execDot(void) {
  dac_output_voltage(DAC_CHANNEL_1, _w - fb.x());
  dac_output_voltage(DAC_CHANNEL_2, fb.y());
  digitalWrite(LEDPIN, !digitalRead(LEDPIN));
}

//===================================================
// grid
//===================================================
void grid(int col, int stp) {
  for (int h = 0; h < _h; h += stp) {
    for (int w = 0; w < _w; w += stp) {
      fb.drawPixel(w, h, col);
    }
  }
}

//===================================================
// draw
//===================================================
//====================================================
//
// textRain:
// https://qiita.com/chrmlinux03/items/c8668f2447dd61a6aabb
//
//====================================================
void px(int x, int y, int h, int c) {
  fb.drawNum(x * h, y * h, random(0, 9), c);
}
void textRain(int x, int y, int h) {
  static int yp[40] = {1};
  for (int i = 0; i < x; i++) {
    px(i, yp[i], h, LINA_WHITE);
    int p = 0;
    for (int j = yp[i] - y; j < yp[i]; j++) {
      px(i, j, h, (p << 3));
      p++;
    }
    if (yp[i] > y) {
      if (random(1000) > 975) yp[i] = 0;
    }
    yp[i]++;
  }
}

//===================================================
// draw
//===================================================
void draw(float fact, uint16_t mdlpt, MDL2D_T *mdl, uint16_t lnkpt, LNK_T *lnk) {
#ifdef OUTPUTOSC
  fb.drawPixel((_w - 1), (_h - 1), 0xff); // trigger
#endif
  grid(LINA_GRAY, 8);
  for (int i = 0; i < lnkpt; i++) {
    uint16_t x1 = _hw + (mdl[lnk[i].start].x * fact);
    uint16_t y1 = _hh + (mdl[lnk[i].start].y * fact);
    uint16_t x2 = _hw + (mdl[lnk[i].end  ].x * fact);
    uint16_t y2 = _hh + (mdl[lnk[i].end  ].y * fact);
    fb.drawLine(x1, y1, x2, y2, lnk[i].color ? LINA_WHITE : LINA_BLACK);
    fb.drawNum(x1, y1, lnk[i].start, LINA_WHITE);
  }
}

//===================================================
// calDraw
//===================================================
void calDraw(void) {
    float fact = 80.0F;
    static uint16_t deg =  0;
    uint32_t tm = micros();

    fb.clear(LINA_BLACK);
    textRain(_w / FB_FSIZE, _h / FB_FSIZE, FB_FSIZE);
    td.rot(ROTY, deg, mdlpt,   mdl, dst3d);
    td.rot(ROTZ,  24, mdlpt, dst3d, dst3d);
    td.cnv(view,      mdlpt, dst3d, dst2d);
    draw(fact, mdlpt, dst2d, lnkpt, lnk);
    deg = (deg + 1) % 360;

#ifdef OUTPUTOSC
  int32_t d = DRAW_LIMIT - (micros() - tm);
  if (d > 0) delayMicroseconds(d);
#else
  M5.Lcd.pushImage(0, 0, _w, _h, fb.getFb());
#endif

}

//===================================================
// setup
//===================================================
void setup(void) {
  M5.begin();
  Serial.begin( 115200 ); delay(1000);
#ifdef OUTPUTOSC
  pinMode(LEDPIN, OUTPUT); digitalWrite(LEDPIN, !LOW);
  fb.begin(FB_WIDTH, FB_HEIGHT, FB_DEPTH, execDot);
#else
  fb.begin(FB_WIDTH, FB_HEIGHT, FB_DEPTH);
#endif
  _w = fb.width();
  _h = fb.height();
  _hw = _w >> 1;
  _hh = _h >> 1;
  td.begin();
}

//===================================================
// loop
//===================================================
void loop(void) {
  calDraw();
}
