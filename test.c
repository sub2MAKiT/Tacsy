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
int main() {
    int fd = open("tacsy.buff", O_RDWR);
    struct stat st;
    fstat(fd, &st);

    // Map the file into memory (no copy!)
    void *buf = mmap(NULL, st.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (buf == MAP_FAILED) {
        printf("mmap\n");
        return 1;
    }

    // Write to the buffer (e.g., 4 bytes)
    // ((char*)buf)[0] = 'A';
    // ((char*)buf)[1] = 'B';

    int totInd = 0;

    for(float i = 0; i < height; i++) {
        for(float j = 0; j < width; j++)
            ((char*)buf)[totInd++] = determineCol(j/width,i/height);
        ((char*)buf)[totInd++] = '\n';
    }



    // Clean up
    munmap(buf, st.st_size);
    close(fd);
    return 0;
}
