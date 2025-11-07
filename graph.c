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

    int input = 0;

    if(argc > 1)
       input = atoi(argv[1]);

    int totInd = 0;

    allShapes = malloc(1);

    sizeOfAllShapes = 0;

    unsigned long long eyeL = createShape();

    unsigned long long eyeR = createShape();

    unsigned long long mouthL = createShape();
    unsigned long long mouthR = createShape();


    // unsigned long long brick = createShape();

    setShapeColour(eyeL,255,0,0,100);

    setShapeColour(eyeR,0,255,0,200);

    setShapeColour(mouthL,0,0,255,70);
    setShapeColour(mouthR,170,160,8,150);

    

    unsigned long long brick[6];

    for(int i = 0; i < 6; i++) {
        srand(input+i);

        brick[i] = createShape();

        // printf("randomTest: %f %d\n",(double)((float)rand())/RAND_MAX,(int)(((float)rand())/RAND_MAX*255));
    
        addPointToShape(brick[i],(double)((float)rand())/RAND_MAX,(double)((float)rand())/RAND_MAX);
        addPointToShape(brick[i],(double)((float)rand())/RAND_MAX,(double)((float)rand())/RAND_MAX);
        addPointToShape(brick[i],(double)((float)rand())/RAND_MAX,(double)((float)rand())/RAND_MAX);
        addPointToShape(brick[i],(double)((float)rand())/RAND_MAX,(double)((float)rand())/RAND_MAX);

        setShapeColour(brick[i],(int)(((float)rand())/RAND_MAX*255),(int)(((float)rand())/RAND_MAX*255),(int)(((float)rand())/RAND_MAX*255),(int)(((float)rand())/RAND_MAX*255));
    }
    

    // setShapeColour(Brick0,170,160,8,150);

    // setShapeColour(brick,255,100,100,100);

    // addPointToShape(brick,0.25,0.25);
    // addPointToShape(brick,0.25,0.75);
    // addPointToShape(brick,0.75,0.75);
    // addPointToShape(brick,0.75,0.25);

    // addArcToShape(brick, 0.1, 0.1,concernThroughHornyToAngyRatio, 0.007, 4.7, 20,0);

    addArcToShape(eyeL, 0.2, 0.2,-0.4, 0.15, 4.7, 20,0);
    addArcToShape(eyeR, 0.8, 0.2,-0.4, 0.15, 4.7, 20,1);

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
