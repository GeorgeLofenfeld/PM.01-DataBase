#include "file.h"
#include "database.h"
#include <stdio.h>
#include <clocale>
#include <time.h>
#include "database.h"
#include "frontend.h"
#include "layouts.h"
#include <windows.h>


int main()
{
    HWND console = GetConsoleWindow();
    HANDLE console_out = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleScreenBufferSize(console_out, GetLargestConsoleWindowSize(console_out));
    ShowWindow(console, SW_MAXIMIZE);
    setlocale(LC_ALL, "");
    char path[] = "test_db";
    base_type bts[3] = { meetings, declarers, offences };
    Database dbs[] = { Database() ,Database() ,Database() };
    Database* dbs_p[] = { &dbs[0], &dbs[1], &dbs[2] };
    Base_operator fo = Base_operator(path, dbs_p, 3, bts);
    fo.initializate();
    if (fo.has_errors()) {
        printf("something went wrong\n");
        return 1;
    }
    Frontend fd = Frontend();   
    fd.set_layout(create_menu_layout(), 0);
    fd.set_layout(create_meetings_layout(dbs_p[0]), 1);
    fd.set_layout(create_declarers_layout(dbs_p[1]), 2);
    fd.run();
    return 0;
}


    //получить актуальную бд get database() -> массив записей database
    // получить актуальную бд people get database() -> массив записей people
    //frontend->обработка кнопок

    /*printf("было:\n");
    db.print();
    struct tm date;
    date.tm_mday = 1;
    Database_record rec1 = Database_record(date, 100);
    date.tm_mday = 2;
    Database_record rec2 = Database_record(date, 1000);
    db.add_record(rec1);
    db.add_record(rec2);
    printf("стало:\n");
    db.print();
    db.save();*/

    /*HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
       COORD pos;
       pos.X = 10;
       pos.Y = 20;
       SetConsoleCursorPosition(hStdOut, pos);
       printf("button1");
       pos.X = 30;
       pos.Y = 20;
       SetConsoleCursorPosition(hStdOut, pos);
       printf("button2");
       */
