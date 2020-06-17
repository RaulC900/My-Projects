//#include "homework.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int num_threads;
int resize_factor;

typedef struct pixel{
	unsigned char r, g, b;
}pixel;

typedef struct image{
	char type[3];
	unsigned int width, height;
	unsigned int max_rgbval;
	int *mat;

}image;


void readInput(const char * fileName, image *img) {

	int color;
	FILE* in;
	img = (image*) malloc(sizeof(image));
	char type[255];
	in = fopen(fileName, "rb");
	if (in == NULL){
		perror("cannot open file to read");
		exit(8);
	}
	/*
	while (getc(in) != '\n');
 
  	while (getc(in) == '#') {
    	while (getc(in) != '\n');
  	}

  	fseek(in, -1, SEEK_CUR);
  	*/
	fscanf(in, "%s", &img->type);
	fscanf(in, "%d", &img->height);
	fscanf(in, "%d", &img->width);
	fscanf(in, "%d", &img->max_rgbval);

	printf("%d\n", img->width);


	if(strcmp(img->type, "P5") == 0){ //grayscale


		img->mat == (int *) malloc(sizeof(int) * img->height * img->width);


		for (int i = 0 ; i < img->height * img->width; ++i) {

    		//for (int j = 0; j < img->width; ++j) {

      			fread(&img->mat[i], sizeof(img->mat), 1, in);
      			printf("%d\n", img->mat[i]);

    		//}
  		}
	}


	/*

	else if(strcmp(type, "P6")){ //color
	
		img->mat == alloc_mat(img->height, img->width);

		for(int i = 0; i < img->height; ++i){
	
			for(int j = 0; j < (img->width * 3); ++j){
	
				fread(in, "%d%d%d", &img->mat[i][j].r, &img->mat[i][j].g, &img->mat[i][j].b);
			}
		}
	}

	*/

	fclose(in);
	//return img;


}

void writeData(const char * fileName, image *img) {




}

void resize(image *in, image * out) {

	//out->height = (in->height)/resize_factor;
	//out->width = (in->width)/resize_factor;
	//int red = 0;
	//int green = 0;
	//int blue = 0;
	int colour;

	// in->mat == (int *) malloc(sizeof(int) * in->height * in->width);
	// out->mat == (int *) malloc(sizeof(int) * out->height * out->width);

	// for (int i = 0; i < in->height; i = i + resize_factor){

	// 	for(int j = 0; j < in->width; j = j + resize_factor){
			
	// 		for(int k = 0; k < i + resize_factor; ++k){
	// 			for(int l = 0; l < j + resize_factor; ++l){
	// 				colour += in->mat[j + k][j + l];
	// 			}
	// 		}
	// 		colour = colour/resize_factor;
			

	// 	}


	// }


}

int main(int argc, char * argv[]) {

	image input;
	image output;

	readInput(argv[1], &input);
	resize(&input, &output);
	writeData(argv[2], &output);

	return 0;
}