#include <stdbool.h>
#include "../math/diff/Euler.h"
#include "../math/diff/EulerSys.h"
#ifndef MENU
#define MENU

typedef EulerSystemAns (*calc_diff_system)(double a, double b, double h, double x0, double y0, double z0);
typedef double (*notlinear_calc)(double a, double b, double e);
typedef double (*cheb_func)(double x, double e);
typedef double (*calc_diff)(double a, double b, int n, double x0, double y0);
typedef double(*calc_func)(double min, double max, int n);
typedef double(*dynamic_integ)(double min, double max, double acc);
typedef double(*mult_integ)(double a, double b, double c, double d, double n_x, double n_y);
typedef void(*pointer_func)();  //Тип указателя на функцию (Чтобы каждый раз это не писать)

typedef struct Option{
    char text[100]; //Текст опции
    struct Tab *connected_tab;
    struct Tab *next_tab;
    pointer_func action;    //Ссылка на функцию которую опция вызывает
} option;

typedef struct Tab{   
    char text[100]; //Текст вкладки
    struct Tab *previous_tab; //Предыдущая вкладка(Для операции "Назад")
    int amount_of_options;  //Количество опций
    int id;
    int tab_type;
    option **options_list;  //Список опций
} tab;

typedef struct Menu{
    bool is_runnging;   //Вот это должно переводиться в состояние "fakse" когда из начальной вкладки происводиться операция "Назад", но чет дааааа, не работает ничего у меня
    int amount_of_tabs; //Количество вкладок
    tab **list_of_tabs; //Массив со всеми вкладками
    tab *current_tab;   //Текущая вкладка
    pointer_func display_tab;   //Ссылка на функцию отображабщую меню
    option *return_button;
} menu;


void option_test_function();   //Тестовая функция для вызова опциями. Тут например могут быть функции из других файлов где у нас есть расчет интегралов 
void display_menu(menu *pM);   //Функция вывода меню
void free_menu(menu *pM);   //Убейте меня
option* create_option(char *text, pointer_func action); //Создание новой опции
tab* create_tab(char *text, tab *previous_tab, int amount_of_options, option **options_list, int type);   //Создание новой вкладки
void open_prev_tab(menu *pM); //Сломаная кнопка возврата
void open_next_tab(menu *pM, tab *pNewTab); //Открывает следующую вкладку
menu* create_menu();
void run_menu(menu *pM);

#endif