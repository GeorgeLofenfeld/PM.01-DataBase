/*
    Лофенфельд Георгий Владимирович
    ПКС - 303
    ***
    Вариант 30 - База Данных Митингов
    ***
    Для чего модуль?
*/

#pragma once 
#define FOREGROUND_YELLOW 14
#define FOREGROUND_TURQUOISE 11

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
    L"Митингам", L"ФИО Нарушителя", L"Нормативному акту", L"Статье и пункту", L"Флагу осуждения судом", L"Назад"};
    wchar_t names_to_show[6][128] = { L"Установите режим:", L"Сортировка",
        L"Добавление", L"Редактирование", L"Удаление", L"Поиск" };
    for (int i = 0; i < 7; i++)
        l->get_object_by_caption(names_to_hide[i])->deactivate();
    for (int i = 0; i < 6; i++)
        l->get_object_by_caption(names_to_show[i])->activate();
}

void meeting_showing(Frontend* fd){
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
    L"Митингам", L"ФИО Нарушителя", L"Нормативному акту", L"Статье и пункту", L"Флагу осуждения судом", L"Назад"};
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
    ринимает ссылку на Frontend (отвечает за отображение и взаимодействие)
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

Table* get_table(Frontend* fd, int i, int choose = 1) {
    /*
    Вспомогательная функция для получения ссылки на таблцу из конкретного layout
    ***
    Принимает ссылку на Frontend (отвечает за отображение и взаимодействие), i - индекс layout, choose - если 1, то таблица считается выбранной
    */
    Layout* l = fd->get_layout(i);
    wchar_t t_name[3][128] = { L"ТАБЛИЦА МИТИНГОВ", L"ТАБЛИЦА ЗАЯВИТЕЛЕЙ", L"ТАБЛИЦА ПРАВОНАРУШЕНИЙ" };
    Table* table = (Table*)l->get_object_by_caption(t_name[i-1]);
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
    wchar_t names[7][128] = {L"Дате", L"Времени", L"Количеству заявленных участников", L"Количеству фактических участников", L"Адресу", L"ФИО Заявителя", L"Разрешению" };
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
    wchar_t names[5][128] = { L"Митингам", L"ФИО Нарушителя", L"Нормативному акту", L"Статье и пункту", L"Флагу осуждения судом"};
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
    Button *button = (Button*)l->get_object_by_caption(t_name);
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


Layout* create_menu_layout() {
    /*
    Сборка и создание menu layout
    */
    static Layout main_menu = Layout();
    wchar_t names[9][128] = { L"БАЗА ДАННЫХ МИТИНГОВ", L"МЕНЮ", L"Митинги",
        L"Заявители", L"Правонарушения", L"Сохранить", L"Выйти", L"ВВЕРХ / ВНИЗ: Переключение пункта меню\nENTER: Выбор пункта меню", L"Лофенфельд Георгий\nПКС-303"};
    static Text texts[4] = { Text(5, 3, names[0]), Text(5, 5, names[1]), Text(0, 39, names[7], FOREGROUND_TURQUOISE), Text(0, 44, names[8], FOREGROUND_YELLOW)};
    static Button buttons[5] = {
        Button(5, 7, names[2], go_meeting),
        Button(5, 8, names[3], go_declarers),
        Button(5, 9, names[4], go_offences),
        Button(5, 11, names[5], save),
        Button(5, 12, names[6], exit)
    };
    Layout_object* objects[9] = {};
    for (int i = 0; i < 4; i++)
        objects[i] = &texts[i];
    for (int i = 4; i < 9; i++)
        objects[i] = &buttons[i-4];
    main_menu.add_object(objects, 9);
    return &main_menu;
}

Layout* create_meetings_layout(Database *db) { 
    /*
    Сборка и создание meetings layout
    ***
    Принимает ссылку на Database (конкретную базу данных)
    */
    static Layout meetings = Layout();
    wchar_t names[28][1024] = { L"ТАБЛИЦА МИТИНГОВ", L"Установите режим:", L"Сортировка",
        L"Добавление", L"Редактирование", L"Удаление", L"Поиск", L"Сортировать по:",
        L"Дате", L"Времени", L"Количеству заявленных участников", L"Количеству фактических участников", L"Разрешению", L"Назад",
        L"ДАТА", L"ВРЕМЯ", L"КОЛ. ЗАЯВ. УЧАСТН.", L"КОЛ. ФАКТ. УЧАСТН.",
        L"АДРЕС", L"ФИО ЗАЯВИТЕЛЯ", L"РАЗРЕШЕНИЕ", L"ВВЕРХ / ВНИЗ: Переключение режима таблицы / сотировки / строки при удалении, редактировании / разрешённости", L"ВЛЕВО / ВПРАВО: Переключение страницы", L"ENTER: Выбор режима таблицы / сортировки / подтверждение ввода / подтверждение поискового запроса", L"ESC: Выход в главное меню / выход из режима таблицы", L"(c) 2022 Created by George L.", L"Адресу", L"ФИО Заявителя"};
    static Text texts[7] = { Text(5, 3, names[1]), Text(5, 3, names[7]), Text(0, 39, names[21], FOREGROUND_TURQUOISE), Text(0, 40, names[22], FOREGROUND_TURQUOISE), Text(0, 41, names[23], FOREGROUND_TURQUOISE), Text(0, 42, names[24], FOREGROUND_TURQUOISE), Text(0, 44, names[25], FOREGROUND_YELLOW) };
    static Button buttons[13] = {
        Button(25, 3, names[2],meeting_showing),
        Button(38, 3, names[3], add_to_meetings_table),
        Button(51, 3, names[4], meetings_change),
        Button(68, 3, names[5], meetings_delete),
        Button(79, 3, names[6],meetings_search),
        Button(23, 3, names[8],meeting_sort),
        Button(30, 3, names[9],meeting_sort),
        Button(40, 3, names[10],meeting_sort),
        Button(75, 3, names[11],meeting_sort),
        Button(111, 3, names[26],meeting_sort),
        Button(120, 3, names[27],meeting_sort),
        Button(136, 3, names[12],meeting_sort),
        Button(158, 3, names[13],meeting_main), 
    };
    wchar_t table_names[20][128] = {};
    int sizes[7] = { 10, 10, 21, 21, 60, 60, 13 };
    static Date_time_handler dth[2] = { Date_time_handler(1), Date_time_handler(0) };
    static Int_char_handler ich[4] = { 
        Int_char_handler(sizes[2],1,0), Int_char_handler(sizes[3],1,0),
        Int_char_handler(sizes[4],1,1), Int_char_handler(sizes[5],0,1) };
    static Bool_handler bh = Bool_handler();
    Key_handler* kh[7] = { &dth[0],&dth[1],&ich[0], &ich[1],&ich[2],&ich[3],&bh };
    for (int i = 0; i < 7; i++)
        wcscpy(table_names[i], names[i + 14]);
    static Table table = Table(0, 10, 20, 7, names[0], table_names, sizes, db);
    for (int i = 0; i < 7; i++)
        table.set_i_handler(i, kh[i]);
    Layout_object* objects[21] = {};
    for (int i = 0; i < 7; i++)
        objects[i] = &texts[i];
    for (int i = 7; i < 20; i++)
        objects[i] = &buttons[i - 7];
    objects[20] = &table;
    meetings.add_object(objects, 21);
    return &meetings;
}

Layout* create_declarers_layout(Database* db) {
    /*
    Сборка и создание declarers layout
    ***
    Принимает ссылку на Database (конкретную базу данных)
    */
    static Layout declarers = Layout();
    wchar_t names[18][128] = { L"ТАБЛИЦА ЗАЯВИТЕЛЕЙ", L"Установите режим:", L"Сортировка",
    L"Добавление", L"Редактирование", L"Удаление", L"Поиск", L"Сортировать по:", 
    L"ФИО", L"Нарушениям", L"Назад", L"ФИО ЗАЯВИТЕЛЯ", L"НАЛИЧИЕ НАРУШЕНИЙ", L"ВВЕРХ / ВНИЗ: Переключение режима таблицы / сотировки / строки при удалении, редактировании / правонарушений", L"ВЛЕВО / ВПРАВО: Переключение страницы", L"ENTER: Выбор режима таблицы / сортировки / подтверждение ввода / подтверждение поискового запроса", L"ESC: Выход в главное меню / выход из режима таблицы", L"(c) 2022 Created by George L." };
    static Text texts[7] = { Text(5, 3, names[1]), Text(5, 3, names[7]), Text(0, 39, names[13], FOREGROUND_TURQUOISE), Text(0, 40, names[14], FOREGROUND_TURQUOISE), Text(0, 41, names[15], FOREGROUND_TURQUOISE), Text(0, 42, names[16], FOREGROUND_TURQUOISE), Text(0, 44, names[17], FOREGROUND_YELLOW) };
    static Button buttons[8] = {
        Button(25, 3, names[2], declarers_showing),
        Button(38, 3, names[3], add_to_declarers_table),
        Button(51, 3, names[4], declarers_change),
        Button(68, 3, names[5], declarers_delete),
        Button(79, 3, names[6], declarers_search),
        Button(23, 3, names[8], declarers_sort),
        Button(29, 3, names[9], declarers_sort),
        Button(51, 3, names[10],declarers_main)
    };
    wchar_t table_names[20][128] = {};
    int sizes[2] = { 60, 20 };
    static Int_char_handler ich =  Int_char_handler(sizes[0],0,1);
    static Bool_handler bh = Bool_handler();
    Key_handler* kh[2] = { &ich ,&bh };
    for (int i = 0; i < 2; i++)
        wcscpy(table_names[i], names[i + 11]);
    static Table table = Table(0, 10, 20, 2, names[0], table_names, sizes, db);
    for (int i = 0; i < 2; i++)
        table.set_i_handler(i, kh[i]);
    Layout_object* objects[16] = {};
    for (int i = 0; i < 7; i++)
        objects[i] = &texts[i];
    for (int i = 7; i < 15; i++)
        objects[i] = &buttons[i - 7];
    objects[15] = &table;
    declarers.add_object(objects, 16);
    return &declarers;
}


Layout* create_offences_layout(Database* db) { 
    /*
    Сборка и создание offences layout
    ***
    Принимает ссылку на Database (конкретную базу данных)
    */
    static Layout offences = Layout();
    wchar_t names[24][128] = { L"ТАБЛИЦА ПРАВОНАРУШЕНИЙ", L"Установите режим:", L"Сортировка",
    L"Добавление", L"Редактирование", L"Удаление", L"Поиск", L"Сортировать по:",
    L"Митингам", L"ФИО Нарушителя",  L"Нормативному акту", L"Статье и пункту", L"Флагу осуждения судом",
    L"Назад", L"МИТИНГ",L"ФИО НАРУШИТЕЛЯ", L"НОРМАТИВНЫЙ АКТ", L"СТАТЬЯ И ПУНКТ", L"ОСУЖДЕНИЕ СУДОМ", L"ВВЕРХ / ВНИЗ: Переключение режима таблицы / сотировки / строки при удалении, редактировании / осуждения судом", L"ВЛЕВО / ВПРАВО: Переключение страницы", L"ENTER: Выбор режима таблицы / сортировки / подтверждение ввода / подтверждение поискового запроса", L"ESC: Выход в главное меню / выход из режима таблицы", L"(c) 2022 Created by George L." };
    static Text texts[7] = { Text(5, 3, names[1]), Text(5, 3, names[7]), Text(0, 39, names[19], FOREGROUND_TURQUOISE), Text(0, 40, names[20], FOREGROUND_TURQUOISE), Text(0, 41, names[21], FOREGROUND_TURQUOISE), Text(0, 42, names[22], FOREGROUND_TURQUOISE), Text(0, 44, names[23], FOREGROUND_YELLOW) }; // статик текст
    static Button buttons[11] = {
        Button(25, 3, names[2], offences_showing),
        Button(38, 3, names[3], add_to_offences_table),
        Button(51, 3, names[4], offences_change),
        Button(68, 3, names[5], offences_delete),
        Button(79, 3, names[6], offences_search),
        Button(23, 3, names[8], offences_sort),
        Button(34, 3, names[9], offences_sort),
        Button(51, 3, names[10], offences_sort),
        Button(71, 3, names[11], offences_sort),
        Button(89, 3, names[12], offences_sort),
        Button(122, 3, names[13],offences_main)
    }; 
    wchar_t table_names[20][128] = {}; // названия столбцов
    int sizes[5] = { 50, 50, 50, 30, 18}; // размеры столбцов
    static Int_char_handler ich[4] =
    { Int_char_handler(sizes[0], 1, 1),
    Int_char_handler(sizes[1], 0, 1),
    Int_char_handler(sizes[2], 1, 1),
    Int_char_handler(sizes[3], 1, 1) };
    static Bool_handler bh = Bool_handler();
    for (int i = 0; i < 5; i++)
        wcscpy(table_names[i], names[i + 14]);
    static Table table = Table(0, 10, 20, 5, names[0], table_names, sizes, db);
    for (int i = 0; i < 4; i++)
        table.set_i_handler(i, &ich[i]);
    table.set_i_handler(4, &bh);
    Layout_object* objects[19] = {}; // массив наследников layout_object, к ним всем можно обращаться по ссылке layout_object*
    for (int i = 0; i < 7; i++)
        objects[i] = &texts[i]; // кладём на первые позиции фоновый текст
    objects[7] = &table; // положили адрес таблицы
    for (int i = 0; i < 11; i++) // Добавление кнопок в массив объектов
        objects[i + 8] = &buttons[i]; 
    offences.add_object(objects, 19); // добавили в layout n объектов
    return &offences; // вернули layout по ссылке 
}