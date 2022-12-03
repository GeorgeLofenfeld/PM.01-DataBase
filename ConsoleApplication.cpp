/*
    Лофенфельд Георгий Владимирович
    ПКС - 303
    ***
    Вариант 30 - База Данных Митингов
    ***
    Главная функция программы (точка входа), подготовка данных перед запуском
*/

#include <windows.h> // Работа с графикой
#include <stdio.h> // Standart Input Output
#include <clocale> // русская локализация
#include <time.h> // Использование встроенной структуры tm 
#include "file.cpp" // Подключение исполняемого модуля file.cpp
#include "database.h" // Подключение заголовочного модуля database.h
//#include "database.cpp" // Подключение исполняемого модуля database.cpp
#include "frontend.h" // Подключение заголовочного модуля frontend.h
#include "frontend.cpp" // Подключение исполняего модуля frontend.cpp
#include "layouts.h" // Подключение заголовочного модуля layouts.h


/*
Этапы работы при запуске:

1. Задаются параметры консоли (41 - 45 строки)

2. Создание баз данных в программе и подгрузка информации из файла,
    если файла нет, создаётся новый с информацией о пустых базах данных (46 - 55 строки)

3. Создание экземпляра Frontend - класса для взаимодействия программы и пользователя (56 строка)

4. Подготовка layout'ов (схемы расположения элементов на экране)
    и их передача в экземпляр Frontend'a (57 - 60 строки)

5. Запуск основного процесса программы (61 строка)

*/

int main()
{
    HWND console = GetConsoleWindow(); // Получаем консоль
    HANDLE console_out = GetStdHandle(STD_OUTPUT_HANDLE); // Получаем обработчик консоли
    SetConsoleScreenBufferSize(console_out, GetLargestConsoleWindowSize(console_out)); // Для увеличения максимального количества выводимых символов
    ShowWindow(console, SW_MAXIMIZE); // Делаем окно максимального размера
    setlocale(LC_ALL, ""); // русская локализация
    char path[] = "Data_base_file"; // путь к файлу бд
    base_type bts[3] = { meetings, declarers, offences }; // Инициализируем три типа бд
    Database dbs[] = { Database() ,Database() ,Database() }; // Инициализируем три объекта бд
    Database* dbs_p[] = { &dbs[0], &dbs[1], &dbs[2] }; // ссылки на три бд
    Base_operator fo = Base_operator(path, dbs_p, 3, bts); // Инициализируем base_operator с тремя таблицами, с указанием их типов и с путём к сохранённому файлу (или создаёт)
    fo.initializate(); // Инициализация баз данных из файла
    if (fo.has_errors()) { // проверка файла
        printf("Файл Базы Данных повреждён или отсутствует\n");
        return 1;
    }
    Frontend fd = Frontend(); // создаём объект класса frontend (отвечает за отображение и взаимодействие) 
    fd.set_layout(create_menu_layout(), 0); // передаём результат функции создания вёрстки главного меню по индексу 0
    fd.set_layout(create_meetings_layout(dbs_p[0]), 1); // аналогично с главным меню + передаём ссылку на объект базы данных по индексу в create_meetings_layout 
    fd.set_layout(create_declarers_layout(dbs_p[1]), 2);
    fd.set_layout(create_offences_layout(dbs_p[2]), 3);
    fd.run(); // работает до тех пор, пока не будет вызван метод stop(), который завершает программу
    return 0;
}