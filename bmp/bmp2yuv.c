/*
	说明：将bmp文件转换为yuv420plat 格式的文件
	参数：
		argv[1] : bmp文件名
		argv[2] :
*/
#include <stdio.h>

#include <sys/types.h> //open
#include <sys/stat.h> //open
#include <fcntl.h> //open
#include <unistd.h> //lseek
#include <string.h> //strerron
#include <errno.h> //errno
#include <stdlib.h> // malloc free

#include "bmp.h"

int main(int argc, char ** argv)
{
		/* open bmp file */
		int fd = open(argv[1], O_RDONLY);
		if (fd < 0 ) {
			printf("%s open fialed!\n", argv[1]);
			return -1;
		}

		printf("sizeof BMP_HEAD : %d\n", sizeof(struct BMP_HEAD));
		printf("sizeof BIT_MAP_HEAD_INFO_S : %d\n", sizeof(BMP_HEAD_INFO_S));

		printf("BMP HEAD INFO\n");

		struct BMP_HEAD bmp_head;

		/* read bmp file head */
		lseek(fd, 0, SEEK_SET);
		size_t  size = read(fd, &bmp_head.bfType, 2);
		if ( size<0 ) {
			printf("%s\n", strerror(errno));
			close(fd);
			return -1;
		}

		lseek(fd, 0x02, SEEK_SET);
		size = read(fd, &bmp_head.bfSize, 4);
		if ( size<0 ) {
			printf("%s\n", strerror(errno));
			close(fd);
			return -1;
		}
		
		lseek(fd, 0x0a, SEEK_SET);
		size = read(fd, &bmp_head.bfOffBits, 4);
		if ( size<0 ) {
			printf("%s\n", strerror(errno));
			close(fd);
			return -1;
		}

		printf("bfType : %c%c\n", bmp_head.bfType[0], bmp_head.bfType[1]);
		printf("bfSize : %d\n", bmp_head.bfSize);
		printf("bfOffBits : %d\n", bmp_head.bfOffBits);


		printf("BMP INFO\n");
		
		struct BMP_INFO bmp_info;
		size = read(fd, &bmp_info, 40);
		if (size < 0) {
			printf("%s\n", strerror(errno));
			close(fd);
			return -1;
		}

		printf("biSize = %d\n", bmp_info.biSize);
		printf("biWidth = %d\n", bmp_info.biWidth);
		printf("biHeight = %d\n", bmp_info.biHeight);
		printf("biBitCount = %d\n", bmp_info.biBitCount);
		printf("biCompression = %d\n", bmp_info.biCompression);
		printf("biSizeImage = %d\n", bmp_info.biSizeImage);

		/* read bmp file */
		lseek(fd, bmp_head.bfOffBits, SEEK_SET);
		char * bmp_data = (char *)malloc(bmp_info.biWidth*bmp_info.biHeight*4);
		if (bmp_data == NULL) {
			printf("%s\n", strerror(errno));
			close(fd);
			return -1;
		}
		int loop;
		for (loop=bmp_info.biHeight-1; loop>0; loop--) {
			size = read(fd, bmp_data+(loop*bmp_info.biWidth*4), bmp_info.biWidth*4);
			if (size != bmp_info.biWidth*4) {
				printf("read bmp failed! : %s\n size = %ld\n", strerror(errno), size);
				free(bmp_data);
				close(fd);
				return -1;
			}
		}

		/* covert to yuv420 */
		unsigned long imageSize = bmp_info.biWidth*bmp_info.biHeight;
		unsigned long r_t, g_t, b_t;

		char * yuv_y = (char *)malloc(imageSize);
		char * yuv_u = (char *)malloc(imageSize/4);
		char * yuv_v = (char *)malloc(imageSize/4);
		char * yuv_u_t = (char *)malloc(imageSize);
		char * yuv_v_t = (char *)malloc(imageSize);

		int loop_index;
		for (loop_index=0; loop_index<imageSize; loop_index++) {
			r_t = bmp_data[(loop_index*4)+2];
			g_t = bmp_data[(loop_index*4)+1];
			b_t = bmp_data[(loop_index*4)];

			yuv_y[loop_index] = (unsigned char)((float)(0.2990*r_t) + (float)(0.5870*g_t) + (float)(0.1140*b_t));
			yuv_u_t[loop_index] = (unsigned char)((float)(-0.1684*r_t) - ((float)(0.3316*g_t)) + b_t/2 + 128);
			yuv_v_t[loop_index] = (unsigned char)((float)(r_t)/2 - (float)(0.4187*g_t) - (float)(0.0813*b_t) + 128);
		}
		unsigned int k=0, i, j;
		for (i=0; i<bmp_info.biHeight; i+=2) {
			for (j=0; j<bmp_info.biWidth; j+=2) {
				yuv_u[k] = (yuv_u_t[i*bmp_info.biWidth+j] + yuv_u_t[(i+1)*bmp_info.biWidth+j] + yuv_u_t[i*bmp_info.biWidth+j+1] + yuv_u_t[(i+1)*bmp_info.biWidth+j+1])/4;
				yuv_v[k] = (yuv_v_t[i*bmp_info.biWidth+j] + yuv_v_t[(i+1)*bmp_info.biWidth+j] + yuv_v_t[i*bmp_info.biWidth+j+1] + yuv_v_t[(i+1)*bmp_info.biWidth+j+1])/4;
				k++;
			}
		}
		for (i=0; i<imageSize; i++) {
			if (yuv_y[i] < 16) {
				yuv_y[i] = 16;
			}
			if (yuv_y[i] >235) {
				yuv_y[i] = 235;
			}
		}
		for (j=0; j<imageSize/4; j++) {
			if (yuv_u[i] < 16) {
				yuv_u[i] = 16;
			}
			if (yuv_u[i] >240) {
				yuv_u[i] = 240;
			}
			if (yuv_v[i] < 16) {
				yuv_v[i] = 16;
			}
			if (yuv_v[i] >240) {
				yuv_v[i] = 240;
			}
		}
		
		if (yuv_u_t) free(yuv_u_t);
		if (yuv_v_t) free(yuv_v_t);

		/* open yuv420 file */
		char filename[50];
		char *p;
		strcpy(filename, argv[1]);
		printf("before filename : %s\n", filename);
		p = strstr(filename, ".bmp");
		strcpy(p+1, "yuv");

		printf("filename = %s\n", filename);
		int fd_yuv = open(filename, O_WRONLY | O_CREAT);
		if (fd_yuv < 0) {
			printf("%s\n", strerror(errno));
			close(fd);
			return -1;
		}
		/* save to yuv420p */
		lseek(fd_yuv, 0, SEEK_SET);
		size = write(fd_yuv, yuv_y, imageSize);
		if (size != imageSize) {
			printf("write yuv_y failed!\n");
			goto EXIT;
		}
		size = write(fd_yuv, yuv_u, imageSize/4);
		if (size != imageSize/4) {
			printf("write yuv_y failed!\n");
			goto EXIT;
		}
		size = write(fd_yuv, yuv_v, imageSize/4);
		if (size != imageSize/4) {
			printf("write yuv_y failed!\n");
			goto EXIT;
		}
		printf("DONE!\n");
		/* close file*/
EXIT:
		close(fd_yuv);
		close(fd);
		free(yuv_y);
		free(yuv_u);
		free(yuv_v);
		free(bmp_data);
		return 0;
}

