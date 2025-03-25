/*-------------------------------------------------------------------------
 *   Image Processing using C-Ansi
 *   Program: 
 *-------------------------------------------------------------------------*/

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 
 #if defined(_WIN32) || defined(__WIN64__) || defined(__CYGWIN__)
 #include "..\\utils\\imagelib.h"
 #elif defined(__linux__)
 #include "../utils/imagelib.h"
 #endif

int abs(int n) 
{
    return n < 0 ? -n : n;
}

void sort (int *v, int n) 
{
    for (int i = 0; i < n - 1; i++) 
    {
        int m = 1;
        for (int j = i + 1; j < n; j++)
            if (v[j] < v[m])
                m = j;
        int tmp = v[m];
        v[m] = v[i];
        v[i] = tmp;
    }
}



image sobel(image img)
{
    image out = img_clone(img);
    int w = img->nc;
    int h = img->nr;
    int max = img->ml;
    int *pixels = img->px;

    for (int i = 0; i < h; i++) 
    {
        out->px[i * w] = 0;
        out->px[i * w + w - 1] = 0;
    }
    for (int j = 0; j < w; j++) 
    {
        out->px[j] = 0;
        out->px[(h - 1) * w + j] = 0;
    }
    for (int i = 1; i < h - 1; i++) 
        for (int j = 1; j < w - 1; j++)
        {
            int Z[9];
            int k = 0;
            for (int y = -1; y < 2; y++)
                for (int x = -1; x < 2; x++)
                    Z[k++] = pixels[(i + y) * w + (j + x)];
            sort(Z, 9);
            out->px[i * w + j] = Z[4];
        }
    return out;
}

void msg(char *s)
{
    printf("\nMediana");
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
     Out = sobel(In);
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
 