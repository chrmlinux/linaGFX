#include <M5StickC.h>

#include <linaGFX.hpp>
static linaGFX fb;
#define WIDTH   (80)
#define HEIGHT  (80)
#define DEPTH    (8)

#include <ThreeD.hpp>
#include "mdl.h"
static ThreeD td;

uint16_t _w;
uint16_t _h;
uint16_t _hw;
uint16_t _hh;

void grid(int col, int stp) {
  for (int h = 0; h < _h; h += stp) {
    for (int w = 0; w < _w; w += stp) {
      fb.drawPixel(w, h, col);
    }
  }
}

void draw(float fact, uint16_t mdlpt, MDL2D_T *mdl, uint16_t lnkpt, LNK_T *lnk)
{
  for (int i = 0; i < lnkpt; i++) {
    uint16_t x1 = _hw + (mdl[lnk[i].start].x * fact);
    uint16_t y1 = _hh + (mdl[lnk[i].start].y * fact);
    uint16_t x2 = _hw + (mdl[lnk[i].end].x * fact);
    uint16_t y2 = _hh + (mdl[lnk[i].end].y * fact);
    fb.drawLine(x1, y1, x2, y2, lnk[1].color ? LINA_WHITE : LINA_BLACK);
    fb.drawNum(x1, y1, lnk[i].start, LINA_WHITE);
  }
}

void setup() {
  M5.begin();
  Serial.begin( 115200 ); delay(1000);
  fb.begin(WIDTH, HEIGHT, DEPTH);

  _w = fb.width();
  _h = fb.height();
  _hw = _w >> 1;
  _hh = _h >> 1;
  td.begin();
}

void loop() {
  float fact = 90.0;
  static uint16_t deg = 0;

  fb.clear();

  grid(LINA_GRAY, 8);
  td.rot(ROTY, deg, mdlpt,   mdl, dst3d);
  td.rot(ROTZ,  24, mdlpt, dst3d, dst3d);
  td.cnv(view,      mdlpt, dst3d, dst2d);
  draw(fact,      mdlpt, dst2d, lnkpt, lnk);

  fb.display();
  deg = (deg + 2) % 360;

  M5.Lcd.pushImage(0, 0, _w, _h, fb.getFb());
}
