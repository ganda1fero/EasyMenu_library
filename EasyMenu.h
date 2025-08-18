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
	//���������� ������

	int32_t easy_run();		// ����� ��� �������� ������� (�������)
	void push_back_butt(string butt_name);
	void pop_back_butt();

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
	vector<string> buttons_vector;		// ������ �������� ������
	int32_t byte_system;				// ������ ����� �������� ������� ���������� �������
	int32_t kb_numb;					// ������ ����� ������ � �������� ������� ���������� �������

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