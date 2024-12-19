#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "menu.h"

#include "../math/integral/IntegFunc.c"
#include "../math/integral/IntegFunc.h"
#include "../math/diff/DiffFunc.c"
#include "../math/diff/DiffFunc.h"

#include "../tools/data_saver.c"
#include "../tools/data_saver.h"

#include "../math/integral/ConstIntegs.c"
#include "../math/integral/ConstIntegs.h"
#include "../math/integral/DynamicIntegs.c"
#include "../math/integral/DynamicIntegs.h"
#include "../math/integral/MultipleIntegs.c"
#include "../math/integral/MultipleIntegs.h"

#include "../math/diff/Euler.c"
#include "../math/diff/Euler.h"
#include "../math/diff/Runge.c"
#include "../math/diff/Runge.h"
#include "../math/diff/EulerSys.c"
#include "../math/diff/EulerSys.h"

#define AMOUNT_OF_TABS      8 //При добавлении новых вкладок, нужно не забывать изменить это значение
#define CONST_INTEG_TAB     0
#define DYNAMIC_INTEG_TAB   1
#define MULTIPLE_INTEG_TAB  2
#define DIFF_TAB            3
#define DIFF_SIMPLE_TAB     4
#define DIFF_SYSTEM_TAB     5

int tab_id_counter = 0;

void option_test_function(){    //Тестовая функция для вызова опциями. Тут например могут быть функции из других файлов где у нас есть расчет интегралов 
    printf("This function was called using option!\n");
    printf("calc results: %lf\n",integ_left_parts(1,10,100));
}

void display_menu(menu *pM){    //Функция вывода меню
    printf("\e[1;1H\e[2J");
    printf("_____________________\n");
    printf("%s\n", pM->current_tab->text);
    for (int i = 0; i < pM->current_tab->amount_of_options; i++){
        printf("%d. %s\n",i ,pM->current_tab->options_list[i]->text);
    }
    printf("%d. Назад\n",pM->current_tab->amount_of_options);
    printf("‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n");
}

void free_menu(menu *pM){   //Убейте меня
    for (int i = 0; i < pM->amount_of_tabs-1; i++){
        for (int j = 0; j < pM->current_tab->amount_of_options-1; j++){ //Минус один т.к. кнопка возврата это один и тот же экземпляр структуры для всех вкладок. 
            free(pM->list_of_tabs[i]->options_list[j]);
        }
        free(pM->list_of_tabs[i]);
    }
    free(pM->return_button);
    free(pM);
}

option* create_option(char *text, pointer_func action){ //Создание новой опции
    option *pO = NULL;
    pO = malloc(sizeof(option));
    strcpy(pO->text, text);
    pO->action = (pointer_func) action;
    pO->next_tab = NULL;
    return pO;
}

tab* create_tab(char *text, tab *previous_tab, int amount_of_options, option **options_list, int type){   //Создание новой вкладки
    tab *pT = NULL;
    pT = malloc(sizeof(tab));
    pT->id = tab_id_counter;
    tab_id_counter++;
    pT->tab_type = type;
    strcpy(pT->text, text);
    pT->previous_tab = previous_tab ? previous_tab : NULL;
    pT->amount_of_options = amount_of_options;
    pT->options_list = options_list;
    for (int i = 0; i < amount_of_options;i++){
        options_list[i]->connected_tab = pT;
    }
    return pT;
}

void open_prev_tab(menu *pM){  //Сломаная кнопка возврата
    if (pM->current_tab->previous_tab == NULL){ 
        pM->is_runnging = false;
    }else{
    pM->current_tab = pM->current_tab->previous_tab;
    }
    //pM->display_tab(pM);
}

void open_next_tab(menu *pM, tab *pNewTab){ //Открывает следующую вкладку
    pNewTab->previous_tab = pM->current_tab;
    pM->current_tab = pNewTab;
    //pM->display_tab(pM);
}

menu* create_menu(){
    tab *pDefaultTab        = NULL; //Создание новой вкладки
    tab *pIntegTab          = NULL;
    tab *pConstIntegTab     = NULL;
    tab *pDynaicIntegTab    = NULL;
    tab *pMultipleIntegTab  = NULL;
    tab *pDiffTab           = NULL;
    tab *pDiffSimpleTab     = NULL;
    tab *pDiffSystemTab     = NULL;
    tab *pConstDiffTab      = NULL;
    tab *pConstSLETab       = NULL;

    option **defult_tab_option_list     = NULL; //Создание опций для вкладки
    option **integ_options_list         = NULL;  
    option **const_integ_options_list   = NULL;
    option **dynamic_integ_options_list = NULL;
    option **multiple_integ_options_list= NULL;
    option **diff_options_list          = NULL;
    option **diff_simple_options_list   = NULL;
    option **diff_system_options_list   = NULL;

    defult_tab_option_list = malloc(sizeof(option*)*4);
    defult_tab_option_list[0] = create_option("Интегралы", open_next_tab);
    defult_tab_option_list[1] = create_option("Дифференциальные уравнения", open_next_tab);
    defult_tab_option_list[2] = create_option("Приблеженное вычисление элементарных функций", open_next_tab);
    defult_tab_option_list[3] = create_option("Нелинейные уравнения", open_next_tab);
    pDefaultTab = create_tab("Выберите тип решаемой задачи",NULL, 4, defult_tab_option_list, -1);    //Текст вкладки, предыдущая вкладка, количество опций, список опций (Пришлось пихнуть отдельно количество опций т.к. sizeof() не работает с динамическими массивами и в си просто нет нормального способа найти длину такого массива)
    pDefaultTab->previous_tab = NULL;

    integ_options_list = malloc(sizeof(option*)*3);
    integ_options_list[0] = create_option("Интегрирование с постоянным шагом",open_next_tab);
    integ_options_list[1] = create_option("Интегрирование с переменным шагом", open_next_tab);
    integ_options_list[2] = create_option("Кратный интеграл", open_next_tab);
    pIntegTab = create_tab("Численное интегрирование", pIntegTab, 3,integ_options_list, -1);

    const_integ_options_list = malloc(sizeof(option*)*4);
    const_integ_options_list[0] = create_option("Метод прямоугольников левых частей",(pointer_func) integ_left_parts);
    const_integ_options_list[1] = create_option("Метод прямоугольников правых частей", (pointer_func) integ_right_parts);
    const_integ_options_list[2] = create_option("Метод трапеций", (pointer_func) integ_trapeze);
    const_integ_options_list[3] = create_option("Метод парабол", (pointer_func) integ_parabola);
    pConstIntegTab = create_tab("Постоянный шаг", pIntegTab, 4, const_integ_options_list, CONST_INTEG_TAB);

    dynamic_integ_options_list  = malloc(sizeof(option*)*2);
    dynamic_integ_options_list[0] = create_option("Двойной пересчет (Медленный)",(pointer_func) integ_dynamic_slow);
    dynamic_integ_options_list[1] = create_option("Быстрый алгоритм", (pointer_func) integ_dynamic_fast);
    pDynaicIntegTab = create_tab("Переменный шаг", pIntegTab, 2, dynamic_integ_options_list, DYNAMIC_INTEG_TAB);

    multiple_integ_options_list = malloc(sizeof(option));
    multiple_integ_options_list[0] = create_option("Метод квадратурных формул", (pointer_func) multiple_integ);
    pMultipleIntegTab = create_tab("Кратный интеграл", pIntegTab, 1, multiple_integ_options_list, MULTIPLE_INTEG_TAB);

    diff_options_list = malloc(sizeof(option*)*2);
    diff_options_list[0] = create_option("Дифференциальные уравнения", open_next_tab);
    diff_options_list[1] = create_option("Системы дифференциальных уравнений", open_next_tab);
    pDiffTab = create_tab("Дифференциальные уравнения", pDefaultTab, 2, diff_options_list,  -1);

    diff_simple_options_list = malloc(sizeof(option*)*2);
    diff_simple_options_list[0] = create_option("Метод Эйлера", (pointer_func) euler);
    diff_simple_options_list[1] = create_option("Метод Рунге-Кутта", (pointer_func) runge_kutt);
    pDiffSimpleTab = create_tab("Дифференциальные уравнения", pDiffTab, 2, diff_simple_options_list,  DIFF_SIMPLE_TAB);

    diff_system_options_list = malloc(sizeof(option*));
    diff_system_options_list[0] = create_option("Систеама, решенная методом Эйлера", (pointer_func) euler_system);
    pDiffSystemTab = create_tab("Системы дифференциальных уравнений", pDiffTab, 1, diff_system_options_list,  DIFF_SYSTEM_TAB);



    //Где то тут нужно прописывать все остальные вкалдки



    pDefaultTab->options_list[0]->next_tab = pIntegTab;  //Завершаем связть между вкладками (До этого там был поинтер NULL)
    pDefaultTab->options_list[1]->next_tab = pDiffTab;
    pIntegTab->options_list[0]->next_tab = pConstIntegTab;
    pIntegTab->options_list[1]->next_tab = pDynaicIntegTab;
    pIntegTab->options_list[2]->next_tab = pMultipleIntegTab;
    pDiffTab->options_list[0]->next_tab = pDiffSimpleTab;
    pDiffTab->options_list[1]->next_tab = pDiffSystemTab;

    menu *pM = NULL; //Создание меню (По сути контроллер, который отвечает за то какая вкладка должна отображаться, и в какую передается пользовательский инпут)
    pM = malloc(sizeof(menu));

    pM->display_tab = display_menu; //Настройка меню
    pM->is_runnging = true;
    pM->current_tab = malloc(sizeof(tab));
    pM->list_of_tabs = malloc(sizeof(tab*)*AMOUNT_OF_TABS);
    pM->list_of_tabs[pDefaultTab->id] = pDefaultTab;
    pM->list_of_tabs[pIntegTab->id]= pIntegTab;
    pM->list_of_tabs[pDiffTab->id] = pDiffTab;
    pM->list_of_tabs[pConstIntegTab->id] = pConstIntegTab;
    pM->list_of_tabs[pDynaicIntegTab->id] = pDynaicIntegTab;
    pM->list_of_tabs[pMultipleIntegTab->id] = pMultipleIntegTab;
    pM->list_of_tabs[pDiffSimpleTab->id] = pDiffSimpleTab;
    pM->list_of_tabs[pDiffSystemTab->id] = pDiffSystemTab;
    pM->amount_of_tabs = AMOUNT_OF_TABS;    //Та же херь, что и с количеством опций во вкладках, длину динамического массива тупа не найти
    pM->current_tab = pM->list_of_tabs[0];
    pM->return_button = create_option("Назад", open_prev_tab);

    return pM;
}

void run_menu(menu *pM){
    int input = 0;
    pM->display_tab(pM);    //Вывод дефолтной вкладки
    while ( pM->is_runnging )
    {
        printf("Выберите опцию (%d - %d): ", 0, pM->current_tab->amount_of_options);
        scanf("%d", &input);
        printf("\n");

        if (input < 0 || input > pM->current_tab->amount_of_options){ //Проверка на выбор вне диапазона
            continue;
        }
        if (input == pM->current_tab->amount_of_options){
            pM->return_button->action(pM);   //Вызов функции возврата
            continue;
        }

        if (pM->current_tab->options_list[input]->next_tab == NULL){
            calc_func call = (calc_func) pM->current_tab->options_list[input]->action;   //Вызов какой то функции, которая привязана к опции
            call(1,10,100);
        }else{
            pM->current_tab->options_list[input]->action(pM, pM->current_tab->options_list[input]->next_tab);   //Вызов функции перехода между вкладками
        }
    }

    free_menu(pM);
}
