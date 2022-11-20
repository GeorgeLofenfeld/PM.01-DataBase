/*
	Лофенфельд Георгий Владимирович
	ПКС - 303
	***
	Вариант 30 - База Данных Митингов
	***
	Модуль в котором описаны классы, обрабатывающие входные данные
*/

#pragma once // Чтобы конкретный исходный файл при компиляции подключался строго один раз
#include <string.h> // Работа со строками
#include <stdio.h> // Standart Input Output

class Key_handler // абстрактный класс
{
public:
	Key_handler() {};
	~Key_handler() {};
	virtual void handle(wchar_t c) = 0; // обработка введнного символа
	int get_is_finished() { return is_finished; } // закончен ли ввод 
	void set_is_finished(int f) { is_finished = f; } // установить законченность ввода 
	virtual wchar_t* get_handled_string() { return handled_string; } // возвращает все запомненные символы (после обработки handle)
	virtual void set_handled_string(wchar_t* s) { wcscpy(handled_string, s); }; // когда нужно задать строку по умолчанию
	wchar_t* get_error_string() { return error_string; } // строка с текстом ошибки
	virtual void clear() { is_finished = 0; wcscpy(handled_string, L""); } // очистить полученную строку после ввода и установить законченность на ноль
protected:
	int is_finished = 0;
	wchar_t handled_string[128] = L""; // ввод с клавиатуры
	wchar_t error_string[128] = L""; // текст ошибки
};

class Int_char_handler : public Key_handler // обработка цифр и (или) букв в зависимости от параметров
{
public:
	Int_char_handler(int maxlength, int int_ok, int char_ok, int can_be_empty = 0);
	~Int_char_handler() {};
	void handle(wchar_t c); // обработка буквы
private:
	int int_ok = 1;
	int char_ok = 1;
	int maxlength = 100;
	int can_be_empty = 0;
};

class Date_time_handler : public Key_handler // обрабатывает дату или время
{
public:
	Date_time_handler(int date_or_time_handling) { this->date_or_time_handling = date_or_time_handling; }; // передаём единицу, если хотим обработать дату, ноль - если время
	~Date_time_handler() {};
	wchar_t* get_handled_string() override { // override переопределяет функцию родительского класса
		return format(handled_string); // форматирование полученной строки
	}
	void set_handled_string(wchar_t* s) override { // переопределение функции
		wcscpy(handled_string, L""); // очищаем полученную строку 
		for (int i = 0; i < wcslen(s); i++) // перевод обратно из формата даты и времени в сплошную строку (для редактирования)
			if (L'0' <= s[i] && s[i] <= L'9')
				wcsncat(handled_string, &s[i], 1);
	}
	void handle(wchar_t c); // обработка символа
private:
	int date_or_time_handling = 1;// 1 if date
	wchar_t* format(wchar_t* s); // получает строку и форматирует (прим. 26.10.22 или 14:25:00)
	wchar_t f_s[128] = {}; // format_string для хранения отформатированной строки
};

class Bool_handler : public Key_handler // для обработки флага 
{
public:
	Bool_handler() { wcscpy(handled_string, L"ДА"); }; // "ДА" - по умолчанию
	~Bool_handler() {};
	void handle(wchar_t c); // обработка символа
	void clear() override { is_finished = 0; state = 1;} // переопределение, устанавливаем флаг по умолчанию
private:
	int state = 1; // state либо единица (ДА), либо ноль (НЕТ)
};