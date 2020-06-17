#ifndef HOMEWORK_H1
#define HOMEWORK_H1


typedef struct {
	char type[3];
	int side;
	int max_rgbval;
	unsigned char **mat;

}image;

typedef struct threadS {
	int id;
	image *img;

}threadS;

void initialize(image *im);
void render(image *im);
void writeData(const char * fileName, image *img);

#endif /* HOMEWORK_H1 */