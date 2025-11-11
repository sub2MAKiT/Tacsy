#include "engine/engine.h"
// #include <perror.h>

float triangleX[] = {0.1,0.2,0.5,0.8,0.9,0.9,0.6,0.9,0.9,0.8,0.5,0.2,0.1,0.1,0.4,0.1};
float triangleY[] = {0.9,0.9,0.6,0.9,0.9,0.8,0.5,0.2,0.1,0.1,0.4,0.1,0.1,0.2,0.5,0.8};


// RGBA RGBAToHSVA(RGBA col) {
//     RGBA retVal;
//     float r = (float)(retVal).R/255;
//     float g = (float)(retVal).G/255;
//     float b = (float)(retVal).B/255;
//     float maxc = fmax(fmax(r, g), b);
//     float minc = fmin(fmin(r, g), b);
//     float v = maxc;
//     if(minc == maxc)
//         return (RGBA){0, 0, v*255,col.A};
//     float s = (maxc-minc) / maxc;
//     float rc = (maxc-r) / (maxc-minc);
//     float gc = (maxc-g) / (maxc-minc);
//     float bc = (maxc-b) / (maxc-minc);
//     float h;
//     if(r == maxc)
//         h = 0.0+bc-gc;
//     else if(g == maxc)
//         h = 2.0+rc-bc;
//     else
//         h = 4.0+gc-rc;
//     h = (h/6.0);
//     return (RGBA){h *255, s *255, v*255,col.A};
// }

float input;

RGBA rainbowL(float X, float Y) {
    RGBA rainbow[6] = {(RGBA){255,0,0,255},(RGBA){250,130,0,255},(RGBA){200,200,0,255},(RGBA){0,255,0,255},(RGBA){0,0,255,255},(RGBA){150,0,255,255}};

    return rainbow[(unsigned char)((X+Y*-3.8-0.50)*6)%6];
}

RGBA rainbowR(float X, float Y) {
    RGBA rainbow[6] = {(RGBA){255,0,0,255},(RGBA){250,130,0,255},(RGBA){200,200,0,255},(RGBA){0,255,0,255},(RGBA){0,0,255,255},(RGBA){150,0,255,255}};

    return rainbow[(unsigned char)((X+Y*3.8-0.50)*6)%6];
}


RGBA rainbowM(float X, float Y) {
    RGBA rainbow[6] = {(RGBA){255,0,0,255},(RGBA){250,130,0,255},(RGBA){200,200,0,255},(RGBA){0,255,0,255},(RGBA){0,0,255,255},(RGBA){150,0,255,255}};

    return rainbow[(unsigned char)((Y+X-0.2)/2*14)%6];
}


int main(int argc, char **argv) {
    FILE *fptr;
    fptr = fopen("tacsyRGBA.buff", "w");
    void *buf = malloc(width*height*sizeof(RGBA));

    float input = 0.0;

    if(argc > 1)
       input = atof(argv[1]);

    int totInd = 0;

    allShapes = malloc(1);

    sizeOfAllShapes = 0;

    // RGBA testCol = RGBAToHSVA((RGBA){255,255,255,255});

    // printf("test: %d %d %d %d\n",testCol.R,testCol.G,testCol.B,testCol.A);

    unsigned long long eyeL = createShape();

    unsigned long long eyeR = createShape();

    unsigned long long mouthL = createShape();
    unsigned long long mouthR = createShape();

    unsigned long long sparkle0 = createShape();
    unsigned long long sparkle1 = createShape();
    unsigned long long sparkle2 = createShape();



    // unsigned long long brick = createShape();

    // addPointToShape(brick,0,0);
    // addPointToShape(brick,0,1);
    // addPointToShape(brick,1,1);
    // addPointToShape(brick,1,0);

    setShapeColour(sparkle0,(RGBA){255,255,255,200});
    setShapeColour(sparkle1,(RGBA){255,255,255,200});
    setShapeColour(sparkle2,(RGBA){255,255,255,200});

    LGBT LGBT0 = (LGBT){1.0,0.0,0.0,1.0};
    LGBT LGBT1 = (LGBT){0.0,1.0,0.0,1.0};
    LGBT LGBT2 = (LGBT){0.0,0.0,1.0,1.0};
    LGBT LGBT3 = (LGBT){1.0,0.0,1.0,1.0};


    RGBA testCol0 = LGBTtoRGBA(LGBT0);
    RGBA testCol1 = LGBTtoRGBA(LGBT1);
    RGBA testCol2 = LGBTtoRGBA(LGBT2);
    RGBA testCol3 = LGBTtoRGBA(LGBT3);

    setShapeColour(eyeL,testCol0);
    setShapeColour(eyeR,testCol1);

    setShapeColour(mouthL,testCol2);
    setShapeColour(mouthR,testCol3);

    // setShapeCustomColour(eyeL,rainbowL);
    // setShapeCustomColour(eyeR,rainbowR);
    // setShapeCustomColour(mouthL,rainbowM);
    // setShapeCustomColour(mouthR,rainbowM);


    // unsigned long long testForLine = createShape();

    // addPointToShape(testForLine,0.1,0.1);
    // addPointToShape(testForLine,0.3,0.1);
    // addPointToShape(testForLine,0.5,0.3);
    // addPointToShape(testForLine,0.2,0.6);
    // addPointToShape(testForLine,0.5,0.9);
    // addPointToShape(testForLine,0.1,0.9);

    // setShapeColour(testForLine,255,255,255,70);

    // unsigned long long brick[6];

    // for(int i = 0; i < 6; i++) {
    //     srand(input+i);

    //     brick[i] = createShape();

    //     // printf("randomTest: %f %d\n",(double)((float)rand())/RAND_MAX,(int)(((float)rand())/RAND_MAX*255));
    
    //     addPointToShape(brick[i],(double)((float)rand())/RAND_MAX,(double)((float)rand())/RAND_MAX);
    //     addPointToShape(brick[i],(double)((float)rand())/RAND_MAX,(double)((float)rand())/RAND_MAX);
    //     addPointToShape(brick[i],(double)((float)rand())/RAND_MAX,(double)((float)rand())/RAND_MAX);
    //     addPointToShape(brick[i],(double)((float)rand())/RAND_MAX,(double)((float)rand())/RAND_MAX);

    //     setShapeColour(brick[i],(int)(((float)rand())/RAND_MAX*255),(int)(((float)rand())/RAND_MAX*255),(int)(((float)rand())/RAND_MAX*255),(int)(((float)rand())/RAND_MAX*255));
    // }
    
    

    // setShapeColour(Brick0,170,160,8,150);

    // setShapeColour(brick,255,100,100,100);

    // addPointToShape(brick,0.25,0.25);
    // addPointToShape(brick,0.25,0.75);
    // addPointToShape(brick,0.75,0.75);
    // addPointToShape(brick,0.75,0.25);

    // addArcToShape(brick, 0.1, 0.1,concernThroughHornyToAngyRatio, 0.007, 4.7, 20,0);
    addArcToShape(sparkle0, 0.12, 0.14,0, 0.04, PI*2, 40,0);
    addArcToShape(sparkle1, 0.2, 0.15,0, 0.02, PI*2, 40,0);
    addArcToShape(sparkle2, 0.08, 0.18,0, 0.01, PI*2, 40,0);

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
    blank.A = 255;

    fillBuff(blank,buf);
    drawShapes(buf);
    referenceGrid(buf);


    // Clean up
    destroyShapes();
    // munmap(buf, st.st_size);
    fwrite(buf, sizeof(RGBA),height*width,fptr);
    free(buf);
    fclose(fptr);
    // close(fd);
    return 0;
}
