/*
	Лофенфельд Георгий Владимирович
	ПКС - 303
	***
	Вариант 30 - База Данных Митингов
	***
	Реализация функций из database.h, относящихся к работе с файлом
*/

#include <stdio.h>
#include "database.h"
#include <wchar.h> // wide char - широкий символ - работа с алфавитами
#include "frontend.h"
#define _CRT_NON_CONFORMING_WCSTOK // Нужно для работы функции wcstok 


Base_operator::Base_operator(char* path, Database** dbs, int base_cnt, base_type* base_types) {
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
	char strs[3][10] = { "meetings", "declarers", "offences" };
	base_type bts[4] = { meetings, declarers, offences, error };
	for (int i = 0; i < 3; i++)
		if (strcmp(str, strs[i]) == 0)
			return bts[i];
	return bts[3];
}
char* bt_to_str(base_type bt) {
	static char strs[3][10] = { "meetings", "declarers", "offences" };
	base_type bts[3] = { meetings, declarers, offences};
	for (int i = 0; i < 3; i++)
		if (bts[i] == bt)
			return strs[i];
}

void Base_operator::initializate()
{
	FILE* in;
	char base_type_str[10] = "";
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
	FILE *out = fopen(path, "w");
	if (out) {
		for (int i = 0; i < base_cnt; i++) {
			int base_size = dbs[i]->get_size();
			fprintf(out, "%s %d\n", bt_to_str(dbs[i]->get_type()), base_size);
			for (int j = 0; j < base_size; j++) {
				fprintf(out, "%ls\n", dbs[i]->get_record(j)->to_line());
			}
		}
		fclose(out);
		return 1;
	}
	return 0;
}

void Base_operator::realloc_array(base_type bt, int cnt)
{

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
	Database_record* answer = NULL;
	wchar_t line[2560] = {};
	wchar_t words[20][128] = {};
	wchar_t delim[] = L"|";
	fgetws(line, 2560, in);
	wchar_t* rowstate = 0;
	line[wcslen(line) - 1] = 0;// remove \n
	wchar_t* ptr = wcstok_s(line, delim,&rowstate);
	int cnt = 0;
	while (ptr != NULL)
	{	
		wcsncpy(words[cnt], ptr, 128); // Копируем строку до ближайшего разделителя ( | )
		ptr = wcstok_s(NULL, delim, &rowstate); // передвигаем указатель на следующий разделитель
		cnt++;
	}
	return this->add(words, bt);
}

Database_record* Base_operator::add(wchar_t words[20][128], base_type bt) {
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
