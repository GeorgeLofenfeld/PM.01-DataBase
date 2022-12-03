/*
    ���������� ������� ������������
    ��� - 303
    ***
    ������� 30 - ���� ������ ��������
    ***
    ������� ������� ��������� (����� �����), ���������� ������ ����� ��������
*/

#include <windows.h> // ������ � ��������
#include <stdio.h> // Standart Input Output
#include <clocale> // ������� �����������
#include <time.h> // ������������� ���������� ��������� tm 
#include "file.cpp" // ����������� ������������ ������ file.cpp
#include "database.h" // ����������� ������������� ������ database.h
//#include "database.cpp" // ����������� ������������ ������ database.cpp
#include "frontend.h" // ����������� ������������� ������ frontend.h
#include "frontend.cpp" // ����������� ���������� ������ frontend.cpp
#include "layouts.h" // ����������� ������������� ������ layouts.h


/*
����� ������ ��� �������:

1. �������� ��������� ������� (41 - 45 ������)

2. �������� ��� ������ � ��������� � ��������� ���������� �� �����,
    ���� ����� ���, �������� ����� � ����������� � ������ ����� ������ (46 - 55 ������)

3. �������� ���������� Frontend - ������ ��� �������������� ��������� � ������������ (56 ������)

4. ���������� layout'�� (����� ������������ ��������� �� ������)
    � �� �������� � ��������� Frontend'a (57 - 60 ������)

5. ������ ��������� �������� ��������� (61 ������)

*/

int main()
{
    HWND console = GetConsoleWindow(); // �������� �������
    HANDLE console_out = GetStdHandle(STD_OUTPUT_HANDLE); // �������� ���������� �������
    SetConsoleScreenBufferSize(console_out, GetLargestConsoleWindowSize(console_out)); // ��� ���������� ������������� ���������� ��������� ��������
    ShowWindow(console, SW_MAXIMIZE); // ������ ���� ������������� �������
    setlocale(LC_ALL, ""); // ������� �����������
    char path[] = "Data_base_file"; // ���� � ����� ��
    base_type bts[3] = { meetings, declarers, offences }; // �������������� ��� ���� ��
    Database dbs[] = { Database() ,Database() ,Database() }; // �������������� ��� ������� ��
    Database* dbs_p[] = { &dbs[0], &dbs[1], &dbs[2] }; // ������ �� ��� ��
    Base_operator fo = Base_operator(path, dbs_p, 3, bts); // �������������� base_operator � ����� ���������, � ��������� �� ����� � � ���� � ����������� ����� (��� ������)
    fo.initializate(); // ������������� ��� ������ �� �����
    if (fo.has_errors()) { // �������� �����
        printf("���� ���� ������ �������� ��� �����������\n");
        return 1;
    }
    Frontend fd = Frontend(); // ������ ������ ������ frontend (�������� �� ����������� � ��������������) 
    fd.set_layout(create_menu_layout(), 0); // ������� ��������� ������� �������� ������ �������� ���� �� ������� 0
    fd.set_layout(create_meetings_layout(dbs_p[0]), 1); // ���������� � ������� ���� + ������� ������ �� ������ ���� ������ �� ������� � create_meetings_layout 
    fd.set_layout(create_declarers_layout(dbs_p[1]), 2);
    fd.set_layout(create_offences_layout(dbs_p[2]), 3);
    fd.run(); // �������� �� ��� ���, ���� �� ����� ������ ����� stop(), ������� ��������� ���������
    return 0;
}