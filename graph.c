#include "engine/engine.h"
// #include <perror.h>



float triangleX[] = {0.1,0.2,0.5,0.8,0.9,0.9,0.6,0.9,0.9,0.8,0.5,0.2,0.1,0.1,0.4,0.1};
float triangleY[] = {0.9,0.9,0.6,0.9,0.9,0.8,0.5,0.2,0.1,0.1,0.4,0.1,0.1,0.2,0.5,0.8};



int main(int argc, char **argv) {
    int fd = open("tacsy.buff", O_RDWR);
    struct stat st;
    fstat(fd, &st);
    void *buf = mmap(NULL, st.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    float concernThroughHornyToAngyRatio = -0.4;

    if(argc > 1)
       concernThroughHornyToAngyRatio = atof(argv[1]);

    int totInd = 0;


    shape eyeL; // = createShape(0);
    shape eyeR; // = createShape(0);

    shape mouthL; // = createShape(0);
    shape mouthR; // = createShape(0);

    eyeL.sizeOfShape = 0;
    eyeR.sizeOfShape = 0;

    mouthL.sizeOfShape = 0;
    mouthR.sizeOfShape = 0;

    // from -1.5 to 1.5


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
    close(fd);
    return 0;
}
