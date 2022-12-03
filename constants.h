/*
	Лофенфельд Георгий Владимирович
	ПКС - 303
	***
	Вариант 30 - База Данных Митингов
	***
	Вынесение константных значений программы в отдельный модуль
*/

#define FOREGROUND_YELLOW 14 // Определение жёлтого цвета текста
#define FOREGROUND_TURQUOISE 11 // Определение бирюзового цвета текста
#define FOREGROUND_WHITE (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED) // Определие белого цвета текста
#define BACKGROUND_WHITE (BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED) // Определение белого цвета фона

#define _CRT_NON_CONFORMING_WCSTOK // Необходимо для работы функции wcstok 

#define KEY_LEFT 75 // Код клавиши "стрелка влево"
#define KEY_RIGHT 77 // Код клавиши "стрелка вправо"
#define KEY_UP 72 // Код клавиши "стрелка вверх"
#define KEY_DOWN 80 // Код клавиши "стрелка вниз"
#define KEY_ESC 27 // Код клавиши "escape"
#define KEY_ENTER 13 // Код клавиши "enter"
#define KEY_BACKSPACE 8 // Код клавиши "backspace"

#define DEFAULT_COL_SIZE 8 // Начальный размер столбца
#define DEFAULT_DBS_SIZE 10 // Начальный размер каждой базы данных
#define MAX_COL_COUNT 20 // Максимальное количество столбов в одной таблице 
#define MAX_STR_SIZE 128 // Макисимальный размер строки
#define	MAX_STR_TO_INT_SIZE 9 // Максимальный размер строкового представления числа при считывании
#define DATE_TIME_STR_SIZE 6 // Фиксированный размер строкового представления даты и времени
#define MAX_AVAILABLE_KEYS_COUNT 300 // Максимальное количество доступных клавиш
#define MAX_LAYOUT_OBJECTS_COUNT 100 // Максимальное количество объектов layout'a
#define MAX_LAYOYTS_COUNT 10 // Максимальное количество layout'ов в классе Frontend