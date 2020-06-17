#include "homework1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <pthread.h>

int num_threads;
int resolution;


unsigned char **alloc_mat(int height, int width){

	unsigned char **mat;

	mat = (unsigned char **) malloc(sizeof(unsigned char *) * height);


	for(int i = 0; i < height; i++){

		mat[i] = (unsigned char *) malloc(sizeof(unsigned char) * width);

	}

	return mat;
}


void initialize(image *im) {

	unsigned char **mat;

	int i, j;
	char type[3] = "P5";

	strcpy(im->type, type);
	im->side = resolution;
	im->max_rgbval = 255;

	mat = alloc_mat(im->side, im->side);

	for(i = 0; i < im->side; i++){
	 	for(j = 0; j < im->side; j++){
	 		mat[i][j] = 255;
	 	}
	}

	im->mat = mat;

}


void *threadFunction(void *var){

	int i, j;
	double distance;
	double a = sqrt(5);

	threadS thr = *(threadS *) var;

	for(i = thr.id; i < resolution; i += num_threads){

		for(j = 0; j < resolution; ++j){

			distance = ((-1) * ((j + 0.5) * 100 / resolution)) + (2 * (resolution -i - 0.5) * 100 / resolution);   
			     
			distance = abs(distance) / a;

			if(distance > 3)
				thr.img->mat[i][j] = 255;
				
			if(distance <= 3)
				thr.img->mat[i][j] = 0;

		}

	}

return NULL;

}


void render(image *im) {

	pthread_t tid[num_threads];
	threadS thread_id[num_threads];

	int i;

	for(i = 0; i < num_threads; i++){
		thread_id[i].id = i;
		thread_id[i].img = im;;
	}

	for(i = 0; i < num_threads; i++) {
		pthread_create(&(tid[i]), NULL, threadFunction, &(thread_id[i]));
	}

	for(i = 0; i < num_threads; i++) {
		pthread_join(tid[i], NULL);
	}

}


void writeData(const char * fileName, image *img) {

	FILE *out;
	int i, j;
	out = fopen(fileName, "wb");

	fprintf(out, "%s\n", img->type);
	fprintf(out, "%d %d\n", img->side, img->side);
	fprintf(out, "%d\n", img->max_rgbval);

	for(i = 0; i < img->side; i++){
		
		for(j = 0; j < img->side; j++){
			fwrite(&img->mat[i][j], 1, 1, out);
		}

	}

	fclose(out);


}

