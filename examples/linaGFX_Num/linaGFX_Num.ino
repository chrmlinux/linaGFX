#include <M5StickC.h>

#include <linaGFX.hpp>
static linaGFX fb;
#define WIDTH   (80)
#define HEIGHT (160)
#define DEPTH    (8)
#define FSIZE    (8)

void setup() {
  M5.begin();
  Serial.begin( 115200 ); delay(1000);
  fb.begin(WIDTH, HEIGHT, DEPTH);
  fb.clear();
}

void loop() {

  static int c = 0;
  static int x = fb.width() >> 1;
  static int xsft = 1;
  static int y = fb.height() >> 1;
  static int ysft = 1;

  fb.drawNum(x, y, c, 0xff);
  x += xsft; if ((x < 1) || (x + FSIZE >  fb.width())) xsft = -xsft;
  y += ysft; if ((y < 1) || (y + FSIZE > fb.height())) ysft = -ysft;
  fb.display();
  M5.Lcd.pushImage(0, 0, fb.width(), fb.height(), fb.getFb());
  fb.clear();
  c = (c + 1) % 10;
}
