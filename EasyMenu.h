#ifndef EASYMENU_H
#define EASYMENU_H

#include <iostream>
#include <vector>
#include <conio.h>
#include <Windows.h>

using std::string;
using std::vector;

class Menu {
public:
	//оберточные методы

	int32_t easy_run();		// метод для простого запуска (обертка)
	void push_back_butt(string butt_name);
	void pop_back_butt();

	// консрукторы

	Menu();					// конструктор по умоланию (все сводится к нему)
	Menu(string	first_butt);
	Menu(string	first_butt, string second_butt);
	Menu(string	first_butt, string second_butt, string thirth_butt);
	Menu(string	first_butt, string second_butt, string thirt_butt, string fourth_butt);
	Menu(string	first_butt, string second_butt, string thirt_butt, string fourth_butt, string fifth_butt);
	Menu(string	first_butt, string second_butt, string thirt_butt, string fourth_butt, string fifth_butt, string sixth_butt);
	Menu(string	first_butt, string second_butt, string thirt_butt, string fourth_butt, string fifth_butt, string sixth_butt, string seventh_butt);
	Menu(string	first_butt, string second_butt, string thirt_butt, string fourth_butt, string fifth_butt, string sixth_butt, string seventh_butt, string eigth_butt);
	Menu(string	first_butt, string second_butt, string thirt_butt, string fourth_butt, string fifth_butt, string sixth_butt, string seventh_butt, string eigth_butt, string nineth_butt);
	Menu(string	first_butt, string second_butt, string thirt_butt, string fourth_butt, string fifth_butt, string sixth_butt, string seventh_butt, string eigth_butt, string nineth_butt, string tenth_butt);

	// 

protected:

private:
	int32_t count_of_buttons;			// хранит количество кнопок
	int32_t pointer;					// хранит положение курсора (с 0 до (n-1) кнопок)
	int32_t last_pointer;				// хранит положение курсора в последний раз (с момента смены)
	vector<string> buttons_vector;		// хранит названия кнопок
	int32_t byte_system;				// хранит номер байтовой системы последнего нажатия
	int32_t kb_numb;					// хранит номер кнопки в байтовой системе последнего нажатия

	// методы (наружние)

	int32_t easy_run_background();		// логика простого запуска
	void display_pointer();				// отображает курсор (без очистки старого)
	void display_menu();				// отображает меню (кнопки и т д)
	void update_pointer();				// смена курсора при действии

	// внутренние методы (бэкграунд)

	void clear_console();				// очистка всей консоли
	void go_to_xy(int32_t x, int32_t y);// перемещает "курсор" на (x,y)
	bool keyboard_check(int32_t* byte_system, int32_t* kb_numb);// проверяет клавиатуру на нажатие кнопок (если нажатие было -> true)
	bool pointer_logic(int32_t* pointer, int32_t* last_pointer, int32_t count_of_buttons, int32_t kb_numb);// логика курсора (возвращает true, если значение изменилось)
};


#endif