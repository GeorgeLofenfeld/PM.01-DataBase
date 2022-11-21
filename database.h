/*
	���������� ������� ������������
	��� - 303
	***
	������� 30 - ���� ������ ��������
	***
	������ ����������� ���� ������ � � ��������, � ��� �� ����� ��� �������������� ���� ������ � �����
*/

#pragma once // ����� ���������� �������� ���� ��� ���������� ����������� ������ ���� ���
#include <string.h> // ������ �� ��������
#include <cstdlib> // ��������� ������, �������� �������� ���������� ���������, �������������� �����
#include <time.h> // ������������� ���������� ��������� tm 
#include <stdio.h> // Standart Input Output
#include "constants.h" // ����������� ������������� ������ constants.h


void mem_check_err(); // ���������� ������� ������ ��������� �� ������ ��� ��������� ��������� ������ � ������ �� ���������

class Base_operator; // ��������� ����������� ����� �������, ������ �����

enum base_type { meetings, declarers, offences, error }; // ������������� ���

class Database_record // ����������� �����, ����������� ����������� ������� ���� ������
{
public:
	virtual void from_string(wchar_t str[MAX_COL_COUNT][MAX_STR_SIZE]) = 0; // ����������� �������, ������� � ����������� �������� �� ������� �� ������ ����� � ������ ������
	virtual wchar_t** to_string(int is_file_format = 0) = 0; // ����������� �������, ������� �������� �� ������� �� ������� ������ � ����� ����� (� ����� �������)
	wchar_t* to_file_line(); // �������, ������� �������� �� ������� � ���� ������ �� ������� ������
	Database_record() { malloc_strings(); }; // ����������� 
	~Database_record() { free_strings(); }; // ����������
	int get_field_cnt() { return field_cnt; }; // ��������� ���������� ��������
	virtual int compare(Database_record* y, int index) = 0; // ����������� ������� ��� ��������� ���� �������� ������ �� �������� ���� ������ ��� �������� (������������ � ����������)
	void find_string(wchar_t* str); // ����� ��������� � ��������� ������������� ������� ������
	int is_string_found() { return string_found; }; // ������� �� ���������
protected: // ���������� ��� ������, �� �����������
	int id=-1; // id ������
	wchar_t** strings; // ����� ��� �������� ���������� ������������� ������� ������ � ���� ������ �����
	wchar_t line[MAX_STR_SIZE * MAX_COL_COUNT] = L""; // ����� ��� �������� ������������� � ���� ����� ������
	void malloc_strings(); // ��������� ������ ��� ������
	void free_strings(); // �������� ������ �����
	int field_cnt = 0; // ���������� ��������
	int string_found = 0; // ������� �� ���������
};

class Database_meetings_record : public Database_record // ����� ��� �������� ���� ������ � ��������
{
public:
	Database_meetings_record() { field_cnt = 7; }; // ���������, ��� � ������ ������� 7 �����
	~Database_meetings_record() {};
	wchar_t** to_string(int is_file_format = 0);
	void from_string(wchar_t str[MAX_COL_COUNT][MAX_STR_SIZE]); // �������� ��, ��� ����� �������� � ������ ������
	int compare(Database_record* y, int index);
private:
	struct tm date = {}; // ���������� ��������� ��� ���� � �������
	wchar_t address[MAX_STR_SIZE] = {}; // ��� �������� ������ � ������ �������
	int declared_cnt = 0; // ��� �������� ������ � ���-�� ���������� ����������
	int real_cnt = 0; // ��� �������� ������ � ���-�� ����������� ����������
	wchar_t declarers[MAX_STR_SIZE] = {}; // ��� �������� ������ � ���-�� ����������
	int permitted = 0; // ������������� (������ 0 ��� 1)
};

class Database_offences_record : public Database_record
{
public:
	Database_offences_record() { field_cnt = 5; };
	~Database_offences_record() {};
	wchar_t** to_string(int is_file_format = 0);
	void from_string(wchar_t str[MAX_COL_COUNT][MAX_STR_SIZE]);
	int compare(Database_record* y, int index) { return 0; };
private:
	int meeting_id = 0;
	wchar_t meeting[MAX_STR_SIZE] = {};
	wchar_t offender_full_name[MAX_STR_SIZE] = {};
	wchar_t normative_act[MAX_STR_SIZE] = {};
	wchar_t article_and_paragraph[MAX_STR_SIZE] = {};
	int conviction_flag = 0;
};


class Database_declarers_record : public Database_record
{
public:
	Database_declarers_record() { field_cnt = 2; };
	~Database_declarers_record() {};
	wchar_t** to_string(int is_file_format = 0);
	void from_string(wchar_t str[MAX_COL_COUNT][MAX_STR_SIZE]);
	int compare(Database_record* y, int index);
private:
	wchar_t full_name[MAX_STR_SIZE] = {};
	int has_offenses_flag = 0;
};

void quickSort(Database_record*** array, int index, int low, int high); // ���������� ������� ������� ����������

class Database // ����� ����� ���� ������
{
public:
	Database(int cnt = 0); 
	void add_record(Database_record* rec); // ��������� ������
	void add_record(wchar_t str[MAX_COL_COUNT][MAX_STR_SIZE]); // ��������� ����� ����� � ������ � ��������� �
	Database_record** get_data(); // ��������� ��������� �� ������ �������
	~Database();
	void set_type(base_type type) { this->type = type; }; // ������������� ��� ���� ������ (�������, ���������, ��������������)
	base_type get_type() { return type; } // ���������� ��� ���� ������
	void set_base_operator(Base_operator *bop) { this->bop = bop; } 
	Base_operator* get_base_operator() { return bop; } // ���������� base_operator
	int get_size() { return cnt; } // ���������� ������ ���� ������ (���������� �������)
	Database_record* get_record(int i) { return base[i]; } // ���������� �� ������� ������ �� ���� ������
	void delete_record(int i); // �������� ������ �� �������
	void change_record(int i, wchar_t str[MAX_COL_COUNT][MAX_STR_SIZE]); // ��������� ������ �� �������
	void sort_by_index(int index) { quickSort(&base, index, 0, cnt - 1); } // ���������� �� �������
	void search(wchar_t* str); // ���������� ���� ������ �� ��������� ���������� � ������� �������
private:
	int cnt = -1; // ����������� ���������� ������� 
	int list_size = DEFAULT_DBS_SIZE; // ������ ��������� ������ ������������� �������
	Database_record** base = {};
	base_type type = error;
	Base_operator* bop = {};
};

class Base_operator // ����� ��� �������������� ���� ������ � ������
{
public:
	Base_operator(char* path, Database** dbs, int base_cnt, base_type* base_types); // �������� ���� � �����, � ��� �� ������ ��� ������, ������� � ��� ��������, �� ���������� � ����
	~Base_operator();
	void initializate(); // �������������� ���������� �� ����� � ���� ������
	int save(); // �������������� ���������� ���� ������ � ����
	int has_errors() { return error; }; // ���������� 1 ���� �������� ������ ��� ������ � ������
	Database_record* add(wchar_t words[MAX_COL_COUNT][MAX_STR_SIZE], base_type bt); // ���������� ������ � ����������� ������
private:
	Database** dbs = {}; // ������ ��������� ��� ������ � ������
	int base_cnt = 0; // ���������� ��� ������
	base_type* base_types = {}; // ���� ��� ������
	void realloc_array(base_type bt, int cnt); // ������������� ������ ��� ���������� ����� ������ (��� �������������)
	char path[MAX_STR_SIZE] = {}; // ���� � �����
	Database_record* read(FILE* in, base_type bt); // ������ �� �����
	int error = 0; // ������� ������ ������ � ������
	Database_meetings_record** meetings_data = {}; // ������������ ������, �������� � ���� ��� ������ ������� ����
	Database_offences_record** offences_data = {}; 
	Database_declarers_record** declarers_data = {};
	int meetings_cnt = 0; // ���������� �������
	int offences_cnt = 0;
	int declarers_cnt = 0;
	int meetings_data_size = DEFAULT_DBS_SIZE; // ������ ���������� ������������ ������
	int offences_data_size = DEFAULT_DBS_SIZE;
	int declarers_data_size = DEFAULT_DBS_SIZE;
};