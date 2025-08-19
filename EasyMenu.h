#ifndef EASYMENU_H
#define EASYMENU_H

#include <iostream>
#include <vector>
#include <conio.h>
#include <Windows.h>

// �������� define (����� �� ���� �������)
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
	//������� �������������
	int easy_run();		// ����� ��� �������� ������� (�������)

	//����������� ������������� (�������� �������������� ��������)
	void advenced_tick();// 1 ��� ������ 
	void advenced_display_menu();// ���������� ����
	bool advenced_is_pressed();
	int advenced_pressed_butt();
	void advenced_clear_console();
	void advenced_optimization_on();
	void advenced_optimization_off();

	// ��������� ������ ����
	void push_back_butt(string butt_name);		// �������� ������ � �����
	void pop_back_butt();						// ������� ������ � �����
	void edit_butt(int index, string new_text);	// �������� ����� ������ �� ������
	void delete_butt(int index);				// ������� ������ �� �������
	void set_info(string new_info);				// ��������/�������� ����������
	void delete_info();							// ������� ����������

	//��������� ����� ����
	void set_buttons_color(int32_t color_id);	// ���������� ����� ���� �������
	void set_pointer_color(int32_t color_id);	// ���������� ����� ���� ���������
	void set_info_color(int32_t color_id);		// ���������� ����� ���� ����������
	void set_mark_choose_color(int32_t color_id);// ���������� ����� ���� ��������� ��������� ������

	//��������� ������� ����
	void set_mark_choose_on();						// �������� ��������� ������ 
	void set_mark_choose_off();						// ��������� ��������� ������
	void set_pointer_off();
	void set_pointer_on();

	// �����������
	Menu();					// ����������� �� �������� (��� �������� � ����)
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
	// �������� ����
	int32_t count_of_buttons;			// ������ ���������� ������
	int32_t pointer;					// ������ ��������� ������� (� 0 �� (n-1) ������)
	int32_t last_pointer;				// ������ ��������� ������� � ��������� ��� (� ������� �����)

	// ���� ����� ����������
	int32_t byte_system;				// ������ ����� �������� ������� ���������� �������
	int32_t kb_numb;					// ������ ����� ������ � �������� ������� ���������� �������

	// ���� �������� ������
	int32_t butt_color;
	int32_t pointer_color;
	int32_t info_color;
	int32_t mark_choose_color;

	// ���� ���������� ����
	vector<string> buttons_vector;		// ������ �������� ������
	string info;

	// ���� ��������
	bool is_info_full;
	bool mark_choose;
	bool is_pointer_on;
	bool advenced_optimization;

	//���� ���������
	bool is_need_screen_update;
	bool is_need_pointer_update;
	bool is_butt_pressed;
	int32_t pressed_but;

	// ������ (��������)
	int32_t easy_run_background();		// ������ �������� �������
	void display_pointer();				// ���������� ������ (��� ������� �������)
	void display_menu();				// ���������� ���� (������ � � �)
	void update_pointer();				// ����� ������� ��� ��������

	// ���������� ������ (���������)
	void clear_console();				// ������� ���� �������
	void go_to_xy(int32_t x, int32_t y);// ���������� "������" �� (x,y)
	bool keyboard_check(int32_t* byte_system, int32_t* kb_numb);// ��������� ���������� �� ������� ������ (���� ������� ���� -> true)
	bool pointer_logic(int32_t* pointer, int32_t* last_pointer, int32_t count_of_buttons, int32_t kb_numb);// ������ ������� (���������� true, ���� �������� ����������)
};


#endif