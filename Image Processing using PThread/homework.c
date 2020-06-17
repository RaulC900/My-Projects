#include "homework.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <math.h>

int num_threads;
int resize_factor;


unsigned char **alloc_mat(int height, int width){

	unsigned char **mat;

	mat = (unsigned char **) malloc(sizeof(unsigned char *) * height);

	for(int i = 0; i < height; i++){

		mat[i] = (unsigned char *) malloc(sizeof(unsigned char) * width);

	}

	return mat;

}


pixel **alloc_mat_color(int height, int width){

	pixel **mat_color;

	mat_color = (pixel **) malloc(sizeof(pixel *) * height);

	for(int i = 0; i < height; i++){

		mat_color[i] = (pixel *) malloc(sizeof(pixel) * width);
		
	}

	return mat_color;

}


void readInput(const char * fileName, image *img) {

	FILE* in;
	int i, j;
	in = fopen(fileName, "rb");

	fscanf(in, "%s\n", img->type);
	fscanf(in, "%d %d\n", &img->width, &img->height);
	fscanf(in, "%d\n", &img->max_rgbval);

	if(!strcmp(img->type, "P5")){ //grayscale

		img->mat = alloc_mat(img->height, img->width);

		for(i = 0; i < img->height; i++){
			for(j = 0; j < img->width; j++){
				fread(&img->mat[i][j], sizeof(unsigned char), 1, in);
			}
		}
	}
	
	else if(!strcmp(img->type, "P6")){ //color
	
		img->mat_color = alloc_mat_color(img->height, img->width);

		for(int i = 0; i < img->height; ++i){
	
			for(int j = 0; j < img->width; ++j){

				fread(&img->mat_color[i][j], sizeof(pixel), 1, in);
			}

		}

	}
	
	fclose(in);

}


void writeData(const char * fileName, image *img) {

	FILE *out;
	int i, j;
	out = fopen(fileName, "wb");

	fprintf(out, "%s\n", img->type);
	fprintf(out, "%d %d\n", img->width, img->height);
	fprintf(out, "%d\n", img->max_rgbval);

	if(!strcmp(img->type, "P5")){ //grayscale .pgm

		for(i = 0; i < img->height; i++){

			for(j = 0; j < img->width; j++){

				fwrite(&img->mat[i][j], sizeof(unsigned char), 1, out);
			}

		}

	}

	else if(!strcmp(img->type, "P6")){ //color .pnm

		for(i = 0; i < img->height; i++){

			for(j = 0; j < img->width; j++){

				fwrite(&img->mat_color[i][j], sizeof(pixel), 1, out);
			
			}

		}

	}

	fclose(out);

}


void *threadFunction(void *var){

	int sum = 0;

	pixelInt sum_color;

	sum_color.r = 0;
	sum_color.g = 0;
	sum_color.b = 0;

	int gaussian[3][3] = {{1, 2, 1}, {2, 4, 2}, {1, 2, 1}};

 	threadS thr = *(threadS *) var;

	int i, j, k, l;

	
	if(!strcmp(thr.img_in->type, "P5")){
																		  
		if(resize_factor == 3){
			
			for (i = thr.id; i < thr.img_out->height; i += num_threads){				

			 	for(j = 0; j < thr.img_out->width; j++){			 		
					
					for(k = i * resize_factor; k < (i + 1)* resize_factor; ++k){						

						for(l = j * resize_factor; l < (j + 1)* resize_factor; ++l){
							
								sum = sum + thr.img_in->mat[k][l] * gaussian[k - resize_factor * i][l - resize_factor * j];
							
						}												

					}
					
					sum = sum/16;
					thr.img_out->mat[i][j] = sum;
					sum = 0;

			 	}

			}

		}else if(!(resize_factor % 2)){

			for (i = thr.id; i < thr.img_out->height; i+= num_threads){
				
			 	for(j = 0; j < thr.img_out->width; j++){

			 		sum = 0;

					for(k = i * resize_factor; k < (i + 1)* resize_factor; ++k){

						for(l = j * resize_factor; l < (j + 1)* resize_factor; ++l){

							sum += thr.img_in->mat[k][l];

						}						

					}

					sum = sum /(resize_factor*resize_factor);
					thr.img_out->mat[i][j] = sum;

			 	}

			}

		}

	}else if(!strcmp(thr.img_in->type, "P6")){

		if(resize_factor == 3){

			for (i = thr.id; i < thr.img_out->height; i+= num_threads){
				
			 	for(j = 0; j < thr.img_out->width; j++){

			 		sum_color.r = 0;
					sum_color.g = 0;
					sum_color.b = 0;

					for(k = i * resize_factor; k < (i + 1)* resize_factor; k++){

						for(l = j * resize_factor; l < (j + 1)* resize_factor; l++){

									sum_color.r = sum_color.r + thr.img_in->mat_color[k][l].r * gaussian[k - resize_factor * i][l - resize_factor * j];
									sum_color.g = sum_color.g + thr.img_in->mat_color[k][l].g * gaussian[k - resize_factor * i][l - resize_factor * j];
									sum_color.b = sum_color.b + thr.img_in->mat_color[k][l].b * gaussian[k - resize_factor * i][l - resize_factor * j];
							
						}
					
					}

					thr.img_out->mat_color[i][j].r = sum_color.r / 16;
					thr.img_out->mat_color[i][j].g = sum_color.g / 16;
					thr.img_out->mat_color[i][j].b = sum_color.b / 16;

			 	}

			}

		}else if(!(resize_factor % 2)){

			for (i = thr.id; i < thr.img_out->height; i+= num_threads){
				
			 	for(j = 0; j < thr.img_out->width; j++){

			 		sum_color.r = 0;
					sum_color.g = 0;
					sum_color.b = 0;
					
					for(k = i * resize_factor; k < (i + 1)* resize_factor; ++k){

						for(l = j * resize_factor; l < (j + 1)* resize_factor; ++l){

							sum_color.r += thr.img_in->mat_color[k][l].r;
							sum_color.g += thr.img_in->mat_color[k][l].g;
							sum_color.b += thr.img_in->mat_color[k][l].b;

						}

					}
					
					sum_color.r = sum_color.r/(resize_factor*resize_factor);
					thr.img_out->mat_color[i][j].r = sum_color.r;

					sum_color.g = sum_color.g/(resize_factor*resize_factor);
					thr.img_out->mat_color[i][j].g = sum_color.g;

					sum_color.b = sum_color.b/(resize_factor*resize_factor);
					thr.img_out->mat_color[i][j].b = sum_color.b;

			 	}			 	

			}

		}

	}	

return NULL;

}


void resize(image *in, image * out) {

	out->height = (in->height)/resize_factor;
	out->width = (in->width)/resize_factor;

	strcpy(out->type, in->type);

	out->max_rgbval = in->max_rgbval;

	if(!strcmp(in->type, "P5")) {
		out->mat = alloc_mat(out->height, out->width);

	}else if(!strcmp(in->type, "P6")) {
		out->mat_color = alloc_mat_color(out->height, out->width);
	}

	pthread_t tid[num_threads];
	threadS thread_id[num_threads];

	int i;

	for(i = 0; i < num_threads; i++){
		thread_id[i].id = i;
		thread_id[i].img_in = in;
		thread_id[i].img_out = out;
	}

	for(i = 0; i < num_threads; i++) {
		pthread_create(&(tid[i]), NULL, threadFunction, &(thread_id[i]));
	}

	for(i = 0; i < num_threads; i++) {
		pthread_join(tid[i], NULL);
	}

}
