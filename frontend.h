#pragma once
#include <string.h>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "database.h"
#include "handler.h"

class Layout; // ��������� �������, ������ �����. ���������� �������� �������� � layout_object (���������� � frontend � key_handler)
class Frontend; 
class Key_handler;

class Layout_object // ���������� ������� layout'a, ��� ��������� ������� �����������
{
public:
	Layout_object() { available_keys = (wchar_t*)malloc(300 * sizeof(wchar_t)); wcscpy(available_keys, L""); }; 
	~Layout_object() { free(available_keys); };
	virtual void print() = 0; // ���������
	virtual void react(wchar_t key) = 0; // ������� �� ���������� �������
	wchar_t* get_available_keys() {return available_keys;} // ���������� ������� ���������� ��� ������� layout_object
	void set_switched(int swiched) { this->swiched = swiched;} // setter ��� ������� ������ �� ������ 
	int get_swichable() { return is_swichable; } // getter, ����� �� ������ ���� ������
	void set_switchable(int is_swichable) { this->is_swichable = is_swichable; save_state();} // setter ��� ������� ����� �� ���� ������ ������
	void set_layout(Layout* lt) {this->lt = lt;} // setter ��� ������ �� ��� layout, �������� ����������� ������ layout_object 
	void set_available_keys(wchar_t* keys) {wcscpy(available_keys, keys);} // setter ��� available_keys
	wchar_t* get_caption() { return caption; } // getter ��� �������� ������� layout_object 
	void set_visible(int v) { visible = v; save_state();} // setter ��� ��������� 
	int get_visible() { return visible;}
	void deactivate(); // ����������� � frontend.cpp
	void activate() { // ���������, ����� ����������� (���� ����)
		is_swichable = saved_state[0];
		visible = saved_state[1];
		deactivated = 0;
	}
	int get_is_background() {return is_background;}
protected:
	int x; // ���������� ������� layout_object
	int y; // ���������� ������� layout_object
	int is_swichable = 0; // ���� ���������� �� ��, ����� �� ������� ���� layout_object ��� ������ (text-table-button, ����� ���� ������ � ������) 
	int swiched = 0; // ���� ������ ������ layout_object 
	wchar_t *available_keys; 
	Layout* lt; // ������ �� ��� layout, � ������� ���������� layout_object 
	wchar_t caption[100]; // �������� layout_object'a
	int visible = 1; // ��������� layout_object'a (����� ����������� ���� �� �����, �������� � ������ �������� layout'a)
	int saved_state[2]={is_swichable, visible}; // ����� ������������ ��������� ��������� 
	void save_state() { // ����� ��� ���������� ���������
		saved_state[0] = is_swichable;
		saved_state[1] = visible;
	}
	int deactivated = 0; // �������� layout_object, ������ �� ����� ����������� 
	int is_background = 0; // ���� ������ ����� ����������� �� ������ ����������, ����� �� �� ������ (�������� ��������� ��� table ������-�����)
};

class Button : public Layout_object
{
public:
	Button(int x, int y, wchar_t t[], void (*action)(Frontend* fd) = nullptr); // ��������� ���� ����������� ����������, ��������� ���� ��������, 
	~Button() {};
	void print(); // ��������� ����� ������
	void react(wchar_t key); // ������� �� ���������� ������� ���������� 
private:
	void (*action)(Frontend* fd); // ������ �� �������, � ���������� ������ �� ����� Frontend
};

class Text : public Layout_object
{
public:
	Text(int x, int y, wchar_t t[]);
	~Text() {};
	void print();
	void react(wchar_t key) {};
};

class Table : public Layout_object
{
public:
	enum Table_states{adding,deleting,changing, choosing_for_changing,neutral, searching}; // ��������� ������� ����� ���� ������ ���� �� ���
	Table(int x, int y, int row_cnt, int col_cnt, wchar_t caption[], wchar_t names[20][128], int *sizes, Database *db);
	void set_i_handler(int i, Key_handler* h) { handlers[i] = h; } // ���������� i-��� handler
	~Table() {};
	void print(); // ���������� ���� �������
	void react(wchar_t key); 
	void change_state(Table_states state);
	void change_page(int delta);
	Database* get_database() { return db; };
private:
	Key_handler* handlers[20]; // ����������� ��������
	int x = 0;
	int y = 0;
	int row_cnt = 20; // ���������� ����� �� ��������
	int col_cnt = 20; 
	wchar_t names[20][128]; // �������� ��������
	int sizes[20]; // ������� ��������
	int page_num = 0; // ����� ������� ��������
	Database* db = NULL; // ������ �� ��
	void print_row(int i); // ����� ��������� ������
	void move_cursor_to_row_col(int row, int col); // ������� �� ������
	void print_adding_row(int a_y); // ��������� ����������� ������
	void print_error_message(); // ��������� ��������� ������
	void clear_adding_strings(); // �������� ������ ��� ����������� ������ (adding_strings)
	void change_row(int delta); // ����� ���������� ������ �� ����� ��������������, ��������
	void delete_chosen_row(); // ������� ��������� ������
	int chosen_row = 0; // ������ ��������� ������
	int show_chosen_row = 0; // ��������� ��������� ������
	Table_states state = neutral; // ��������� �������, ����� ������� �������� ������ �� ������������ enum Table_states
	int adding_counter = 0; // ����� �������� ������� � ����������� ������ 
	wchar_t adding_strings[20][128]; // ����� ��������� ����� ��� ����� ������
	wchar_t error_message[128]; // ��� �������� ��������� �� �����-���� ������ 
	Int_char_handler search_handler = Int_char_handler(50,1,1); // handler ��� �������� ������� �� ����� 
	wchar_t search_string[128]; // ��� �������� ������� �� �����
};
class Layout
{
public:
	Layout();
	~Layout() {};
	void set_screen();
	void set_frontend(Frontend* fd){ this->fd = fd; }; // �������� ������ �� frontend � ���������� � ���������� fd
	Frontend* get_frontend() { return fd; };
	void set_prev_layout(int idx) { prev_layout_idx = idx; };
	int get_prev_layout() { return prev_layout_idx; };
	wchar_t* get_available_keys();
	void react(wchar_t key);
	void add_object(Layout_object* object);
	void add_object(Layout_object** object, int cnt);
	Layout_object* get_object_by_caption(wchar_t caption[]);
	Layout_object* get_chosen_object() { return chosen_index > 0 ? objects[chosen_index] : nullptr; }
	void change_swichable_object(int delta);
	void change_swichable_object(Layout_object* object);
private:
	Frontend* fd;
	int chosen_index = -1;
	wchar_t available_keys[100];
	Layout_object* objects[100];
	int object_cnt = 0;
	int prev_layout_idx = 0;
};

class Key_reader
{
public:
	Key_reader() {};
	~Key_reader() {};
	//wchar_t read();
	wchar_t read(wchar_t* keys);

private:

};

class Frontend // �������� �� ��������� �� ������ � �������������� � �������������. ���� �� ��� ��������� 
{
public:
	Frontend();
	~Frontend() {};
	void set_layout(Layout *in, int index);//�������� ����� ������������ � ������ ������ �� ������� (*layouts[10])
	Layout* get_layout(int index) { return layouts[index]; }; // �������� �� ���������� ������� ������ �� layout
	void run();// �������� ������
	void change_layout(int index); // ������� ������� layout
	void leave(); 
	void stop();
private:
	Key_reader reader;
	Layout *layouts[10]; // ������ ���� ������ (����, �������)
	int current_layout_idx = 0;
	int exit = 0;
	void clear_screen();
};
