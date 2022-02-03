#include <FastLED.h>
#include <colorutils.h>
#include "customPalettes.h"

int darkBlue = 0x1900ff;
int mediumBlue = 0x004cff;
int lightBlue = 0x00d0ff;
int grey = 0xd6d6d6;

extern const TProgmemRGBPalette16 White_p FL_PROGMEM = {
  CRGB:: Grey,
  CRGB:: Grey,
  CRGB:: Grey,
  CRGB:: Grey,

  CRGB:: Grey,
  CRGB:: Grey,
  CRGB:: Grey,
  CRGB:: Grey,

  CRGB:: Grey,
  CRGB:: Grey,
  CRGB:: Grey,
  CRGB:: Grey,

  CRGB:: Grey,
  CRGB:: Grey,
  CRGB:: Grey,
  CRGB:: Grey,
};

const TProgmemPalette16 Red_p FL_PROGMEM = {
  CRGB::Red,
  CRGB::Red,
  CRGB::Red,
  CRGB::Red,

  CRGB::Red,
  CRGB::Red,
  CRGB::Red,
  CRGB::Red,

  CRGB::Red,
  CRGB::Red,
  CRGB::Red,
  CRGB::Red,

  CRGB::Red,
  CRGB::Red,
  CRGB::Red,
  CRGB::Red,
};

extern const TProgmemPalette16 Orange_p FL_PROGMEM = {
  0xf58700, 0xf58700, 0xf58700, 0xf58700,
  0xf58700, 0xf58700, 0xf58700, 0xf58700,
  0xf58700, 0xf58700, 0xf58700, 0xf58700,
  0xf58700, 0xf58700, 0xf58700, 0xf58700,
};

extern const TProgmemPalette16 Yellow_p FL_PROGMEM = {
  0xfff700, 0xfff700, 0xfff700, 0xfff700,
  0xfff700, 0xfff700, 0xfff700, 0xfff700,
  0xfff700, 0xfff700, 0xfff700, 0xfff700,
  0xfff700, 0xfff700, 0xfff700, 0xfff700,
};

extern const TProgmemPalette16 Green_p FL_PROGMEM = {
  0x0ff22, 0x0ff22, 0x0ff22, 0x0ff22,
  0x0ff22, 0x0ff22, 0x0ff22, 0x0ff22,
  0x0ff22, 0x0ff22, 0x0ff22, 0x0ff22,
  0x0ff22, 0x0ff22, 0x0ff22, 0x0ff22,
};

extern const TProgmemPalette16 Blue_p FL_PROGMEM = {
  CRGB::Blue,
  CRGB::Blue,
  CRGB::Blue,
  CRGB::Blue,

  CRGB::Blue,
  CRGB::Blue,
  CRGB::Blue,
  CRGB::Blue,

  CRGB::Blue,
  CRGB::Blue,
  CRGB::Blue,
  CRGB::Blue,

  CRGB::Blue,
  CRGB::Blue,
  CRGB::Blue,
  CRGB::Blue,
};

extern const TProgmemPalette16 Purple_p FL_PROGMEM = {
  0x600ecc, 0x600ecc, 0x600ecc, 0x600ecc,
  0x600ecc, 0x600ecc, 0x600ecc, 0x600ecc,
  0x600ecc, 0x600ecc, 0x600ecc, 0x600ecc,
  0x600ecc, 0x600ecc, 0x600ecc, 0x600ecc,
};

extern const TProgmemPalette16 Villains_p FL_PROGMEM = {
  0x600ecc, 0x600ecc, 0x0ff22, 0x0ff22,
  0x600ecc, 0x600ecc, 0x0ff22, 0x0ff22,
  0x600ecc, 0x600ecc, 0x0ff22, 0x0ff22,
  0x600ecc, 0x600ecc, 0x0ff22, 0x0ff22,
};

extern const TProgmemPalette16 CloudyDays_p FL_PROGMEM = {
  darkBlue, mediumBlue, lightBlue, grey,
  grey, lightBlue, mediumBlue, darkBlue,
  darkBlue, mediumBlue, lightBlue, grey,
  grey, lightBlue, mediumBlue, darkBlue,

};
