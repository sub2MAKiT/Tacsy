#include "engine.h"

shape * allShapes;
unsigned long long sizeOfAllShapes;

// RGBAd convertToRGBAd(RGBA col) {
//     RGBAd new;

//     new.R = (float)(col.R)/255;
//     new.G = (float)(col.G)/255;
//     new.B = (float)(col.B)/255;
//     new.A = (float)(col.A)/255;

//     return new;
// }

// RGBA convertToRGBA(RGBAd col) {
//     RGBA new;

//     new.R = col.R*255;
//     new.G = col.G*255;
//     new.B = col.B*255;
//     new.A = col.A*255;

//     return new;
// }


RGBA mixColours(RGBA colA, RGBA colB) {
    RGBA mixed;

    mixed.A = ((float)(colA.A)/255 + (1-(float)(colA.A)/255) * (float)(colB.A)/255)*255;
    mixed.R = ( (float)(colA.R)/255 * (float)(colA.A)/255 / ((float)(colA.A)/255+ (float)(colB.A)/255) + (float)(colB.R)/255 * (float)(colB.A)/255 / ((float)(colA.A)/255+ (float)(colB.A)/255)  ) * 255;
    mixed.G = ( (float)(colA.G)/255 * (float)(colA.A)/255 / ((float)(colA.A)/255+ (float)(colB.A)/255) + (float)(colB.G)/255 * (float)(colB.A)/255 / ((float)(colA.A)/255+ (float)(colB.A)/255)  ) * 255;
    mixed.B = ( (float)(colA.B)/255 * (float)(colA.A)/255 / ((float)(colA.A)/255+ (float)(colB.A)/255) + (float)(colB.B)/255 * (float)(colB.A)/255 / ((float)(colA.A)/255+ (float)(colB.A)/255)  ) * 255;
    return mixed;
}

char checkLine(float p0X, float p0Y, float p1X, float p1Y, float pointX, float pointY) {

    if((pointY==p0Y && pointX > p0X) || (pointY==p1Y && pointX > p1X))
        return 3;

    if(pointY<=(p1Y > p0Y?p0Y:p1Y) || pointY>=(p1Y > p0Y?p1Y:p0Y))
        return 0;

    if(p0X < pointX && p1X < pointX)
        return 1;

    if(p0X >= pointX && p1X >= pointX)
        return 0;

    if((p0X <= p1X && p0Y <= p1Y) || (p0X >= p1X && p0Y >= p1Y))
        if((p1Y-p0Y)/(p1X-p0X) * pointX + p0Y-(p1Y-p0Y)/(p1X-p0X)*p0X <= pointY)
            return 0;

    if((p0X >= p1X && p0Y <= p1Y) || (p0X <= p1X && p0Y >= p1Y))
        if((p1Y-p0Y)/(p1X-p0X) * pointX + p0Y-(p1Y-p0Y)/(p1X-p0X)*p0X >= pointY)
            return 0;

    return 1;
}

char checkShape(float * shapeX, float * shapeY, float pointX, float pointY, long long sizeOfShape) {

    int crosses = 0;

    for(int i = 0; i < sizeOfShape;i += checkLine(shapeX[i], shapeY[i], shapeX[(i+1)%sizeOfShape], shapeY[(i+1)%sizeOfShape], pointX, pointY)/2+1)
        crosses += checkLine(shapeX[i], shapeY[i], shapeX[(i+1)%sizeOfShape], shapeY[(i+1)%sizeOfShape], pointX, pointY);

    return crosses%2;

}

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
                    if(checkShape(line->shap.X,line->shap.Y,((float)j)/width,((float)(line->lineDex*line->packSize + i))/height,line->shap.sizeOfShape))
                        line->line[j+i*width] = mixColours(line->line[j+i*width],line->col);
}


void drawShapes(void * buf) {
    int totInd = 0;
    pthread_t threads[height];
    lineD tempLine[height];

    int packsize = 20;
    for(int shpindex = 0; shpindex < sizeOfAllShapes; shpindex++) {
        for(int i = 0; i < height/packsize; i++) {
            tempLine[i].shap = allShapes[shpindex];
            tempLine[i].line = &(((RGBA*)buf)[width*i*packsize]);
            tempLine[i].lineDex = i;
            tempLine[i].packSize = packsize;
            tempLine[i].col = allShapes[shpindex].col;

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



}

void fillBuff(RGBA fill, void * buf) {
    int totInd = 0;
    for(float i = 0; i < height; i++) {
        for(float j = 0; j < width; j++)
            ((RGBA*)buf)[totInd++] = fill;
    }
}

unsigned long long createShape() {
    sizeOfAllShapes += 1;
    allShapes = realloc(allShapes,sizeOfAllShapes * sizeof(shape));


    allShapes[sizeOfAllShapes-1].sizeOfShape = 0;
    allShapes[sizeOfAllShapes-1].X = malloc(1);
    allShapes[sizeOfAllShapes-1].Y = malloc(1);

    allShapes[sizeOfAllShapes-1].col.R = 255;
    allShapes[sizeOfAllShapes-1].col.G = 255;
    allShapes[sizeOfAllShapes-1].col.B = 255;
    allShapes[sizeOfAllShapes-1].col.A = 255;

    checkBoundaries(&allShapes[sizeOfAllShapes-1]);



    return sizeOfAllShapes-1;
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

void destroyShapes() {
    for(int i = 0; i < sizeOfAllShapes; i++) {
        free(allShapes[i].X);
        free(allShapes[i].Y);
    }

    free(allShapes);
    return;
}

void addArcToShape(unsigned long long shpindex, float X, float Y, float phase, float radius, float angle, long long n, char flip) {

    long long prevSize = allShapes[shpindex].sizeOfShape;

    expandShape(&allShapes[shpindex], n);

    for(int i = 0; i < n; i++) {
        allShapes[shpindex].X[prevSize+i] = radius * cos(phase + angle/n*i)*(flip?-1:1) + X;
        allShapes[shpindex].Y[prevSize+i] =  radius * sin(phase + angle/n*i) + Y;
    }
    checkBoundaries(&allShapes[shpindex]);
}

void addPointToShape(unsigned long long shpindex, float X, float Y) {

    long long prevSize = allShapes[shpindex].sizeOfShape;

    expandShape(&allShapes[shpindex], 1);

    allShapes[shpindex].X[prevSize] = X;
    allShapes[shpindex].Y[prevSize] =  Y;

    checkBoundaries(&allShapes[shpindex]);
}

void setShapeColour(unsigned long long shpindex, char R, char G, char B, char A) {

    allShapes[shpindex].col.R = R;
    allShapes[shpindex].col.G = G;
    allShapes[shpindex].col.B = B;
    allShapes[shpindex].col.A = A;


}

