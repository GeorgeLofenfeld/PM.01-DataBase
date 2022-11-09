#pragma once
#include <string.h>
#include <cstdlib>
#include <time.h>
#include <stdio.h>

class Base_operator;

enum base_type { meetings, declarers, offences, error };

class Database_record
{
public:
	virtual void from_string(wchar_t str[20][128]) = 0;
	virtual wchar_t** to_string() = 0;
	wchar_t* to_line();
	Database_record() { malloc_strings(); };
	~Database_record() { free_strings(); };
	int get_field_cnt() { return field_cnt; };
	virtual int compare(Database_record* y, int index) = 0;
	void find_string(wchar_t* str);
	int is_string_found() { return string_found; };
protected:
	int id=-1;
	wchar_t** strings;// [20] [128] ;
	wchar_t line[2560] = L"";
	void malloc_strings();
	void free_strings();
	int field_cnt = 0;
	int string_found = 0;
};

class Database_meetings_record : public Database_record
{
public:
	Database_meetings_record() { field_cnt = 7; };
	~Database_meetings_record() {};
	wchar_t** to_string();
	void from_string(wchar_t str[20][128]);
	int compare(Database_record* y, int index);
private:
	struct tm date;
	wchar_t address[128];
	int declared_cnt = 0;
	int real_cnt = 0;
	//int ids[100];
	//int declarers_cnt=0;
	wchar_t declarers[128];
	int permitted=0;
};

class Database_offences_record : public Database_record
{
public:
	Database_offences_record() { field_cnt = 5; };
	~Database_offences_record() {};
	wchar_t** to_string();
	void from_string(wchar_t str[20][128]);
	int compare(Database_record* y, int index) { return 0; };
private:
	int meeting_id;
	wchar_t meeting[128];
	wchar_t offender_full_name[128];
	wchar_t normative_act[128];
	wchar_t article_and_paragraph[128];
	int conviction_flag = 0;
};


class Database_declarers_record : public Database_record
{
public:
	Database_declarers_record() { field_cnt = 2; };
	~Database_declarers_record() {};
	wchar_t** to_string();
	void from_string(wchar_t str[20][128]);
	int compare(Database_record* y, int index);
private:
	wchar_t full_name[128];
	int has_offenses_flag = 0;
};

void quickSort(Database_record*** array, int index, int low, int high);

class Database
{
public:
	Database(int cnt=0);
	void add_record(Database_record* rec);
	void add_record(wchar_t str[20][128]);
	Database_record** get_data();
	~Database();
	void set_type(base_type type) { this->type = type; };
	base_type get_type() { return type; }
	void set_base_operator(Base_operator *bop) { this->bop = bop; }
	Base_operator* get_base_operator() { return bop; }
	int get_size() { return cnt; }
	Database_record* get_record(int i) { return base[i]; }
	void delete_record(int i);
	void change_record(int i, wchar_t str[20][128]);
	void sort_by_index(int index) { quickSort(&base, index, 0, cnt - 1); }
	void search(wchar_t* str);
private:
	int cnt = -1;
	int list_size = 10;
	Database_record** base;
	base_type type = error;
	Base_operator* bop;
};

class Base_operator
{
public:
	Base_operator(char* path, Database** dbs, int base_cnt, base_type* base_types);
	~Base_operator();
	void initializate();
	int save();
	int has_errors() { return error; };
	Database_record* add(wchar_t words[20][128], base_type bt);
private:
	Database** dbs;
	int base_cnt;
	base_type* base_types;
	void realloc_array(base_type bt, int cnt);
	char path[128]="";
	Database_record* read(FILE* in, base_type bt);
	int error = 0;
	Database_meetings_record** meetings_data;
	Database_offences_record** offences_data;
	Database_declarers_record** declarers_data;
	int meetings_cnt = 0;
	int offences_cnt = 0;
	int declarers_cnt = 0;
	int meetings_data_size = 10;
	int offences_data_size = 10;
	int declarers_data_size = 10;
};