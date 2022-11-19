#pragma once
#include "frontend.h"

void meeting_main(Frontend* fd);

void declarers_main(Frontend* fd);

void offences_main(Frontend* fd);

void meeting_showing(Frontend* fd);

void declarers_showing(Frontend* fd);

void offences_showing(Frontend* fd);

void go_meeting(Frontend* fd);

void go_declarers(Frontend* fd);

void go_offences(Frontend* fd);

Table* get_table(Frontend* fd, int i, int choose = 1);

void meeting_sort(Frontend* fd);

void declarers_sort(Frontend* fd);

void offences_sort(Frontend* fd);

void add_to_meetings_table(Frontend* fd);

void add_to_declarers_table(Frontend* fd);

void add_to_offences_table(Frontend* fd);

void meetings_delete(Frontend* fd);

void declarers_delete(Frontend* fd);

void offences_delete(Frontend* fd);

void meetings_change(Frontend* fd);

void declarers_change(Frontend* fd);

void offences_change(Frontend* fd);

void meetings_search(Frontend* fd);

void declarers_search(Frontend* fd);

void offences_search(Frontend* fd);

void save(Frontend* fd);

void exit(Frontend* fd);
