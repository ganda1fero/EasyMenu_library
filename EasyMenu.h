/*
			Функционал Menu
#######################################
	int easy_run() - легкий способ работы
	pop_back_butt()
	push_back_butt(string name)
	set_buttons_color(int32_t) - указывается через define
	set_pointer_color(int32_t) - указывается через define
	set_info(string new_info) - добавить/изменить доп иформацию 
	set_info_color(int32_t)
	delete_info()











*/
#ifndef EASYMENU_H
#define EASYMENU_H

#include <iostream>
#include <vector>
#include <conio.h>
#include <Windows.h>

#define BLACK_COLOR 0
#define BLUE_COLOR 1
#define GREEN_COLOR 2
#define CYAN_COLOR 3
#define RED_COLOR 4
#define MAGENTA_COLOR 5
#define YELLOW_COLOR 6
#define LIGHT_GRAY_COLOR 7
#define DARK_GRAY_COLOR 8
#define LIGHT_BlUE_COLOR 9
#define LIGHT_GREEN_COLOR 10
#define LIGHT_CYAN_COLOR 11
#define LIGHT_RED_COLOR 12
#define LIGHT_MAGENTA_COLOR 13
#define LIGHT_YELLOW_COLOR 14
#define WHITE_COLOR 15

using std::string;
using std::vector;

class Menu {
public:
	//оберточные методы

	int easy_run();		// метод для простого запуска (обертка)
	void push_back_butt(string butt_name);
	void pop_back_butt();
	void set_buttons_color(int32_t color_id);
	void set_pointer_color(int32_t color_id);
	void set_info_color(int32_t color_id);
	void set_info(string new_info);
	void delete_info();
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
	int32_t byte_system;				// хранит номер байтовой системы последнего нажатия
	int32_t kb_numb;					// хранит номер кнопки в байтовой системе последнего нажатия
	int32_t butt_color;
	int32_t pointer_color;
	int32_t info_color;

	vector<string> buttons_vector;		// хранит названия кнопок
	string info;
	bool is_info_full;	

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