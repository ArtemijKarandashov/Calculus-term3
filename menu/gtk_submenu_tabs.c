#include <gtk/gtk.h>
#include "gtk_submenu_tabs.h"
#include "menu.h"

void
diff_system_callback( GtkWidget *button,
                      gpointer data    )
{
  DiffSystemCalcData *converted_data = (DiffSystemCalcData*) data;
  calc_diff_system calculation_function = (calc_diff_system) converted_data->function;
  
  const gchar *bottom_limit_input   = gtk_editable_get_text(GTK_EDITABLE(converted_data->bottom_limit   ));
  const gchar *top_limit_input      = gtk_editable_get_text(GTK_EDITABLE(converted_data->top_limit      ));
  const gchar *x0_input             = gtk_editable_get_text(GTK_EDITABLE(converted_data->x0             ));
  const gchar *y0_input             = gtk_editable_get_text(GTK_EDITABLE(converted_data->y0             ));
  const gchar *z0_input             = gtk_editable_get_text(GTK_EDITABLE(converted_data->y0             ));
  const gchar *iterations_input     = gtk_editable_get_text(GTK_EDITABLE(converted_data->iteration_limit));
  
  double bottom_lim = g_ascii_strtod(bottom_limit_input ,NULL);
  double top_lim    = g_ascii_strtod(top_limit_input    ,NULL);
  double x0         = g_ascii_strtod(x0_input           ,NULL);
  double y0         = g_ascii_strtod(y0_input           ,NULL);
  double z0         = g_ascii_strtod(z0_input           ,NULL);
  double iter       = g_ascii_strtod(iterations_input   ,NULL);

  EulerSystemAns result = calculation_function(bottom_lim,top_lim,iter,x0,y0,z0);
  gchar *result_str = g_strdup_printf("      Result:\n    x = %.6f\n    y = %.6f\n    z = %.6f",result.x,result.y,result.z);
  gtk_label_set_text(GTK_LABEL(converted_data->result_output),result_str);  
}

void
diff_callback( GtkWidget *button,
                gpointer data)
{
  DiffCalcData *converted_data = (DiffCalcData*) data;
  calc_diff calculation_function = (calc_diff) converted_data->function;
  
  const gchar *bottom_limit_input   = gtk_editable_get_text(GTK_EDITABLE(converted_data->bottom_limit   ));
  const gchar *top_limit_input      = gtk_editable_get_text(GTK_EDITABLE(converted_data->top_limit      ));
  const gchar *x0_input             = gtk_editable_get_text(GTK_EDITABLE(converted_data->x0             ));
  const gchar *y0_input             = gtk_editable_get_text(GTK_EDITABLE(converted_data->y0             ));
  const gchar *iterations_input     = gtk_editable_get_text(GTK_EDITABLE(converted_data->iteration_limit));
  
  double bottom_lim = g_ascii_strtod(bottom_limit_input ,NULL);
  double top_lim    = g_ascii_strtod(top_limit_input    ,NULL);
  double x0         = g_ascii_strtod(x0_input           ,NULL);
  double y0         = g_ascii_strtod(y0_input           ,NULL);
  double iter       = g_ascii_strtod(iterations_input   ,NULL);

  double result = calculation_function(bottom_lim,top_lim,iter,x0,y0);
  gchar *result_str = g_strdup_printf("   Result: %.6f",result);
  gtk_label_set_text(GTK_LABEL(converted_data->result_output),result_str);  
}

void
multi_integ(GtkWidget *button,
            gpointer   data)
{
  MultipleIntegCalcData *converted_data = (MultipleIntegCalcData*) data;
  mult_integ calculation_function     = (mult_integ) converted_data->function;
  
  const gchar *bottom_limit_x_input = gtk_editable_get_text(GTK_EDITABLE(converted_data->bottom_limit_x   ));
  const gchar *top_limit_x_input    = gtk_editable_get_text(GTK_EDITABLE(converted_data->top_limit_x      ));
  const gchar *bottom_limit_y_input = gtk_editable_get_text(GTK_EDITABLE(converted_data->bottom_limit_y   ));
  const gchar *top_limit_y_input    = gtk_editable_get_text(GTK_EDITABLE(converted_data->top_limit_y      ));
  const gchar *iterations_x         = gtk_editable_get_text(GTK_EDITABLE(converted_data->iteration_limit_x));
  const gchar *iterations_y         = gtk_editable_get_text(GTK_EDITABLE(converted_data->iteration_limit_y));

  double bottom_lim_x = g_ascii_strtod(bottom_limit_x_input ,NULL);
  double top_lim_x    = g_ascii_strtod(top_limit_x_input    ,NULL);
  double bottom_lim_y = g_ascii_strtod(bottom_limit_y_input ,NULL);
  double top_lim_y    = g_ascii_strtod(top_limit_y_input    ,NULL);
  double iter_x       = g_ascii_strtod(iterations_x         ,NULL);
  double iter_y       = g_ascii_strtod(iterations_y         ,NULL);

  double result = calculation_function(bottom_lim_x,top_lim_x,bottom_lim_y,top_lim_y,iter_x,iter_y);
  
  gchar *result_str = g_strdup_printf("   Result: %.6f",result);
  gtk_label_set_text(GTK_LABEL(converted_data->result_output),result_str);                     
}

void
dynamic_step_integ( GtkWidget *button,
                    gpointer   data)
{
  DynamicIntegCalcData *converted_data = (DynamicIntegCalcData*) data;
  dynamic_integ calculation_function     = (dynamic_integ) converted_data->function;
  
  const gchar *bottom_limit_input = gtk_editable_get_text(GTK_EDITABLE(converted_data->bottom_limit   ));
  const gchar *top_limit_input    = gtk_editable_get_text(GTK_EDITABLE(converted_data->top_limit      ));
  const gchar *accuracy_input     = gtk_editable_get_text(GTK_EDITABLE(converted_data->accuracy       ));

  double bottom_lim = g_ascii_strtod(bottom_limit_input ,NULL);
  double top_lim    = g_ascii_strtod(top_limit_input    ,NULL);
  double acc        = g_ascii_strtod(accuracy_input     ,NULL);

  double result = calculation_function(bottom_lim,top_lim,acc);
  
  gchar *result_str = g_strdup_printf("   Result: %.6f",result);
  gtk_label_set_text(GTK_LABEL(converted_data->result_output),result_str);                     
}

void
const_step_integ( GtkWidget *button,
                  gpointer data)
{
  ConstIntegCalcData *converted_data = (ConstIntegCalcData*) data;
  calc_func calculation_function     = (calc_func) converted_data->function;
  
  const gchar *bottom_limit_input = gtk_editable_get_text(GTK_EDITABLE(converted_data->bottom_limit   ));
  const gchar *top_limit_input    = gtk_editable_get_text(GTK_EDITABLE(converted_data->top_limit      ));
  const gchar *iterations_input   = gtk_editable_get_text(GTK_EDITABLE(converted_data->iteration_limit));

  double bottom_lim = g_ascii_strtod(bottom_limit_input ,NULL);
  double top_lim    = g_ascii_strtod(top_limit_input    ,NULL);
  double iter_lim   = g_ascii_strtod(iterations_input   ,NULL);

  double result = calculation_function(bottom_lim,top_lim,iter_lim);
  
  gchar *result_str = g_strdup_printf("   Result: %.6f",result);
  gtk_label_set_text(GTK_LABEL(converted_data->result_output),result_str);
}

GtkWidget 
*new_const_integ_menu( pointer_func func )
{
  GtkWidget *grid_container     = gtk_grid_new();
  GtkWidget *bottom_limit_entry = gtk_entry_new();
  GtkWidget *top_limit_entry    = gtk_entry_new();
  GtkWidget *iterations_entry   = gtk_entry_new();

  GtkWidget *calculate_button   = gtk_button_new_with_label("Вычислить");

  GtkWidget *function_label     = gtk_label_new("   Function: x^2");
  GtkWidget *bottom_limit_label = gtk_label_new(" A: ");
  GtkWidget *top_limit_label    = gtk_label_new(" B: ");
  GtkWidget *iterations_label   = gtk_label_new(" N: ");
  GtkWidget *result_label       = gtk_label_new("   Result: ");

  GtkWidget *blank_label        = gtk_label_new("");

  gtk_grid_attach(GTK_GRID(grid_container),bottom_limit_entry, 1,0,1,1);
  gtk_grid_attach(GTK_GRID(grid_container),function_label    , 2,0,1,1);
  gtk_grid_attach(GTK_GRID(grid_container),top_limit_entry   , 1,1,1,1);
  gtk_grid_attach(GTK_GRID(grid_container),result_label      , 2,1,2,1);
  gtk_grid_attach(GTK_GRID(grid_container),iterations_entry  , 1,2,1,1);

  gtk_grid_attach(GTK_GRID(grid_container),bottom_limit_label, 0,0,1,1);
  gtk_grid_attach(GTK_GRID(grid_container),top_limit_label   , 0,1,1,1);
  gtk_grid_attach(GTK_GRID(grid_container),iterations_label  , 0,2,1,1);
  
  gtk_grid_attach(GTK_GRID(grid_container),blank_label       , 0,4,4,1);
  gtk_grid_attach(GTK_GRID(grid_container),calculate_button  , 1,5,2,1);

  ConstIntegCalcData *args = malloc(sizeof(ConstIntegCalcData));
  args->bottom_limit    = bottom_limit_entry;
  args->top_limit       = top_limit_entry;
  args->iteration_limit = iterations_entry;
  args->function        = func;
  args->result_output   = result_label;

  g_signal_connect(calculate_button,"clicked",G_CALLBACK(const_step_integ),(gpointer) args);

  return grid_container;
}

GtkWidget 
*new_dynamic_integ_menu( pointer_func func )
{
  GtkWidget *grid_container     = gtk_grid_new();
  GtkWidget *bottom_limit_entry = gtk_entry_new();
  GtkWidget *top_limit_entry    = gtk_entry_new();
  GtkWidget *accuracy_entry     = gtk_entry_new();

  GtkWidget *calculate_button   = gtk_button_new_with_label("Вычислить");

  GtkWidget *function_label     = gtk_label_new("   Function: x^2");
  GtkWidget *bottom_limit_label = gtk_label_new(" A: ");
  GtkWidget *top_limit_label    = gtk_label_new(" B: ");
  GtkWidget *accuracy_label     = gtk_label_new(" E: ");
  GtkWidget *result_label       = gtk_label_new("   Result: ");

  GtkWidget *blank_label        = gtk_label_new("");

  gtk_grid_attach(GTK_GRID(grid_container),bottom_limit_entry, 1,0,1,1);
  gtk_grid_attach(GTK_GRID(grid_container),function_label    , 2,0,1,1);
  gtk_grid_attach(GTK_GRID(grid_container),top_limit_entry   , 1,1,1,1);
  gtk_grid_attach(GTK_GRID(grid_container),result_label      , 2,1,2,1);
  gtk_grid_attach(GTK_GRID(grid_container),accuracy_entry  , 1,2,1,1);

  gtk_grid_attach(GTK_GRID(grid_container),bottom_limit_label, 0,0,1,1);
  gtk_grid_attach(GTK_GRID(grid_container),top_limit_label   , 0,1,1,1);
  gtk_grid_attach(GTK_GRID(grid_container),accuracy_label  , 0,2,1,1);
  
  gtk_grid_attach(GTK_GRID(grid_container),blank_label       , 0,4,4,1);
  gtk_grid_attach(GTK_GRID(grid_container),calculate_button  , 1,5,2,1);

  DynamicIntegCalcData *args = malloc(sizeof(DynamicIntegCalcData));
  args->bottom_limit    = bottom_limit_entry;
  args->top_limit       = top_limit_entry;
  args->accuracy        = accuracy_entry;
  args->function        = func;
  args->result_output   = result_label;

  g_signal_connect(calculate_button,"clicked",G_CALLBACK(dynamic_step_integ),(gpointer) args);

  return grid_container;
}

GtkWidget 
*new_multiple_integ_menu( pointer_func func )
{
  GtkWidget *grid_container       = gtk_grid_new();
  GtkWidget *bottom_limit_x_entry = gtk_entry_new();
  GtkWidget *top_limit_x_entry    = gtk_entry_new();
  GtkWidget *bottom_limit_y_entry = gtk_entry_new();
  GtkWidget *top_limit_y_entry    = gtk_entry_new();
  GtkWidget *iterations_x_entry   = gtk_entry_new();
  GtkWidget *iterations_y_entry   = gtk_entry_new();

  GtkWidget *calculate_button   = gtk_button_new_with_label("Вычислить");

  GtkWidget *function_label       = gtk_label_new("   Function: sin(x+y)");
  GtkWidget *bottom_limit_x_label = gtk_label_new(" A: ");
  GtkWidget *top_limit_x_label    = gtk_label_new(" B: ");
  GtkWidget *bottom_limit_y_label = gtk_label_new(" C: ");
  GtkWidget *top_limit_y_label    = gtk_label_new(" D: ");
  GtkWidget *iterations_x_label   = gtk_label_new(" N_X: ");
  GtkWidget *iterations_y_label   = gtk_label_new(" N_Y: ");
  GtkWidget *result_label         = gtk_label_new("   Result: ");

  GtkWidget *blank_label          = gtk_label_new("");

  gtk_grid_attach(GTK_GRID(grid_container),bottom_limit_x_entry, 1,0,1,1);
  gtk_grid_attach(GTK_GRID(grid_container),function_label      , 2,0,1,1);
  gtk_grid_attach(GTK_GRID(grid_container),top_limit_x_entry   , 1,1,1,1);
  gtk_grid_attach(GTK_GRID(grid_container),bottom_limit_y_entry, 1,2,1,1);
  gtk_grid_attach(GTK_GRID(grid_container),top_limit_y_entry   , 1,3,1,1);
  gtk_grid_attach(GTK_GRID(grid_container),result_label        , 2,1,2,1);
  gtk_grid_attach(GTK_GRID(grid_container),iterations_x_entry  , 1,4,1,1);
  gtk_grid_attach(GTK_GRID(grid_container),iterations_y_entry  , 1,5,1,1);

  gtk_grid_attach(GTK_GRID(grid_container),bottom_limit_x_label, 0,0,1,1);
  gtk_grid_attach(GTK_GRID(grid_container),top_limit_x_label   , 0,1,1,1);
  gtk_grid_attach(GTK_GRID(grid_container),bottom_limit_y_label, 0,2,1,1);
  gtk_grid_attach(GTK_GRID(grid_container),top_limit_y_label   , 0,3,1,1);
  gtk_grid_attach(GTK_GRID(grid_container),iterations_x_label  , 0,4,1,1);
  gtk_grid_attach(GTK_GRID(grid_container),iterations_y_label  , 0,5,1,1);

  
  gtk_grid_attach(GTK_GRID(grid_container),blank_label       , 0,6,4,1);
  gtk_grid_attach(GTK_GRID(grid_container),calculate_button  , 1,7,2,1);

  MultipleIntegCalcData *args = malloc(sizeof(MultipleIntegCalcData));
  args->bottom_limit_x    = bottom_limit_x_entry;
  args->top_limit_x       = top_limit_x_entry;
  args->bottom_limit_y    = bottom_limit_y_entry;
  args->top_limit_y       = top_limit_y_entry;
  args->iteration_limit_x = iterations_x_entry;
  args->iteration_limit_y = iterations_y_entry;
  args->function          = func;
  args->result_output     = result_label;

  g_signal_connect(calculate_button,"clicked",G_CALLBACK(multi_integ),(gpointer) args);

  return grid_container;
}

GtkWidget 
*new_diff_menu( pointer_func func )
{
  GtkWidget *grid_container       = gtk_grid_new();
  GtkWidget *bottom_limit_entry   = gtk_entry_new();
  GtkWidget *top_limit_entry      = gtk_entry_new();
  GtkWidget *x0_entry             = gtk_entry_new();
  GtkWidget *y0_entry             = gtk_entry_new();
  GtkWidget *iterations_entry     = gtk_entry_new();

  GtkWidget *calculate_button     = gtk_button_new_with_label("Вычислить");

  GtkWidget *function_label       = gtk_label_new("   Function: y` = y*(1-x)");
  GtkWidget *bottom_limit_label   = gtk_label_new(" A: ");
  GtkWidget *top_limit_label      = gtk_label_new(" B: ");
  GtkWidget *x0_label             = gtk_label_new(" X0: ");
  GtkWidget *y0_label             = gtk_label_new(" Y0: ");
  GtkWidget *iterations_label     = gtk_label_new(" N: ");
  GtkWidget *result               = gtk_label_new("   Result: ");

  GtkWidget *blank_label          = gtk_label_new("");

  gtk_grid_attach(GTK_GRID(grid_container),bottom_limit_entry, 1,0,1,1);
  gtk_grid_attach(GTK_GRID(grid_container),function_label    , 2,0,1,1);
  gtk_grid_attach(GTK_GRID(grid_container),top_limit_entry   , 1,1,1,1);
  gtk_grid_attach(GTK_GRID(grid_container),x0_entry          , 1,2,1,1);
  gtk_grid_attach(GTK_GRID(grid_container),y0_entry          , 1,3,1,1);
  gtk_grid_attach(GTK_GRID(grid_container),result            , 2,1,2,1);
  gtk_grid_attach(GTK_GRID(grid_container),iterations_entry  , 1,4,1,1);

  gtk_widget_set_halign(result, GTK_ALIGN_CENTER);

  gtk_grid_attach(GTK_GRID(grid_container),bottom_limit_label, 0,0,1,1);
  gtk_grid_attach(GTK_GRID(grid_container),top_limit_label   , 0,1,1,1);
  gtk_grid_attach(GTK_GRID(grid_container),x0_label          , 0,2,1,1);
  gtk_grid_attach(GTK_GRID(grid_container),y0_label          , 0,3,1,1);
  gtk_grid_attach(GTK_GRID(grid_container),iterations_label  , 0,4,1,1);
  
  gtk_grid_attach(GTK_GRID(grid_container),blank_label       , 0,6,4,1);
  gtk_grid_attach(GTK_GRID(grid_container),calculate_button  , 1,7,2,1);

  DiffCalcData *args = malloc(sizeof(DiffCalcData));
  args->bottom_limit      = bottom_limit_entry;
  args->top_limit         = top_limit_entry;
  args->x0                = x0_entry;
  args->y0                = y0_entry;
  args->iteration_limit   = iterations_entry;
  args->function          = func;
  args->result_output     = result;

  g_signal_connect(calculate_button,"clicked",G_CALLBACK(diff_callback),(gpointer) args);

  return grid_container;
}

GtkWidget 
*new_diff_system_menu( pointer_func func )
{
  GtkWidget *grid_container       = gtk_grid_new();
  GtkWidget *bottom_limit_entry   = gtk_entry_new();
  GtkWidget *top_limit_entry      = gtk_entry_new();
  GtkWidget *x0_entry             = gtk_entry_new();
  GtkWidget *y0_entry             = gtk_entry_new();
  GtkWidget *z0_entry             = gtk_entry_new();
  GtkWidget *iterations_entry     = gtk_entry_new();

  GtkWidget *calculate_button     = gtk_button_new_with_label("Вычислить");

  GtkWidget *function_label       = gtk_label_new("   Function:\n    x` = -2x+5z\n    y` = sin(t-1)*x-y+3z\n    z` = -x+2z'");
  GtkWidget *bottom_limit_label   = gtk_label_new(" A: ");
  GtkWidget *top_limit_label      = gtk_label_new(" B: ");
  GtkWidget *x0_label             = gtk_label_new(" X0: ");
  GtkWidget *y0_label             = gtk_label_new(" Y0: ");
  GtkWidget *z0_label             = gtk_label_new(" Z0: ");
  GtkWidget *iterations_label     = gtk_label_new(" H: ");
  GtkWidget *result               = gtk_label_new("   Result: ");

  GtkWidget *blank_label          = gtk_label_new("");

  gtk_grid_attach(GTK_GRID(grid_container),bottom_limit_entry, 1,0,1,1);
  gtk_grid_attach(GTK_GRID(grid_container),function_label    , 0,6,1,1);
  gtk_grid_attach(GTK_GRID(grid_container),top_limit_entry   , 1,1,1,1);
  gtk_grid_attach(GTK_GRID(grid_container),x0_entry          , 1,2,1,1);
  gtk_grid_attach(GTK_GRID(grid_container),y0_entry          , 1,3,1,1);
  gtk_grid_attach(GTK_GRID(grid_container),z0_entry          , 1,4,1,1);
  gtk_grid_attach(GTK_GRID(grid_container),iterations_entry  , 1,5,1,1);
  gtk_grid_attach(GTK_GRID(grid_container),result            , 2,6,2,1);

  gtk_widget_set_halign(result, GTK_ALIGN_CENTER);

  gtk_grid_attach(GTK_GRID(grid_container),bottom_limit_label, 0,0,1,1);
  gtk_grid_attach(GTK_GRID(grid_container),top_limit_label   , 0,1,1,1);
  gtk_grid_attach(GTK_GRID(grid_container),x0_label          , 0,2,1,1);
  gtk_grid_attach(GTK_GRID(grid_container),y0_label          , 0,3,1,1);
  gtk_grid_attach(GTK_GRID(grid_container),z0_label          , 0,4,1,1);
  gtk_grid_attach(GTK_GRID(grid_container),iterations_label  , 0,5,1,1);
  
  gtk_grid_attach(GTK_GRID(grid_container),blank_label       , 0,7,4,1);
  gtk_grid_attach(GTK_GRID(grid_container),calculate_button  , 1,8,2,1);

  DiffSystemCalcData *args = malloc(sizeof(DiffSystemCalcData));
  args->bottom_limit      = bottom_limit_entry;
  args->top_limit         = top_limit_entry;
  args->x0                = x0_entry;
  args->y0                = y0_entry;
  args->z0                = z0_entry;
  args->iteration_limit   = iterations_entry;
  args->function          = func;
  args->result_output     = result;

  g_signal_connect(calculate_button,"clicked",G_CALLBACK(diff_system_callback),(gpointer) args);

  return grid_container;
}