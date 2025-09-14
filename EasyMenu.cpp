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

// ��������� ���� ������ ����
#define BUTTON 1
#define TEXT 0
#define ADVANCED_INPUT 2

EasyMenu::EasyMenu() {
    pointer_ = 0;
    last_pointer_ = -1;
    x_pos_ = 0;
    y_pos_ = 0;
    count_of_buttons_ = 0;
    count_of_lines_ = 0;
    byte_system_ = -1;
    kb_numb_ = -1;
    butt_color_ = CYAN_COLOR;
    pointer_color_ = LIGHT_YELLOW_COLOR;
    info_color_ = DARK_GRAY_COLOR;
    mark_choose_color_ = GREEN_COLOR;
    text_color_ = DARK_GRAY_COLOR;
    info_ = "";
    is_info_full_ = false;
    mark_choose_ = false;
    is_pointer_on_ = true;
    is_need_screen_update_ = false;
    advanced_optimization_ = false;
    is_butt_pressed_ = false;
    is_need_pointer_update_ = false;
    pressed_but_ = -1;

    std::setlocale(LC_ALL, "");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}

EasyMenu::EasyMenu(string first_butt) : EasyMenu() {
    count_of_buttons_++;
    buttons_vector_.push_back(first_butt);
    count_of_lines_++;
    buttons_type_vector_.push_back(BUTTON);
}

EasyMenu::EasyMenu(string first_butt, string second_butt) : EasyMenu(first_butt) {
    count_of_buttons_++;
    buttons_vector_.push_back(second_butt);
    count_of_lines_++;
    buttons_type_vector_.push_back(BUTTON);
}

EasyMenu::EasyMenu(string first_butt, string second_butt, string third_butt) : EasyMenu(first_butt, second_butt) {
    count_of_buttons_++;
    buttons_vector_.push_back(third_butt);
    count_of_lines_++;
    buttons_type_vector_.push_back(BUTTON);
}

EasyMenu::EasyMenu(string first_butt, string second_butt, string third_butt, string fourth_butt) : EasyMenu(first_butt, second_butt, third_butt) {
    count_of_buttons_++;
    buttons_vector_.push_back(fourth_butt);
    count_of_lines_++;
    buttons_type_vector_.push_back(BUTTON);
}

EasyMenu::EasyMenu(string first_butt, string second_butt, string third_butt, string fourth_butt, string fifth_butt) : EasyMenu(first_butt, second_butt, third_butt, fourth_butt) {
    count_of_buttons_++;
    buttons_vector_.push_back(fifth_butt);
    count_of_lines_++;
    buttons_type_vector_.push_back(BUTTON);
}

EasyMenu::EasyMenu(string first_butt, string second_butt, string third_butt, string fourth_butt, string fifth_butt, string sixth_butt) : EasyMenu(first_butt, second_butt, third_butt, fourth_butt, fifth_butt) {
    count_of_buttons_++;
    buttons_vector_.push_back(sixth_butt);
    count_of_lines_++;
    buttons_type_vector_.push_back(BUTTON);
}

EasyMenu::EasyMenu(string first_butt, string second_butt, string third_butt, string fourth_butt, string fifth_butt, string sixth_butt, string seventh_butt) : EasyMenu(first_butt, second_butt, third_butt, fourth_butt, fifth_butt, sixth_butt) {
    count_of_buttons_++;
    buttons_vector_.push_back(seventh_butt);
    count_of_lines_++;
    buttons_type_vector_.push_back(BUTTON);
}

EasyMenu::EasyMenu(string first_butt, string second_butt, string third_butt, string fourth_butt, string fifth_butt, string sixth_butt, string seventh_butt, string eighth_butt) : EasyMenu(first_butt, second_butt, third_butt, fourth_butt, fifth_butt, sixth_butt, seventh_butt) {
    count_of_buttons_++;
    buttons_vector_.push_back(eighth_butt);
    count_of_lines_++;
    buttons_type_vector_.push_back(BUTTON);
}

EasyMenu::EasyMenu(string first_butt, string second_butt, string third_butt, string fourth_butt, string fifth_butt, string sixth_butt, string seventh_butt, string eighth_butt, string ninth_butt) : EasyMenu(first_butt, second_butt, third_butt, fourth_butt, fifth_butt, sixth_butt, seventh_butt, eighth_butt) {
    count_of_buttons_++;
    buttons_vector_.push_back(ninth_butt);
    count_of_lines_++;
    buttons_type_vector_.push_back(BUTTON);
}

EasyMenu::EasyMenu(string first_butt, string second_butt, string third_butt, string fourth_butt, string fifth_butt, string sixth_butt, string seventh_butt, string eighth_butt, string ninth_butt, string tenth_butt) : EasyMenu(first_butt, second_butt, third_butt, fourth_butt, fifth_butt, sixth_butt, seventh_butt, eighth_butt, ninth_butt) {
    count_of_buttons_++;
    buttons_vector_.push_back(tenth_butt);
    count_of_lines_++;
    buttons_type_vector_.push_back(BUTTON);
}

int EasyMenu::easy_run() {
    return easy_run_background();
}

int32_t EasyMenu::easy_run_background() {
    if (count_of_buttons_ <= 0)
        return -1;
    clear_console();
    display_menu();
    display_pointer();
    while (true) {
        if (keyboard_check(&byte_system_, &kb_numb_)) {
            if (byte_system_ == BYTE_SYSTEM_IS_NOT_ONEBYTE) {
                if (pointer_logic(&pointer_, &last_pointer_, count_of_buttons_, kb_numb_))
                    update_pointer();
            }
            else if (byte_system_ == BYTE_SYSTEM_IS_ONEBYTE) {
                if (kb_numb_ == ENTER_BUT) {
                    clear_console();
                    return pointer_;
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
    go_to_xy(x_pos_, y_pos_);
    if (is_info_full_) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), info_color_);
        std::cout << info_;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), butt_color_);
    for (int32_t i = 0; i < count_of_lines_; i++) {
        go_to_xy(x_pos_, y_pos_ + is_info_full_ + i);
        if (buttons_type_vector_[i] == BUTTON) {
            if (is_pointer_on_)
                std::cout << "   ";
            std::cout << '[' << buttons_vector_[i] << ']';
        } 
        else {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text_color_);
            std::cout << buttons_vector_[i];
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), butt_color_);
        }
    }
    std::cout.flush(); // ������� �����
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE_COLOR);
    is_need_screen_update_ = false;
}

void EasyMenu::go_to_xy(int32_t x, int32_t y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { short(x), short(y) };
    SetConsoleCursorPosition(hConsole, pos);
}

void EasyMenu::display_pointer() {
    go_to_xy(x_pos_, y_pos_ + get_pointer_index(pointer_) + is_info_full_);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), pointer_color_);
    if (is_pointer_on_) {
        std::cout << "-->";
        if (mark_choose_) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), butt_color_);
            std::cout << '[';
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), mark_choose_color_);
            std::cout << buttons_vector_[get_pointer_index(pointer_)];
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), butt_color_);
            std::cout << ']';
            go_to_xy(x_pos_ + 3, y_pos_ + get_pointer_index(pointer_) + is_info_full_);
        }
    }
    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), mark_choose_color_);
        std::cout << '[' << buttons_vector_[get_pointer_index(pointer_)] << ']';
        go_to_xy(x_pos_, y_pos_ + get_pointer_index(pointer_) + is_info_full_);
    }
    last_pointer_ = pointer_;
    std::cout.flush(); // ������� �����
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE_COLOR);
}

void EasyMenu::update_pointer() {
    go_to_xy(x_pos_, y_pos_ + get_pointer_index(last_pointer_) + is_info_full_);
    if (is_pointer_on_) {
        std::cout << "   ";
        if (mark_choose_) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), butt_color_);
            std::cout << '[' << buttons_vector_[get_pointer_index(last_pointer_)] << ']';
        }
    }
    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), butt_color_);
        std::cout << '[' << buttons_vector_[get_pointer_index(last_pointer_)] << ']';
    }
    std::cout.flush(); // ����� �� ���� ���������� (������� �����)
    display_pointer();  
    is_need_pointer_update_ = false;
}

bool EasyMenu::keyboard_check(int32_t* byte_system, int32_t* kb_numb) {
    if (_kbhit()) {
        int key = _getch();
        if (key == 0) {
            *byte_system = 0;
            *kb_numb = _getch();
        }
        else if (key == 224) {
            if (_kbhit()) {
                *byte_system = 224;
                *kb_numb = _getch();
            }
            else {
                *byte_system = BYTE_SYSTEM_IS_ONEBYTE;
                *kb_numb = key;
            }
        }
        else {
            *byte_system = BYTE_SYSTEM_IS_ONEBYTE;
            *kb_numb = key;
        }
        return 1;
    }
    else {
        return 0;
    }
}

bool EasyMenu::pointer_logic(int32_t* pointer, int32_t* last_pointer, int32_t count_of_buttons, int32_t kb_numb) {
    *last_pointer = *pointer;
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
    count_of_buttons_++;
    count_of_lines_++;
    buttons_vector_.push_back(butt_name);
    buttons_type_vector_.push_back(BUTTON);
    is_need_screen_update_ = true;
}

void EasyMenu::push_back_text(string text) {
    count_of_lines_++;
    buttons_vector_.push_back(text);
    buttons_type_vector_.push_back(TEXT);
    is_need_screen_update_ = true;
}

void EasyMenu::insert_butt(int32_t prev_index, string butt_name) {
    if (prev_index < -1)
        prev_index = -1;
    count_of_buttons_++;
    count_of_lines_++;
    buttons_vector_.insert(buttons_vector_.begin() + prev_index + 1, butt_name);
    buttons_type_vector_.insert(buttons_type_vector_.begin() + prev_index + 1, BUTTON);
    is_need_screen_update_ = true;
}

void EasyMenu::insert_text(int32_t prev_index, string text) {
    if (prev_index < -1)
        prev_index = -1;
    count_of_lines_++;
    buttons_vector_.insert(buttons_vector_.begin() + prev_index + 1, text);
    buttons_type_vector_.insert(buttons_type_vector_.begin() + prev_index + 1, TEXT);
    is_need_screen_update_ = true;
}

void EasyMenu::pop_back() {
    if (count_of_lines_ > 0) {
        if (buttons_type_vector_[count_of_lines_ - 1] == BUTTON)
            count_of_buttons_--;
        count_of_lines_--;
        buttons_vector_.pop_back();
        buttons_type_vector_.pop_back();
        is_need_screen_update_ = true;
    }
}

void EasyMenu::set_buttons_color(int32_t color_id) {
    if (color_id > 15 || color_id < 0)
        return;
    butt_color_ = color_id;
    is_need_screen_update_ = true;
}

void EasyMenu::set_pointer_color(int32_t color_id) {
    if (color_id > 15 || color_id < 0)
        return;
    pointer_color_ = color_id;
    is_need_screen_update_ = true;
}

void EasyMenu::set_info(string new_info) {
    info_ = new_info;
    if (new_info.length() > 0)
        is_info_full_ = true;
    is_need_screen_update_ = true;
}

void EasyMenu::delete_info() {
    if (is_info_full_)
        is_need_screen_update_ = true;
    is_info_full_ = false;
}

void EasyMenu::set_info_color(int32_t color_id) {
    if (color_id > 15 || color_id < 0)
        return;
    info_color_ = color_id;
    is_need_screen_update_ = true;
}

void EasyMenu::set_mark_choose_on() {
    if (!mark_choose_)
        is_need_screen_update_ = true;
    mark_choose_ = true;
}

void EasyMenu::set_mark_choose_off() {
    if (mark_choose_)
        is_need_screen_update_ = true;
    mark_choose_ = false;
}

void EasyMenu::set_mark_choose_color(int32_t color_id) {
    if (color_id > 15 || color_id < 0)
        return;
    mark_choose_color_ = color_id;
    is_need_screen_update_ = true;
}

void EasyMenu::set_text_color(int32_t color_id) {
    if (color_id > 15 || color_id < 0)
        return;
    text_color_ = color_id;
    is_need_screen_update_ = true;
}

void EasyMenu::edit(int index, string new_text) {
    if (index >= 0 && index < count_of_lines_) {
        buttons_vector_[index] = new_text;
        is_need_screen_update_ = true;
        return;
    }
    return;
}

void EasyMenu::delete_butt(int index) {
    if (index >= 0 && index < count_of_lines_) {
        bool wasButton = (buttons_type_vector_[index] != TEXT);
        buttons_vector_.erase(buttons_vector_.begin() + index);
        buttons_type_vector_.erase(buttons_type_vector_.begin() + index);
        if (wasButton) {
            count_of_buttons_--;
            if (pointer_ >= count_of_buttons_)
                pointer_ = count_of_buttons_ - 1;  // ��������� ���������
            if (pointer_ < 0)
                pointer_ = 0;
            last_pointer_ = -1; // ���������� ������������
        }
        count_of_lines_--;
        is_need_screen_update_ = true;
    }
}

void EasyMenu::delete_all_text() {
    if (count_of_buttons_ == count_of_lines_)
        return;
    vector<string> tmp_vector;
    vector<int32_t> tmp_vector_types;
    tmp_vector.reserve(count_of_buttons_);
    tmp_vector_types.reserve(count_of_buttons_);
    for (int i{ 0 }; i < count_of_lines_; i++)
        if (buttons_type_vector_[i] != TEXT) {
            tmp_vector.push_back(buttons_vector_[i]);
            tmp_vector_types.push_back(buttons_type_vector_[i]);
        }
    // �������� ������ �� �����
    buttons_vector_ = tmp_vector;
    buttons_type_vector_ = tmp_vector_types;
    count_of_lines_ = count_of_buttons_;

    if (pointer_ >= count_of_buttons_)
        pointer_ = count_of_buttons_ - 1;
    if (pointer_ < 0)
        pointer_ = 0;
    last_pointer_ = -1; // ����� ����� ������������� ���������

    is_need_screen_update_ = true;
    is_need_pointer_update_ = true;
    return;
}

void EasyMenu::set_pointer_on() {
    if (!is_pointer_on_)
        is_need_screen_update_ = true;
    is_pointer_on_ = true;
}

void EasyMenu::set_pointer_off() {
    if (is_pointer_on_)
        is_need_screen_update_ = true;
    is_pointer_on_ = false;
}

void EasyMenu::advanced_tick() {
    if (is_need_screen_update_) {
        clear_console();
        if (count_of_buttons_ <= 0) {
            is_need_pointer_update_ = false;
            return;
        }
        display_menu();
        display_pointer();
        is_need_pointer_update_ = false;
    }
    if (keyboard_check(&byte_system_, &kb_numb_)) {
        if (byte_system_ == BYTE_SYSTEM_IS_NOT_ONEBYTE) {
            if (pointer_logic(&pointer_, &last_pointer_, count_of_buttons_, kb_numb_))
                update_pointer();
        }
        else if (byte_system_ == BYTE_SYSTEM_IS_ONEBYTE) {
            if (kb_numb_ == ENTER_BUT) {
                is_butt_pressed_ = true;
                pressed_but_ = pointer_;
            }
        }
    }
    else if (advanced_optimization_)
        Sleep(5);
}

void EasyMenu::advanced_display_menu() {
    if (count_of_buttons_ <= 0)
        return;
    display_menu();
    display_pointer();
}

bool EasyMenu::advanced_is_pressed() {
    return is_butt_pressed_;
}

int EasyMenu::advanced_pressed_butt() {
    if (is_butt_pressed_) {
        is_butt_pressed_ = false;
        return pressed_but_;
    }
    return -1;
}

void EasyMenu::advanced_clear_console() {
    clear_console();
}

void EasyMenu::advanced_optimization_on() {
    advanced_optimization_ = true;
}

void EasyMenu::advanced_optimization_off() {
    advanced_optimization_ = false;
}

void EasyMenu::set_x_y_position(int32_t x, int32_t y) {
    if (x < 0)
        x = 0;
    if (y < 0)
        y = 0;
    x_pos_ = x;
    y_pos_ = y;
}

int32_t EasyMenu::get_pointer_index(int32_t pointer_) {
    if (count_of_buttons_ == count_of_lines_)
        return pointer_;
    int32_t tmp{ -1 };
    for (int i{ 0 }; i < count_of_lines_; i++) {
        if (buttons_type_vector_[i] == BUTTON)
            tmp++;
        if (tmp == pointer_)
            return i;   // ���������� ������ ������ 
    }
    return NULL;
}