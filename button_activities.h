/*
    Лофенфельд Георгий Владимирович
    ПКС - 303
    ***
    Вариант 30 - База Данных Митингов
    ***
    Объявления функций реализованных в модуле button_activities.cpp
*/

#pragma once
#include "frontend.h"

void meeting_main(Frontend* fd); // Переключается между отображаемыми наборами кнопок

void declarers_main(Frontend* fd); 

void offences_main(Frontend* fd);

void meeting_showing(Frontend* fd); // Переключается между отображаемыми наборами кнопок (инверсивно по отношению к meeting_main)

void declarers_showing(Frontend* fd);

void offences_showing(Frontend* fd);

void go_meeting(Frontend* fd); // Переход на другой layout

void go_declarers(Frontend* fd);

void go_offences(Frontend* fd);

Table* get_table(Frontend* fd, int i, int choose = 1); // Вспомогательная функция для получения ссылки на таблцу из конкретного layout

void meeting_sort(Frontend* fd); // Вызывает сортировку в зависимости от нажатой кнопки

void declarers_sort(Frontend* fd);

void offences_sort(Frontend* fd);

void add_to_meetings_table(Frontend* fd);  // Запускает процесс добавления данных в таблицу

void add_to_declarers_table(Frontend* fd);

void add_to_offences_table(Frontend* fd);

void meetings_delete(Frontend* fd); // Запускает процесс выбора данных для удаления из таблицы

void declarers_delete(Frontend* fd);

void offences_delete(Frontend* fd);

void meetings_change(Frontend* fd); // Запускает процесс выбора данных для изменения в таблице (построчно)

void declarers_change(Frontend* fd);

void offences_change(Frontend* fd);

void meetings_search(Frontend* fd); // Запускает процесс поиска

void declarers_search(Frontend* fd);

void offences_search(Frontend* fd);

void save(Frontend* fd); // Запускает процесс сохранения данных из всех таблиц

void exit(Frontend* fd); // Запускает процесс выхода из программы при нажатии кнопки "Выход"
