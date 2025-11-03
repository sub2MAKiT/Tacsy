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


    shape star;
    star.sizeOfShape = 0;



    // addPointToShape(&star, 0.5, 0.0);
    // addPointToShape(&star, 0.6, 0.25);
    // addPointToShape(&star, 1.0, 0.25);
    // addPointToShape(&star, 0.7, 0.7);
    // addPointToShape(&star, 0.7, 1.0);

    // addPointToShape(&star, 0.5, 0.7);

    // addPointToShape(&star, 0.3, 1.0);
    // addPointToShape(&star, 0.3, 0.7);
    // addPointToShape(&star, 0.0, 0.25);
    // addPointToShape(&star, 0.4, 0.25);
    // addPointToShape(&star, 0.5, 0.0);

    double pi = 3.14159265;

    addArcToShape(&star, 0.5, 0.5,0.0+pi*2/5 * 0, 0.5, 1.0, 1,0);
    addArcToShape(&star, 0.5, 0.5,pi/5+pi*2/5 * 0, 0.2, 1.0, 1,0);
    addArcToShape(&star, 0.5, 0.5,0.0+pi*2/5 * 1, 0.5, 1.0, 1,0);
    addArcToShape(&star, 0.5, 0.5,pi/5+pi*2/5 * 1, 0.2, 1.0, 1,0);
    addArcToShape(&star, 0.5, 0.5,0.0+pi*2/5 * 2, 0.5, 1.0, 1,0);
    addArcToShape(&star, 0.5, 0.5,pi/5+pi*2/5 * 2, 0.2, 1.0, 1,0);
    addArcToShape(&star, 0.5, 0.5,0.0+pi*2/5 * 3, 0.5, 1.0, 1,0);
    addArcToShape(&star, 0.5, 0.5,pi/5+pi*2/5 * 3, 0.2, 1.0, 1,0);
    addArcToShape(&star, 0.5, 0.5,0.0+pi*2/5 * 4, 0.5, 1.0, 1,0);
    addArcToShape(&star, 0.5, 0.5,pi/5+pi*2/5 * 4, 0.2, 1.0, 1,0);


    float arcLen = 4.2;



    fillBuff('0',buf);
    drawShape(star,buf);


    destroyShape(star);


    munmap(buf, st.st_size);
    close(fd);
    return 0;
}
