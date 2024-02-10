#include "raylib.h"

#ifndef HELPER
#define HELPER

int min(int a, int b);
int max(int a, int b);
int getSign(int a);
bool colourEquals(Color c1, Color c2);
Vector2 getMaxFontBox(Font font);

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

bool vecEquals(Vector2 v1, Vector2 v2);
int myAbs(int a);
int minVec(Vector2 v1);
int maxVec(Vector2 v1);
double vecAngle(Vector2 v1, Vector2 v2);
#endif