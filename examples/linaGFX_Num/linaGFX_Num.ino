#include <M5StickC.h>

#include <linaGFX.hpp>
static linaGFX fb;
#define WIDTH  (80)
#define HEIGHT (80 + 1)
#define DEPTH  (8)
#define FSIZE  (8)

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

void setup() {
  M5.begin();
  Serial.begin( 115200 ); delay(1000);
  fb.begin(WIDTH, HEIGHT, DEPTH);
  _w = fb.width();
  _h = fb.height();
  _hw = _w >> 1;
  _hh = _h >> 1;

}

void loop() {

  static int c = 0;
  static int x = _hw;
  static int xsft = 1;
  static int y = _hh;
  static int ysft = 1;

  fb.clear(LINA_BLACK);
  grid(LINA_GRAY, 8);
  fb.drawNum(x, y, c, LINA_WHITE);
  x += xsft; if ((x < 1) || (x + FSIZE > _w)) xsft = -xsft;
  y += ysft; if ((y < 1) || (y + FSIZE > _h)) ysft = -ysft;
  fb.display();
  M5.Lcd.pushImage(0, 0, _w, _h, fb.getFb());
  c = (c + 1) % 10;
}
