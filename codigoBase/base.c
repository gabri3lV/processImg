/*-------------------------------------------------------------------------
 * Image Processing using C-Ansi
 *   Program: Processing of the image negative
 *-------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32) || defined(__WIN64__) || defined(__CYGWIN__)
#include "..\\utils\\imagelib.h"
#elif defined(__linux__)
#include "../utils/imagelib.h"
#endif

// funcao de deixar negativo
image neg (image img) {
    int w = img->nc;
    int h = img->nr;
    int max = img->ml;
    int *pixels = img->px;
    for (int i = 0; i < h * w; i++)
        img->px[i] = max - pixels[i];
    return img;
}

// transformacao pontual
image pontual(image img) {
    int w = img->nc;
    int h = img->nr;
    int max = img->ml;
    int *pixels = img->px;
    int T[max+1];

    for (int i = 0; i <= max; i++) 
        T[i] = (i > 100 && i < 150) ? 190 : i;

    for (int i = 0; i < h * w; i++)
        pixels[i] = T[pixels[i]];

    return img;
}
void msg(char *s)
{
    printf("\nNegative image");
    printf("\n-------------------------------");
    printf("\nUsage:  %s  image-name[.pgm]\n\n", s);
    printf("    image-name[.pgm] is image file in pgm format \n\n");
    exit(1);
}

/*-------------------------------------------------------------------------
 * main function
 *-------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    int nc, nr, ml, tp;
    char *p, nameIn[100], nameOut[100], cmd[110];
    image In, Out;
    if (argc < 2)
        msg(argv[0]);

    //-- define input/output file name
    img_name(argv[1], nameIn, nameOut, GRAY, GRAY);

    //-- read image
    In = img_get(nameIn, GRAY);
    //-- transformation
    Out = pontual(In);
    //-- save image
    img_put(Out, nameOut, GRAY);

    //-- show image
    sprintf(cmd, "%s %s &", VIEW, nameOut);
    puts(cmd);
    system(cmd);
    img_free(In);
    img_free(Out);
    return 0;
}
