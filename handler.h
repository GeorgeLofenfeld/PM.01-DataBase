/*
	���������� ������� ������������
	��� - 303
	***
	������� 30 - ���� ������ ��������
	***
	������ � ������� ������� ������, �������������� ������� ������
*/

#pragma once // ����� ���������� �������� ���� ��� ���������� ����������� ������ ���� ���
#include <string.h> // ������ �� ��������
#include <stdio.h> // Standart Input Output

class Key_handler // ����������� �����
{
public:
	Key_handler() {};
	~Key_handler() {};
	virtual void handle(wchar_t c) = 0; // ��������� ��������� �������
	int get_is_finished() { return is_finished; } // �������� �� ���� 
	void set_is_finished(int f) { is_finished = f; } // ���������� ������������� ����� 
	virtual wchar_t* get_handled_string() { return handled_string; } // ���������� ��� ����������� ������� (����� ��������� handle)
	virtual void set_handled_string(wchar_t* s) { wcscpy(handled_string, s); }; // ����� ����� ������ ������ �� ���������
	wchar_t* get_error_string() { return error_string; } // ������ � ������� ������
	virtual void clear() { is_finished = 0; wcscpy(handled_string, L""); } // �������� ���������� ������ ����� ����� � ���������� ������������� �� ����
protected:
	int is_finished = 0;
	wchar_t handled_string[128] = L""; // ���� � ����������
	wchar_t error_string[128] = L""; // ����� ������
};

class Int_char_handler : public Key_handler // ��������� ���� � (���) ���� � ����������� �� ����������
{
public:
	Int_char_handler(int maxlength, int int_ok, int char_ok, int can_be_empty = 0);
	~Int_char_handler() {};
	void handle(wchar_t c); // ��������� �����
private:
	int int_ok = 1;
	int char_ok = 1;
	int maxlength = 100;
	int can_be_empty = 0;
};

class Date_time_handler : public Key_handler // ������������ ���� ��� �����
{
public:
	Date_time_handler(int date_or_time_handling) { this->date_or_time_handling = date_or_time_handling; }; // ������� �������, ���� ����� ���������� ����, ���� - ���� �����
	~Date_time_handler() {};
	wchar_t* get_handled_string() override { // override �������������� ������� ������������� ������
		return format(handled_string); // �������������� ���������� ������
	}
	void set_handled_string(wchar_t* s) override { // ��������������� �������
		wcscpy(handled_string, L""); // ������� ���������� ������ 
		for (int i = 0; i < wcslen(s); i++) // ������� ������� �� ������� ���� � ������� � �������� ������ (��� ��������������)
			if (L'0' <= s[i] && s[i] <= L'9')
				wcsncat(handled_string, &s[i], 1);
	}
	void handle(wchar_t c); // ��������� �������
private:
	int date_or_time_handling = 1;// 1 if date
	wchar_t* format(wchar_t* s); // �������� ������ � ����������� (����. 26.10.22 ��� 14:25:00)
	wchar_t f_s[128] = {}; // format_string ��� �������� ����������������� ������
};

class Bool_handler : public Key_handler // ��� ��������� ����� 
{
public:
	Bool_handler() { wcscpy(handled_string, L"��"); }; // "��" - �� ���������
	~Bool_handler() {};
	void handle(wchar_t c); // ��������� �������
	void clear() override { is_finished = 0; state = 1;} // ���������������, ������������� ���� �� ���������
private:
	int state = 1; // state ���� ������� (��), ���� ���� (���)
};