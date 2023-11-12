#include "helper.h"

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

Vector2 getFontSize(int width, Font font) {
  Rectangle max_rec = {0, 0, 0, 0};
  Vector2 f_size;
  for (int i = 0; i < font.glyphCount; i++) {
    if (font.recs[i].width > max_rec.width)
      max_rec = font.recs[i];
  }
  f_size.x = width;
  f_size.y = width * (max_rec.height / max_rec.width);
  return f_size;
}
Vector2 addVec(Vector2 v1, int cons) {
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

Vector2 scaleVec(Vector2 v1, int cons) {
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

Vector2 divVec(Vector2 v1, Vector2 v2) {
  return Vector2{v1.x / v2.x, v1.y / v2.y};
}

Vector2 divVec(Vector2 v1, int cons) {
  return Vector2{v1.x / cons, v1.y / cons};
}

Vector2 scaleVec(Vector2 v1, Vector2 v2) {
  return Vector2{v1.x * v2.x, v1.y * v2.y};
}

int minVec(Vector2 v1) { return min(v1.x, v1.y); }

int maxVec(Vector2 v1) { return max(v1.x, v1.y); }

Vector2 setBothVec(float a) { return Vector2{a, a}; }

bool vecEquals(Vector2 v1, Vector2 v2) { return v1.x == v2.x && v1.y == v2.y; }
