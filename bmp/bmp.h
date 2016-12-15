#ifndef __BMP_H
#define __BMP_H

typedef unsigned long DWORD;
typedef unsigned char BYTE;
typedef unsigned short WORD;

typedef struct BIT_MAP_HEAD_INFO_S{
	WORD bfType; 
	DWORD bfSize;
	WORD bfReserved1;
	WORD bfReserved2;
	DWORD bfOffBits;
}BMP_HEAD_INFO_S;

typedef struct BIT_MAP_INFO_S{
	DWORD 	biSize;		//	head + info size
	DWORD 	biWidth;		// image width
	DWORD 	biHeight;		// image height
	WORD 	biPlanes;	
	WORD 	biBitCount;	//	pix bit count
	DWORD 	biCompression;	// wether compression
	DWORD 	biSizeImage;	// image size
	DWORD 	biXPelPerMeter;
	DWORD 	biYPelPerMeter;
	DWORD 	bitClrUsed;
	DWORD 	biImportant;
}BMP_BIT_MAP_INFO_S;

#endif

