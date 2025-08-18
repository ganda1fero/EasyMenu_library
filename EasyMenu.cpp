#include "EasyMenu.h"

#define BYTE_SYSTEM_IS_ONEBYTE -1
#define BYTE_SYSTEM_IS_NOT_ONEBYTE 224
#define ENTER_BUT 13														
#define TAB_BUT 9
#define BACKSPACE_BUT 8														
#define ESC_BUT 27															
#define SPACE_BUT 32	
#define DOWN_POINTER_BUT 80
#define UP_POINTER_BUT 72

// все для Menu

Menu::Menu() {	// конструктор по умолчанию
	// инициализация
	pointer = 0;
	last_pointer = NULL;
	count_of_buttons = 0;
	byte_system = NULL;
	kb_numb = NULL;
	butt_color = CYAN_COLOR;
	pointer_color = LIGHT_YELLOW_COLOR;
	info_color = DARK_GRAY_COLOR;
	info = "";
	is_info_full = 0;
	vector<string> buttons_vector;	// пустой вектор
	// настройка (на всякий)
	std::setlocale(LC_ALL, "");
	SetConsoleCP(1251);				// Кодовая страница для ввода
	SetConsoleOutputCP(1251);		// Кодовая страница для вывода
}

Menu::Menu(string first_butt) : Menu() {	// конструктор с 1 кнопкой
	count_of_buttons++;
	buttons_vector.push_back(first_butt);	// добавли 
}

Menu::Menu(string first_butt, string second_butt) : Menu(first_butt) {	// конструтор с 2 кнопками
	count_of_buttons++;
	buttons_vector.push_back(second_butt);
}

Menu::Menu(string first_butt, string second_butt, string thirth_butt) : Menu(first_butt, second_butt) {
	count_of_buttons++;
	buttons_vector.push_back(thirth_butt);
}

Menu::Menu(string first_butt, string second_butt, string thirt_butt, string fourth_butt) : Menu(first_butt, second_butt, thirt_butt) {
	count_of_buttons++;
	buttons_vector.push_back(fourth_butt);
}

Menu::Menu(string first_butt, string second_butt, string thirt_butt, string fourth_butt, string fifth_butt) : Menu(first_butt, second_butt, thirt_butt, fourth_butt) {
	count_of_buttons++;
	buttons_vector.push_back(fifth_butt);
}

Menu::Menu(string first_butt, string second_butt, string thirt_butt, string fourth_butt, string fifth_butt, string sixth_butt) : Menu(first_butt, second_butt, thirt_butt, fourth_butt, fifth_butt) {
	count_of_buttons++;
	buttons_vector.push_back(sixth_butt);
}

Menu::Menu(string first_butt, string second_butt, string thirt_butt, string fourth_butt, string fifth_butt, string sixth_butt, string seventh_butt) : Menu(first_butt, second_butt, thirt_butt, fourth_butt, fifth_butt, sixth_butt) {
	count_of_buttons++;
	buttons_vector.push_back(seventh_butt);
}

Menu::Menu(string first_butt, string second_butt, string thirt_butt, string fourth_butt, string fifth_butt, string sixth_butt, string seventh_butt, string eigth_butt) : Menu(first_butt, second_butt, thirt_butt, fourth_butt, fifth_butt, sixth_butt, seventh_butt) {
	count_of_buttons++;
	buttons_vector.push_back(eigth_butt);
}

Menu::Menu(string first_butt, string second_butt, string thirt_butt, string fourth_butt, string fifth_butt, string sixth_butt, string seventh_butt, string eigth_butt, string nineth_butt) : Menu(first_butt, second_butt, thirt_butt, fourth_butt, fifth_butt, sixth_butt, seventh_butt, eigth_butt) {
	count_of_buttons++;
	buttons_vector.push_back(nineth_butt);
}

Menu::Menu(string first_butt, string second_butt, string thirt_butt, string fourth_butt, string fifth_butt, string sixth_butt, string seventh_butt, string eigth_butt, string nineth_butt, string tenth_butt) : Menu(first_butt, second_butt, thirt_butt, fourth_butt, fifth_butt, sixth_butt, seventh_butt, eigth_butt, nineth_butt) {
	count_of_buttons++;
	buttons_vector.push_back(tenth_butt);
}

int Menu::easy_run() {
	return easy_run_background();
}

int32_t Menu::easy_run_background() {
	if (count_of_buttons <= 0)
		return -1;		// ошибка (нет кнопок)
	clear_console();	// очистили консоль
	display_menu();		// отобразили само меню (кнопки и т д)
	display_pointer();	// отобразили стрелочку
	while (true) {		// бесконечный цикл
		if (keyboard_check(&byte_system, &kb_numb)) {
			if (byte_system == BYTE_SYSTEM_IS_NOT_ONEBYTE) {	// не однобайтовая система (возможно стрелочки)
				if (pointer_logic(&pointer, &last_pointer, count_of_buttons, kb_numb))
					update_pointer();
			}
			else if (byte_system == BYTE_SYSTEM_IS_ONEBYTE) {	// одноайтовая система (может быть ENTER)
				if (kb_numb == ENTER_BUT) {
					clear_console();
					return pointer;	// выходим из беск. цикла (нажали на кнопку)
				}
			}
		}
		else Sleep(15);
	}
}

void Menu::clear_console() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordScreen = { 0, 0 };
	DWORD charsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD consoleSize;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	consoleSize = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter(hConsole, ' ', consoleSize, coordScreen, &charsWritten);
	FillConsoleOutputAttribute(hConsole, csbi.wAttributes, consoleSize, coordScreen, &charsWritten);
	SetConsoleCursorPosition(hConsole, coordScreen);
}

void Menu::display_menu() {
	if (is_info_full) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), info_color);
		std::cout << info << std::endl;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), butt_color);
	for (int32_t i = 0; i < count_of_buttons; i++) {
		std::cout << "   " << '[' << buttons_vector[i] << ']' << std::endl;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE_COLOR);
}

void Menu::go_to_xy(int32_t x, int32_t y) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { short(x), short(y) };
	SetConsoleCursorPosition(hConsole, pos);
}

void Menu::display_pointer() {
	go_to_xy(0, pointer + is_info_full);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), pointer_color);
	std::cout << "-->";
	last_pointer = pointer;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE_COLOR);
}

void Menu::update_pointer() {
	go_to_xy(0, last_pointer + is_info_full);
	std::cout << "   ";
	display_pointer();
}

bool Menu::keyboard_check(int32_t* byte_system, int32_t* kb_numb) {
	if (_kbhit()) {															// keyboardhit() если нажата какая-нибудь клавиша
		int key = _getch();													// получаем номер символа (возможно первого -> 2-х байтовые клавиши)
		if (key == 0) {														// если первый байт = 0. (Функциональные клавиши F1–F12 в старых версиях DOS)
			*byte_system = 0;												// первый байт
			*kb_numb = _getch();											// получаем второй байт
		}
		else if (key == 224) {												// если первый байт = 224. (Стрелки)
			if (_kbhit()) {													// на русской раскладке однобайтовая система, но байт 'р' == 224
				*byte_system = 224;											// первый байт
				*kb_numb = _getch();										// получаем второй байт
			}
			else {                                      					// это была рус 'р'
				*byte_system = BYTE_SYSTEM_IS_ONEBYTE;						// первый байт
				*kb_numb = key;												// передаем знач. клавиши
			}
		}
		else {																// значит однобайтовая система
			*byte_system = BYTE_SYSTEM_IS_ONEBYTE;							// значит однобайтовая система
			*kb_numb = key;                             					// передаем знач. клавиши
		}
		return 1;															// нажатие было
	}
	else {
		return 0;															// нажатия не было
	}
}

bool Menu::pointer_logic(int32_t *pointer, int32_t *last_pointer, int32_t count_of_buttons, int32_t kb_numb) {
	*last_pointer = *pointer;	// переписали значение
	if (kb_numb == DOWN_POINTER_BUT) {
		if (*pointer >= count_of_buttons - 1)
			*pointer = 0;
		else
			*pointer += 1;
	}
	else if (kb_numb == UP_POINTER_BUT) {
		if (*pointer <= 0)
			*pointer = count_of_buttons - 1;
		else
			*pointer -= 1;
	}
	else
		return false;
	return true;
}

void Menu::push_back_butt(string butt_name) {
	count_of_buttons++;
	buttons_vector.push_back(butt_name);
}

void Menu::pop_back_butt() {
	if (count_of_buttons > 0) {
		count_of_buttons--;
		buttons_vector.pop_back();
	}
}

void Menu::set_buttons_color(int32_t color_id) {
	if (color_id > 15 || color_id < 0)
		return;
	butt_color = color_id;
}

void Menu::set_pointer_color(int32_t color_id) {
	if (color_id > 15 || color_id < 0)
		return;
	pointer_color = color_id;
}

void Menu::set_info(string new_info) {
	info = new_info;
	if (new_info.length() > 0)
		is_info_full = true;
}

void Menu::delete_info() {
	is_info_full = false;
}

void Menu::set_info_color(int32_t color_id) {
	if (color_id > 15 || color_id < 0)
		return;
	info_color = color_id;
}
//