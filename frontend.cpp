#include "frontend.h"
#include <wchar.h>

#define FOREGROUND_YELLOW 14

void move_cursor_to(int x, int y) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hStdOut, pos);
}

int min_number(int a, int b) {
	return a <= b ? a : b;
}

Text::Text(int x, int y, wchar_t t[], int color)
{
	this->x = x;
	this->y = y;
	this->text_color = color;
	wcscpy(caption, t); // текст текста 
	is_swichable = 0; // текст никогда нельзя выбрать
}


void Text::print() 
{
	move_cursor_to(x, y);
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); // вспомогательная переменная для смены фона 
	SetConsoleTextAttribute(hStdOut, text_color | FOREGROUND_INTENSITY);
	printf("%ls", caption); // wchar* (long string), выводим название 
	SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
}


Button::Button(int x, int y, wchar_t t[], void (*action)(Frontend* fd))
{
	this->x = x;
	this->y = y;
	this->action = action;
	wcscpy(caption, t); // сохранили название (текст кнопки)
	this->set_switchable(1); // данный объект может быть выбран
	available_keys[0] = 13; // код enter 
	available_keys[1] = 0;// для корректной работы string.h (нуль-терминированная строка)
}


void Button::print()
{
	move_cursor_to(x, y); // перемещаем курсор на данную координату
	if (swiched) { // если выбран
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); // вспомогательная переменная для смены фона 
		SetConsoleTextAttribute(hStdOut, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY); // смена фона надписи на белый 
		printf("%ls", caption); // wchar*, выводим название 
		SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY); // смена фона надписи на черный 
	}
	else
		printf("%ls", caption); // иначе если не выбран, то без смены фона
		
}

void Button::react(wchar_t key)
{
	if (action != nullptr) // если ссылка не пуста
		action(lt->get_frontend()); // вызываем action от Frontned'a которому принадлежит layout, которому принадлежит layout_object
}

Table::Table(int x, int y, int row_cnt, int col_cnt, wchar_t caption[], wchar_t names[20][128], int *sizes, Database* db)
{
	this->x = x;
	this->y = y;
	this->row_cnt = row_cnt;
	this->col_cnt = col_cnt+1;
	wcscpy(this->caption, caption);
	wcscpy(this->names[0], L"№");
	this->sizes[0] = 8;
	this->db = db;
	for (int i = 0; i < col_cnt; i++) {
		wcscpy(this->names[i+1], names[i]);
		this->sizes[i+1] = sizes[i];
	}
	change_state(neutral);
	is_background = 1;
}

void Table::print()
{
	int cur_x = x;
	int vertical_shifts[3] = {0,3,row_cnt + 3 + 1};
	for (int i = 0; i < col_cnt; i++) {
		int space_cnt = sizes[i] - wcslen(names[i]);
		for (int j = 0; j < 3; j++) {
			move_cursor_to(cur_x + (j != 0), y + vertical_shifts[j]);
			for (int k = 0; k < sizes[i]; k++)
				printf("_");
		}
		move_cursor_to(cur_x + (space_cnt+1) / 2, y + 2);
		printf("%ls",names[i]);
		cur_x += sizes[i];
		for (int j = 1; j <= row_cnt + 3 + 1; j++) {
			move_cursor_to(cur_x, y + j);
			printf("|");
		}
	}
	move_cursor_to(x + (cur_x - x - wcslen(caption)) / 2, y-1);
	printf("%ls", caption);
	if (state == searching) {
		move_cursor_to(x , y - 2);
		printf("Введите для поиска: %ls", search_string);
	}
	for (int i = page_num * row_cnt; i < min_number(row_cnt * (page_num + 1), db->get_size()); i++)
		if (!(i == chosen_row && state == changing))
			print_row(i);
	if (state == adding)
		print_adding_row(db->get_size() % row_cnt);
	else if (state == changing)
		print_adding_row(chosen_row % row_cnt);
	if (state==adding || state == changing) 
		print_error_message();
	move_cursor_to(x, y + row_cnt + 3 + 2+1);
	printf("Страница %d", page_num+1);
}

void Table::react(wchar_t key)
{
	if (key == 27) {
		handlers[adding_counter]->clear();
		adding_counter = 0;
		clear_adding_strings();
		lt->change_swichable_object(1);
		change_state(neutral);
		return;
	}
	if (state == adding || state == changing) {
		Key_handler* kh = handlers[adding_counter];
		kh->handle(key);
		wcscpy(adding_strings[adding_counter], kh->get_handled_string());
		if (kh->get_is_finished()) {
			adding_counter++;
			kh->clear();
			if (adding_counter == col_cnt - 1) {
				adding_counter = 0;
				if (state == changing)
					db->change_record(chosen_row, adding_strings);
				else
					db->add_record(adding_strings);
				clear_adding_strings();
				lt->change_swichable_object(1);
				change_state(neutral);
			}
			else {
				if (state == changing)
					handlers[adding_counter]->set_handled_string(adding_strings[adding_counter]);
				wcscpy(adding_strings[adding_counter], handlers[adding_counter]->get_handled_string());
			}
		}

		wcscpy(error_message, kh->get_error_string());
	}
	else if (state == searching) {
		search_handler.handle(key);
		wcscpy(search_string, search_handler.get_handled_string());
		if (search_handler.get_is_finished()) {
			search_handler.set_is_finished(0);
			db->search(search_string);
		}
	}
	else if (state == neutral){
		switch (key)
		{
		case 75://left
			change_page(-1);
			break;
		case 77://right
			change_page(1);
			break;
		default:
			break;
		}
	}
	else if (state == deleting || state == choosing_for_changing) {
		switch (key)
		{
		case 75://left
			change_page(-1);
			break;
		case 77://right
			change_page(1);
			break;
		case 72:
			change_row(-1);
			break;
		case 80:
			change_row(1);
			break;
		case 13:
			if (state == deleting)
				delete_chosen_row();
			else if (db->get_size() > 0)
				change_state(changing);
			break;
		default:
			break;
		}
	}

	
}

void generate_available_letters(wchar_t** s) {
	(*s)[0] = 13;
	(*s)[1] = 8;
	(*s)[2] = L' ';
	for (wchar_t i = L','; i <= L'z'; i++)// , - . / 0 1 2 ... z
		(*s)[i - L',' + 3] = i;
	int first_part = L'z' - L',' + 4;
	for (wchar_t j = L'А'; j <= L'я'; j++)
		(*s)[first_part + j - L'А'] = j;
	(*s)[first_part + L'я' - L'А' + 1] = 0;
}

void Table::change_state(Table_states state)
{
	this->state = state; 
	if (state == neutral) {
		available_keys[0] = 75;
		available_keys[1] = 77;
		available_keys[2] = 0;
		show_chosen_row = 0;
	} else if (state == deleting || state == choosing_for_changing) {
		chosen_row = page_num * row_cnt;
		show_chosen_row = 1;
		available_keys[0] = 75;
		available_keys[1] = 77;
		available_keys[2] = 13;
		available_keys[3] = 72;
		available_keys[4] = 80;
		available_keys[5] = 27;
		available_keys[6] = 0;
	}
	else {
		if (state == adding) {
			change_page(db->get_size() / row_cnt - page_num);
			show_chosen_row = 0;
		}
		if (state == changing) {
			for (int i = 0; i < col_cnt; i++)
				wcscpy(adding_strings[i], db->get_record(chosen_row)->to_string()[i]);
			handlers[0]->set_handled_string(adding_strings[0]);
		}
		if (state == searching)
			change_page(-page_num);
		wchar_t esc = 27;
		generate_available_letters(&available_keys);
		wcsncat(available_keys, &esc, 1);
		
	}
}

void Table::change_page(int delta)
{
	int max_page_num = db->get_size() / row_cnt + 1; 
	page_num = (page_num + delta) % max_page_num;
	if (page_num < 0)
		page_num = max_page_num + page_num;
	chosen_row = page_num * row_cnt;
}



void Table::print_row(int i)
{
	Database_record *rec = db->get_record(i);
	wchar_t** strings = rec->to_string();
	int cur_x = x;
	int row = i % row_cnt;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (i == chosen_row && show_chosen_row)
		SetConsoleTextAttribute(hStdOut, FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
	move_cursor_to_row_col(row, 0);
	printf(" %d", i+1);
	for (int j = 0; j < col_cnt-1; j++) {
		move_cursor_to_row_col(row, j+1);
		printf("%ls", strings[j]);
		cur_x += sizes[j];
	}
	if (i == chosen_row && show_chosen_row)
		SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
}

void Table::move_cursor_to_row_col(int row, int col)
{
	int cur_x = x;
	for (int i = 0; i < col; i++)
		cur_x += sizes[i];
	int cur_y = y + 3 + 1;
	for (int i = 0; i < row; i++)
		cur_y++;
	move_cursor_to(cur_x+1, cur_y);
}

void Table::print_adding_row(int a_y)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	
	for (int i = 0; i < col_cnt-1; i++) {
		if (i == adding_counter)
			SetConsoleTextAttribute(hStdOut, FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
		move_cursor_to_row_col(a_y, i+1);
		printf("%ls", adding_strings[i]);
		if (i == adding_counter)
			SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
	}
}

void Table::print_error_message()
{
	int cur_x = x;
	for (int i = 0; i < col_cnt; i++)
		cur_x += sizes[i];
	move_cursor_to(x + (cur_x - x - wcslen(caption)) / 2, y + row_cnt + 3 + 2);
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
	printf("%ls", error_message);
	wcscpy(error_message, L"");
	SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
}

void Table::clear_adding_strings() // очищение буфера добавляемой строки 
{
	for (int i = 0; i < 20; i++)
		wcscpy(adding_strings[i], L"");
}

void Table::change_row(int delta)
{
	int max_row_num = db->get_size();
	if (max_row_num == 0) {
		chosen_row = 0;
		return;
	}
	chosen_row = (chosen_row + delta) % max_row_num;
	if (chosen_row < 0)
		chosen_row = max_row_num + chosen_row;
	page_num = chosen_row / row_cnt;
}

void Table::delete_chosen_row()
{
	if (db->get_size() > chosen_row) {
		db->delete_record(chosen_row);
		if (chosen_row >= db->get_size())
			change_row(-1);
	}
}



Layout::Layout()
{
	available_keys[0] = 72; //KEY_UP 
	available_keys[1] = 80; //KEY_DOWN 
	available_keys[2] = 27; //ESC
	available_keys[3] = 0;  //end of string for correct work
}


void Layout::set_screen()
{
	for (int i = 0; i < object_cnt; i++)
		if (objects[i]->get_visible())
			objects[i]->print();
}


wchar_t* Layout::get_available_keys()
{
	static wchar_t keys[1000]; // массив для доступных клавиш клавиатуры
	wcscpy(keys, available_keys); // strcpy(x, y), available_keys - клавиши доступные для самого layout'a
	if (chosen_index != -1) { // chose_index - индекс выбранного объекта
		wcsncat(keys, objects[chosen_index]->get_available_keys(), 300); // добавили доступные клавиши для выбранного layout_object
	}
	for (int i = 0; i < object_cnt; i++) // итерируемся по всем объектам данного layout'a
		if (objects[i]->get_is_background() && i != chosen_index) // get_is_background - метод класса layout_object, может ли данный объект реагировать на клавиши не будучи выбранным
			wcsncat(keys, objects[i]->get_available_keys(), 300); // добавили доступные клавиши для выбранного layout_object
	return keys; // возвращаем массив доступных клавиш клавиатуры
}

void Layout::react(wchar_t key)
{
	if (chosen_index != -1 && wcschr(objects[chosen_index]->get_available_keys(), key)) // если объект выбран (индекс не равен -1) и нажатая клавиша доступна для выбранного объекта
		objects[chosen_index]->react(key); // вызываем реакцию по данному объекту
	else // если нажатая клавиша недоступна для данного объекта, то значит это либо доступная клавиша для самого layout, либо она доступна для background объекта (например перелистывание страниц в таблице)
	{
		switch (key)
		{
		case 80: //down
			change_swichable_object(1); // перелистывание вниз
			break;
		case 72: //up
			change_swichable_object(-1); // перелистывание вверх
			break;
		case 27: // esc
			fd->leave(); // вызов метода fd::leave для переключения на предыдущий layout
			break;
		default:
			for (int i = 0; i < object_cnt; i++)
				if (objects[i]->get_is_background()
						&& wcschr(objects[i]->get_available_keys(), key))
					objects[i]->react(key);
			break;
		}
	}
}

void Layout::add_object(Layout_object* object)
{
	objects[object_cnt] = object;
	objects[object_cnt]->set_layout(this);
	if (object->get_swichable() && chosen_index == -1) {
		chosen_index = object_cnt;
		objects[object_cnt]->set_switched(1);
	}
	object_cnt++;
}

void Layout::add_object(Layout_object** objects, int cnt)
{
	for (int i = 0; i < cnt; i++)
		add_object(objects[i]);
}

Layout_object* Layout::get_object_by_caption(wchar_t caption[])
{
	for (int i = 0; i < object_cnt; i++)
		if (wcscmp(objects[i]->get_caption(), caption) == 0)
			return objects[i];
	return nullptr;
}

void Layout::change_swichable_object(int delta)//смещение вверх или вниз по списку
{
	//delta must be 1 or -1
	if (chosen_index != -1) {
		objects[chosen_index]->set_switched(0);
		do
		{
			chosen_index = (chosen_index + delta) % object_cnt;
			if (chosen_index < 0)
				chosen_index = object_cnt + chosen_index;
		} while (objects[chosen_index]->get_swichable() != 1);
		objects[chosen_index]->set_switched(1);
	}
}

void Layout::change_swichable_object(Layout_object* object)
{
	if (chosen_index != -1) {
		objects[chosen_index]->set_switched(0);
	}
	for (int i =0; i < object_cnt; i++)
		if (objects[i] == object)
		{
			chosen_index = i;
			objects[chosen_index]->set_switched(1);
			return;
		}
}


wchar_t Key_reader::read(wchar_t* keys)
{
	wchar_t key;
	do
	{
		key = _getwch();
	} while (wcschr(keys, key) == NULL);
	return key;
}

Frontend::Frontend()
{
	reader = Key_reader();
}

void Frontend::set_layout(Layout *in, int index) // добавления в текущий frontend нового layout по индексу
{
	layouts[index] = in;
	layouts[index]->set_frontend(this); // передаём в добавленый layout ссылку на объект класса frontend, который вызвал set_layout. Теперь он может с ним взаимодействовать
}

void Frontend::stop() {
	exit = 1; // выход из цикла внутри Frontend::run, завершается программа, т.к. цикл внутри метода run завершён (сам  цикл отвечает за работу программы) 
}

void Frontend::wait()
{
	waiting = 1;
}

void Frontend::clear_screen()
{
	if (waiting)
		waiting = 0;
	else
		system("@cls||clear");
}

void Frontend::run() {
	while (!exit) { // exit - переменная frontend, пока не выбрана 
		layouts[current_layout_idx]->set_screen(); // отрисовывает текущую вёрстку на экран
		wchar_t* keys = layouts[current_layout_idx]->get_available_keys(); // получаем массив доступных кнопок
		layouts[current_layout_idx]->react(reader.read(keys)); // вызываем реакцию текущего layout, метод read класса reader возвращает полученную кнопку, если она есть среди доступных (у каждой кнопки программы своя реакция)
		clear_screen(); // после каждой реакции очищаем экран и заполняем на следующей итерации цикла
	}
}

void Frontend::change_layout(int index)
{
	int prev = current_layout_idx;
	current_layout_idx = index;
	layouts[current_layout_idx]->set_prev_layout(prev);
}

void Frontend::leave()
{
	current_layout_idx = layouts[current_layout_idx]->get_prev_layout(); // При переходе в новый layout мы запомнили предыдущий. Возвращаемся к нему
}

void Layout_object::deactivate()
{
	if (!deactivated) { // если не деактивировано
		save_state(); // сохраняем состояние
		if (swiched) // если выбрано ( != 0 )
			lt->change_swichable_object(1); // выбираем другой объект данного layout'a, с которым можно взаимодействвать (не текст)
		is_swichable = 0, visible = 0; 
		deactivated = 1;
	}
}
