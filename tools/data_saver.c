#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include "data_saver.h"

char* 
make_dir(char *path_to_dir)
{
    
    char* path = malloc(32);

    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
    timeinfo = localtime (&rawtime);

    strcpy(path,path_to_dir);
    strcat(path,asctime(timeinfo));

    struct stat st = {0};

    if (stat(path,&st) == -1){
        mkdir(path,0700);
    }

    return path;
}

void
save_integ_data(int len, double* arr_x, double* arr_y)
{
    char* saving_path = make_dir("out/integral/");

    char x_path[60];
    char y_path[60];

    sprintf(x_path,"%s/integral_result_x.txt",saving_path);
    sprintf(y_path,"%s/integral_result_y.txt",saving_path);

    FILE *file_x = fopen(x_path, "w");
    FILE *file_y = fopen(y_path, "w");

    for (int i = 0; i < len; i++){
        fprintf(file_x, "%lf\n",arr_x[i]);
        fprintf(file_y, "%lf\n",arr_y[i]);
    }

    fclose(file_x);
    fclose(file_y);
    free(saving_path);
}

void
save_integ_csv(int len, double* arr_x, double* arr_y)
{
    char* saving_path = make_dir("out/integral/");

    char csv_path[60];

    sprintf(csv_path,"%s/integral_result.csv",saving_path);

    FILE *file = fopen(csv_path, "w");

    for (int i = 0; i < len; i++){
        fprintf(file, "%d,%lf,%lf\n",len,arr_x[i],arr_y[i]);
    }

    fclose(file);
    free(saving_path);
}
/*
void
save_multi_integ_csv(int len, double* arr_x, double* arr_y)
{
    char* saving_path = make_dir("out/integral/");

    char path[60];
    sprintf(path,"%s/multiple_integral_result.csv",saving_path);

    FILE *file = fopen(path, "w");

    for(int i = 0; i<len;i++){
        fprintf(file, "%d,%lf,%lf,%lf,%lf\n",len,arr_x[i],arr_y[i]);
    }
    fclose(file);
    
    free(saving_path);
}
*/

void 
save_diff_data( int       len,
                double   *arr_x,
                double   *arr_y,
                double   *arr_f)
{   
    char* saving_path = make_dir("out/diff/");

    char x_path[50];
    char y_path[50];
    char f_path[50];

    sprintf(x_path,"%s/x.txt",saving_path);
    sprintf(y_path,"%s/y.txt",saving_path);
    sprintf(f_path,"%s/f.txt",saving_path);

    FILE *file_x = fopen(x_path, "w");
    FILE *file_y = fopen(y_path, "w");
    FILE *file_f = fopen(f_path, "w");

    for (int i = 0; i < len; i++){
        fprintf(file_x, "%lf\n",arr_x[i]);
        fprintf(file_y, "%lf\n", arr_y[i]);
        fprintf(file_f, "%lf\n",arr_f[i]);
    }

    fclose(file_x);
    fclose(file_y);
    fclose(file_f);

    free(saving_path);
}

void 
save_diff_csv(  int       len,
                double   *arr_x,
                double   *arr_y,
                double   *arr_f)
{
    char* saving_path = make_dir("out/diff/");

    char csv_path[50];
    sprintf(csv_path,"%s/out.csv",saving_path);

    FILE *file = fopen(csv_path, "w");

    for (int i = 0; i < len; i++){
        fprintf(file, "%d,%lf,%lf,%lf\n",i+1,arr_x[i],arr_y[i],arr_f[i]);
    }

    fclose(file);    

    free(saving_path);
}

void 
save_diff_sys_csv(  int       len,
                    double   *arr_x,
                    double   *arr_y,
                    double   *arr_z,
                    double   *arr_t)
{
    char* saving_path = make_dir("out/diff/");

    char csv_path[50];
    sprintf(csv_path,"%s/sys_out.csv",saving_path);

    FILE *file = fopen(csv_path, "w");

    for (int i = 0; i < len; i++){
        fprintf(file, "%d,%lf,%lf,%lf,%lf\n",i+1,arr_x[i],arr_y[i],arr_z[i],arr_t[i]);
    }

    fclose(file);    

    free(saving_path);
}
