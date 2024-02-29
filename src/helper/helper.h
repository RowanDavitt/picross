#include "raylib.h"

#ifndef HELPER
#define HELPER

int min(int a, int b);
int max(int a, int b);
int getSign(int a);
bool colourEquals(Color c1, Color c2);
Vector2 getMaxFontBox(Font font);
int getMaxFontWidthNums(Font font, int fontsize);
Vector2 getTextsizeInBound(const char *msg, Vector2 size, float margin);
Vector2 getMaxFontBoxNumsInBounds(Font font, Vector2 char_box);

Vector2 addVec(Vector2 v1, float cons);
Vector2 addVec(Vector2 v1, Vector2 v2);
Vector2 subVec(Vector2 v1, Vector2 v2);
Vector2 signVec(Vector2 v1);
Vector2 keepMaxMag(Vector2 v1);
Vector2 doubleMaxMag(Vector2 v1);
Vector2 doubleMinMag(Vector2 v1);
Vector2 divVec(Vector2 v1, Vector2 v2);
Vector2 divVec(Vector2 v1, float cons);
Vector2 scaleVec(Vector2 v1, float cons);
Vector2 scaleVec(Vector2 v1, Vector2 v2);
Vector2 setBothVec(float a);
Vector2 ceilVec(Vector2 v1);
Vector2 floorVec(Vector2 v1);

bool vecEquals(Vector2 v1, Vector2 v2);
int myAbs(int a);
float minVec(Vector2 v1);
float maxVec(Vector2 v1);
double vecAngle(Vector2 v1, Vector2 v2);
#endif