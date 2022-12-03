/*
	���������� ������� ������������
	��� - 303
	***
	������� 30 - ���� ������ ��������
	***
	��������� ����������� �������� ��������� � ��������� ������
*/

#define FOREGROUND_YELLOW 14 // ����������� ������ ����� ������
#define FOREGROUND_TURQUOISE 11 // ����������� ���������� ����� ������
#define FOREGROUND_WHITE (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED) // ��������� ������ ����� ������
#define BACKGROUND_WHITE (BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED) // ����������� ������ ����� ����

#define _CRT_NON_CONFORMING_WCSTOK // ���������� ��� ������ ������� wcstok 

#define KEY_LEFT 75 // ��� ������� "������� �����"
#define KEY_RIGHT 77 // ��� ������� "������� ������"
#define KEY_UP 72 // ��� ������� "������� �����"
#define KEY_DOWN 80 // ��� ������� "������� ����"
#define KEY_ESC 27 // ��� ������� "escape"
#define KEY_ENTER 13 // ��� ������� "enter"
#define KEY_BACKSPACE 8 // ��� ������� "backspace"

#define DEFAULT_COL_SIZE 8 // ��������� ������ �������
#define DEFAULT_DBS_SIZE 10 // ��������� ������ ������ ���� ������
#define MAX_COL_COUNT 20 // ������������ ���������� ������� � ����� ������� 
#define MAX_STR_SIZE 128 // ������������� ������ ������
#define	MAX_STR_TO_INT_SIZE 9 // ������������ ������ ���������� ������������� ����� ��� ����������
#define DATE_TIME_STR_SIZE 6 // ������������� ������ ���������� ������������� ���� � �������
#define MAX_AVAILABLE_KEYS_COUNT 300 // ������������ ���������� ��������� ������
#define MAX_LAYOUT_OBJECTS_COUNT 100 // ������������ ���������� �������� layout'a
#define MAX_LAYOYTS_COUNT 10 // ������������ ���������� layout'�� � ������ Frontend