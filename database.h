/*
	Лофенфельд Георгий Владимирович
	ПКС - 303
	***
	Вариант 30 - База Данных Митингов
	***
	Модуль описывающий базу данных и её элементы, а так же класс для взаимодействия базы данных и файла
*/

#pragma once // Чтобы конкретный исходный файл при компиляции подключался строго один раз
#include <string.h> // Работа со строками
#include <cstdlib> // Выделение памяти, контроль процесса выполнения программы, преобразование типов
#include <time.h> // Использование встроенной структуры tm 
#include <stdio.h> // Standart Input Output

void mem_check_err(); // Объявление функции вывода сообщения об ошибке при неудачном выделении памяти и выхода из программы

class Base_operator; // Объявляем необходимый класс заранее, опишем позже

enum base_type { meetings, declarers, offences, error }; // Перечисляемый тип

class Database_record // Виртуальный класс, описывающий абстрактный элемент базы данных
{
public:
	virtual void from_string(wchar_t str[20][128]) = 0; // Виртуальная функция, которая в наследниках отвечает за перевод из набора строк в объект класса
	virtual wchar_t** to_string(int is_file_format = 0) = 0; // Виртуальная функция, которая отвечает за перевод из объекта класса в набор строк (в самой таблице)
	wchar_t* to_file_line(); // Функция, которая отвечает за перевод в одну строку из объекта класса
	Database_record() { malloc_strings(); }; // Конструктор 
	~Database_record() { free_strings(); }; // Деструктор
	int get_field_cnt() { return field_cnt; }; // Получение количества столбцов
	virtual int compare(Database_record* y, int index) = 0; // Виртуальная функция для сравнения двух объектов класса по значению поля класса под индексом (используется в сортировке)
	void find_string(wchar_t* str); // Поиск подстроки в строковом представлении объекта класса
	int is_string_found() { return string_found; }; // Найдена ли подстрока
protected: // Недоступен вне класса, но наследуется
	int id=-1; // id записи
	wchar_t** strings; // Буфер для хранения строкового представления объекта класса в виде набора строк
	wchar_t line[2560] = L""; // Буфер для хранения представления в виде одной строки
	void malloc_strings(); // Выделение памяти под буферы
	void free_strings(); // Очищения буфера строк
	int field_cnt = 0; // Количество столбцов
	int string_found = 0; // Найдена ли подстрока
};

class Database_meetings_record : public Database_record // Класс для элемента базы данных о митингах
{
public:
	Database_meetings_record() { field_cnt = 7; }; // Указываем, что в данной таблице 7 полей
	~Database_meetings_record() {};
	wchar_t** to_string(int is_file_format = 0);
	void from_string(wchar_t str[20][128]); // Передаем то, что хотим записать в данную запись
	int compare(Database_record* y, int index);
private:
	struct tm date = {}; // Встроенная структура для даты и времени
	wchar_t address[128] = {}; // Для хранения данных о адресе митинга
	int declared_cnt = 0; // Для хранения данных о кол-ве заявленных участников
	int real_cnt = 0; // Для хранения данных о кол-ве фактических участников
	wchar_t declarers[128] = {}; // Для хранения данных о кол-ве заявителей
	int permitted = 0; // Разрешенность (только 0 или 1)
};

class Database_offences_record : public Database_record
{
public:
	Database_offences_record() { field_cnt = 5; };
	~Database_offences_record() {};
	wchar_t** to_string(int is_file_format = 0);
	void from_string(wchar_t str[20][128]);
	int compare(Database_record* y, int index) { return 0; };
private:
	int meeting_id = 0;
	wchar_t meeting[128] = {};
	wchar_t offender_full_name[128] = {};
	wchar_t normative_act[128] = {};
	wchar_t article_and_paragraph[128] = {};
	int conviction_flag = 0;
};


class Database_declarers_record : public Database_record
{
public:
	Database_declarers_record() { field_cnt = 2; };
	~Database_declarers_record() {};
	wchar_t** to_string(int is_file_format = 0);
	void from_string(wchar_t str[20][128]);
	int compare(Database_record* y, int index);
private:
	wchar_t full_name[128] = {};
	int has_offenses_flag = 0;
};

void quickSort(Database_record*** array, int index, int low, int high); // Объявление функции быстрой сортировки

class Database // Класс самой базы данных
{
public:
	Database(int cnt = 0); 
	void add_record(Database_record* rec); // Добавляет запись
	void add_record(wchar_t str[20][128]); // Переводит набор строк в запись и добавляет её
	Database_record** get_data(); // Получение указателя на массив записей
	~Database();
	void set_type(base_type type) { this->type = type; }; // Устанавливает тип базы данных (Митинги, Заявители, Правонарушения)
	base_type get_type() { return type; } // Возвращает тип базы данных
	void set_base_operator(Base_operator *bop) { this->bop = bop; } 
	Base_operator* get_base_operator() { return bop; } // Возвращает base_operator
	int get_size() { return cnt; } // Возвращает размер базы данных (количество записей)
	Database_record* get_record(int i) { return base[i]; } // Возвращает по индексу запись из базы данных
	void delete_record(int i); // Удаление записи по индексу
	void change_record(int i, wchar_t str[20][128]); // Изменение записи по индексу
	void sort_by_index(int index) { quickSort(&base, index, 0, cnt - 1); } // Сортировка по индексу
	void search(wchar_t* str); // Сортировка базы данных по параметру совпадения с искомой строкой
private:
	int cnt = -1; // Фактическое количество записей 
	int list_size = 10; // Размер выделения памяти динамического массива
	Database_record** base = {};
	base_type type = error;
	Base_operator* bop = {};
};

class Base_operator // Класс для взаимодействия базы данных и файлов
{
public:
	Base_operator(char* path, Database** dbs, int base_cnt, base_type* base_types); // Получает путь к файлу, а так же список баз данных, которые с ним связанны, их количество и типы
	~Base_operator();
	void initializate(); // Преобразование информации из файла в базу данных
	int save(); // Преобразование информации базы данных в файл
	int has_errors() { return error; }; // Возвращает 1 если возникли ошибки при работе с файлом
	Database_record* add(wchar_t words[20][128], base_type bt); // Добавление записи в оперативную память
private:
	Database** dbs = {}; // Список связанных баз данных с файлом
	int base_cnt = 0; // Количество баз данных
	base_type* base_types = {}; // Типы баз данных
	void realloc_array(base_type bt, int cnt); // Перевыделение памяти при добавлении новой записи (при необходимости)
	char path[128] = {}; // Путь к файлу
	Database_record* read(FILE* in, base_type bt); // Чтение из файла
	int error = 0; // Наличие ошибки работы с файлом
	Database_meetings_record** meetings_data = {}; // Динамическая память, хранящая в себе все записи данного типа
	Database_offences_record** offences_data = {}; 
	Database_declarers_record** declarers_data = {};
	int meetings_cnt = 0; // Количество записей
	int offences_cnt = 0;
	int declarers_cnt = 0;
	int meetings_data_size = 10; // Размер выделенной динамической памяти
	int offences_data_size = 10;
	int declarers_data_size = 10;
};