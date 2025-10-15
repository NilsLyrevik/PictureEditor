#ifndef LOADIMAGE_H
#define LOADIMAGE_H

unsigned char* loadimage(const char* filename, int& width, int& height, int& channels);
void freeimage(unsigned char* data);
#endif
