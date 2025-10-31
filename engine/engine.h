#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>

#define height 300
#define width 400

#define PI 3.14159265

typedef struct shapeStruct {
    unsigned long long sizeOfShape;
    float * X;
    float * Y;
} shape;


typedef struct lineStruct {
    shape shap;
    char * line;
    unsigned long long lineDex;
    unsigned long long packSize;
} lineD;

char checkLine(float p0X, float p0Y, float p1X, float p1Y, float pointX, float pointY);
char checkShape(float * shapeX, float * shapeY, float pointX, float pointY, long long sizeOfShape);
// char determineCol(float x,float y);
void drawShape(shape shap, void * buf);
void fillBuff(char fill, void * buf);
shape createShape(unsigned long long n);
void expandShape(shape * shap,unsigned long long n);
void destroyShape(shape shap);
void addArcToShape(shape * shap, float X, float Y, float phase, float radius, float angle, long long n, char flip);
void * drawLine(void * line);