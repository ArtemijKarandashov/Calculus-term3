#ifndef DATASAVER
#define DATASAVER

void save_integ_data(int len, double *arr_x, double *arr_y);
void save_multi_integ_data(double a, double b, double c, double d, double result);
void save_diff_data(int len, double *arr_x, double *arr_y, double *arr_f);
void save_diff_csv(int len, double *arr_x, double *arr_y, double *arr_f);

#endif