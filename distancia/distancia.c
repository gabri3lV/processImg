#include <stdio.h>

int nc = 10;
int nl = 10;

int img[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 1, 1, 1, 1, 1, 0, 0,
    0, 0, 1, 1, 1, 1, 1, 1, 0, 0,
    0, 0, 1, 1, 1, 1, 1, 1, 0, 0,
    0, 0, 1, 1, 1, 1, 1, 1, 0, 0,
    0, 0, 1, 1, 1, 1, 1, 1, 0, 0,
    0, 0, 1, 1, 1, 1, 1, 1, 0, 0,
    0, 0, 1, 1, 1, 1, 1, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

void showImage (int img[]) {
    for(int i = 0; i < nl; i++){
        for(int j = 0; j < nc; j++){
            printf("%3d ", img[i * nc + j]);
        }
        printf("\n");
    }
}

int menor(int x, int y, int z){
    if (x < y || x < z)
        return x;
    else if (y < z) 
        return y;
    else 
        return z;
}

void distance (int img[]) {
    
    // Ida - Fase 1 do algoritmo
    for(int i = 1; i < nl; i++){
        for(int j = 1; j < nc; j++){
            
            int a = (i - 1) * nc + j; // Vizinho de cima
            int b = i * nc + j - 1; // Vizinho da esquerda
            int p = i * nc + j;

            if(img[p] != 0) {
                if(img[a] + 1 < img[b] + 1){
                    img[p] = img[a] + 1;
                } else {
                    img[p] = img[b] + 1;
                }
            }

        }
    }

    // Volta - Fase 2 do algoritmo
    for(int i = nl-2; i >= 0; i--){
        for(int j = nc-2; j >= 0; j--){

            int p = i * nc + j; // ref
            int a = i * nc + j + 1; // Vizinho da direita
            int b = (i + 1) * nc + j; // Vizinho de baixo
            img[p] = menor(img[p], img[a] + 1, img[b] + 1);

        }
    }    
}

int main(){

    showImage(img);
    puts(" ");
    distance(img);
    showImage(img);

}