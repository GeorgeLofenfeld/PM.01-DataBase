/*
    Лофенфельд Георгий Владимирович
    ПКС - 303
    ***
    Вариант 30 - База Данных Митингов
    ***
    Описание функций, которые вызываются при взаимодествии с кнопками
*/

#pragma once 
#include "button_activities.h"

void meeting_main(Frontend* fd) {
    /*
    Переключается между отображаемыми наборами кнопок
    ***
    Принимает ссылку на Frontend (отвечает за отображение и взаимодействие)
    */
    Layout* l = fd->get_layout(1);
    wchar_t names_to_hide[9][128] = { L"Сортировать по:",
        L"Дате", L"Времени", L"Количеству заявленных участников", L"Количеству фактических участников", L"Адресу", L"ФИО Заявителя", L"Разрешению", L"Назад" };
    wchar_t names_to_show[6][128] = { L"Установите режим:", L"Сортировка",
        L"Добавление", L"Редактирование", L"Удаление", L"Поиск" };
    for (int i = 0; i < 9; i++)
        l->get_object_by_caption(names_to_hide[i])->deactivate();
    for (int i = 0; i < 6; i++)
        l->get_object_by_caption(names_to_show[i])->activate();
}

void declarers_main(Frontend* fd) {
    Layout* l = fd->get_layout(2);
    wchar_t names_to_hide[4][128] = { L"Сортировать по:",
    L"ФИО", L"Нарушениям", L"Назад" };
    wchar_t names_to_show[6][128] = { L"Установите режим:", L"Сортировка",
        L"Добавление", L"Редактирование", L"Удаление", L"Поиск" };
    for (int i = 0; i < 4; i++)
        l->get_object_by_caption(names_to_hide[i])->deactivate();
    for (int i = 0; i < 6; i++)
        l->get_object_by_caption(names_to_show[i])->activate();
}

void offences_main(Frontend* fd) {
    Layout* l = fd->get_layout(3);
    wchar_t names_to_hide[7][128] = { L"Сортировать по:",
    L"Митингам", L"ФИО Нарушителя", L"Нормативному акту", L"Статье и пункту", L"Флагу осуждения судом", L"Назад" };
    wchar_t names_to_show[6][128] = { L"Установите режим:", L"Сортировка",
        L"Добавление", L"Редактирование", L"Удаление", L"Поиск" };
    for (int i = 0; i < 7; i++)
        l->get_object_by_caption(names_to_hide[i])->deactivate();
    for (int i = 0; i < 6; i++)
        l->get_object_by_caption(names_to_show[i])->activate();
}

void meeting_showing(Frontend* fd) {
    /*
    Переключается между отображаемыми наборами кнопок (инверсивно по отношению к meeting_main etc.)
    ***
    Принимает ссылку на Frontend (отвечает за отображение и взаимодействие)
    */
    Layout* l = fd->get_layout(1);
    wchar_t names_to_show[9][128] = { L"Сортировать по:",
        L"Дате", L"Времени", L"Количеству заявленных участников", L"Количеству фактических участников", L"Адресу", L"ФИО Заявителя", L"Разрешению", L"Назад" };
    wchar_t names_to_hide[6][128] = { L"Установите режим:", L"Сортировка",
        L"Добавление", L"Редактирование", L"Удаление", L"Поиск" };
    for (int i = 0; i < 6; i++)
        l->get_object_by_caption(names_to_hide[i])->deactivate();
    for (int i = 0; i < 9; i++)
        l->get_object_by_caption(names_to_show[i])->activate();
}

void declarers_showing(Frontend* fd) {
    Layout* l = fd->get_layout(2);
    wchar_t names_to_show[4][128] = { L"Сортировать по:",
    L"ФИО", L"Нарушениям", L"Назад" };
    wchar_t names_to_hide[6][128] = { L"Установите режим:", L"Сортировка",
        L"Добавление", L"Редактирование", L"Удаление", L"Поиск" };
    for (int i = 0; i < 6; i++)
        l->get_object_by_caption(names_to_hide[i])->deactivate();
    for (int i = 0; i < 4; i++)
        l->get_object_by_caption(names_to_show[i])->activate();
}

void offences_showing(Frontend* fd) {
    Layout* l = fd->get_layout(3);
    wchar_t names_to_show[7][128] = { L"Сортировать по:",
    L"Митингам", L"ФИО Нарушителя", L"Нормативному акту", L"Статье и пункту", L"Флагу осуждения судом", L"Назад" };
    wchar_t names_to_hide[6][128] = { L"Установите режим:", L"Сортировка",
        L"Добавление", L"Редактирование", L"Удаление", L"Поиск" };
    for (int i = 0; i < 6; i++)
        l->get_object_by_caption(names_to_hide[i])->deactivate();
    for (int i = 0; i < 7; i++)
        l->get_object_by_caption(names_to_show[i])->activate();
}

void go_meeting(Frontend* fd) {
    /*
    Переход на другой layout
    ***
    Принимает ссылку на Frontend (отвечает за отображение и взаимодействие)
    */
    fd->change_layout(1);
    meeting_main(fd);
}

void go_declarers(Frontend* fd) {
    fd->change_layout(2);
    declarers_main(fd);
}

void go_offences(Frontend* fd) {
    fd->change_layout(3);
    offences_main(fd);
}

Table* get_table(Frontend* fd, int i, int choose) {
    /*
    Вспомогательная функция для получения ссылки на таблцу из конкретного layout
    ***
    Принимает ссылку на Frontend (отвечает за отображение и взаимодействие), i - индекс layout, choose - если 1, то таблица считается выбранной
    */
    Layout* l = fd->get_layout(i);
    wchar_t t_name[3][128] = { L"ТАБЛИЦА МИТИНГОВ", L"ТАБЛИЦА ЗАЯВИТЕЛЕЙ", L"ТАБЛИЦА ПРАВОНАРУШЕНИЙ" };
    Table* table = (Table*)l->get_object_by_caption(t_name[i - 1]);
    if (choose)
        l->change_swichable_object(table);
    return table;
}


void meeting_sort(Frontend* fd) {
    /*
    Вызывает сортировку в зависимости от нажатой кнопки
    ***
    Принимает ссылку на Frontend (отвечает за отображение и взаимодействие)
    */
    Layout* l = fd->get_layout(1);
    Layout_object* lo = l->get_chosen_object();
    wchar_t names[7][128] = { L"Дате", L"Времени", L"Количеству заявленных участников", L"Количеству фактических участников", L"Адресу", L"ФИО Заявителя", L"Разрешению" };
    if (lo != nullptr) {
        int index = -1;
        for (int i = 0; i < 7; i++)
            if (wcscmp(names[i], lo->get_caption()) == 0)
                index = i;
        Table* table = get_table(fd, 1, 0);
        if (index >= 0)
            table->get_database()->sort_by_index(index);
    }
}

void declarers_sort(Frontend* fd) {
    Layout* l = fd->get_layout(2);
    Layout_object* lo = l->get_chosen_object();
    wchar_t names[2][128] = { L"ФИО", L"Нарушениям" };
    if (lo != nullptr) {
        int index = -1;
        for (int i = 0; i < 2; i++)
            if (wcscmp(names[i], lo->get_caption()) == 0)
                index = i;
        Table* table = get_table(fd, 2, 0);
        if (index >= 0)
            table->get_database()->sort_by_index(index);
    }
}

void offences_sort(Frontend* fd) {
    Layout* l = fd->get_layout(3);
    Layout_object* lo = l->get_chosen_object();
    wchar_t names[5][128] = { L"Митингам", L"ФИО Нарушителя", L"Нормативному акту", L"Статье и пункту", L"Флагу осуждения судом" };
    if (lo != nullptr) {
        int index = -1;
        for (int i = 0; i < 5; i++)
            if (wcscmp(names[i], lo->get_caption()) == 0)
                index = i;
        Table* table = get_table(fd, 3, 0);
        if (index >= 0)
            table->get_database()->sort_by_index(index);
    }
}

void add_to_meetings_table(Frontend* fd) {
    /*
    Запускает процесс добавления данных в таблицу
    ***
    Принимает ссылку на Frontend (отвечает за отображение и взаимодействие)
    */
    Table* table = get_table(fd, 1);
    table->change_state(Table::adding);

}

void add_to_declarers_table(Frontend* fd) {
    Table* table = get_table(fd, 2);
    table->change_state(Table::adding);

}

void add_to_offences_table(Frontend* fd) {
    Table* table = get_table(fd, 3);
    table->change_state(Table::adding);

}

void meetings_delete(Frontend* fd) {
    /*
    Запускает процесс выбора данных для удаления из таблицы
    ***
    Принимает ссылку на Frontend (отвечает за отображение и взаимодействие)
    */
    Table* table = get_table(fd, 1);
    table->change_state(Table::deleting);
}

void declarers_delete(Frontend* fd) {
    Table* table = get_table(fd, 2);
    table->change_state(Table::deleting);
}

void offences_delete(Frontend* fd) {
    Table* table = get_table(fd, 3);
    table->change_state(Table::deleting);
}


void meetings_change(Frontend* fd) {
    /*
    Запускает процесс выбора данных для изменения в таблице (построчно)
    ***
    Принимает ссылку на Frontend (отвечает за отображение и взаимодействие)
    */
    Table* table = get_table(fd, 1);
    table->change_state(Table::choosing_for_changing);
}

void declarers_change(Frontend* fd) {
    Table* table = get_table(fd, 2);
    table->change_state(Table::choosing_for_changing);
}

void offences_change(Frontend* fd) {
    Table* table = get_table(fd, 3);
    table->change_state(Table::choosing_for_changing);
}

void meetings_search(Frontend* fd) {
    /*
    Запускает процесс поиска
    ***
    Принимает ссылку на Frontend (отвечает за отображение и взаимодействие)
    */
    Table* table = get_table(fd, 1);
    table->change_state(Table::searching);
}

void declarers_search(Frontend* fd) {
    Table* table = get_table(fd, 2);
    table->change_state(Table::searching);
}

void offences_search(Frontend* fd) {
    Table* table = get_table(fd, 3);
    table->change_state(Table::searching);
}

void save(Frontend* fd) {
    /*
    Запускает процесс сохранения данных из всех таблиц
    ***
    Принимает ссылку на Frontend (отвечает за отображение и взаимодействие)
    */
    Table* table = get_table(fd, 1, 0);
    int ok = table->get_database()->get_base_operator()->save();// get_base_operator един для всех
    Layout* l = fd->get_layout(0);
    wchar_t t_name[128] = L"Сохранить";
    Button* button = (Button*)l->get_object_by_caption(t_name);
    move_cursor_to(button->get_x() + 10, button->get_y());
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (ok) { // Если сохранение успешно, метод save вернёт 1, иначе 0 (Base_operator::save)
        SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
        printf("Сохранение успешно");
    }
    else {
        SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
        printf("Сохранение невозможно");
    }
    fd->wait();
    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);

}

void exit(Frontend* fd) {
    /*
    Запускает процесс выхода из программы при нажатии кнопки "Выход"
    ***
    Принимает ссылку на Frontend (отвечает за отображение и взаимодействие)
    */
    fd->stop();
}

