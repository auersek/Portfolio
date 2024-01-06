#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "c_img.h"
//#include "c_img.c"
#include "seamcarving.h"

//part1 Dual-gradient Energy Function

void calc_energy(struct rgb_img *im, struct rgb_img **grad){
    create_img(grad, im->height, im->width);
    int i, j;
    for (i=0; i < im->height; i++){
        for (j=0; j < im->width; j++)
        {
            int r_y = 0;
            int g_y = 0;
            int b_y = 0;

            int r_x = 0;
            int g_x = 0;
            int b_x = 0;


            if (i == 0){
                r_y = get_pixel(im, i+1, j, 0) - get_pixel(im, im->height - 1, j, 0);
                g_y = get_pixel(im, i+1, j, 1) - get_pixel(im, im->height - 1, j, 1);
                b_y = get_pixel(im, i+1, j, 2) - get_pixel(im, im->height - 1, j, 2);
            }
            else if (i == im->height - 1){
                r_y = get_pixel(im, 0, j, 0) - get_pixel(im, i-1, j, 0);
                g_y = get_pixel(im, 0, j, 1) - get_pixel(im, i-1, j, 1);
                b_y = get_pixel(im, 0, j, 2) - get_pixel(im, i-1, j, 2);
            }
            else{
                r_y = get_pixel(im, i+1, j, 0) - get_pixel(im, i-1, j, 0);
                g_y = get_pixel(im, i+1, j, 1) - get_pixel(im, i-1, j, 1);
                b_y = get_pixel(im, i+1, j, 2) - get_pixel(im, i-1, j, 2);
            }
            if (j == 0){
                r_x = get_pixel(im, i, j+1, 0) - get_pixel(im, i, im->width - 1, 0);
                g_x = get_pixel(im, i, j+1, 1) - get_pixel(im, i, im->width - 1, 1);
                b_x = get_pixel(im, i, j+1, 2) - get_pixel(im, i, im->width - 1, 2);
            }
            else if (j == im->width - 1){
                r_x = get_pixel(im, i, 0, 0) - get_pixel(im, i, j-1, 0);
                g_x = get_pixel(im, i, 0, 1) - get_pixel(im, i, j-1, 1);
                b_x = get_pixel(im, i, 0, 2) - get_pixel(im, i, j-1, 2);
            }
            else{
                r_x = get_pixel(im, i, j+1, 0) - get_pixel(im, i, j-1, 0);
                g_x = get_pixel(im, i, j+1, 1) - get_pixel(im, i, j-1, 1);
                b_x = get_pixel(im, i, j+1, 2) - get_pixel(im, i, j-1, 2);
            }

            uint8_t e = sqrt(r_x*r_x + g_x*g_x + b_x*b_x + r_y*r_y + g_y*g_y + b_y*b_y)/10;
            set_pixel(*grad,i,j,e,e,e);
        }
    }
}

//Part2: Cost Array

void dynamic_seam(struct rgb_img *grad, double **best_arr)
{
    int i, j;
    *best_arr = (double*)malloc(grad->height * grad->width * sizeof(double));
        for (i=0; i < grad->height;i++){
            for (j=0; j < grad->width; j++){
                if (i == 0){
                    (*best_arr)[i*grad->width + j] = get_pixel(grad, i, j, 0);
                }
                else if (j == 0){
                    double min = (*best_arr)[(i-1)*grad->width + j];
                    for (int k = j; k <= j+1; k++){
                        if ((*best_arr)[(i-1)*grad->width + k] < min){
                            min = (*best_arr)[(i-1)*grad->width + k];
                        }
                    }
                    (*best_arr)[i*grad->width + j] = get_pixel(grad, i, j, 0) + min;
                }
                else if (j == grad->width - 1){
                    double min = (*best_arr)[(i-1)*grad->width + j-1];
                    for (int k = j-1; k <= j; k++){
                        if ((*best_arr)[(i-1)*grad->width + k] < min){
                            min = (*best_arr)[(i-1)*grad->width + k];
                        }
                    }
                    (*best_arr)[i*grad->width + j] = get_pixel(grad, i, j, 0) + min;
                }
                else{
                    double min = (*best_arr)[(i-1)*grad->width + j-1];
                    for (int k = j-1; k <= j+1; k++){
                        if ((*best_arr)[(i-1)*grad->width + k] < min){
                            min = (*best_arr)[(i-1)*grad->width + k];
                        }
                    }
                    (*best_arr)[i*grad->width + j] = get_pixel(grad, i, j, 0) + min;
            }
        }
    }
}

// This function allocates a path through the minimum seam as defined by the array best.
void recover_path(double *best, int height, int width, int **path)
{
    *path = (int*)malloc(height * sizeof(int));
    int i;
    for (i = height-1; i >= 0; i--){
        if (i == height-1){
            int cur_k = 0;
            for (int k = 0; k < width; k++){
                if (best[(i)*width+k] <= best[(i)*width+cur_k]){
                    cur_k = k;
                }
            }
            (*path)[i] = cur_k;
        }
        else{
            int cur_k = (*path)[i+1];
            int prev_k = cur_k;
            if (cur_k == 0){
                for (int k = cur_k; k <= prev_k + 1; k++){
                    if (best[(i)*width + k] <= best[(i)*width + cur_k]){
                        cur_k = k;
                    }
                }
                (*path)[i] = cur_k;
            }
            else if (cur_k == width - 1){
                int prev_k = cur_k;
                for (int k = cur_k - 1; k <= prev_k; k++){
                    if (best[(i)*width + k] <= best[(i)*width + cur_k]){
                        cur_k = k;
                    }
                }
                (*path)[i] = cur_k;
            }
            else{
                int prev_k = cur_k;
                for (int k = cur_k - 1; k <= prev_k + 1; k++){
                    if (best[(i)*(width) + k] <= best[(i)*(width) + cur_k]){
                        cur_k = k;
                    }
                }
                (*path)[i] = cur_k;
            }
            
        }
    }
            
}

// The function creates the destination image, and writes to it the source image, with the seam removed.
void remove_seam(struct rgb_img *src, struct rgb_img **dest, int *path)
{
    create_img(dest, src->height, src->width - 1);
    int i, j;
    for (i = 0; i < src->height; i++){
        for (j = 0; j < src->width-1; j++){
            if (j < path[i]){
                set_pixel(*dest, i, j, get_pixel(src, i, j, 0), get_pixel(src, i, j, 1), get_pixel(src, i, j, 2));
            }
            else if (j > path[i]){
                set_pixel(*dest, i, j-1, get_pixel(src, i, j, 0), get_pixel(src, i, j, 1), get_pixel(src, i, j, 2));
            }
        }
    }

}


/* int main()
{
    /*
    struct rgb_img *im, *grad;
    double *best_arr;
    int *path;

    read_in_img(&im, "6x5.bin");
  
    calc_energy(im,  &grad);
      
    print_grad(grad);

    dynamic_seam(grad, &best_arr);

    
    for (int i=0; i < grad->height * grad->width; i++){
        printf("%f\t", best_arr[i]);
        }
    

    recover_path(best_arr, grad->height, grad->width, &path);
    
    for (int i = 0; i < grad->height; i++){
        printf("%d\t", path[i]);
    }
    printf("\n");

    destroy_image(im);

    int* array[] = {1,3,4,5,6,7,8,9,10};
    for (int i = 8; i >= 0; i--){
        printf("%d\t", array[i]);
    }
    printf("\n");
    
    
   

    struct rgb_img *im;
    struct rgb_img *cur_im;
    struct rgb_img *grad;
    double *best;
    int *path;

    read_in_img(&im, "HJoceanSmall.bin");
    
    for(int i = 0; i < 5; i++){
        printf("i = %d\n", i);
        calc_energy(im,  &grad);
        dynamic_seam(grad, &best);
        recover_path(best, grad->height, grad->width, &path);
        remove_seam(im, &cur_im, path);

        char filename[200];
        sprintf(filename, "img%d.bin", i);
        write_img(cur_im, filename);


        destroy_image(im);
        destroy_image(grad);
        free(best);
        free(path);
        im = cur_im;
    }
    destroy_image(im);
    
}
*/