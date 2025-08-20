#include "EasyMenu.h"

// внутренние define (видны только внутри файла)
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

EasyMenu::EasyMenu() {	// конструктор по умолчанию
	// инициализация
	pointer = 0;
	last_pointer = NULL;
	count_of_buttons = 0;
	byte_system = NULL;
	kb_numb = NULL;
	butt_color = CYAN_COLOR;
	pointer_color = LIGHT_YELLOW_COLOR;
	info_color = DARK_GRAY_COLOR;
	mark_choose_color = GREEN_COLOR;
	info = "";
	is_info_full = 0;
	mark_choose = false;
	is_pointer_on = true;
	is_need_screen_update = false;
	advanced_optimization = false;

	// настройка (на всякий)
	std::setlocale(LC_ALL, "");
	SetConsoleCP(1251);				// Кодовая страница для ввода
	SetConsoleOutputCP(1251);		// Кодовая страница для вывода
}

EasyMenu::EasyMenu(string first_butt) : EasyMenu() {	// конструктор с 1 кнопкой
	count_of_buttons++;
	buttons_vector.push_back(first_butt);	// добавли 
}

EasyMenu::EasyMenu(string first_butt, string second_butt) : EasyMenu(first_butt) {	// конструтор с 2 кнопками
	count_of_buttons++;
	buttons_vector.push_back(second_butt);
}

EasyMenu::EasyMenu(string first_butt, string second_butt, string thirth_butt) : EasyMenu(first_butt, second_butt) {
	count_of_buttons++;
	buttons_vector.push_back(thirth_butt);
}

EasyMenu::EasyMenu(string first_butt, string second_butt, string thirt_butt, string fourth_butt) : EasyMenu(first_butt, second_butt, thirt_butt) {
	count_of_buttons++;
	buttons_vector.push_back(fourth_butt);
}

EasyMenu::EasyMenu(string first_butt, string second_butt, string thirt_butt, string fourth_butt, string fifth_butt) : EasyMenu(first_butt, second_butt, thirt_butt, fourth_butt) {
	count_of_buttons++;
	buttons_vector.push_back(fifth_butt);
}

EasyMenu::EasyMenu(string first_butt, string second_butt, string thirt_butt, string fourth_butt, string fifth_butt, string sixth_butt) : EasyMenu(first_butt, second_butt, thirt_butt, fourth_butt, fifth_butt) {
	count_of_buttons++;
	buttons_vector.push_back(sixth_butt);
}

EasyMenu::EasyMenu(string first_butt, string second_butt, string thirt_butt, string fourth_butt, string fifth_butt, string sixth_butt, string seventh_butt) : EasyMenu(first_butt, second_butt, thirt_butt, fourth_butt, fifth_butt, sixth_butt) {
	count_of_buttons++;
	buttons_vector.push_back(seventh_butt);
}

EasyMenu::EasyMenu(string first_butt, string second_butt, string thirt_butt, string fourth_butt, string fifth_butt, string sixth_butt, string seventh_butt, string eigth_butt) : EasyMenu(first_butt, second_butt, thirt_butt, fourth_butt, fifth_butt, sixth_butt, seventh_butt) {
	count_of_buttons++;
	buttons_vector.push_back(eigth_butt);
}

EasyMenu::EasyMenu(string first_butt, string second_butt, string thirt_butt, string fourth_butt, string fifth_butt, string sixth_butt, string seventh_butt, string eigth_butt, string nineth_butt) : EasyMenu(first_butt, second_butt, thirt_butt, fourth_butt, fifth_butt, sixth_butt, seventh_butt, eigth_butt) {
	count_of_buttons++;
	buttons_vector.push_back(nineth_butt);
}

EasyMenu::EasyMenu(string first_butt, string second_butt, string thirt_butt, string fourth_butt, string fifth_butt, string sixth_butt, string seventh_butt, string eigth_butt, string nineth_butt, string tenth_butt) : EasyMenu(first_butt, second_butt, thirt_butt, fourth_butt, fifth_butt, sixth_butt, seventh_butt, eigth_butt, nineth_butt) {
	count_of_buttons++;
	buttons_vector.push_back(tenth_butt);
}

int EasyMenu::easy_run() {
	return easy_run_background();
}

int32_t EasyMenu::easy_run_background() {
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
		else Sleep(5);
	}
}

void EasyMenu::clear_console() {
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

void EasyMenu::display_menu() {
	if (is_info_full) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), info_color);
		std::cout << info << std::endl;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), butt_color);
	for (int32_t i = 0; i < count_of_buttons; i++) {
		if (is_pointer_on)
			std::cout << "   ";
		std::cout << '[' << buttons_vector[i] << ']' << std::endl;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE_COLOR);
	is_need_screen_update = false;
}

void EasyMenu::go_to_xy(int32_t x, int32_t y) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { short(x), short(y) };
	SetConsoleCursorPosition(hConsole, pos);
}

void EasyMenu::display_pointer() {
	go_to_xy(0, pointer + is_info_full);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), pointer_color);
	if (is_pointer_on) {
		std::cout << "-->";
		if (mark_choose) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), butt_color);
			std::cout << '[';
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), mark_choose_color);
			std::cout << buttons_vector[pointer];
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), butt_color);
			std::cout << ']';
			go_to_xy(3, pointer + is_info_full);
		}
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), mark_choose_color);
		std::cout << '[' << buttons_vector[pointer] << ']';
		go_to_xy(0, pointer + is_info_full);
	}
	last_pointer = pointer;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE_COLOR);
}

void EasyMenu::update_pointer() {
	go_to_xy(0, last_pointer + is_info_full);
	if (is_pointer_on) {
		std::cout << "   ";
		if (mark_choose) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), butt_color);
			std::cout << '[' << buttons_vector[last_pointer] << ']';
		}
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), butt_color);
		std::cout << '[' << buttons_vector[last_pointer] << ']';
	}
	display_pointer();
	is_need_pointer_update = false;
}

bool EasyMenu::keyboard_check(int32_t* byte_system, int32_t* kb_numb) {
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

bool EasyMenu::pointer_logic(int32_t *pointer, int32_t *last_pointer, int32_t count_of_buttons, int32_t kb_numb) {
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

void EasyMenu::push_back_butt(string butt_name) {
	count_of_buttons++;
	buttons_vector.push_back(butt_name);
	is_need_screen_update = true;
}

void EasyMenu::pop_back_butt() {
	if (count_of_buttons > 0) {
		count_of_buttons--;
		buttons_vector.pop_back();
		is_need_screen_update = true;
	}
}

void EasyMenu::set_buttons_color(int32_t color_id) {
	if (color_id > 15 || color_id < 0)
		return;
	butt_color = color_id;
	is_need_screen_update = true;
}

void EasyMenu::set_pointer_color(int32_t color_id) {
	if (color_id > 15 || color_id < 0)
		return;
	pointer_color = color_id;
	is_need_screen_update = true;
}

void EasyMenu::set_info(string new_info) {
	info = new_info;
	if (new_info.length() > 0)
		is_info_full = true;
	is_need_screen_update = true;
}

void EasyMenu::delete_info() {
	if(is_info_full)
		is_need_screen_update = true;
	is_info_full = false;
}

void EasyMenu::set_info_color(int32_t color_id) {
	if (color_id > 15 || color_id < 0)
		return;
	info_color = color_id;
	is_need_screen_update = true;
}

void EasyMenu::set_mark_choose_on() {
	if (!mark_choose)
		is_need_screen_update = true;
	mark_choose = true;
}

void EasyMenu::set_mark_choose_off() {
	if (mark_choose)
		is_need_screen_update = true;
	mark_choose = false;
}

void EasyMenu::set_mark_choose_color(int32_t color_id) {
	if (color_id > 15 || color_id < 0)
		return;
	mark_choose_color = color_id;
	is_need_screen_update = true;
}

void EasyMenu::edit_butt(int index, string new_text) {
	if (index >= 0 && index < count_of_buttons) {
		buttons_vector[index] = new_text;
		is_need_screen_update = true;
		return;
	}
	return;
}

void EasyMenu::delete_butt(int index) {
	if (index >= 0 && index < count_of_buttons) {
		buttons_vector.erase(buttons_vector.begin() + index);	// удалили
		count_of_buttons--;
		is_need_screen_update = true;
		return;
	}
}

void EasyMenu::set_pointer_on() {
	if(!is_pointer_on)
		is_need_screen_update = true;
	is_pointer_on = true;
}

void EasyMenu::set_pointer_off() {
	if(is_pointer_on)
		is_need_screen_update = true;
	is_pointer_on = false;
}

void EasyMenu::advanced_tick() {
	if (is_need_screen_update) {
		clear_console();
		if (count_of_buttons < 0)
			return;
		display_menu();		// отобразили само меню (кнопки и т д)
		display_pointer();	// отобразили стрелочку
		is_need_pointer_update = false;
	}
	if (keyboard_check(&byte_system, &kb_numb)) {
		if (byte_system == BYTE_SYSTEM_IS_NOT_ONEBYTE) {	// не однобайтовая система (возможно стрелочки)
			if (pointer_logic(&pointer, &last_pointer, count_of_buttons, kb_numb))
				update_pointer();
		}
		else if (byte_system == BYTE_SYSTEM_IS_ONEBYTE) {	// одноайтовая система (может быть ENTER)
			if (kb_numb == ENTER_BUT) {
				is_butt_pressed = true;
				pressed_but = pointer;
			}
		}
	}
	else if (advanced_optimization)
		Sleep(5);
}

void EasyMenu::advanced_display_menu() {
	if (count_of_buttons < 0)
		return;
	display_menu();		// отобразили само меню (кнопки и т д)
	display_pointer();	// отобразили стрелочку
}

bool EasyMenu::advanced_is_pressed() {
	return is_butt_pressed;
}

int EasyMenu::advanced_pressed_butt() {
	if (is_butt_pressed) {
		is_butt_pressed = false;
		return pressed_but;
	}
	return -1;
}

void EasyMenu::advanced_clear_console() {
	clear_console();
}

void EasyMenu::advanced_optimization_on() {
	advanced_optimization = true;
}

void EasyMenu::advanced_optimization_off() {
	advanced_optimization = false;
}