#pragma once


void meeting_main(Frontend* fd) {
    Layout* l = fd->get_layout(1);
    wchar_t names_to_hide[7][128] = { L"Сортировать по:",
        L"Дате", L"Времени", L"Количеству заявленных участников", L"Количеству фактических участников", L"Разрешению", L"Назад" };
    wchar_t names_to_show[6][128] = { L"Установите режим:", L"Сортировка",
        L"Добавление", L"Редактирование", L"Удаление", L"Поиск" };
    for (int i = 0; i < 7; i++) 
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

void meeting_showing(Frontend* fd){
    Layout* l = fd->get_layout(1);
    wchar_t names_to_show[7][128] = { L"Сортировать по:",
        L"Дате", L"Времени", L"Количеству заявленных участников", L"Количеству фактических участников", L"Разрешению", L"Назад" };
    wchar_t names_to_hide[6][128] = { L"Установите режим:", L"Сортировка",
        L"Добавление", L"Редактирование", L"Удаление", L"Поиск" };
    for (int i = 0; i < 6; i++)
        l->get_object_by_caption(names_to_hide[i])->deactivate();
    for (int i = 0; i < 7; i++)
        l->get_object_by_caption(names_to_show[i])->activate();
}

void declarers_showing(Frontend* fd) {
    Layout* l = fd->get_layout(2);
    wchar_t names_to_show[6][128] = { L"Сортировать по:",
    L"ФИО", L"Нарушениям", L"Назад" };
    wchar_t names_to_hide[6][128] = { L"Установите режим:", L"Сортировка",
        L"Добавление", L"Редактирование", L"Удаление", L"Поиск" };
    for (int i = 0; i < 6; i++)
        l->get_object_by_caption(names_to_hide[i])->deactivate();
    for (int i = 0; i < 4; i++)
        l->get_object_by_caption(names_to_show[i])->activate();
}

void go_meeting(Frontend* fd) {
    fd->change_layout(1);
    meeting_main(fd);
}

void go_declarers(Frontend* fd) {
    fd->change_layout(2);
    declarers_main(fd);
}

Table* get_meetings_table(Frontend* fd, int choose = 1) {
    Layout* l = fd->get_layout(1);
    wchar_t t_name[128] = L"ТАБЛИЦА МИТИНГОВ";
    Table* table = (Table*)l->get_object_by_caption(t_name);
    if (choose)
        l->change_swichable_object(table);
    return table;
}

Table* get_declarers_table(Frontend* fd, int choose = 1) {
    Layout* l = fd->get_layout(2);
    wchar_t t_name[128] = L"ТАБЛИЦА ЗАЯВИТЕЛЕЙ";
    Table* table = (Table*)l->get_object_by_caption(t_name);
    if (choose)
        l->change_swichable_object(table);
    return table;
}

void meeting_sort(Frontend* fd) {
    Layout* l = fd->get_layout(1);
    Layout_object* lo = l->get_chosen_object();
    wchar_t names[5][128] = {L"Дате", L"Времени", L"Количеству заявленных участников", L"Количеству фактических участников", L"Разрешению" };
    if (lo != nullptr) {
        int index = -1;
        for (int i = 0; i < 5; i++)
            if (wcscmp(names[i], lo->get_caption()) == 0)
                index = i;
        Table* table = get_meetings_table(fd, 0);
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
        Table* table = get_declarers_table(fd, 0);
        if (index >= 0)
            table->get_database()->sort_by_index(index);
    }
}

void add_to_meetings_table(Frontend* fd) {
    Table* table = get_meetings_table(fd);
    table->change_state(Table::adding);

}

void add_to_declarers_table(Frontend* fd) {
    Table* table = get_declarers_table(fd);
    table->change_state(Table::adding);

}

void meetings_delete(Frontend* fd) {
    Table* table = get_meetings_table(fd);
    table->change_state(Table::deleting);
}

void declarers_delete(Frontend* fd) {
    Table* table = get_declarers_table(fd);
    table->change_state(Table::deleting);
}


void meetings_change(Frontend* fd) {
    Table* table = get_meetings_table(fd);
    table->change_state(Table::choosing_for_changing);
}

void declarers_change(Frontend* fd) {
    Table* table = get_declarers_table(fd);
    table->change_state(Table::choosing_for_changing);
}

void meetings_search(Frontend* fd) {
    Table* table = get_meetings_table(fd);
    table->change_state(Table::searching);
}

void declarers_search(Frontend* fd) {
    Table* table = get_declarers_table(fd);
    table->change_state(Table::searching);
}

void save(Frontend* fd) {
    Table* table = get_meetings_table(fd, 0);
    table->get_database()->get_base_operator()->save();// get_base_operator един для всех
}

void exit(Frontend* fd) {
    fd->stop();
}

Layout* create_menu_layout() {
    static Layout main_menu = Layout();
    wchar_t names[8][128] = { L"БАЗА ДАННЫХ МИТИНГОВ", L"МЕНЮ", L"Митинги",
        L"Заявители", L"Правонарушения", L"Сохранить", L"Выйти", L"test"};
    static Text texts[3] = { Text(15, 1, names[0]),Text(15, 3, names[1]), Text(10,20,names[7])};
    static Button buttons[5] = {
        Button(15, 5, names[2],go_meeting),
        Button(15, 6, names[3],go_declarers),
        Button(15, 7, names[4]),
        Button(15, 9, names[5], save),
        Button(15, 10, names[6], exit)
    };
    Layout_object* objects[8];
    for (int i = 0; i < 3; i++)
        objects[i] = &texts[i];
    for (int i = 3; i < 8; i++)
        objects[i] = &buttons[i-3];
    main_menu.add_object(objects, 8);
    return &main_menu;
}

Layout* create_meetings_layout(Database *db) {
    static Layout meetings = Layout();
    wchar_t names[21][128] = { L"ТАБЛИЦА МИТИНГОВ", L"Установите режим:", L"Сортировка",
        L"Добавление", L"Редактирование", L"Удаление", L"Поиск", L"Сортировать по:",
        L"Дате", L"Времени", L"Количеству заявленных участников", L"Количеству фактических участников", L"Разрешению", L"Назад",
        L"ДАТА", L"ВРЕМЯ", L"КОЛ. ЗАЯВ. УЧАСТН.", L"КОЛ. ФАКТ. УЧАСТН.",
        L"АДРЕС", L"ФИО ЗАЯВИТЕЛЯ", L"РАЗРЕШЕНИЕ"};
    static Text texts[2] = { Text(5, 3, names[1]), Text(5, 3, names[7])};
    static Button buttons[11] = {
        Button(25, 3, names[2],meeting_showing),
        Button(40, 3, names[3], add_to_meetings_table),
        Button(60, 3, names[4], meetings_change),
        Button(80, 3, names[5], meetings_delete),
        Button(95, 3, names[6],meetings_search),
        Button(25, 3, names[8],meeting_sort),
        Button(35, 3, names[9],meeting_sort),
        Button(45, 3, names[10],meeting_sort),
        Button(80, 3, names[11],meeting_sort),
        Button(115, 3, names[12],meeting_sort),
        Button(140, 3, names[13],meeting_main),
    };
    wchar_t table_names[20][128];
    int sizes[7] = { 15 ,15,40,40, 30,30, 13 };
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
    Layout_object* objects[14];
    for (int i = 0; i < 2; i++)
        objects[i] = &texts[i];
    for (int i = 2; i < 13; i++)
        objects[i] = &buttons[i - 2];
    objects[13] = &table;
    meetings.add_object(objects, 14);
    return &meetings;
}

Layout* create_declarers_layout(Database* db) {
    static Layout declarers = Layout();
    wchar_t names[13][128] = { L"ТАБЛИЦА ЗАЯВИТЕЛЕЙ", L"Установите режим:", L"Сортировка",
    L"Добавление", L"Редактирование", L"Удаление", L"Поиск", L"Сортировать по:",
    L"ФИО", L"Нарушениям", L"Назад", L"ФИО ЗАЯВИТЕЛЯ", L"НАЛИЧИЕ НАРУШЕНИЙ" };
    static Text texts[2] = { Text(5, 3, names[1]), Text(5, 3, names[7]) };
    static Button buttons[8] = {
        Button(25, 3, names[2], declarers_showing),
        Button(40, 3, names[3], add_to_declarers_table),
        Button(60, 3, names[4], declarers_change),
        Button(80, 3, names[5], declarers_delete),
        Button(95, 3, names[6], declarers_search),
        Button(25, 3, names[8], declarers_sort),
        Button(35, 3, names[9], declarers_sort),
        Button(60, 3, names[10],declarers_main)
    };
    wchar_t table_names[20][128];
    int sizes[2] = { 90, 30 };
    static Int_char_handler ich =  Int_char_handler(sizes[0],0,1);
    static Bool_handler bh = Bool_handler();
    Key_handler* kh[2] = { &ich ,&bh };
    for (int i = 0; i < 2; i++)
        wcscpy(table_names[i], names[i + 11]);
    static Table table = Table(0, 10, 20, 2, names[0], table_names, sizes, db);
    for (int i = 0; i < 2; i++)
        table.set_i_handler(i, kh[i]);
    Layout_object* objects[11];
    for (int i = 0; i < 2; i++)
        objects[i] = &texts[i];
    for (int i = 2; i < 10; i++)
        objects[i] = &buttons[i - 2];
    objects[10] = &table;
    declarers.add_object(objects, 11);
    return &declarers;
}

/*
Layout* create_offences_layout(Database* db) {
    static Layout offences = Layout();
    wchar_t names[16][128] = { L"ТАБЛИЦА ПРАВОНАРУШЕНИЙ", L"Установите режим:", L"Просмотр",
    L"Добавление", L"Редактирование", L"Удаление", L"Поиск", L"Сортировать по:",
    L"ФИО", L"Нарушениям", L"Назад", L"МИТИНГ","ФИО НАРУШИТЕЛЯ", L"НОРМАТИВНЫЙ АКТ", L"СТАТЬЯ И ПУНКТ", L"ОСУЖДЕНИЕ СУДОМ"};
    static Text texts[2] = { Text(5, 3, names[1]), Text(5, 3, names[7]) };
    static Button buttons[8] = {
        Button(25, 3, names[2]),
        Button(40, 3, names[3]),
        Button(60, 3, names[4]),
        Button(80, 3, names[5]),
        Button(95, 3, names[6]),
        Button(25, 3, names[8]),
        Button(35, 3, names[9]),
        Button(60, 3, names[10])
    };
    wchar_t table_names[20][128];
    static Int_char_handler ich = Int_char_handler(0, 1);
    static Bool_handler bh = Bool_handler();
    Key_handler* kh[2] = { &ich ,&bh };
    int sizes[2] = { 90, 30 };
    for (int i = 0; i < 2; i++)
        wcscpy(table_names[i], names[i + 11]);
    static Table table = Table(0, 10, 20, 2, names[0], table_names, sizes, db);
    for (int i = 0; i < 2; i++)
        table.set_i_handler(i, kh[i]);
    Layout_object* objects[11];
    for (int i = 0; i < 2; i++)
        objects[i] = &texts[i];
    for (int i = 2; i < 10; i++)
        objects[i] = &buttons[i - 2];
    objects[10] = &table;
    offences.add_object(objects, 11);
    return &offences;
}*/