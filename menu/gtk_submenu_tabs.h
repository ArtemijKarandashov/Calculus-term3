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

void        const_step_integ(GtkWidget *button, gpointer data);
void        dynamic_step_integ(GtkWidget *button, gpointer data);
GtkWidget*  new_const_integ_menu( pointer_func func );
GtkWidget*  new_dynamic_integ_menu( pointer_func func );

#endif