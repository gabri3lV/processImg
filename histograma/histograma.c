/*-------------------------------------------------------------------------
 * Histograma
 * Por Luiz Eduardo da Silva.
 *-------------------------------------------------------------------------*/

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <math.h>
 #include "../utils/imagelib.h"
 
 image equaliza(image In)
 {
     int nr = In->nr, nc = In->nc, ml = In->ml;
     int histo[ml + 1];
     double pk[ml + 1]; // probabilidade dos pixels
     double ak[ml + 1]; // probabilidade acumulada
     int sk[ml + 1];    // pixel equalizado
     image Out = img_clone(In);
     // calculo do histograma
     for (int i = 0; i <= ml; i++)
         histo[i] = 0;
     for (int i = 0; i < nr * nc; i++)
         histo[In->px[i]]++;
     // calculo das probabilidades dos pixels
     for (int i = 0; i < ml + 1; i++)
         pk[i] = (double)histo[i] / (nr * nc);
     // calculo das probabilidades acumuladas
     ak[0] = pk[0];
     for (int i = 1; i < ml + 1; i++)
         ak[i] = ak[i - 1] + pk[i];
     // equalização dos pixels
     for (int i = 0; i < ml + 1; i++)
         sk[i] = ak[i] * ml;
     // calculo da imagem com os pixels equalizados
     for (int i = 0; i < nr * nc; i++)
         Out->px[i] = sk[In->px[i]];
     return Out;
 }

 image histograma(image img) {
    int w = img->nc;
    int h = img->nr;
    int max = img->ml;
    int *pixels = img->px;

    float n[max + 1]; // histograma
    float pr[max +1]; // probabilidade acumulada
    int T[max + 1]; // tabela transformação

    // calcula o histograma
    for (int i = 0; i < max + 1; i++)
        n[i] = 0;
    for (int i = 0; i < h * w; i++)
        n[pixels[i]]++;

    // probabilidade acumulada das intensidades
    pr[0] = n[0] / (w * h);
    for (int i = 1; i < max + 1; i++)
        pr[i] = pr[i - 1] + n[i] / (w * h);

    // vetor de transformação das intensidades
    for (int i = 0; i < max + 1; i++)
        T[i] = (int)(pr[i] * max);

    // varredura final
    for (int i = 0; i < w * h; i++)
        pixels[i] = T[pixels[i]];
    return img;
 }
 
 void msg(char *s)
 {
     printf("\nEqualização de Histograma");
     printf("\n-------------------------------");
     printf("\nUso:  %s  nome-imagem[.pgm] \n\n", s);
     printf("    nome-imagem[.pgm] é o nome do arquivo da imagem \n");
     exit(1);
 }
 
 /*-------------------------------------------------------------------------
  * main function
  *-------------------------------------------------------------------------*/
 int main(int argc, char *argv[])
 {
     char nameIn[100], nameOut[100], cmd[110];
     image In, Out;
     if (argc < 2)
         msg(argv[0]);
 
     img_name(argv[1], nameIn, nameOut, GRAY, GRAY);
 
     //-- read image
     In = img_get(nameIn, GRAY);
     //-- transformation
     Out = histograma(In);
     //-- save image
     img_put(Out, nameOut, GRAY);
 
     sprintf(cmd, "%s %s &", VIEW, nameOut);
     system(cmd);
     img_free(In);
     // img_free(Out);
     return 0;
 }