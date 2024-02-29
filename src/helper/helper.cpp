#include "helper.h"
#include "cmath"

int min(int a, int b) {
  if (a > b) return b;
  return a;
}

int max(int a, int b) {
  if (a < b) return b;
  return a;
}

int getSign(int a) {
  if (a > 0) return 1;
  if (a == 0) return 0;
  return -1;
}

int myAbs(int a) {
  if (a < 0) return -a;
  return a;
}

bool colourEquals(Color c1, Color c2) {
  return c1.a == c2.a && c1.r == c2.r && c1.g == c2.g && c1.b == c2.b;
}

// Gets the height and width of the widest character at a defualt font size
Vector2 getMaxFontBox(Font font) {
  Rectangle max_rec = {0, 0, 0, 0};
  for (int i = 0; i < font.glyphCount; i++) {
    if (font.recs[i].width > max_rec.width)
      max_rec = font.recs[i];
  }
  return Vector2{max_rec.width, max_rec.height};
}

int getMaxFontWidthNums(Font font, int fontsize) {
  int max_width = 0;
  for (char c = '0'; c <= '9'; c++) {
    int width = MeasureText(&c, fontsize);
    if (width > max_width) {
      max_width = width;
    }
  }
  return max_width;
}

Vector2 getMaxFontBoxNumsInBounds(Font font, Vector2 char_box) {
  Vector2 maxVec = {0, 0};
  for (char c = '0'; c <= '9'; c++) {
    Vector2 resSize = getTextsizeInBound(&c, char_box, 1);
    if (resSize.x < maxVec.x) {
      resSize = maxVec;
    }
  }
  return maxVec;
}

Vector2 getTextsizeInBound(const char *msg, Vector2 size, float margin) {

  float textHeight = size.y * margin;
  if ((size.x * margin) < MeasureText(msg, textHeight)) {
    textHeight = ((textHeight / MeasureText(msg, textHeight)) * size.x) * margin;
  }
  return {(float)MeasureText(msg, textHeight), textHeight};
}

Vector2 addVec(Vector2 v1, float cons) {
  v1.x += cons;
  v1.y += cons;
  return v1;
}

Vector2 addVec(Vector2 v1, Vector2 v2) {
  v1.x += v2.x;
  v1.y += v2.y;
  return v1;
}

Vector2 subVec(Vector2 v1, Vector2 v2) {
  v1.x -= v2.x;
  v1.y -= v2.y;
  return v1;
}

Vector2 scaleVec(Vector2 v1, float cons) {
  v1.x *= cons;
  v1.y *= cons;
  return v1;
}

Vector2 signVec(Vector2 v1) {
  v1.x = getSign(v1.x);
  v1.y = getSign(v1.y);
  return v1;
}

Vector2 keepMaxMag(Vector2 v1) {
  if (myAbs(v1.y) > myAbs(v1.x)) {
    v1.x = 0;
  } else {
    v1.y = 0;
  }
  return v1;
}

Vector2 doubleMaxMag(Vector2 v1) {
  if (myAbs(v1.y) > myAbs(v1.x)) {
    v1.x = v1.y;
  } else {
    v1.y = v1.x;
  }
  return v1;
}

Vector2 doubleMinMag(Vector2 v1) {
  if (myAbs(v1.y) < myAbs(v1.x)) {
    v1.x = v1.y;
  } else {
    v1.y = v1.x;
  }
  return v1;
}

Vector2 divVec(Vector2 v1, Vector2 v2) {
  return Vector2{v1.x / v2.x, v1.y / v2.y};
}

Vector2 divVec(Vector2 v1, float cons) {
  return Vector2{v1.x / cons, v1.y / cons};
}

Vector2 scaleVec(Vector2 v1, Vector2 v2) {
  return Vector2{v1.x * v2.x, v1.y * v2.y};
}

float minVec(Vector2 v1) { return min(v1.x, v1.y); }

float maxVec(Vector2 v1) { return max(v1.x, v1.y); }

Vector2 setBothVec(float a) { return Vector2{a, a}; }

bool vecEquals(Vector2 v1, Vector2 v2) { return v1.x == v2.x && v1.y == v2.y; }

// angle in radians from x axis, origin at v1
double vecAngle(Vector2 v1, Vector2 v2) {
  return atan((v2.y - v1.y) / (v2.x - v1.x));
}

Vector2 ceilVec(Vector2 v1) {
  v1.x = ceil(v1.x);
  v1.y = ceil(v1.y);
  return v1;
}

Vector2 floorVec(Vector2 v1) {
  v1.x = floor(v1.x);
  v1.y = floor(v1.y);
  return v1;
}
