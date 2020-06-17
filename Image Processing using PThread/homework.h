#ifndef HOMEWORK_H
#define HOMEWORK_H


typedef struct {
	unsigned char r, g, b;
	
}pixel;

typedef struct {
	int r, g, b;

}pixelInt;

typedef struct image{
	char type[2];
	int width, height;
	int max_rgbval;
	unsigned char **mat;
	pixel **mat_color;

}image;

typedef struct threadS {
	int id;
	image *img_in;
	image *img_out;

}threadS;


void readInput(const char * fileName, image *img);

void writeData(const char * fileName, image *img);

void resize(image *in, image * out);

#endif /* HOMEWORK_H */