#include <gtk/gtk.h>
#include "gtk_submenu_tabs.h"
#include "menu.h"

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