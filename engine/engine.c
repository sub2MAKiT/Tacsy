#include "engine.h"


char checkLine(float p0X, float p0Y, float p1X, float p1Y, float pointX, float pointY) {


    if(pointY<(p1Y > p0Y?p0Y:p1Y) || pointY>(p1Y > p0Y?p1Y:p0Y))
        return 0;

    if(p0X < pointX && p1X < pointX)
        return 1;

    if(p0X > pointX && p1X > pointX)
        return 0;

    if((p0X < p1X && p0Y < p1Y) || (p0X > p1X && p0Y > p1Y))
        if((p1Y-p0Y)/(p1X-p0X) * pointX + p0Y-(p1Y-p0Y)/(p1X-p0X)*p0X < pointY)
            return 0;

    if((p0X > p1X && p0Y < p1Y) || (p0X < p1X && p0Y > p1Y))
        if((p1Y-p0Y)/(p1X-p0X) * pointX + p0Y-(p1Y-p0Y)/(p1X-p0X)*p0X > pointY)
            return 0;

    return 1;
}

char checkShape(float * shapeX, float * shapeY, float pointX, float pointY, long long sizeOfShape) {

    int crosses = 0;

    for(int i = 0; i < sizeOfShape;i++)
        crosses += checkLine(shapeX[i], shapeY[i], shapeX[(i+1)%sizeOfShape], shapeY[(i+1)%sizeOfShape], pointX, pointY);

    return crosses%2;

}

// char determineCol(float x,float y) {

//     if(checkShape(triangleX,triangleY,x,y,16))
//         return '1';
//     else
//         return '0';

// }

void checkBoundaries(shape * shap) {
    shap->HY = 0.0;
    shap->LY = 1.0;
    shap->HX = 0.0;
    shap->LX = 1.0;

    for(int i = 0; i < shap->sizeOfShape; i++) {
        shap->HY = shap->Y[i] > shap->HY?shap->Y[i]:shap->HY;
        shap->LY = shap->Y[i] < shap->LY?shap->Y[i]:shap->LY;
        shap->HX = shap->X[i] > shap->HX?shap->X[i]:shap->HX;
        shap->LX = shap->X[i] < shap->LX?shap->X[i]:shap->LX;
    }
    return;
}

void * drawLine(void * inp) {

    lineD * line = inp;
    for(int i = 0; i < line->packSize; i++)
        if( !(((float)(line->lineDex*line->packSize + i))/height > line->shap.HY || ((float)(line->lineDex*line->packSize + i))/height < line->shap.LY) )
            for(int j = 0; j < width; j++)
                if( !(((float)j)/width > line->shap.HX || ((float)j)/width < line->shap.LX) )
                    line->line[j+i*(width+1)] = checkShape(line->shap.X,line->shap.Y,((float)j)/width,((float)(line->lineDex*line->packSize + i))/height,line->shap.sizeOfShape)?'1':line->line[j+i*(width+1)];
}


void drawShape(shape shap, void * buf) {
    int totInd = 0;

    pthread_t threads[height];
    lineD tempLine[height];

    int packsize = 20;

    for(int i = 0; i < height/packsize; i++) {
        tempLine[i].shap = shap;
        tempLine[i].line = &(((char*)buf)[(width+1)*i*packsize]);
        tempLine[i].lineDex = i;
        tempLine[i].packSize = packsize;


        // drawLine(&tempLine[i]);

        int rc = pthread_create(&threads[i], NULL, drawLine,
                            (void*)&tempLine[i]);
        if (rc) {
            printf("Error: unable to create thread, %d\n",
                   rc);
            exit(-1);
        }
    }

    for (int i = 0; i < height; ++i) {
        pthread_join(threads[i], NULL);
    }

}

void fillBuff(char fill, void * buf) {
    int totInd = 0;
    for(float i = 0; i < height; i++) {
        for(float j = 0; j < width; j++)
            ((char*)buf)[totInd++] = fill;
        ((char*)buf)[totInd++] = '\n';
    }
}

shape createShape(unsigned long long n) {
    shape shap;

    shap.sizeOfShape = n;
    shap.X = malloc(n*sizeof(float));
    shap.Y = malloc(n*sizeof(float));

    checkBoundaries(&shap);



    return shap;
}

void expandShape(shape * shap,unsigned long long n) {

    shap->sizeOfShape = shap->sizeOfShape+n;

    if(n < shap->sizeOfShape) {
        shap->X = realloc(shap->X,shap->sizeOfShape*sizeof(float));
        shap->Y = realloc(shap->Y,shap->sizeOfShape*sizeof(float));
    } else {
        shap->X = malloc(shap->sizeOfShape*sizeof(float));
        shap->Y = malloc(shap->sizeOfShape*sizeof(float));
    }
    return;
}

void destroyShape(shape shap) {
    free(shap.X);
    free(shap.Y);
    return;
}

void addArcToShape(shape * shap, float X, float Y, float phase, float radius, float angle, long long n, char flip) {

    long long prevSize = shap->sizeOfShape;

    expandShape(shap, n);

    for(int i = 0; i < n; i++) {
        shap->X[prevSize+i] = radius * cos(phase + angle/n*i)*(flip?-1:1) + X;
        shap->Y[prevSize+i] =  radius * sin(phase + angle/n*i) + Y;
    }
    checkBoundaries(shap);
}

void addPointToShape(shape * shap, float X, float Y) {

    long long prevSize = shap->sizeOfShape;

    expandShape(shap, 1);

    shap->X[prevSize] = X;
    shap->Y[prevSize] =  Y;

    checkBoundaries(shap);
}

