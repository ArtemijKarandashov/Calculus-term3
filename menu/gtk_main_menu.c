#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>

#include "gtk_main_menu.h"
#include "gtk_submenu_tabs.c"
#include "gtk_submenu_tabs.h"
#include "menu.c"
#include "menu.h"

menu *pM = NULL;

GtkWidget **tabs = NULL;

GtkWidget *main_box = NULL;
GtkWidget *sub_box = NULL;

int tabs_counter = 0;

typedef GtkWidget*(*gtk_widget_func)(tab* tab_to_convert);  //Указатель на функцию создающуюю новый GtkWidget

typedef struct CallbackData{
  pointer_func function;
  char tab_name[100];
  int tab_type;
}CallbackData;

typedef struct CallbackSwapData{
  int prev_tab;
  int new_tab;
  gtk_widget_func generation_func;
}CallbackSwapData;

typedef struct GarbageData{
  CallbackData **pG;  //Указатель на функции
  CallbackSwapData **pSG; //Указатель на данные необходимые для переключения между вкладками
  ConstIntegCalcData **pCIG; //Указатель на данные необходимые для вычислений интеграла с постоянным шагом
  GtkWidget **pT; //Указатель на вкладки
  menu *pM;
  int pG_length;
  int pSG_length;
  int pT_length;
  int pCIG_length;
}GarbageData;

CallbackData **garbage_collector = NULL;
int garbage_counter = 0;
CallbackSwapData **swap_garbage_collector = NULL;
int swap_garbage_counter = 0;
ConstIntegCalcData **const_integ_garbage_collector = NULL;
int const_integ_counter = 0;


void 
clear_dynamic_memory( GtkWidget *widget,
                      gpointer data)
{
  GarbageData *garbage = (GarbageData*) data;  
  
  for (int i = 0; i < garbage->pG_length;i++)
  {
    free(garbage->pG[i]);
  }
  for (int i = 0; i < garbage->pSG_length;i++)
  {
    free(garbage->pSG[i]);
  }
  for (int i = 0; i < garbage->pT_length;i++)
  {
    free(garbage->pT[i]);
  }
  free_menu(garbage->pM);
  free(garbage);
}

void clear_box( GtkWidget *box )
{
  while (gtk_widget_get_first_child(GTK_WIDGET(box))!=NULL)
  {
    GtkWidget *child = gtk_widget_get_first_child(GTK_WIDGET(box));
    gtk_box_remove(GTK_BOX(box),child);
  }
}

double
create_submenu( GtkWidget *button ,
                gpointer data)
{
  CallbackData *converted_data = (CallbackData*) data;
  
  clear_box(sub_box);

  
  GtkWidget *tab_text = gtk_label_new(converted_data->tab_name); 
  int type = converted_data->tab_type;

  GtkWidget *new_input_tab = NULL;
  switch (type)
  {
  case CONST_INTEG_TAB:
    new_input_tab = new_const_integ_menu(converted_data->function);
    break;
  
  case DYNAMIC_INTEG_TAB:
    new_input_tab = new_dynamic_integ_menu(converted_data->function);
    break;
  case MULTIPLE_INTEG_TAB:
    new_input_tab = new_multiple_integ_menu(converted_data->function);
    break;
  case DIFF_SIMPLE_TAB:
    new_input_tab = new_diff_menu(converted_data->function);
    break;
  case DIFF_SYSTEM_TAB:
    new_input_tab = new_diff_system_menu(converted_data->function);
    break;
  default:
    g_print("WARNING : invalid tab type %d\n",type);
    break;
  }

  gtk_box_append(GTK_BOX(sub_box), tab_text);
  if (new_input_tab != NULL)
  {
  gtk_box_append(GTK_BOX(sub_box), new_input_tab);
  }
}

void 
display_tab( GtkWidget *button,
             gpointer data )
{
  CallbackSwapData *converted_data = (CallbackSwapData *) data;

  clear_box(main_box);
  clear_box(sub_box);

  GtkWidget *new_tab = converted_data->generation_func(pM->list_of_tabs[converted_data->new_tab]);

  gtk_box_prepend(GTK_BOX(main_box), new_tab);
}

GtkWidget*
tab_to_widget(tab *tab_to_convert)
{
  GtkWidget *container    = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
  GtkWidget *title_label  = gtk_label_new(tab_to_convert->text);
  tabs[tabs_counter]      = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  for (int j=0; j < tab_to_convert->amount_of_options;j++)
  {
    option *option_pointer = tab_to_convert->options_list[j];
    GtkWidget *tab_option = gtk_button_new_with_label(option_pointer->text);
      if (option_pointer->action != open_next_tab)
      {
        CallbackData *option_data          = malloc(sizeof(CallbackData));
        strcpy(option_data->tab_name,        option_pointer->text);
        option_data->function              = option_pointer->action;
        option_data->tab_type              = option_pointer->connected_tab->tab_type;
        garbage_collector[garbage_counter] = option_data;
        garbage_counter++;
        g_signal_connect(tab_option,"clicked",G_CALLBACK(create_submenu),(gpointer)option_data);
      }
      else
      {
        CallbackSwapData *option_data = malloc(sizeof(CallbackSwapData));

        //Созание кнопки 
        if (option_pointer->next_tab != NULL)
        {
          option_data->prev_tab           = tab_to_convert->id;
          option_data->new_tab            = option_pointer->next_tab->id;
          option_data->generation_func    = tab_to_widget;
          g_signal_connect(tab_option,"clicked",G_CALLBACK(display_tab),(gpointer)option_data);
        }
      }
    gtk_box_append(GTK_BOX(tabs[tabs_counter]), tab_option);
  }
  gtk_box_append(GTK_BOX(container),title_label);
  gtk_box_append(GTK_BOX(container),tabs[tabs_counter]);
  
  //Создание кнопки возврата
  if (tab_to_convert->id){  
    GtkWidget *return_button        = gtk_button_new_with_label("Назад");
    CallbackSwapData *option_data   = malloc(sizeof(CallbackSwapData));
    option_data->prev_tab           = tab_to_convert->id;
    option_data->new_tab            = 0;
    option_data->generation_func    = tab_to_widget;
    gtk_box_append(GTK_BOX(container),return_button);
    g_signal_connect(return_button,"clicked",G_CALLBACK(display_tab),(gpointer)option_data);
  }
  tabs_counter++;
  return container;
}

static void
activate (GtkApplication *app,
          gpointer        user_data)
{
  GtkWidget *start_window;
  GtkWidget *window_box         = gtk_box_new(GTK_ORIENTATION_VERTICAL,5);
  garbage_collector             = malloc(sizeof(CallbackData      ));
  swap_garbage_collector        = malloc(sizeof(CallbackSwapData  ));
  const_integ_garbage_collector = malloc(sizeof(ConstIntegCalcData));
  tabs                          = malloc(sizeof(GtkWidget*        ) * AMOUNT_OF_TABS);
  pM                            = create_menu();
  main_box                      = gtk_box_new(GTK_ORIENTATION_VERTICAL,10);
  sub_box                       = gtk_box_new(GTK_ORIENTATION_VERTICAL,5);

  tab       *default_menu_tab   = pM->list_of_tabs[0];
  GtkWidget *current_tab        = tab_to_widget(default_menu_tab);

  gtk_box_append(GTK_BOX(window_box), main_box   );
  gtk_box_append(GTK_BOX(window_box), sub_box    );
  gtk_box_append(GTK_BOX(main_box)  , current_tab);

  gtk_widget_set_halign(sub_box, GTK_ALIGN_CENTER);

  start_window = gtk_application_window_new (app);
  gtk_window_set_title        (GTK_WINDOW(start_window), "Вычеслительная математика");
  gtk_window_set_default_size (GTK_WINDOW(start_window), 450, 432);
  gtk_window_set_resizable    (GTK_WINDOW(start_window), FALSE);
  gtk_window_set_child        (GTK_WINDOW(start_window), window_box);

  GarbageData *garbage = malloc(sizeof(GarbageData));
  garbage->pG           = garbage_collector;
  garbage->pSG          = swap_garbage_collector;
  garbage->pCIG         = const_integ_garbage_collector;
  garbage->pT           = tabs;
  garbage->pM           = pM;
  garbage->pG_length    = garbage_counter;
  garbage->pSG_length   = swap_garbage_counter;
  garbage->pT_length    = AMOUNT_OF_TABS;
  garbage->pCIG_length  = const_integ_counter;

  g_signal_connect(app,"shutdown",G_CALLBACK(clear_dynamic_memory),garbage);
  gtk_window_present (GTK_WINDOW (start_window)); //Открывает стартовое окно
}

int
gtk_run_menu (int    argc,
              char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("gtk.org.example", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}

