/*
			���������� Menu
#######################################
	int easy_run() - ������ ������ ������
	pop_back_butt()
	push_back_butt(string name)
	set_buttons_color(int32_t) - ����������� ����� define
	set_pointer_color(int32_t) - ����������� ����� define
	set_info(string new_info) - ��������/�������� ��� ��������� 
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
	//���������� ������

	int easy_run();		// ����� ��� �������� ������� (�������)
	void push_back_butt(string butt_name);
	void pop_back_butt();
	void set_buttons_color(int32_t color_id);
	void set_pointer_color(int32_t color_id);
	void set_info_color(int32_t color_id);
	void set_info(string new_info);
	void delete_info();
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

	// 

protected:

private:
	int32_t count_of_buttons;			// ������ ���������� ������
	int32_t pointer;					// ������ ��������� ������� (� 0 �� (n-1) ������)
	int32_t last_pointer;				// ������ ��������� ������� � ��������� ��� (� ������� �����)
	int32_t byte_system;				// ������ ����� �������� ������� ���������� �������
	int32_t kb_numb;					// ������ ����� ������ � �������� ������� ���������� �������
	int32_t butt_color;
	int32_t pointer_color;
	int32_t info_color;

	vector<string> buttons_vector;		// ������ �������� ������
	string info;
	bool is_info_full;	

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