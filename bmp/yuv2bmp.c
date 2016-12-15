/*
	说明：将yuv422 plat格式的图片转换为8位的bmp图片
	参数：
		argv[1] ： bmp文件名
		argv[2]	:	 yuv文件名
*/
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "bmp.h"

//创建调色板
//B=G=R 灰度图
int creatBitmap(int bitmapSize, char * bitmap)
{
		int i;
		for (i=0; i<256; i++) {
			bitmap[i*4] = i; 	//B
			bitmap[i*4+1] = i;	//G
			bitmap[i*4+2] = i;	//R
			bitmap[i*4+3] = 0;	//A	
		}
		return 0;
}

/* create bmp file */
int main(int argc, char ** argv)
{
		int fd = open(argv[1], O_WRONLY | O_CREAT);
		if (fd < 0) {
			printf("open file failed : %s\n", strerror(errno));
			return -1;
		}

		BMP_HEAD_INFO_S stHeadInfo;
		stHeadInfo.bfType = 0x4D42; // "BM"
		stHeadInfo.bfSize = 102454; //352*288+54+256*4
		stHeadInfo.bfReserved1 = 0;
		stHeadInfo.bfReserved2 = 0;
		stHeadInfo.bfOffBits = 54+256*4;

		lseek(fd, 0, SEEK_SET);
		ssize_t size = write(fd, &stHeadInfo.bfType, 2);
		lseek(fd, 0x02, SEEK_SET);
		size = write(fd, &stHeadInfo.bfSize, 4);
		lseek(fd, 0x06, SEEK_SET);
		size = write(fd, &stHeadInfo.bfReserved1, 2);
		lseek(fd, 0x08, SEEK_SET);
		size = write(fd, &stHeadInfo.bfReserved2, 2);
		lseek(fd, 0x0A, SEEK_SET);
		size = write(fd, &stHeadInfo.bfOffBits, 4);
	
		BMP_BIT_MAP_INFO_S stBitmapInfo;
		stBitmapInfo.biSize 		= 40; //54
		stBitmapInfo.biWidth 		= 352;
		stBitmapInfo.biHeight 		= 288;
		stBitmapInfo.biPlanes 		= 1;
		stBitmapInfo.biBitCount 	= 8;
		stBitmapInfo.biCompression	= 0;
		stBitmapInfo.biSizeImage	= 0; //352*288;
		stBitmapInfo.biXPelPerMeter	= 0;
		stBitmapInfo.biYPelPerMeter	= 0;
		stBitmapInfo.bitClrUsed		= 256;	 // 0;
		stBitmapInfo.biImportant	= 256; //0;

		lseek(fd, 0x0E, SEEK_SET);
		size = write(fd, &stBitmapInfo, sizeof(stBitmapInfo));
		lseek(fd, 0x32, SEEK_SET);
		size = write(fd, &stBitmapInfo.biImportant, 4);
		printf("size = %d, seek = %#x\n", size, lseek(fd, 0x0, SEEK_CUR));

		char * bitmap = (char *)malloc(256*4);
		if (bitmap == NULL){
			printf("malloc bit map failed! : %s\n", strerror(errno) );
			close(fd);
			fd = -1;
			return -1;
		}
		if (creatBitmap(256, bitmap) <0 ) {
			printf("create bit map failed! : %s\n", strerror(errno) );
			free(bitmap);
			bitmap = NULL;
			if (fd >0 ) close(fd);
			return -1;
		}
		
		lseek(fd, 0x36, SEEK_SET);
		size = write(fd, bitmap, 256*4);
		free(bitmap);
		bitmap = NULL;

		char * yuv_data = (char*)malloc(352*288);
		if (yuv_data == NULL) {
			printf(" yuv_data malloc failed! %s \n", strerror(errno));
			if (fd > 0) close(fd);
			return -1;
		}

		int fd_yuv = open(argv[2], O_RDONLY);
		size = read(fd_yuv, yuv_data, 352*288);
		close(fd_yuv);
		
		char * bmp_data = (char*)malloc(352*288);
		if (bmp_data == NULL) {
			printf(" bmp_data malloc failed! %s \n", strerror(errno));
			if (yuv_data != NULL) {
					free(yuv_data);
					yuv_data = NULL;
			}
			if (fd_yuv > 0) {
				close(fd_yuv);
				fd_yuv = -1;
			}
			if (fd>0) {
				close(fd);
				fd = -1;
			}
			return -1;
		}
		int i,j;
		for (i=287; i>=0; i--) {
			for (j=0; j<352; j++) {
				bmp_data[i*352+j] = yuv_data[(287-i)*352+j];
				//printf("%d, %d,      %d, %d\n", i, j, i*352+j, (288-i)*352+j);
			}
		}
		printf("before write\n");
		lseek(fd, 0x436, SEEK_SET);
		size = write(fd, bmp_data, 352*288);
		if (fd > 0) {
			close(fd);
			fd = -1;
		}
		
		printf("before free\n");	
		if (bmp_data != NULL) {
				free(bmp_data);
				bmp_data = NULL;
		}
		printf(" free bmp\n");
		if (yuv_data != NULL){
				free(yuv_data);
				yuv_data = NULL;
		}
		printf(" free yuv\n");

		printf("DONE!!\n");


		return 0;
}

