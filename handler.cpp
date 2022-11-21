/*
	���������� ������� ������������
	��� - 303
	***
	������� 30 - ���� ������ ��������
	***
	���������� ������� �� handler.h
*/

#include <wchar.h> // Wide char - ������� ������ - ������ � ����������
#include "handler.h" // ����������� ������������ ������ handler.h
#include "constants.h" // ����������� ������������� ������ constants.h

Int_char_handler::Int_char_handler(int maxlength, int int_ok, int char_ok, int can_be_empty) 
{
	/*
	����������� ����������� ������ Int_char_handler
	***
	�������� ������ ���������� ����. ������ ������. int_ok - ���� �������� � ������, char_ok - ���� � ������ (����� ���� ������������), can_be_empty (�� ��������� 0),
	���� ������ ����� ���� ������
	*/
	this->maxlength = maxlength; 
	if (int_ok && !char_ok)
		if (maxlength > MAX_STR_TO_INT_SIZE)
			this->maxlength = MAX_STR_TO_INT_SIZE;
	this->int_ok = int_ok;
	this->char_ok = char_ok; 
	this->can_be_empty = can_be_empty;
}

void Int_char_handler::handle(wchar_t c) // ��������� ����������� �������
{
	if (char_ok && (((L'a' <= c) && (c <= L'z')) || ((L'A' <= c) && (c <= L'Z')) || c == L' ' 
		|| ((L'�' <= c) && (c <= L'�')) || ((L'�' <= c) && (c <= L'�')) || ((L',' <= c) && (c <= L'/')))
		||
		int_ok && (L'0' <= c) && (c <= L'9')) {
		if (wcslen(handled_string) < maxlength - 1) {// ����� ��������� �� ��� ���, ���� ������ ������ ������������ �� ������� 
			wcsncat(handled_string, &c, 1); // ��������� ������ 
			wcscpy(error_string, L""); // �������� ������ � ������� 
		} 
		else
			wcscpy(error_string, L"������� ������������ ���������� ��������");
	}
	else {
		if (c == KEY_ENTER) {
			if (wcslen(handled_string) > 0 || can_be_empty) { 
				is_finished = 1; // ���� �������
				wcscpy(error_string, L"");
			}
			else
				wcscpy(error_string, L"������ �� ����� ���� �����");
		}
		else if (c == KEY_BACKSPACE && wcslen(handled_string) > 0) { // backspase 
			handled_string[wcslen(handled_string) - 1] = '\0'; // ������� ��������� ������
			wcscpy(error_string, L"");
		}
		else
			wcscpy(error_string, L"������������ ������");
	}
}

int is_correct(wchar_t* s, int date_or_time) { 
	if (wcslen(s) != DATE_TIME_STR_SIZE)
		return 0;  
	wchar_t s_divided[3][3] = { L"",L"",L"" };
	for (int i = 0; i < 3; i++) {
		wcsncpy(s_divided[i], s + i * 2, 2);
		s_divided[i][2] = 0;
	}
		
	if (date_or_time == 1) {
		int dd, mm, yy;
		dd = wcstol(s_divided[0], NULL, 10);
		mm = wcstol(s_divided[1], NULL, 10);
		yy = wcstol(s_divided[2], NULL, 10);
		//check year 
		if (yy >= 00 && yy <= 99)
			//check month 
			if (mm >= 1 && mm <= 12)
				//check days
				if ((dd >= 1 && dd <= 31) && (mm == 1 || mm == 3 || mm == 5 || mm == 7 || mm == 8 || mm == 10 || mm == 12))
					return 1;
				else if ((dd >= 1 && dd <= 30) && (mm == 4 || mm == 6 || mm == 9 || mm == 11))
					return 1;
				else if ((dd >= 1 && dd <= 28) && (mm == 2))
					return 1;
				else if (dd == 29 && mm == 2 && (yy % 4 == 0 && yy != 0))
					return 1;
	}
	else {
		int hh, mm, ss;
		hh = wcstol(s_divided[0], NULL, 10);
		mm = wcstol(s_divided[1], NULL, 10);
		ss = wcstol(s_divided[2], NULL, 10);
		if (hh < 24 && mm < 60 && ss < 60)
			return 1;
	}
	return 0;
}

void Date_time_handler::handle(wchar_t c)
{
	if (date_or_time_handling) { 
		if (wcslen(handled_string) < DATE_TIME_STR_SIZE && ('0' <= c) && (c <= '9')) {
			wcsncat(handled_string, &c, 1);
			wcscpy(error_string, L"");
		}
		else
			wcscpy(error_string, L"������������ ���� / �����");
	}
	else
	{
		if (wcslen(handled_string) < DATE_TIME_STR_SIZE && ('0' <= c) && (c <= '9')) {
			wcsncat(handled_string, &c, 1);
			wcscpy(error_string, L"");
		}
		else
			wcscpy(error_string, L"������������ ���� / �����");
	}
	if (c == KEY_BACKSPACE && wcslen(handled_string) > 0) { 
		handled_string[wcslen(handled_string) - 1] = '\0'; // ������� ��������� ������
		wcscpy(error_string, L"");
	}
	if (c == KEY_ENTER && is_correct(handled_string, date_or_time_handling)) {
		is_finished = 1;
		wcscpy(error_string, L"");
	}
	

}

wchar_t* Date_time_handler::format(wchar_t* s)
{
	wchar_t spacer[2] = L":";
	if (date_or_time_handling)
		wcscpy(spacer, L".");
	wchar_t ss[3][2] = {L"",L"",L""};
	wcscpy(f_s, L"");
	for (int i = 0; i < 3; i++)
		if (i * 2 < wcslen(s)) {
			int len = wcslen(s + i * 2);
			if (len > 2)
				len = 2;
			wcsncpy(ss[i], s + i * 2, len);
		}
	for (int i = 0; i < 3; i++) {
		if (wcslen(ss[i]) > 0) {
			if (wcslen(f_s) > 0)
				wcscat(f_s, spacer);
			wcsncat(f_s, ss[i], 2);
		}
		wcscpy(ss[i], L"");
	}
	return f_s;
}


void Bool_handler::handle(wchar_t c)
{
	if (c == KEY_UP || c == KEY_DOWN) { 
		state = (state + 1) % 2; // ���� �������������, ����� ����� �������� 1 ��� 0
		if (state == 1)
			wcscpy(handled_string, L"��");
		else
			wcscpy(handled_string, L"���");
		wcscpy(error_string, L""); // ������ ����������� �� ������ ���� �� �������
	}
	else { 
		if (c == KEY_ENTER) { // ���� ������� ������� enter
			is_finished = 1; // ���� ��������
			wcscpy(error_string, L""); // �������� ������ � ������� 
		}
		else
			wcscpy(error_string, L"������������ ������");
	}
}
