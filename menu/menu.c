#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "menu.h"
#include "../math/integral/integs.c"
#include "../math/integral/integs.h"

typedef void(*pointer_func)();  //Тип указателя на функцию (Чтобы каждый раз это не писать)

typedef struct Option{
    char text[100]; //Текст опции
    struct Tab *next_tab;
    pointer_func action;    //Ссылка на функцию которую опция вызывает
} option;

typedef struct Tab{   
    char text[100]; //Текст вкладки
    struct Tab *previous_tab; //Предыдущая вкладка(Для операции "Назад")
    int amount_of_options;  //Количество опций
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

void option_test_function(){    //Тестовая функция для вызова опциями. Тут например могут быть функции из других файлов где у нас есть расчет интегралов 
    printf("This function was called using option!\n");
    printf("calc results: %d\n",integ_left_parts(1,10,100));
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
    pO->action = action;
    pO->next_tab = NULL;
    return pO;
}

tab* create_tab(char *text, tab *previous_tab, int amount_of_options, option **options_list){   //Создание новой вкладки
    tab *pT = NULL;
    pT = malloc(sizeof(tab));
    strcpy(pT->text, text);
    pT->previous_tab = previous_tab ? previous_tab : NULL;
    pT->amount_of_options = amount_of_options;
    pT->options_list = options_list;
    return pT;
}

void open_prev_tab(menu *pM){  //Сломаная кнопка возврата
    if (pM->current_tab->previous_tab == NULL){ 
        pM->is_runnging = false;
    }else{
    pM->current_tab = pM->current_tab->previous_tab;
    }
    pM->display_tab(pM);
}

void open_next_tab(menu *pM, tab *pNewTab){ //Открывает следующую вкладку
    pNewTab->previous_tab = pM->current_tab;
    pM->current_tab = pNewTab;
    pM->display_tab(pM);
}

int create_menu(){
    int input = 0;
    const int amount_of_tabs = 3; //При добавлении новых вкладок, нужно не забывать изменить это значение 

    option **options_list1 = NULL; //Создание опций для вкладки
    options_list1 = malloc(sizeof(option*)*4);

    options_list1[0] = create_option("Интегралы", open_next_tab);
    options_list1[1] = create_option("Дифференциальные уравнения", open_next_tab);
    options_list1[2] = create_option("Системы алгебрарических уравнений", open_next_tab);
    options_list1[3] = create_option("НУ", open_next_tab);

    tab *pDefaultTab = NULL; //Создание новой вкладки
    pDefaultTab = create_tab("Выберите тип решаемой задачи",NULL,4, options_list1);    //Текст вкладки, предыдущая вкладка, количество опций, список опций (Пришлось пихнуть отдельно количество опций т.к. sizeof() не работает с динамическими массивами и в си просто нет нормального способа найти длину такого массива)
    pDefaultTab->previous_tab = NULL;

    option **options_list2 = NULL;  //Опшан лист для второй вкладки
    options_list2 = malloc(sizeof(option*)*4);
    options_list2[0] = create_option("Метод прямоугольников левых частей", option_test_function);
    options_list2[1] = create_option("Метод прямоугольников правых частей", option_test_function);
    options_list2[2] = create_option("Метод трапеций", option_test_function);
    options_list2[3] = create_option("Метод парабол", option_test_function);

    tab *pIntegTab = NULL;   //Для теста перехода между вкладками (Опция 1 вкладки "pDefaultTab")
    pIntegTab = create_tab("Численное интегрирование",pDefaultTab,4, options_list2);
    pDefaultTab->options_list[0]->next_tab = pIntegTab;  //Завершаем связть между вкладками (До этого там был поинтер NULL)



    //Где то тут нужно прописывать все остальные вкалдки



    menu *pM = NULL; //Создание меню (По сути контроллер, который отвечает за то какая вкладка должна отображаться, и в какую передается пользовательский инпут)
    pM = malloc(sizeof(menu));

    pM->display_tab = display_menu; //Настройка меню
    pM->is_runnging = true;
    pM->current_tab = malloc(sizeof(tab));
    pM->list_of_tabs = malloc(sizeof(tab*)*amount_of_tabs);
    pM->list_of_tabs[0] = pDefaultTab;
    pM->list_of_tabs[1] = pIntegTab;
    pM->amount_of_tabs = amount_of_tabs;    //Та же херь, что и с количеством опций во вкладках, длину динамического массива тупа не найти
    pM->current_tab = pM->list_of_tabs[0];
    pM->return_button = create_option("Назад", open_prev_tab);
    
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
            pM->current_tab->options_list[input]->action();   //Вызов какой то функции, которая привязана к опции
        }else{
            pM->current_tab->options_list[input]->action(pM, pM->current_tab->options_list[input]->next_tab);   //Вызов функции перехода между вкладками
        }
    }

    free_menu(pM);
}
