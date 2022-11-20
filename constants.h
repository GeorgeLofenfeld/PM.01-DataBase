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