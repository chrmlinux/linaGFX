//======================================================================================
// OSC OutPut Wave v2.0
//--------------------------------------------------------------------------------------
// date/author    : 2022/05/21 @chrmlinux03
// update/author  : 2022/06/01 @chrmlinux03 edit dacWrite
// M5StackC-Plus/M5Atom-Lite/M5StacK ..etc Models with DAC1/DAC2
//======================================================================================
//===================================================
// https://www.arduinolibraries.info/libraries/three-d
//---------------------------------------------------
// Processes a 3D coordinate matrix to generate 2D coordinates.
//===================================================
#include <ThreeD.hpp>
#include "mdl.h"
static ThreeD td;

//===================================================
// https://github.com/chrmlinux/linaGFX
//---------------------------------------------------
// Draw a line segment and one number on the memory
//===================================================
#include <driver/dac.h>
#include <linaGFX.hpp>
static linaGFX fb;

#define FB_WIDTH  (256 - 4)
#define FB_HEIGHT (256 - 4)
#define FB_DEPTH   (8)
#define LEDPIN    (-1) // -1:non n:pinNo
#define GRID      ( 0) //  0:non n:pixSize
#define TRIG      ( 0) //  0:non n:TRIG color

uint16_t _w; // width
uint16_t _h; // height
uint16_t _hw; // half width
uint16_t _hh; // half height

//===================================================
// draw pixel
//===================================================
void execDot(void) {
  if (fb.x()||fb.y()) {
    dacWrite(25,      fb.x());
    dacWrite(26, _h - fb.y());
  }
  if (LEDPIN != -1) digitalWrite(LEDPIN, !digitalRead(LEDPIN));
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
void draw(float fact, uint16_t mdlpt, MDL2D_T *mdl, uint16_t lnkpt, LNK_T *lnk) {
  fb.clear(LINA_BLACK);
  if (TRIG) fb.drawPixel((_w - 1), (_h - 1), TRIG);
  if (GRID) grid(LINA_GRAY, GRID);
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
  float fact = 100.0F;
  static uint16_t deg =  0;

  td.rot(ROTY, deg, mdlpt,   mdl, dst3d);
  td.rot(ROTZ,  24, mdlpt, dst3d, dst3d);
  td.cnv(view,      mdlpt, dst3d, dst2d);
  draw  (fact, mdlpt, dst2d, lnkpt, lnk);
  deg = (deg + 6) % 360;
}

//===================================================
// setup
//===================================================
void setup(void) {
  Serial.begin( 115200 ); delay(!Serial);
  if (LEDPIN != -1) {
    pinMode(LEDPIN, OUTPUT); digitalWrite(LEDPIN, !LOW);
  }
  fb.begin(FB_WIDTH, FB_HEIGHT, FB_DEPTH, execDot);
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
