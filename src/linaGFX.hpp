//========================================
//
// date/author    : 2022/05/18 @chrmlinux
// LICENSE        : MIT
//
//========================================

#ifndef __LINAGFX_HPP__
#define __LINAGFX_HPP__

#include <Arduino.h>

class linaGFX {

    //========================================
    // public
    //========================================
  public:

    //========================================
    // constractor
    //========================================
    linaGFX() {};
    ~linaGFX() {};

    //========================================
    // getFps
    //========================================
    uint32_t getfps(void)
    {
      static uint32_t psec = 0;
      static uint32_t cnt = 0;
      static uint32_t fps = 0;
      uint32_t sec = 0;

      sec = millis() / 1000;
      ++cnt;
      if (psec != sec) {
        psec = sec;
        fps = cnt;
        cnt = 0;
      }
      return fps;
    }

    //========================================
    // begin
    //========================================
    uint16_t begin(uint16_t width, uint16_t height, uint16_t depth) {
      uint16_t rtn = 0;
      _width = width;
      _height = height;
      _size = _width * _height;
      _fb = new uint8_t[_size];
      return rtn;
    }

    //========================================
    // width
    //========================================
    uint16_t width() {
      return _width;
    }

    //========================================
    // height
    //========================================
    uint16_t height() {
      return _height;
    }

    //========================================
    // end
    //========================================
    uint16_t end() {
      uint16_t rtn = 0;
      free(_fb);
      return rtn;
    }

    //========================================
    // getFb
    //========================================
    uint8_t *getFb() {
      return _fb;
    }

    //========================================
    // drawPixel
    //========================================
    uint16_t drawPixel(uint16_t x, uint16_t y, uint8_t col) {
      uint16_t rtn = 0;
      uint32_t pos = y * _width + x;
      _fb[pos] = col;
      return rtn;
    }

    //========================================
    // drawNum
    //========================================
    void drawNum(uint16_t x, uint16_t y, uint16_t num, uint8_t col) {
      for (int h = 0; h < 8; h++) {
        for (int w = 0; w < 8; w++) {
          if (_num[num][h] & (0x80 >> w)) {
            drawPixel(x + w, y + h, col);
          }
        }
      }
    }

    //========================================
    // drawLine
    // https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
    //========================================
    void drawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t col) {
      int dx = abs(x1 - x0);
      int dy = abs(y1 - y0);
      int sx, sy, err, e2;

      if (x0 < x1) {
        sx = 1;
      } else {
        sx = -1;
      }
      if (y0 < y1) {
        sy = 1;
      } else {
        sy = -1;
      }
      err = dx - dy;

      while (1) {
        drawPixel(x0, y0, col);
        if ((x0 == x1) && (y0 == y1)) break;
        e2 = 2 * err;
        if (e2 > -dy) {
          err -= dy;
          x0 += sx;
        }
        if (e2 < dx) {
          err += dx;
          y0 += sy;
        }
      }
    }

    //========================================
    // display
    //========================================
    uint16_t display() {
      _displayEnable = true;
      return _displayEnable;
    }

    //========================================
    // dump
    //========================================
    void dump() {
      uint32_t pos = 0;
      for (int h = 0; h < _height; h++) {
        for (int w = 0; w < _width; w++) {
          Serial.print(_fb[pos]);
          pos++;
        }
        Serial.println();
      }
      Serial.println();
    }

    //========================================
    // clear
    //========================================
    uint16_t clear() {
      memset(_fb, _col, _size);
      _displayEnable = false;
      return _displayEnable;
    }
    uint16_t clear(uint16_t col) {
      uint16_t rtn = 0;
      _col = col;
      rtn = clear();
      return rtn;
    }

    //========================================
    // private
    //========================================
  private:

    uint16_t _width = 0;
    uint16_t _height = 0;
    uint32_t _size = 0;
    uint16_t _col = 0;
    uint16_t _depth = 8;
    uint8_t *_fb = {0};
    bool _displayEnable = false;
    uint8_t _num[10][8] = {
      { // 0
        B00111110,
        B01000001,
        B01010001,
        B01001001,
        B01000101,
        B01000001,
        B00111110,
        B00000000,
      },
      { // 1
        B00011000,
        B00001000,
        B00001000,
        B00001000,
        B00001000,
        B00001000,
        B00111110,
        B00000000,
      },
      { // 2
        B00111110,
        B00000001,
        B00000001,
        B00111110,
        B01000000,
        B01000000,
        B00111110,
        B00000000,
      },
      { // 3
        B00111110,
        B00000001,
        B00000001,
        B00111110,
        B00000001,
        B00000001,
        B00111110,
        B00000000,
      },
      { // 4
        B00000000,
        B01000001,
        B01000001,
        B01111110,
        B00000001,
        B00000001,
        B00000001,
        B00000000,
      },
      { // 5
        B00111110,
        B01000000,
        B01000000,
        B01111110,
        B00000001,
        B00000001,
        B00111110,
        B00000000,
      },
      { // 6
        B00111110,
        B01000000,
        B01000000,
        B01111110,
        B01000001,
        B01000001,
        B00111110,
        B00000000,
      },
      { // 7
        B00111110,
        B00000011,
        B00000100,
        B00001000,
        B00001000,
        B00001000,
        B00001000,
        B00000000,
      },
      { // 8
        B00111110,
        B01000001,
        B01000001,
        B00111110,
        B01000001,
        B01000001,
        B00111110,
        B00000000,
      },
      { // 9
        B00111110,
        B01000001,
        B01000001,
        B00111110,
        B00000001,
        B00000001,
        B00111110,
        B00000000,
      },
    };

};

#endif
