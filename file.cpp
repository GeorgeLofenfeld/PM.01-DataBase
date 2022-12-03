/*
	Лофенфельд Георгий Владимирович
	ПКС - 303
	***
	Вариант 30 - База Данных Митингов
	***
	Реализация функций из database.h, относящихся к работе с файлом
*/

#include <stdio.h> // Standart Input Output
#include <wchar.h> // Wide char - широкий символ - работа с алфавитами
#include "database.h" // Подключение заголовочного модуля databse.h
#include "frontend.h" // Подключение заголовочного модуля frontend.h
#include "constants.h" // Подключение заголовочного модуля constants.h


Base_operator::Base_operator(char* path, Database** dbs, int base_cnt, base_type* base_types) {
	/*
	Конструктор класса Base_operator
	***
	Принимает путь к файлу path, массив ссылок на базы данных dbs, размер массива base_cnt, типы баз данных в виде массива base_types
	*/
	this->dbs = dbs;
	this->base_cnt = base_cnt;
	this->base_types = base_types;
	strcpy(this->path, path);
	meetings_data = (Database_meetings_record**)malloc(sizeof(Database_meetings_record*) * meetings_data_size);
	declarers_data = (Database_declarers_record**)malloc(sizeof(Database_declarers_record*) * declarers_data_size);
	offences_data = (Database_offences_record**)malloc(sizeof(Database_offences_record*) * offences_data_size);
	if ((meetings_data == NULL) || (declarers_data == NULL) || (offences_data == NULL)) {
		mem_check_err();
	} 
}

Base_operator::~Base_operator() {
	if (meetings_data != NULL) {
		for (int i = 0; i < meetings_cnt; i++)
			delete meetings_data[i];
		free(meetings_data);
	}
	if (declarers_data != NULL) {
		for (int i = 0; i < declarers_cnt; i++)
			delete declarers_data[i];
		free(declarers_data);
	}
	if (offences_data != NULL) {
		for (int i = 0; i < offences_cnt; i++)
			delete offences_data[i];
		free(offences_data);
	}
};

base_type str_to_bt(char* str) {
	/*
	Переводит строку в тип данных base_type, 
	если строка не совпадает ни с одним из типов base_type, 
	то возвращает специальный тип error
	***
	Принимает строку str (хранит тип таблицы)
	***
	Возвращает тип базы данных в виде base_type
	*/
	char strs[3][MAX_STR_SIZE] = { "meetings", "declarers", "offences" };
	base_type bts[4] = { meetings, declarers, offences, error };
	for (int i = 0; i < 3; i++)
		if (strcmp(str, strs[i]) == 0)
			return bts[i];
	return bts[3];
}
char* bt_to_str(base_type bt) {
	/*
	Переводит тип базы данных base_type в строку, необходимо для записи в файл
	***
	Принимает тип базы данных bt  
	***
	Возвращает строку
	*/
	static char strs[3][MAX_STR_SIZE] = { "meetings", "declarers", "offences" };
	base_type bts[3] = { meetings, declarers, offences};
	for (int i = 0; i < 3; i++)
		if (bts[i] == bt)
			return strs[i];
}

void Base_operator::initializate()
{
	/*
	Подготовка баз данных привязанных к base_operator в конструкторе, 
	если файл в котором сохранены базы данных существует, 
	то происходит загрузка информации баз данных из него,
	иначе создаётся новый файл, и в него записывается
	информация о пустых базах данных
	*/
	FILE* in;
	char base_type_str[MAX_STR_SIZE] = "";
	int base_size = 0;
	in = fopen(path, "r");
	if (in) {
		for (int i = 0; i < base_cnt; i++) {
			fscanf(in, "%s %d\n", base_type_str, &base_size);
			base_type bt = str_to_bt(base_type_str);
			if (base_types[i] != bt) {
				error = 1;
				return;
			}
			dbs[i]->set_type(bt);
			dbs[i]->set_base_operator(this);
			realloc_array(bt, base_size);
			for (int j = 0; j < base_size; j++) {
				Database_record* rec = read(in, bt);
				if (rec != NULL)
					dbs[i]->add_record(rec);
				else
				{
					fclose(in);
					error = 1;
					return;
				}
			}
		}
		fclose(in);
	}
	else
	{
		FILE* out;
		out = fopen(path, "w");
		if (out) {
			for (int i = 0; i < base_cnt; i++) {
				(dbs[i])->set_type(base_types[i]);
				dbs[i]->set_base_operator(this);
				fprintf(out, "%s %d\n", bt_to_str(base_types[i]), 0);
			}
			fclose(out);
		}
		else
		{
			error = 1;
			return;
		}
	}
}

int Base_operator::save()
{
	/*
	Сохранение всех баз данных в файл
	***
	Возвращает единицу если сохранение успешно
	*/
	FILE *out = fopen(path, "w");
	if (out) {
		for (int i = 0; i < base_cnt; i++) {
			int base_size = dbs[i]->get_size();
			fprintf(out, "%s %d\n", bt_to_str(dbs[i]->get_type()), base_size);
			for (int j = 0; j < base_size; j++) {
				fprintf(out, "%ls\n", dbs[i]->get_record(j)->to_file_line());
			}
		}
		fclose(out);
		return 1;
	}
	return 0;
}

void Base_operator::realloc_array(base_type bt, int cnt)
{
	/*
	Динамическое перевыделение оперативной памяти баз данных при достижении их предельного размера
	***
	Принимает тип базы данных и новый размер базы данных
	*/
	switch (bt)
	{
	case base_type::meetings:
		if (cnt > meetings_data_size) {
			meetings_data = (Database_meetings_record**)realloc(meetings_data, sizeof(Database_meetings_record*) * cnt); 
			meetings_data_size = cnt;
			if (meetings_data == NULL) {
				mem_check_err();
			}
		}
		break;
	case base_type::declarers:
		if (cnt > declarers_data_size) {
			declarers_data = (Database_declarers_record**)realloc(declarers_data, sizeof(Database_declarers_record*) * cnt);
			declarers_data_size = cnt;
			if (declarers_data == NULL) {
				mem_check_err();
			}
		}
		break;
	case base_type::offences:
		if (cnt > offences_data_size) {
			offences_data = (Database_offences_record**)realloc(offences_data, sizeof(Database_offences_record*) * cnt);
			offences_data_size = cnt;
			if (offences_data == NULL) {
				mem_check_err();
			}
		}
		break;
	default:
		break;
	}
}

Database_record* Base_operator::read(FILE* in, base_type bt) {
	/*
	Считывание одной строки базы данных из файла
	***
	Принимает ссылку на файл и тип базы данных
	***
	Возвращает ссылку на преобразованную из строки запись базы данных
	*/
	Database_record* answer = NULL;
	wchar_t line[MAX_STR_SIZE * MAX_COL_COUNT] = {};
	wchar_t words[MAX_COL_COUNT][MAX_STR_SIZE] = {};
	wchar_t delim[] = L"|";
	fgetws(line, MAX_STR_SIZE * MAX_COL_COUNT, in);
	wchar_t* rowstate = 0;
	line[wcslen(line) - 1] = 0;// Удаляем \n
	wchar_t* ptr = wcstok_s(line, delim,&rowstate);
	int cnt = 0;
	while (ptr != NULL)
	{	
		wcsncpy(words[cnt], ptr, MAX_STR_SIZE); // Копируем строку до ближайшего разделителя ( | )
		ptr = wcstok_s(NULL, delim, &rowstate); // Передвигаем указатель на следующий разделитель
		cnt++;
	}
	return this->add(words, bt);
}

Database_record* Base_operator::add(wchar_t words[MAX_COL_COUNT][MAX_STR_SIZE], base_type bt) {
	/*
	Сохранение новой записи в оперативной памяти
	***
	Принимает массив строк (строковое представление записи) и тип базы данных 
	***
	Возвращает указатель на сохранённую запись
	*/
	Database_record* answer = NULL;
	switch (bt)
	{
	case base_type::meetings:
		meetings_data[meetings_cnt] = new Database_meetings_record();
		meetings_data[meetings_cnt]->from_string(words);
		answer = meetings_data[meetings_cnt];
		meetings_cnt++;
		if (meetings_cnt == meetings_data_size - 1)
			this->realloc_array(base_type::meetings, meetings_cnt + meetings_cnt / 2);
		break;
	case base_type::declarers:
		declarers_data[declarers_cnt] = new Database_declarers_record();
		declarers_data[declarers_cnt]->from_string(words);
		answer = declarers_data[declarers_cnt];
		declarers_cnt++;
		if (declarers_cnt == declarers_data_size - 1)
			this->realloc_array(base_type::declarers, declarers_cnt + declarers_cnt / 2);
		break;
	case base_type::offences:
		offences_data[offences_cnt] = new Database_offences_record();
		offences_data[offences_cnt]->from_string(words);
		answer = offences_data[offences_cnt];
		offences_cnt++;
		if (offences_cnt == offences_data_size - 1)
			this->realloc_array(base_type::offences, offences_cnt + offences_cnt / 2);
		break;
	default:
		break;
	}
	return answer;
}
