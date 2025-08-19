#ifndef EASYMENU_H
#define EASYMENU_H

#include <iostream>
#include <vector>
#include <conio.h>
#include <Windows.h>

// наружние define (видны во всем проекте)
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
	//простое использование
	int easy_run();		// метод для простого запуска (обертка)

	//продвинутое использование (возможно контролировать ситуацию)
	void advenced_tick();// 1 тик логики 
	void advenced_display_menu();// отобразить меню
	bool advenced_is_pressed();
	int advenced_pressed_butt();
	void advenced_clear_console();
	void advenced_optimization_on();
	void advenced_optimization_off();

	// настройка кнопок меню
	void push_back_butt(string butt_name);		// добавить кнопку в конец
	void pop_back_butt();						// удалить кнопку с конца
	void edit_butt(int index, string new_text);	// изменить текст кнопки по идексу
	void delete_butt(int index);				// удалить кнопку по индексу
	void set_info(string new_info);				// добавить/изменить информацию
	void delete_info();							// удалить информацию

	//настройка цвета меню
	void set_buttons_color(int32_t color_id);	// установить новый цвет кнопкам
	void set_pointer_color(int32_t color_id);	// установить новый цвет стрелочке
	void set_info_color(int32_t color_id);		// установить новый цвет информации
	void set_mark_choose_color(int32_t color_id);// установить новый цвет выделению выбранной кнопки

	//настройка функций меню
	void set_mark_choose_on();						// включить подсветку выбора 
	void set_mark_choose_off();						// выключить подсветку выбора
	void set_pointer_off();
	void set_pointer_on();

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
protected:

private:
	// основные поля
	int32_t count_of_buttons;			// хранит количество кнопок
	int32_t pointer;					// хранит положение курсора (с 0 до (n-1) кнопок)
	int32_t last_pointer;				// хранит положение курсора в последний раз (с момента смены)

	// поля ввода клавиатуры
	int32_t byte_system;				// хранит номер байтовой системы последнего нажатия
	int32_t kb_numb;					// хранит номер кнопки в байтовой системе последнего нажатия

	// поля хранения цветов
	int32_t butt_color;
	int32_t pointer_color;
	int32_t info_color;
	int32_t mark_choose_color;

	// поля информации меню
	vector<string> buttons_vector;		// хранит названия кнопок
	string info;

	// поля настроек
	bool is_info_full;
	bool mark_choose;
	bool is_pointer_on;
	bool advenced_optimization;

	//поля триггеров
	bool is_need_screen_update;
	bool is_need_pointer_update;
	bool is_butt_pressed;
	int32_t pressed_but;

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