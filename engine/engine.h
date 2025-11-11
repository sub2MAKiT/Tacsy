#pragma once

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>

#define height 240
#define width 320

#define PI 3.14159265

typedef struct LGBTStruct {
    double L;
    double G;
    double B;
    double T;
} LGBT;

#define LGBTtoRGBA(LGBTv) (RGBA){LGBTv.L*255,((1-(LGBTv.L*LGBTv.B))*LGBTv.L/(sqrt(2))+LGBTv.G)*255, (LGBTv.B-(LGBTv.L*LGBTv.B)*(1-LGBTv.G))*255 ,LGBTv.T*255}

typedef struct RGBAStruct {
    unsigned char R;
    unsigned char G;
    unsigned char B;
    unsigned char A;
} RGBA;

typedef struct RGBADoubleStruct {
    unsigned char R;
    unsigned char G;
    unsigned char B;
    unsigned char A;
} RGBAd;

typedef struct shapeStruct {
    unsigned long long sizeOfShape;
    float * X;
    float * Y;
    float HY;
    float LY;
    float HX;
    float LX;
    RGBA (*customCol)(float, float);
    char useCustomCol;
    RGBA col;
} shape;


typedef struct lineStruct {
    shape shap;
    RGBA * line;
    unsigned long long lineDex;
    unsigned long long packSize;
    RGBA col;
    RGBA (*customCol)(float, float);
    char useCustomCol;
} lineD; // what in the actual fuck is this struct?

char checkLine(float p0X, float p0Y, float p1X, float p1Y, float pointX, float pointY);
char checkShape(float * shapeX, float * shapeY, float pointX, float pointY, long long sizeOfShape);
// char determineCol(float x,float y);
void drawShapes(void * buf);
void fillBuff(RGBA fill, void * buf);
unsigned long long createShape();
void expandShape(shape * shap,unsigned long long n);
void destroyShapes();
void addArcToShape(unsigned long long shpindex, float X, float Y, float phase, float radius, float angle, long long n, char flip);
void * drawLine(void * line);
void checkBoundaries(shape * shap);
void addPointToShape(unsigned long long shpindex, float X, float Y);
void setShapeColour(unsigned long long shpindex, RGBA col);
RGBA mixColours(RGBA colA, RGBA colB);
void setShapeCustomColour(unsigned long long shpindex, RGBA (*customCol)(float, float));
void referenceGrid(void * buf);

extern shape * allShapes;
extern unsigned long long sizeOfAllShapes;