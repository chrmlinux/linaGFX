#include <M5StickC.h>

#include "linaGFX.hpp"
static linaGFX fb;
#define WIDTH   (80)
#define HEIGHT  (80)
#define DEPTH    (8)

#include <ThreeD.hpp>
#include "mdl.h"
static ThreeD td;

uint16_t _hw;
uint16_t _hh;

void draw(float fact, uint16_t mdlpt, MDL2D_T *mdl, uint16_t lnkpt, LNK_T *lnk)
{
  for (int i=0; i<lnkpt; i++) {
    uint16_t x1 = _hw + (mdl[lnk[i].start].x * fact);
    uint16_t y1 = _hh + (mdl[lnk[i].start].y * fact);
    uint16_t x2 = _hw + (mdl[lnk[i].end].x * fact);
    uint16_t y2 = _hh + (mdl[lnk[i].end].y * fact);
    fb.drawLine(x1, y1, x2, y2, lnk[1].color);
    fb.drawNum(x1, y1, lnk[i].start, 0xff);
  }
}

void setup() {
  M5.begin();
  Serial.begin( 115200 ); delay(1000);
  fb.begin(WIDTH, HEIGHT, DEPTH);
  _hw = fb.width() >> 1;
  _hh = fb.height() >> 1;
  td.begin();
}

void loop() {
  float fact = 90.0;
  static uint16_t deg = 0;  

  fb.clear();

  td.rot(ROTY, deg, mdlpt,   mdl, dst3d); 
  td.rot(ROTZ,  24, mdlpt, dst3d, dst3d); 
  td.cnv(view,      mdlpt, dst3d, dst2d);
    draw(fact,      mdlpt, dst2d, lnkpt, lnk);

  fb.display();
  deg = (deg + 2) % 360;

  M5.Lcd.pushImage(0, 0, fb.width(), fb.height(), fb.getFb());
}
