#ifndef EASYMENU_H
#define EASYMENU_H

#include <iostream>
#include <vector>
#include <algorithm>
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

class EasyMenu {
public:
    int easy_run();

    void advanced_tick();
    void advanced_display_menu();
    bool advanced_is_pressed();
    int advanced_pressed_butt();
    void advanced_clear_console();
    void advanced_optimization_on();
    void advanced_optimization_off();

    void push_back_butt(string butt_name);
    void push_back_text(string text);
    void push_back_checkbox(string text);
    void push_back_checkbox(string text, bool is_activated);
    void push_back_advanced_cin(string name);
    void push_back_advanced_cin(string name, string original_text);

    void insert_butt(int32_t prev_index, string butt_name);
    void insert_text(int32_t prev_index, string text);
    void insert_checkbox(int32_t prev_index, string text);
    void insert_checkbox(int32_t prev_index, string text, bool is_activated);
    void insert_advanced_cin(int32_t prev_index, string name);
    void insert_advanced_cin(int32_t prev_index, string name, string original_text);

    void edit(int32_t index, string new_text);

    void pop_back();
    void delete_butt(int32_t index);
    void delete_all_text();
    void delete_notification(int32_t index);
    void set_info(string new_info);
    void set_notification(int32_t index, string new_notification);
    void delete_info();

    void set_color(int32_t index, int32_t color_id);
    void set_notification_color(int32_t index, int32_t color_id);
    void set_buttons_main_color(int32_t color_id);
    void set_pointer_main_color(int32_t color_id);
    void set_info_main_color(int32_t color_id);
    void set_mark_choose_main_color(int32_t color_id);
    void set_text_main_color(int32_t color_id);
    void set_checkbox_main_color(int32_t color_id);
    void set_advanced_cin_correct_color(int32_t color_id);
    void set_advanced_cin_uncorrect_color(int32_t color_id);
    void set_advanced_cin_max_input_length(int32_t index, int32_t max_length);

    void set_x_y_position(int32_t x, int32_t y);
    void set_mark_choose_on();
    void set_mark_choose_off();
    void set_new_pointer(string new_pointer);
    void set_pointer_off();
    void set_pointer_on();
    void set_advanced_cin_ban_not_allowed_on(int32_t index);
    void set_advanced_cin_ban_not_allowed_off(int32_t index);
    void set_advanced_cin_secure_input_on(int32_t index);
    void set_advanced_cin_secure_input_off(int32_t index);


    int32_t get_color(int32_t index);
    bool get_mark_choose_status();
    bool get_pointer_status();
    bool get_optimization_status();
    bool get_checkbox_status(int32_t index);
    std::vector<bool> get_all_checkbox_status();

    bool is_checkbox(int32_t index);
 

    EasyMenu();
    EasyMenu(string first_butt);
    EasyMenu(string first_butt, string second_butt);
    EasyMenu(string first_butt, string second_butt, string third_butt);
    EasyMenu(string first_butt, string second_butt, string third_butt, string fourth_butt);
    EasyMenu(string first_butt, string second_butt, string third_butt, string fourth_butt, string fifth_butt);
    EasyMenu(string first_butt, string second_butt, string third_butt, string fourth_butt, string fifth_butt, string sixth_butt);
    EasyMenu(string first_butt, string second_butt, string third_butt, string fourth_butt, string fifth_butt, string sixth_butt, string seventh_butt);
    EasyMenu(string first_butt, string second_butt, string third_butt, string fourth_butt, string fifth_butt, string sixth_butt, string seventh_butt, string eighth_butt);
    EasyMenu(string first_butt, string second_butt, string third_butt, string fourth_butt, string fifth_butt, string sixth_butt, string seventh_butt, string eighth_butt, string ninth_butt);
    EasyMenu(string first_butt, string second_butt, string third_butt, string fourth_butt, string fifth_butt, string sixth_butt, string seventh_butt, string eighth_butt, string ninth_butt, string tenth_butt);

private:
    // возможные типы кнопок меню
    #define BUTTON 1
    #define TEXT 0
    #define ADVANCED_INPUT 2
    #define CHECKBOX 3

    struct ButtData
    {   
        class AdvancedCIN 
        {
        public:
            AdvancedCIN();
            AdvancedCIN(string original_text);
            ~AdvancedCIN();

            void set_owner(EasyMenu* ptr);
            void set_text(string new_text);
            void set_max_inn_length(int32_t new_max_length);

            void ban_not_allowed_on();
            void ban_not_allowed_off();
            void secure_input_off();
            void secure_input_on();

            void run_cin(int32_t owner_index); // для ENTER_BUT
            void run_cin(int32_t owner_index, char symbol); // для ПРЯМОГО ВВОДА

            void displayCIN(int32_t owner_index);

            void clear();
            
        private:
            EasyMenu* owner_ptr_;

            int32_t max_length_;

            string buffer_;
            vector<char> allowed_char_vector_;

            bool is_need_output_refresh_;
            bool is_ban_not_allowed_;
            bool is_secured_;

            bool basic_input_check();
            void run_cin_background(char symbol, int32_t owner_index);
            char GetCharKey(int byte_system, int kb_numb);

            friend class EasyMenu;
        };

        ButtData() {
            name = "";
            notification = "";
            type = 1;
            color_id = WHITE_COLOR;
            notification_color_id = YELLOW_COLOR;
        }
        ButtData(string name, int32_t type, int32_t color_id) {
            this->name = name;
            this->type = type;
            this->color_id = color_id;
            notification = "";
            notification_color_id = YELLOW_COLOR;
        }
        ButtData(string name, int32_t type, int32_t color_id, bool is_activated) {
            this->name = name;
            this->type = type;
            this->color_id = color_id;
            this->is_activated = is_activated;
            notification = "";
            notification_color_id = YELLOW_COLOR;
        }
        ~ButtData() {}
        string name = "";
        string notification = "";
        int32_t type = 1;
        int32_t color_id = WHITE_COLOR;
        int32_t notification_color_id = YELLOW_COLOR;
        AdvancedCIN advanced_cin;   // будет инициализироваться по умолчанию
        bool is_activated = false;
    };

    int32_t x_pos_;
    int32_t y_pos_;

    int32_t count_of_lines_;
    int32_t count_of_buttons_;
    int32_t pointer_;
    int32_t last_pointer_;

    int32_t byte_system_;
    int32_t kb_numb_;

    int32_t butt_color_;
    int32_t pointer_color_;
    int32_t info_color_;
    int32_t mark_choose_color_;
    int32_t text_color_;
    int32_t checkbox_color_;
    int32_t advanced_input_color_;
    int32_t advanced_input_correct_color_;
    int32_t advanced_input_uncorrect_color_;

    vector<ButtData> buttons_data_vector_;
    string info_;

    string pointer_str_;
    string pointer_space_;  // для увеличения производительности

    bool is_info_full_;
    bool mark_choose_;
    bool is_pointer_on_;
    bool advanced_optimization_;

    bool is_need_screen_update_;
    bool is_need_pointer_update_;
    bool is_butt_pressed_;
    int32_t pressed_but_;

    int32_t easy_run_background();
    void display_pointer();
    void display_menu();
    void update_pointer();

    void clear_console();
    void go_to_xy(int32_t x, int32_t y);
    bool keyboard_check(int32_t* byte_system, int32_t* kb_numb);
    bool pointer_logic(int32_t* pointer, int32_t* last_pointer, int32_t count_of_buttons, int32_t kb_numb);

    int32_t get_pointer_index(int32_t pointer_);

    friend class AdvancedCIN;
};

#endif