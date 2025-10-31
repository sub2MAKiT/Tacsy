#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
// #include <perror.h>

#define height 300
#define width 400

#define PI 3.14159265

typedef struct shapeStruct {
    unsigned long long sizeOfShape;
    float * X;
    float * Y;
} shape;

float triangleX[] = {0.1,0.2,0.5,0.8,0.9,0.9,0.6,0.9,0.9,0.8,0.5,0.2,0.1,0.1,0.4,0.1};
float triangleY[] = {0.9,0.9,0.6,0.9,0.9,0.8,0.5,0.2,0.1,0.1,0.4,0.1,0.1,0.2,0.5,0.8};





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

char determineCol(float x,float y) {

    if(checkShape(triangleX,triangleY,x,y,16))
        return '1';
    else
        return '0';

}


void drawShape(shape shap, void * buf) {
    int totInd = 0;
    for(float i = 0; i < height; i++) {
        for(float j = 0; j < width; j++)
            ((char*)buf)[totInd++] = checkShape(shap.X,shap.Y,j/width,i/height,shap.sizeOfShape)?'1':((char*)buf)[totInd];
        ((char*)buf)[totInd++] = '\n';
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
}

int main() {

    const char *shm_name = "/tacsy.buff";
    int shmid = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
    if (shmid == -1) {
        perror("shm_open");
        exit(1);
    }
    int fd = open(shm_name, O_RDWR);
    ftruncate(shmid, 300*401);
    close(fd);

    struct stat st;
    fstat(shmid, &st);
    void *buf = mmap(NULL, st.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, shmid, 0);
    if (buf == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }


    shape eyeL; // = createShape(0);
    shape eyeR; // = createShape(0);

    shape mouthL; // = createShape(0);
    shape mouthR; // = createShape(0);

    eyeL.sizeOfShape = 0;
    eyeR.sizeOfShape = 0;

    mouthL.sizeOfShape = 0;
    mouthR.sizeOfShape = 0;

    // from -1.5 to 1.5

    float concernThroughHornyToAngyRatio = -0.2;

    addArcToShape(&eyeL, 0.2, 0.2,concernThroughHornyToAngyRatio, 0.15, 4.7, 20,0);
    addArcToShape(&eyeR, 0.8, 0.2,concernThroughHornyToAngyRatio, 0.15, 4.7, 20,1);

    float arcLen = 4.2;

    addArcToShape(&mouthL, 0.35, 0.6, -1, 0.15, arcLen, 20,1);
    addArcToShape(&mouthL, 0.35, 0.6, 0, 0.19, arcLen, 20,0);

    addArcToShape(&mouthR, 0.65, 0.6, 0, 0.19, arcLen, 20,1);
    addArcToShape(&mouthR, 0.65, 0.6, -1, 0.15, arcLen, 20,0);
    // for(int i = 0; i < 16; i++) {
        // eye.X[i] = triangleX[i];
        // eye.Y[i] = triangleY[i];
    // }

    fillBuff('0',buf);
    drawShape(eyeL,buf);
    drawShape(eyeR,buf);
    drawShape(mouthL,buf);
    drawShape(mouthR,buf);


    // Clean up
    destroyShape(eyeL);
    destroyShape(eyeR);
    destroyShape(mouthL);
    destroyShape(mouthR);
    munmap(buf, st.st_size);
    close(shmid);
    shm_unlink(shm_name);
    // close(fd);
    return 0;
}
