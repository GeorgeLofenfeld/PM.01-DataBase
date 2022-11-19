/*
    ���������� ������� ������������
    ��� - 303
    ***
    ������� 30 - ���� ������ ��������
    ***
    �������� �������, ������� ���������� ��� ������������� � ��������
*/

#pragma once 
#include "button_activities.h"

void meeting_main(Frontend* fd) {
    /*
    ������������� ����� ������������� �������� ������
    ***
    ��������� ������ �� Frontend (�������� �� ����������� � ��������������)
    */
    Layout* l = fd->get_layout(1);
    wchar_t names_to_hide[9][128] = { L"����������� ��:",
        L"����", L"�������", L"���������� ���������� ����������", L"���������� ����������� ����������", L"������", L"��� ���������", L"����������", L"�����" };
    wchar_t names_to_show[6][128] = { L"���������� �����:", L"����������",
        L"����������", L"��������������", L"��������", L"�����" };
    for (int i = 0; i < 9; i++)
        l->get_object_by_caption(names_to_hide[i])->deactivate();
    for (int i = 0; i < 6; i++)
        l->get_object_by_caption(names_to_show[i])->activate();
}

void declarers_main(Frontend* fd) {
    Layout* l = fd->get_layout(2);
    wchar_t names_to_hide[4][128] = { L"����������� ��:",
    L"���", L"����������", L"�����" };
    wchar_t names_to_show[6][128] = { L"���������� �����:", L"����������",
        L"����������", L"��������������", L"��������", L"�����" };
    for (int i = 0; i < 4; i++)
        l->get_object_by_caption(names_to_hide[i])->deactivate();
    for (int i = 0; i < 6; i++)
        l->get_object_by_caption(names_to_show[i])->activate();
}

void offences_main(Frontend* fd) {
    Layout* l = fd->get_layout(3);
    wchar_t names_to_hide[7][128] = { L"����������� ��:",
    L"��������", L"��� ����������", L"������������ ����", L"������ � ������", L"����� ��������� �����", L"�����" };
    wchar_t names_to_show[6][128] = { L"���������� �����:", L"����������",
        L"����������", L"��������������", L"��������", L"�����" };
    for (int i = 0; i < 7; i++)
        l->get_object_by_caption(names_to_hide[i])->deactivate();
    for (int i = 0; i < 6; i++)
        l->get_object_by_caption(names_to_show[i])->activate();
}

void meeting_showing(Frontend* fd) {
    /*
    ������������� ����� ������������� �������� ������ (���������� �� ��������� � meeting_main etc.)
    ***
    ��������� ������ �� Frontend (�������� �� ����������� � ��������������)
    */
    Layout* l = fd->get_layout(1);
    wchar_t names_to_show[9][128] = { L"����������� ��:",
        L"����", L"�������", L"���������� ���������� ����������", L"���������� ����������� ����������", L"������", L"��� ���������", L"����������", L"�����" };
    wchar_t names_to_hide[6][128] = { L"���������� �����:", L"����������",
        L"����������", L"��������������", L"��������", L"�����" };
    for (int i = 0; i < 6; i++)
        l->get_object_by_caption(names_to_hide[i])->deactivate();
    for (int i = 0; i < 9; i++)
        l->get_object_by_caption(names_to_show[i])->activate();
}

void declarers_showing(Frontend* fd) {
    Layout* l = fd->get_layout(2);
    wchar_t names_to_show[4][128] = { L"����������� ��:",
    L"���", L"����������", L"�����" };
    wchar_t names_to_hide[6][128] = { L"���������� �����:", L"����������",
        L"����������", L"��������������", L"��������", L"�����" };
    for (int i = 0; i < 6; i++)
        l->get_object_by_caption(names_to_hide[i])->deactivate();
    for (int i = 0; i < 4; i++)
        l->get_object_by_caption(names_to_show[i])->activate();
}

void offences_showing(Frontend* fd) {
    Layout* l = fd->get_layout(3);
    wchar_t names_to_show[7][128] = { L"����������� ��:",
    L"��������", L"��� ����������", L"������������ ����", L"������ � ������", L"����� ��������� �����", L"�����" };
    wchar_t names_to_hide[6][128] = { L"���������� �����:", L"����������",
        L"����������", L"��������������", L"��������", L"�����" };
    for (int i = 0; i < 6; i++)
        l->get_object_by_caption(names_to_hide[i])->deactivate();
    for (int i = 0; i < 7; i++)
        l->get_object_by_caption(names_to_show[i])->activate();
}

void go_meeting(Frontend* fd) {
    /*
    ������� �� ������ layout
    ***
    ��������� ������ �� Frontend (�������� �� ����������� � ��������������)
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
    ��������������� ������� ��� ��������� ������ �� ������ �� ����������� layout
    ***
    ��������� ������ �� Frontend (�������� �� ����������� � ��������������), i - ������ layout, choose - ���� 1, �� ������� ��������� ���������
    */
    Layout* l = fd->get_layout(i);
    wchar_t t_name[3][128] = { L"������� ��������", L"������� ����������", L"������� ��������������" };
    Table* table = (Table*)l->get_object_by_caption(t_name[i - 1]);
    if (choose)
        l->change_swichable_object(table);
    return table;
}


void meeting_sort(Frontend* fd) {
    /*
    �������� ���������� � ����������� �� ������� ������
    ***
    ��������� ������ �� Frontend (�������� �� ����������� � ��������������)
    */
    Layout* l = fd->get_layout(1);
    Layout_object* lo = l->get_chosen_object();
    wchar_t names[7][128] = { L"����", L"�������", L"���������� ���������� ����������", L"���������� ����������� ����������", L"������", L"��� ���������", L"����������" };
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
    wchar_t names[2][128] = { L"���", L"����������" };
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
    wchar_t names[5][128] = { L"��������", L"��� ����������", L"������������ ����", L"������ � ������", L"����� ��������� �����" };
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
    ��������� ������� ���������� ������ � �������
    ***
    ��������� ������ �� Frontend (�������� �� ����������� � ��������������)
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
    ��������� ������� ������ ������ ��� �������� �� �������
    ***
    ��������� ������ �� Frontend (�������� �� ����������� � ��������������)
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
    ��������� ������� ������ ������ ��� ��������� � ������� (���������)
    ***
    ��������� ������ �� Frontend (�������� �� ����������� � ��������������)
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
    ��������� ������� ������
    ***
    ��������� ������ �� Frontend (�������� �� ����������� � ��������������)
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
    ��������� ������� ���������� ������ �� ���� ������
    ***
    ��������� ������ �� Frontend (�������� �� ����������� � ��������������)
    */
    Table* table = get_table(fd, 1, 0);
    int ok = table->get_database()->get_base_operator()->save();// get_base_operator ���� ��� ����
    Layout* l = fd->get_layout(0);
    wchar_t t_name[128] = L"���������";
    Button* button = (Button*)l->get_object_by_caption(t_name);
    move_cursor_to(button->get_x() + 10, button->get_y());
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (ok) { // ���� ���������� �������, ����� save ����� 1, ����� 0 (Base_operator::save)
        SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
        printf("���������� �������");
    }
    else {
        SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
        printf("���������� ����������");
    }
    fd->wait();
    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);

}

void exit(Frontend* fd) {
    /*
    ��������� ������� ������ �� ��������� ��� ������� ������ "�����"
    ***
    ��������� ������ �� Frontend (�������� �� ����������� � ��������������)
    */
    fd->stop();
}

