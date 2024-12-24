  #include <gtk/gtk.h>
#include "menu.h"
#ifndef GTK_SUBMENU
#define GTK_SUBMENU

typedef struct ConstIntegCalcData{
  GtkWidget *bottom_limit;
  GtkWidget *top_limit;
  GtkWidget *iteration_limit;
  GtkWidget *result_output;
  pointer_func function;
}ConstIntegCalcData;

typedef struct DynamicIntegCalcData{
  GtkWidget *bottom_limit;
  GtkWidget *top_limit;
  GtkWidget *accuracy;
  GtkWidget *result_output;
  pointer_func function;
}DynamicIntegCalcData;

typedef struct MultipleIntegCalcData{
  GtkWidget *bottom_limit_x;
  GtkWidget *top_limit_x;
  GtkWidget *bottom_limit_y;
  GtkWidget *top_limit_y;
  GtkWidget *iteration_limit_x;
  GtkWidget *iteration_limit_y;
  GtkWidget *result_output;
  pointer_func function;
}MultipleIntegCalcData;

typedef struct DiffCalcData{
  GtkWidget *bottom_limit;
  GtkWidget *top_limit;
  GtkWidget *x0;
  GtkWidget *y0;
  GtkWidget *iteration_limit;
  GtkWidget *result_output;
  pointer_func function;
}DiffCalcData;

typedef struct DiffSystemCalcData{
  GtkWidget *bottom_limit;
  GtkWidget *top_limit;
  GtkWidget *x0;
  GtkWidget *y0;
  GtkWidget *z0;
  GtkWidget *iteration_limit;
  GtkWidget *result_output;
  pointer_func function;
}DiffSystemCalcData;

typedef struct ChebyshevCalcData{
  GtkWidget *x;
  GtkWidget *e;
  GtkWidget *result_output;
  pointer_func function;
}ChebyshevCalcData;

typedef struct NotlinearCalcData{
  GtkWidget *bottom_limit;
  GtkWidget *top_limit;
  GtkWidget *iteration_limit;
  GtkWidget *result_output;
  pointer_func function;
}NotlinearCalcData;

void        const_step_integ(GtkWidget *button, gpointer data);
void        dynamic_step_integ(GtkWidget *button, gpointer data);
void        multi_integ(GtkWidget *button, gpointer data);
void        diff_callback(GtkWidget *button, gpointer data);
void        diff_system_callback(GtkWidget *button, gpointer data);
GtkWidget*  new_const_integ_menu( pointer_func func );
GtkWidget*  new_dynamic_integ_menu( pointer_func func );
GtkWidget*  new_multiple_integ_menu( pointer_func func );
GtkWidget*  new_diff_menu( pointer_func func );
GtkWidget*  new_diff_system_menu( pointer_func func );

#endif