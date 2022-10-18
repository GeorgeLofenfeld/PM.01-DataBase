#include "database.h"


Database::Database(int cnt)
{
	this->cnt = cnt;
	list_size = cnt > 5 ? (cnt + cnt / 2) : 10;
	base = (Database_record**)malloc(list_size * sizeof(Database_record*));
	base[0] = NULL;
}

Database::~Database()
{
	free(base);
}

void Database::delete_record(int i)
{
	Database_record* deleted = base[i];
	for (int j = i; j < cnt - 1; j++)
		base[j] = base[j + 1]; //memory will be free in Base_operator
	cnt -= 1;
}

void Database::change_record(int i, wchar_t str[20][128])
{
	base[i]->from_string(str);
}

void Database::search(wchar_t* str)
{
	for (int i = 0; i < cnt; i++)
		base[i]->find_string(str);
	quickSort(&base, -1, 0, cnt - 1);
}

void Database::add_record(Database_record* rec) {
	base[cnt] = rec;
	cnt += 1;
	if (cnt == list_size - 1) {
		list_size = list_size + list_size / 2;
		base = (Database_record**)realloc(base, list_size * sizeof(Database_record*));
	}
	base[cnt] = NULL;
}

void Database::add_record(wchar_t str[20][128])
{
	this->add_record(bop->add(str, this->type));
}

Database_record** Database::get_data()
{
	return base;
}


wchar_t* Database_record::to_line()
{
	wchar_t** str = this->to_string();
	for (int i = 0; i < field_cnt; i++) {
		wcsncat(line, str[i], 300);
		wcsncat(line, L"|", 300);
	}
	return line;
}

void Database_record::find_string(wchar_t* str)
{
	wchar_t* line = this->to_line();
	string_found = (wcsstr(line, str) != NULL);
}

void Database_record::malloc_strings()
{

	strings = (wchar_t**)malloc(20 * sizeof(wchar_t*));
	for (int i = 0; i < 20; i++)
		strings[i] = (wchar_t*)malloc(128 * sizeof(wchar_t));
}

void Database_record::free_strings()
{
	for (int i = 0; i < 20; i++)
		free(strings[i]);
	free(strings);
}

wchar_t** Database_meetings_record::to_string()
{
	swprintf(strings[0], 50, L"%d.%d.%d", date.tm_mday, date.tm_mon, date.tm_year);
	swprintf(strings[1], 50, L"%d:%d:%d", date.tm_hour, date.tm_min, date.tm_sec);
	swprintf(strings[2], 50, L"%d", declared_cnt);
	swprintf(strings[3], 50, L"%d", real_cnt);
	wcscpy(strings[4], address);
	wcscpy(strings[5], declarers);
	/*for (int i =0; i <declarers_cnt; i++)
		swprintf(strings[5] + strlen(strings[5]), "%d_", ids[i]);
	*/
	if (permitted)
		wcscpy(strings[6], L"ÄÀ");
	else
		wcscpy(strings[6], L"ÍÅÒ");
	return strings;
}

void Database_meetings_record::from_string(wchar_t str[20][128])
{
	swscanf(str[0], L"%d.%d.%d", &date.tm_mday, &date.tm_mon, &date.tm_year);
	swscanf(str[1], L"%d:%d:%d", &date.tm_hour, &date.tm_min, &date.tm_sec);
	swscanf(str[2], L"%d", &declared_cnt);
	swscanf(str[3], L"%d", &real_cnt);
	wcscpy(address, str[4]);
	wcscpy(declarers, str[5]);
	/*sscanf(str[4], "%d", &declarers_cnt);
	int shift = 0;
	int n = 0;
	for (int i = 0; i < declarers_cnt; i++) {
		sscanf(str[5]+shift, "%d%n_", &ids[i], &n);
		shift += n+1;
	}*/
	if (wcscmp(str[6], L"ÄÀ") == 0)
		permitted = 1;
	else
		permitted = 0;
}

int Database_meetings_record::compare(Database_record* y, int index)
{
	Database_meetings_record* y_m = (Database_meetings_record*)y;
	struct tm d1 = this->date;
	struct tm d2 = y_m->date;
	int date1 = 0, date2 = 0, time1 = 0, time2 = 0;
	switch (index)
	{
	case -1:
		return this->is_string_found() < y->is_string_found();
	case 0:
		date1 = d1.tm_year * 10000 + d1.tm_mon * 100 + d1.tm_mday;
		date2 = d2.tm_year * 10000 + d2.tm_mon * 100 + d2.tm_mday;
		return date1> date2;
	case 1:
		time1 = d1.tm_hour * 10000 + d1.tm_min * 100 + d1.tm_sec;
		time2 = d2.tm_hour * 10000 + d2.tm_min * 100 + d2.tm_sec;
		return time1 > time2;
	case 2:
		return this->declared_cnt > y_m->declared_cnt;
	case 3:
		return this->real_cnt > y_m->real_cnt;
	case 4:
		return this->permitted < y_m->permitted;
	default:
		break;
	}
	return 0;
}

wchar_t** Database_offences_record::to_string()
{
	wcscpy(strings[0], meeting);
	wcscpy(strings[1], offender_full_name);
	wcscpy(strings[2], normative_act);
	wcscpy(strings[3], article_and_paragraph);
	if (conviction_flag)
		wcscpy(strings[4], L"ÄÀ");
	else
		wcscpy(strings[4], L"ÍÅÒ");
	return strings;
}

void Database_offences_record::from_string(wchar_t str[20][128])
{
	wcscpy(meeting, str[0]);
	wcscpy(offender_full_name, str[1]);
	wcscpy(normative_act, str[2]);
	wcscpy(article_and_paragraph, str[3]);
	if (wcscmp(str[4], L"ÄÀ") == 0)
		conviction_flag = 1;
	else
		conviction_flag = 0;
}

wchar_t** Database_declarers_record::to_string()
{
	wcscpy(strings[0], full_name);
	if (has_offenses_flag)
		wcscpy(strings[1], L"ÄÀ");
	else
		wcscpy(strings[1], L"ÍÅÒ");
	return strings;
}

void Database_declarers_record::from_string(wchar_t str[20][128])
{
	wcscpy(full_name, str[0]);
	if (wcscmp(str[1], L"ÄÀ") == 0)
		has_offenses_flag = 1;
	else
		has_offenses_flag = 0;
}

int Database_declarers_record::compare(Database_record* y, int index)
{
	if (index == -1)
		return this->is_string_found() < y->is_string_found();
	return wcscmp(this->to_string()[index], y->to_string()[index]) >0;
}

void swap_record(Database_record** a, Database_record** b) {
	Database_record* t = *a;
	*a = *b;
	*b = t;
}

int partition(Database_record*** array, int index, int low, int high) {
	Database_record* pivot = (*array)[high];
	int i = (low - 1);
	for (int j = low; j < high; j++) {
		if (pivot->compare((*array)[j], index)) {
			i++;
			swap_record(&((*array)[i]), &((*array)[j]));
		}
	}
	swap_record(&((*array)[i + 1]), &((*array)[high]));
	return (i + 1);
}

void quickSort(Database_record*** array, int index, int low, int high) {
	if (low < high) {
		int pi = partition(array, index, low, high);
		quickSort(array, index, low, pi - 1);
		quickSort(array, index, pi + 1, high);
	}
}
