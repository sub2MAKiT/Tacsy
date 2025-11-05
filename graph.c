#include "engine/engine.h"
// #include <perror.h>



float triangleX[] = {0.1,0.2,0.5,0.8,0.9,0.9,0.6,0.9,0.9,0.8,0.5,0.2,0.1,0.1,0.4,0.1};
float triangleY[] = {0.9,0.9,0.6,0.9,0.9,0.8,0.5,0.2,0.1,0.1,0.4,0.1,0.1,0.2,0.5,0.8};



int main(int argc, char **argv) {
    int fd = open("tacsy.buff", O_RDWR);
    FILE *fptr;
    fptr = fopen("tacsyRGBA.buff", "w");
    // struct stat st;
    // fstat(fd, &st);
    void *buf = malloc(width*height*sizeof(RGBA));//mmap(NULL, st.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    float concernThroughHornyToAngyRatio = -0.4;

    if(argc > 1)
       concernThroughHornyToAngyRatio = atof(argv[1]);

    int totInd = 0;

    allShapes = malloc(1);

    sizeOfAllShapes = 0;


    unsigned long long eyeL = createShape();

    unsigned long long eyeR = createShape();

    unsigned long long mouthL = createShape();
    unsigned long long mouthR = createShape();

    setShapeColour(eyeL,200,0,100,255);

    setShapeColour(eyeR,100,0,200,255);

    setShapeColour(mouthL,255,100,0,100);
    setShapeColour(mouthR,100,0,255,100);


    addArcToShape(eyeL, 0.2, 0.2,concernThroughHornyToAngyRatio, 0.15, 4.7, 20,0);
    addArcToShape(eyeR, 0.8, 0.2,concernThroughHornyToAngyRatio, 0.15, 4.7, 20,1);

    float arcLen = 4.2;

    addArcToShape(mouthL, 0.35, 0.6, -1, 0.15, arcLen, 20,1);
    addArcToShape(mouthL, 0.35, 0.6, 0, 0.19, arcLen, 20,0);

    addArcToShape(mouthR, 0.65, 0.6, 0, 0.19, arcLen, 20,1);
    addArcToShape(mouthR, 0.65, 0.6, -1, 0.15, arcLen, 20,0);

    RGBA blank;
    blank.R = 0;
    blank.G = 0;
    blank.B = 0;
    blank.A = 0;

    fillBuff(blank,buf);
    drawShapes(buf);


    // Clean up
    destroyShapes();
    // munmap(buf, st.st_size);
    fwrite(buf, sizeof(RGBA),height*width,fptr);
    free(buf);
    fclose(fptr);
    // close(fd);
    return 0;
}
