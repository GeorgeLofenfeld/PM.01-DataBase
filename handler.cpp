#include "handler.h"


void Int_char_handler::handle(wchar_t c) // обработка полученного символа
{
	if (char_ok && (((L'a' <= c) && (c <= L'z')) || ((L'A' <= c) && (c <= L'Z')) || c == L' ' 
		|| ((L'а' <= c) && (c <= L'я')) || ((L'А' <= c) && (c <= L'Я')) )
		||
		int_ok && (L'0' <= c) && (c <= L'9')) {
		if (wcslen(handled_string) < maxlength-1) // можем добавлять до тех пор, пока строка меньше максимальной на единицу
			wcsncat(handled_string, &c, 1); // добавляем символ 
		wcscpy(error_string, L""); // очищение строки с ошибкой 
	}
	else {
		if (c == 13) {
			if (wcslen(handled_string) > 0) { // enter 
				is_finished = 1; // ввод окончен
				wcscpy(error_string, L"");
			}
			else
				wcscpy(error_string, L"Строка не может быть пуста");
		}
		else if (c == 8 && wcslen(handled_string) > 0) { // backspase 
			handled_string[wcslen(handled_string) - 1] = '\0'; // удалить последний символ
			wcscpy(error_string, L"");
		}
		else
			wcscpy(error_string, L"Недопустимый знак");
	}
}

int is_correct(wchar_t* s, int date_or_time) { // в разработке
	if (wcslen(s) == 6)
		return 1;  
	return 0;
}

void Date_time_handler::handle(wchar_t c)
{
	if (date_or_time_handling) { 
		if (wcslen(handled_string) < 6 && ('0' <= c) && (c <= '9')) {
			wcsncat(handled_string, &c, 1);
			wcscpy(error_string, L"");
		}
		else
			wcscpy(error_string, L"Недопустимая дата / время");
	}
	else
	{
		if (wcslen(handled_string) < 6 && ('0' <= c) && (c <= '9')) {
			wcsncat(handled_string, &c, 1);
			wcscpy(error_string, L"");
		}
		else
			wcscpy(error_string, L"Недопустимая дата / время");
	}
	if (c == 8 && wcslen(handled_string) > 0) { // backspase key
		handled_string[wcslen(handled_string) - 1] = '\0'; //delete last letter
		wcscpy(error_string, L"");
	}
	if (c == 13 && is_correct(handled_string, date_or_time_handling)) {
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
	if (c == 72 || c == 80) { //72 KEY_UP 80 KEY_DOWN
		state = (state + 1) % 2; // флаг разрешенности, может иметь значение 1 или 0
		if (state == 1)
			wcscpy(handled_string, L"ДА");
		else
			wcscpy(handled_string, L"НЕТ");
		wcscpy(error_string, L""); // чистим отображение об ошибке если всё успешно
	}
	else { 
		if (c == 13) { // если нажатая клавиша enter
			is_finished = 1; // ввод закончен
			wcscpy(error_string, L""); // очистили строку с ошибкой 
		}
		else
			wcscpy(error_string, L"Недопустимый знак");
	}
}
