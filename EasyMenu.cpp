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
#define LEFT_POINTER_BUT 75
#define RIGHT_POINTER_BUT 77

EasyMenu::EasyMenu() {
    pointer_ = 0;
    pointer_str_ = "-->";
    pointer_space_ = "   ";
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
    checkbox_color_ = WHITE_COLOR;
    advanced_input_color_ = LIGHT_BlUE_COLOR;
    advanced_input_correct_color_ = WHITE_COLOR;
    advanced_input_uncorrect_color_ = RED_COLOR;
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
    count_of_lines_++;
    buttons_data_vector_.push_back(ButtData(first_butt, BUTTON, butt_color_));
}

EasyMenu::EasyMenu(string first_butt, string second_butt) : EasyMenu(first_butt) {
    count_of_buttons_++;
    count_of_lines_++;
    buttons_data_vector_.push_back(ButtData(second_butt, BUTTON, butt_color_));
}

EasyMenu::EasyMenu(string first_butt, string second_butt, string third_butt) : EasyMenu(first_butt, second_butt) {
    count_of_buttons_++;
    count_of_lines_++;
    buttons_data_vector_.push_back(ButtData(third_butt, BUTTON, butt_color_));
}

EasyMenu::EasyMenu(string first_butt, string second_butt, string third_butt, string fourth_butt) : EasyMenu(first_butt, second_butt, third_butt) {
    count_of_buttons_++;
    count_of_lines_++;
    buttons_data_vector_.push_back(ButtData(fourth_butt, BUTTON, butt_color_));
}

EasyMenu::EasyMenu(string first_butt, string second_butt, string third_butt, string fourth_butt, string fifth_butt) : EasyMenu(first_butt, second_butt, third_butt, fourth_butt) {
    count_of_buttons_++;
    count_of_lines_++;
    buttons_data_vector_.push_back(ButtData(fifth_butt, BUTTON, butt_color_));
}

EasyMenu::EasyMenu(string first_butt, string second_butt, string third_butt, string fourth_butt, string fifth_butt, string sixth_butt) : EasyMenu(first_butt, second_butt, third_butt, fourth_butt, fifth_butt) {
    count_of_buttons_++;
    count_of_lines_++;
    buttons_data_vector_.push_back(ButtData(sixth_butt, BUTTON, butt_color_));
}

EasyMenu::EasyMenu(string first_butt, string second_butt, string third_butt, string fourth_butt, string fifth_butt, string sixth_butt, string seventh_butt) : EasyMenu(first_butt, second_butt, third_butt, fourth_butt, fifth_butt, sixth_butt) {
    count_of_buttons_++;
    count_of_lines_++;
    buttons_data_vector_.push_back(ButtData(seventh_butt, BUTTON, butt_color_));
}

EasyMenu::EasyMenu(string first_butt, string second_butt, string third_butt, string fourth_butt, string fifth_butt, string sixth_butt, string seventh_butt, string eighth_butt) : EasyMenu(first_butt, second_butt, third_butt, fourth_butt, fifth_butt, sixth_butt, seventh_butt) {
    count_of_buttons_++;
    count_of_lines_++;
    buttons_data_vector_.push_back(ButtData(eighth_butt, BUTTON, butt_color_));
}

EasyMenu::EasyMenu(string first_butt, string second_butt, string third_butt, string fourth_butt, string fifth_butt, string sixth_butt, string seventh_butt, string eighth_butt, string ninth_butt) : EasyMenu(first_butt, second_butt, third_butt, fourth_butt, fifth_butt, sixth_butt, seventh_butt, eighth_butt) {
    count_of_buttons_++;
    count_of_lines_++;
    buttons_data_vector_.push_back(ButtData(ninth_butt, BUTTON, butt_color_));
}

EasyMenu::EasyMenu(string first_butt, string second_butt, string third_butt, string fourth_butt, string fifth_butt, string sixth_butt, string seventh_butt, string eighth_butt, string ninth_butt, string tenth_butt) : EasyMenu(first_butt, second_butt, third_butt, fourth_butt, fifth_butt, sixth_butt, seventh_butt, eighth_butt, ninth_butt) {
    count_of_buttons_++;
    count_of_lines_++;
    buttons_data_vector_.push_back(ButtData(tenth_butt, BUTTON, butt_color_));
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
                    if (buttons_data_vector_[get_pointer_index(pointer_)].type == BUTTON) {
                        clear_console();
                        return pointer_;
                    }
                    else if (buttons_data_vector_[get_pointer_index(pointer_)].type == CHECKBOX) {
                        buttons_data_vector_[get_pointer_index(pointer_)].is_activated = !buttons_data_vector_[get_pointer_index(pointer_)].is_activated;
                        go_to_xy(x_pos_ + ((is_pointer_on_ == true) ? pointer_str_.length() : 0), y_pos_ + get_pointer_index(pointer_));
                        if (buttons_data_vector_[get_pointer_index(pointer_)].is_activated == true) {
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN_COLOR);
                            std::cout << "[#] ";
                        }
                        else {
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_GRAY_COLOR);
                            std::cout << "[ ] ";
                        }
                        go_to_xy(x_pos_ + (is_pointer_on_ == true) ? pointer_str_.length() : 0, y_pos_ + get_pointer_index(pointer_));
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE_COLOR);
                        std::cout.flush();
                        go_to_xy(x_pos_ + ((is_pointer_on_ == true) ? pointer_str_.length() : 0), y_pos_ + get_pointer_index(pointer_));
                    }
                    else if (buttons_data_vector_[get_pointer_index(pointer_)].type == ADVANCED_INPUT) {
                        buttons_data_vector_[get_pointer_index(pointer_)].advanced_cin.run_cin(get_pointer_index(pointer_));
                        update_pointer();
                    }
                }
                else if (buttons_data_vector_[get_pointer_index(pointer_)].type == ADVANCED_INPUT) {
                    buttons_data_vector_[get_pointer_index(pointer_)].advanced_cin.run_cin(get_pointer_index(pointer_), buttons_data_vector_[get_pointer_index(pointer_)].advanced_cin.GetCharKey(byte_system_, kb_numb_));
                    update_pointer();
                }
            }
        }
        else Sleep(5);
        if (is_need_screen_update_ == true) {
            clear_console();
            display_menu();
            display_pointer();
            is_need_screen_update_ = false;
            is_need_pointer_update_ = false;
        }
        else if (is_need_pointer_update_ == true) {
            update_pointer();
            is_need_pointer_update_ = false;
        }
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
    for (int32_t i = 0; i < count_of_lines_; i++) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), buttons_data_vector_[i].color_id);
        go_to_xy(x_pos_, y_pos_ + is_info_full_ + i);
        switch (buttons_data_vector_[i].type)
        {
        case BUTTON:
            if (is_pointer_on_)
                std::cout << pointer_space_;
            std::cout << '[' << buttons_data_vector_[i].name << ']';
            if (buttons_data_vector_[i].notification.length() > 0) { // выводим уведомление
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), buttons_data_vector_[i].notification_color_id);
                std::cout << "  " << buttons_data_vector_[i].notification;
            }
            break;
        case ADVANCED_INPUT:
            if (is_pointer_on_)
                std::cout << pointer_space_;
            std::cout << "[Ввод] ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_GRAY_COLOR);
            std::cout << buttons_data_vector_[i].name << ' ';
            buttons_data_vector_[i].advanced_cin.displayCIN(i);
            break;
        case CHECKBOX:
            if (is_pointer_on_)
                std::cout << pointer_space_;
            if (buttons_data_vector_[i].is_activated == true) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN_COLOR);
                std::cout << "[#] ";
            }
            else {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_GRAY_COLOR);
                std::cout << "[ ] ";    
            }
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), buttons_data_vector_[i].color_id);
            std::cout << buttons_data_vector_[i].name;
            if (buttons_data_vector_[i].notification.length() > 0) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), buttons_data_vector_[i].notification_color_id);
                std::cout << "  " << buttons_data_vector_[i].notification;
            }
            break;
        default:
            std::cout << buttons_data_vector_[i].name;
            break;
        }
    }
    std::cout.flush(); // очищаем буфер
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
        std::cout << pointer_str_;
        if (mark_choose_) {
            switch (buttons_data_vector_[get_pointer_index(pointer_)].type)
            {
            case ADVANCED_INPUT:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), mark_choose_color_);
                std::cout << "[Ввод]";
                go_to_xy(x_pos_ + pointer_str_.length(), y_pos_ + get_pointer_index(pointer_) + is_info_full_);
                break;
            case CHECKBOX:
                go_to_xy(x_pos_ + pointer_str_.length() + 4, y_pos_ + get_pointer_index(pointer_) + is_info_full_);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN_COLOR);
                std::cout << buttons_data_vector_[get_pointer_index(pointer_)].name;
                go_to_xy(x_pos_ + pointer_str_.length(), y_pos_ + get_pointer_index(pointer_) + is_info_full_);
                break;
            default:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), buttons_data_vector_[get_pointer_index(pointer_)].color_id);
                std::cout << '[';
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), mark_choose_color_);
                std::cout << buttons_data_vector_[get_pointer_index(pointer_)].name;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), buttons_data_vector_[get_pointer_index(pointer_)].color_id);
                std::cout << ']';
                go_to_xy(x_pos_ + pointer_str_.length(), y_pos_ + get_pointer_index(pointer_) + is_info_full_);
                break;
            }
        }
    }
    else {
        switch (buttons_data_vector_[get_pointer_index(pointer_)].type)
        {
        case ADVANCED_INPUT:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), mark_choose_color_);
            std::cout << "[Ввод]";
            go_to_xy(x_pos_, y_pos_ + get_pointer_index(pointer_) + is_info_full_);
            break;
        case CHECKBOX:
            go_to_xy(x_pos_ + 4, y_pos_ + get_pointer_index(pointer_) + is_info_full_);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN_COLOR);
            std::cout << buttons_data_vector_[get_pointer_index(pointer_)].name;
            go_to_xy(x_pos_, y_pos_ + get_pointer_index(pointer_) + is_info_full_);
            break;
        default:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), mark_choose_color_);
            std::cout << '[' << buttons_data_vector_[get_pointer_index(pointer_)].name << ']';
            go_to_xy(x_pos_, y_pos_ + get_pointer_index(pointer_) + is_info_full_);
            break;
        }
    }
    last_pointer_ = pointer_;
    std::cout.flush(); // очищаем буфер
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE_COLOR);
}

void EasyMenu::update_pointer() {
    go_to_xy(x_pos_, y_pos_ + get_pointer_index(last_pointer_) + is_info_full_);
    if (is_pointer_on_) {
        std::cout << pointer_space_;
        if (mark_choose_) {
            switch (buttons_data_vector_[get_pointer_index(last_pointer_)].type)
            {
            case ADVANCED_INPUT:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), buttons_data_vector_[get_pointer_index(last_pointer_)].color_id);
                std::cout << "[Ввод]";
                break;
            case CHECKBOX:
                go_to_xy(x_pos_ + pointer_str_.length() + 4, y_pos_ + get_pointer_index(last_pointer_) + is_info_full_);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), buttons_data_vector_[get_pointer_index(last_pointer_)].color_id);
                std::cout << buttons_data_vector_[get_pointer_index(last_pointer_)].name;
                break;
            default:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), buttons_data_vector_[get_pointer_index(last_pointer_)].color_id);
                std::cout << '[' << buttons_data_vector_[get_pointer_index(last_pointer_)].name << ']';
                break;
            }
        }
    }
    else {
        switch (buttons_data_vector_[get_pointer_index(last_pointer_)].type)
        {
        case ADVANCED_INPUT:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), buttons_data_vector_[get_pointer_index(last_pointer_)].color_id);
            std::cout << "[Ввод]";
            break;
        case CHECKBOX:
            go_to_xy(x_pos_ + 4, y_pos_ + get_pointer_index(last_pointer_) + is_info_full_);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), buttons_data_vector_[get_pointer_index(last_pointer_)].color_id);
            std::cout << buttons_data_vector_[get_pointer_index(last_pointer_)].name;
            break;
        default:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), buttons_data_vector_[get_pointer_index(last_pointer_)].color_id);
            std::cout << '[' << buttons_data_vector_[get_pointer_index(last_pointer_)].name << ']';
            break;
        }
    }
    std::cout.flush(); // чтобы не было отставания (очищаем буфер)
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
    buttons_data_vector_.push_back(ButtData(butt_name, BUTTON, butt_color_));
    is_need_screen_update_ = true;
}

void EasyMenu::push_back_text(string text) {
    count_of_lines_++;
    buttons_data_vector_.push_back(ButtData(text, TEXT, text_color_));
    is_need_screen_update_ = true;
}

void EasyMenu::push_back_checkbox(string text) {
    count_of_buttons_++;
    count_of_lines_++;
    buttons_data_vector_.push_back(ButtData(text, CHECKBOX, checkbox_color_));
    is_need_screen_update_ = true;
}

void EasyMenu::push_back_checkbox(string text, bool is_activated) {
    count_of_buttons_++;
    count_of_lines_++;
    buttons_data_vector_.push_back(ButtData(text, CHECKBOX, checkbox_color_, is_activated));
    is_need_screen_update_ = true;
}

void EasyMenu::push_back_advanced_cin(string name) {
    buttons_data_vector_.push_back(ButtData(name, ADVANCED_INPUT, advanced_input_color_));
    buttons_data_vector_[count_of_lines_].advanced_cin.set_owner(this);
    count_of_buttons_++;
    count_of_lines_++;
    is_need_screen_update_ = true;
}

void EasyMenu::push_back_advanced_cin(string name, string original_text) {
    buttons_data_vector_.push_back(ButtData(name, ADVANCED_INPUT, advanced_input_color_));
    buttons_data_vector_[count_of_lines_].advanced_cin.set_text(original_text);
    buttons_data_vector_[count_of_lines_].advanced_cin.set_owner(this);
    count_of_buttons_++;
    count_of_lines_++;
    is_need_screen_update_ = true;
}

void EasyMenu::insert_butt(int32_t index, string butt_name) {
    if (index < 0) {
        index = 0;
    }
    else if (index > count_of_lines_ - 1) {
        buttons_data_vector_.push_back(ButtData(butt_name, BUTTON, butt_color_));
        count_of_buttons_++;
        count_of_lines_++;
        is_need_screen_update_ = true;
        return;
    }
    buttons_data_vector_.insert(buttons_data_vector_.begin() + index, ButtData(butt_name, BUTTON, butt_color_));
    count_of_buttons_++;
    count_of_lines_++;
    is_need_screen_update_ = true;
    return;
}

void EasyMenu::insert_text(int32_t index, string text) {
    if (index < 0) {
        index = 0;
    }
    else if (index > count_of_lines_ - 1) {
        buttons_data_vector_.push_back(ButtData(text, TEXT, text_color_));
        count_of_lines_++;
        is_need_screen_update_ = true;
        return;
    }
    buttons_data_vector_.insert(buttons_data_vector_.begin() + index, ButtData(text, TEXT, text_color_));
    count_of_lines_++;
    is_need_screen_update_ = true;
    return;
}

void EasyMenu::insert_checkbox(int32_t index, string text) {
    if (index < 0) {
        index = 0;
    }
    else if (index > count_of_lines_ - 1) {
        buttons_data_vector_.push_back(ButtData(text, CHECKBOX, checkbox_color_));
        count_of_buttons_++;
        count_of_lines_++;
        is_need_screen_update_ = true;
        return;
    }
    buttons_data_vector_.insert(buttons_data_vector_.begin() + index, ButtData(text, CHECKBOX, checkbox_color_));
    count_of_buttons_++;
    count_of_lines_++;
    is_need_screen_update_ = true;
    return;
}

void EasyMenu::insert_checkbox(int32_t index, string text, bool is_activated) {
    if (index < 0) {
        index = 0;
    }
    else if (index > count_of_lines_ - 1) {
        buttons_data_vector_.push_back(ButtData(text, CHECKBOX, checkbox_color_, is_activated));
        count_of_buttons_++;
        count_of_lines_++;
        is_need_screen_update_ = true;
        return;
    }
    buttons_data_vector_.insert(buttons_data_vector_.begin() + index, ButtData(text, CHECKBOX, checkbox_color_, is_activated));
    count_of_buttons_++;
    count_of_lines_++;
    is_need_screen_update_ = true;
    return;
}

void EasyMenu::insert_advanced_cin(int32_t index, string name) {
    if (index < 0) {
        index = 0;
    }
    else if (index > count_of_lines_ - 1) {
        buttons_data_vector_.push_back(ButtData(name, ADVANCED_INPUT, advanced_input_color_));
        buttons_data_vector_.back().advanced_cin.set_owner(this);
        count_of_buttons_++;
        count_of_lines_++;
        is_need_screen_update_ = true;
        return;
    }
    buttons_data_vector_.insert(buttons_data_vector_.begin() + index, ButtData(name, ADVANCED_INPUT, advanced_input_color_));
    buttons_data_vector_[index].advanced_cin.set_owner(this);
    count_of_buttons_++;
    count_of_lines_++;
    is_need_screen_update_ = true;
    return;
}

void EasyMenu::insert_advanced_cin(int32_t index, string name, string original_text) {
    if (index < 0) {
        index = 0;
    }
    else if (index > count_of_lines_ - 1) {
        buttons_data_vector_.push_back(ButtData(name, ADVANCED_INPUT, advanced_input_color_));
        buttons_data_vector_.back().advanced_cin.set_text(original_text);
        buttons_data_vector_.back().advanced_cin.set_owner(this);
        count_of_buttons_++;
        count_of_lines_++;
        is_need_screen_update_ = true;
        return;
    }
    buttons_data_vector_.insert(buttons_data_vector_.begin() + index, ButtData(name, ADVANCED_INPUT, advanced_input_color_));
    buttons_data_vector_[index].advanced_cin.set_text(original_text);
    buttons_data_vector_[index].advanced_cin.set_owner(this);
    count_of_buttons_++;
    count_of_lines_++;
    is_need_screen_update_ = true;
    return;
}

void EasyMenu::pop_back() {
    if (count_of_lines_ > 0) {
        if (buttons_data_vector_[count_of_lines_ - 1].type != TEXT)
            count_of_buttons_--;
        count_of_lines_--;
        buttons_data_vector_.pop_back();
        is_need_screen_update_ = true;
    }
}

void EasyMenu::set_color(int32_t index, int32_t color_id) {
    if (index < 0 || index > count_of_lines_ - 1)
        return;
    if(color_id > 15 || color_id < 0)
        switch (buttons_data_vector_[index].type)
        {
        case BUTTON:
            color_id = butt_color_;
            break;
        case TEXT:
            color_id = text_color_;
            break;
        case ADVANCED_INPUT:
            color_id = advanced_input_color_;
            break;
        default:
            color_id = WHITE_COLOR;
            break;
        }
    buttons_data_vector_[index].color_id = color_id;
    is_need_screen_update_ = true;
    return;
}

void EasyMenu::set_notification_color(int32_t index, int32_t color_id) {
    if (index < 0 || index > count_of_lines_ - 1)
        return;
    if (color_id < 0 || color_id > 15)
        return;
    buttons_data_vector_[index].notification_color_id = color_id;
    return;
}

int32_t EasyMenu::get_color(int32_t index) {
    if (index < 0 || index > count_of_lines_ - 1)
        return -1;
    return buttons_data_vector_[index].color_id;
}

void EasyMenu::set_buttons_main_color(int32_t color_id) {
    if (color_id > 15 || color_id < 0)
        return;
    butt_color_ = color_id;
}

void EasyMenu::set_pointer_main_color(int32_t color_id) {
    if (color_id > 15 || color_id < 0)
        return;
    pointer_color_ = color_id;
}

void EasyMenu::set_checkbox_main_color(int32_t color_id) {
    if (color_id > 15 || color_id < 0)
        return;
    checkbox_color_ = color_id;
}

void EasyMenu::set_advanced_cin_correct_color(int32_t color_id) {
    if (color_id < 0 || color_id > 15 || color_id == advanced_input_correct_color_)
        return;
    advanced_input_correct_color_ = color_id;
    is_need_screen_update_ = true;
    return;
}

void EasyMenu::set_advanced_cin_uncorrect_color(int32_t color_id) {
    if (color_id < 0 || color_id > 15 || color_id == advanced_input_uncorrect_color_)
        return;
    advanced_input_uncorrect_color_ = color_id;
    is_need_screen_update_ = true;
    return;
}

void EasyMenu::set_advanced_cin_max_input_length(int32_t index, int32_t max_length) {
    if (index < 0 || index > count_of_lines_)
        return;
    if (buttons_data_vector_[index].type != ADVANCED_INPUT)
        return;
    buttons_data_vector_[index].advanced_cin.set_max_inn_length(max_length);
    is_need_screen_update_ = true;
    return;
}

void EasyMenu::set_advanced_cin_new_allowed_chars(int32_t index, std::vector<char> new_chars) {
    if (index < 0 || index > count_of_lines_ - 1)
        return;
    if (buttons_data_vector_[index].type == ADVANCED_INPUT)
        buttons_data_vector_[index].advanced_cin.set_new_allowed_chars(new_chars);
    return;
}

void EasyMenu::set_advanced_cin_new_allowed_chars(int32_t index, std::string new_chars) {
    if (index < 0 || index > count_of_lines_ - 1)
        return;
    if (buttons_data_vector_[index].type == ADVANCED_INPUT)
        buttons_data_vector_[index].advanced_cin.set_new_allowed_chars(new_chars);
    return;
}

void EasyMenu::set_info(string new_info) {
    info_ = new_info;
    if (new_info.length() > 0)
        is_info_full_ = true;
}

void EasyMenu::set_notification(int32_t index, string new_notification) {
    if (index < 0 || index > count_of_lines_ - 1)
        return;
    buttons_data_vector_[index].notification = new_notification;
    return;
}

void EasyMenu::delete_info() {
    if (is_info_full_)
        is_need_screen_update_ = true;
    is_info_full_ = false;
}

void EasyMenu::delete_notification(int32_t index) {
    if (index < 0 || index > count_of_lines_ - 1)
        return;
    buttons_data_vector_[index].notification.clear(); 
    return;
}

void EasyMenu::delete_all_notifications() {
    for (int i{ 0 }; i < buttons_data_vector_.size(); i++)
        buttons_data_vector_[i].notification.clear();
    return;
}

void EasyMenu::set_info_main_color(int32_t color_id) {
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

bool EasyMenu::get_mark_choose_status() {
    return mark_choose_;
}

void EasyMenu::set_mark_choose_main_color(int32_t color_id) {
    if (color_id > 15 || color_id < 0)
        return;
    mark_choose_color_ = color_id;
    is_need_screen_update_ = true;
}

void EasyMenu::set_text_main_color(int32_t color_id) {
    if (color_id > 15 || color_id < 0)
        return;
    text_color_ = color_id;
    is_need_screen_update_ = true;
}

void EasyMenu::edit(int32_t index, string new_text) {
    if (index >= 0 && index < count_of_lines_) {
        buttons_data_vector_[index].name = new_text;
        is_need_screen_update_ = true;
        return;
    }
    return;
}

void EasyMenu::delete_butt(int32_t index) {
    if (index >= 0 && index < count_of_lines_) {
        bool wasButton = (buttons_data_vector_[index].type != TEXT);
        buttons_data_vector_.erase(buttons_data_vector_.begin() + index);
        if (wasButton) {
            count_of_buttons_--;
            if (pointer_ >= count_of_buttons_)
                pointer_ = count_of_buttons_ - 1;  // фиксируем указатель
            if (pointer_ < 0)
                pointer_ = 0;
            last_pointer_ = -1; // заставляем перерисовать
        }
        count_of_lines_--;
        is_need_screen_update_ = true;
    }
}

void EasyMenu::delete_all_text() {
    if (count_of_buttons_ == count_of_lines_)
        return;
    vector<ButtData> tmp_vector;
    tmp_vector.reserve(count_of_buttons_);
    for (int i{ 0 }; i < count_of_lines_; i++)
        if (buttons_data_vector_[i].type != TEXT)
            tmp_vector.push_back(ButtData(buttons_data_vector_[i].name, buttons_data_vector_[i].type, buttons_data_vector_[i].color_id));
    // записали только НЕ ТЕКСТ
    buttons_data_vector_ = tmp_vector;
    count_of_lines_ = count_of_buttons_;

    if (pointer_ >= count_of_buttons_)
        pointer_ = count_of_buttons_ - 1;
    if (pointer_ < 0)
        pointer_ = 0;
    last_pointer_ = -1; // чтобы точно перерисовался указатель

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

void EasyMenu::set_advanced_cin_ban_not_allowed_on(int32_t index) {
    if (index < 0 || index > count_of_lines_)
        return;
    if (buttons_data_vector_[index].type != ADVANCED_INPUT)
        return;
    buttons_data_vector_[index].advanced_cin.ban_not_allowed_on();
    return;
}

void EasyMenu::set_advanced_cin_ban_not_allowed_off(int32_t index) {
    if (index < 0 || index > count_of_lines_)
        return;
    if (buttons_data_vector_[index].type != ADVANCED_INPUT)
        return;
    buttons_data_vector_[index].advanced_cin.ban_not_allowed_off();
    return;
}

void EasyMenu::set_advanced_cin_secure_input_on(int32_t index) {
    if (index < 0 || index > count_of_lines_)
        return;
    if (buttons_data_vector_[index].type != ADVANCED_INPUT)
        return;
    buttons_data_vector_[index].advanced_cin.secure_input_on();
    return;
}

void EasyMenu::set_advanced_cin_secure_input_off(int32_t index) {
    if (index < 0 || index > count_of_lines_)
        return;
    if (buttons_data_vector_[index].type != ADVANCED_INPUT)
        return;
    buttons_data_vector_[index].advanced_cin.secure_input_off();
    return;
}

void EasyMenu::set_new_pointer(string new_pointer) {
    if (new_pointer.length() == 0 || new_pointer.length() > 5)
        return;
    pointer_str_ = new_pointer;
    pointer_space_ = "";
    for (int i{ 0 }; i < pointer_str_.length(); i++)
        pointer_space_.push_back(' ');  // заполняем новый pointer_space_
    is_need_screen_update_ = true;
    return;
}

bool EasyMenu::get_pointer_status() {
    return is_pointer_on_;
}

void EasyMenu::advanced_tick() {
    if (is_need_screen_update_ == true) {
        clear_console();
        if (count_of_buttons_ <= 0) {
            is_need_pointer_update_ = false;
            return;
        }
        display_menu();
        display_pointer();
        is_need_pointer_update_ = false;
    }
    if (is_need_pointer_update_ == true) {
        update_pointer();
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

bool EasyMenu::get_optimization_status() {
    return advanced_optimization_;
}

bool EasyMenu::get_checkbox_status(int32_t index) {
    if (index < 0 || index > count_of_lines_ - 1)
        return false;
    if (buttons_data_vector_[index].type == CHECKBOX)
        return buttons_data_vector_[index].is_activated;
    return false;
}

std::vector<bool> EasyMenu::get_all_checkbox_status() {
    std::vector<bool> tmp_vector;
    tmp_vector.reserve(count_of_buttons_);  // просто на всякий резервируем для ускорения (при больше 1 чекбоксе)
    for (int i{ 0 }; i < count_of_lines_; i++)
        if (buttons_data_vector_[i].type == CHECKBOX)
            tmp_vector.push_back(buttons_data_vector_[i].is_activated);
    return tmp_vector;
}

std::string EasyMenu::get_advanced_cin_input(int32_t index) {
    if (index < 0 || index > count_of_lines_ - 1)
        return "";
    if (buttons_data_vector_[index].type == ADVANCED_INPUT)
        return buttons_data_vector_[index].advanced_cin.buffer_;
    return "";
}

std::vector<std::string> EasyMenu::get_all_advacned_cin_input() {
    std::vector<std::string> tmp_vector;
    tmp_vector.reserve(count_of_buttons_);
    for (int i{ 0 }; i < count_of_lines_; i++)
        if (buttons_data_vector_[i].type == ADVANCED_INPUT)
            tmp_vector.push_back(buttons_data_vector_[i].advanced_cin.buffer_);
    return tmp_vector;
}

int32_t EasyMenu::get_pointer_index(int32_t pointer_) {
    if (count_of_buttons_ == count_of_lines_)
        return pointer_;
    int32_t tmp{ -1 };
    for (int i{ 0 }; i < count_of_lines_; i++) {
        if (buttons_data_vector_[i].type != TEXT)
            tmp++;
        if (tmp == pointer_)
            return i;   // возвращаем нужный индекс 
    }
    return NULL;
}

bool EasyMenu::is_checkbox(int32_t index) {
    if (index < 0 || index > count_of_lines_ - 1)
        return false;
    if (buttons_data_vector_[index].type == CHECKBOX)
        return true;
    return false;
}

bool EasyMenu::is_advanced_cin(int32_t index) {
    if (index < 0 || index > count_of_lines_ - 1)
        return false;
    if (buttons_data_vector_[index].type == ADVANCED_INPUT)
        return true;
    return false;
}

bool EasyMenu::is_advanced_cin_correct(int32_t index) {
    if (index < 0 || index > count_of_lines_ - 1)
        return false;
    if (buttons_data_vector_[index].type == ADVANCED_INPUT)
        return ((buttons_data_vector_[index].advanced_cin.count_of_mistakes > 0) ? false : true);
    return false;
}

bool EasyMenu::is_all_advanced_cin_correct() {
    int32_t count_of_advanecd_cin{ 0 };
    for (int i{ 0 }; i < count_of_lines_; i++)
        if (buttons_data_vector_[i].type == ADVANCED_INPUT) {
            if (buttons_data_vector_[i].advanced_cin.count_of_mistakes > 0)
                return false;
            count_of_advanecd_cin++;
        }
    if (count_of_advanecd_cin == 0)
        return false;
    return true;
}

void EasyMenu::set_x_y_position(int32_t x, int32_t y) {
    if (x < 0)
        x = 0;
    if (y < 0)
        y = 0;
    x_pos_ = x;
    y_pos_ = y;
}

// все для EasyMenu::ButtData::AdvancedCIN...

EasyMenu::ButtData::AdvancedCIN::AdvancedCIN() {
    max_length_ = 20;
    count_of_mistakes = 0;
    buffer_ = "";
    buffer_.reserve(max_length_ + 3);
    is_need_output_refresh_ = false;
    is_ban_not_allowed_ = false;
    is_secured_ = false;
    owner_ptr_ = nullptr;
    allowed_char_vector_ = {    // базовый набор
    'A','B','C','D','E','F','G','H','I','J','K','L','M',
    'N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
    'a','b','c','d','e','f','g','h','i','j','k','l','m',
    'n','o','p','q','r','s','t','u','v','w','x','y','z',
    '0','1','2','3','4','5','6','7','8','9','-','_'
    };
    std::sort(allowed_char_vector_.begin(), allowed_char_vector_.end());
}

EasyMenu::ButtData::AdvancedCIN::AdvancedCIN(string original_text) : AdvancedCIN() {
    buffer_ = original_text;
}

EasyMenu::ButtData::AdvancedCIN::~AdvancedCIN() {
    // пасхалкО (300$)
}

void EasyMenu::ButtData::AdvancedCIN::set_owner(EasyMenu* ptr) {
    if (ptr != nullptr)
        owner_ptr_ = ptr;
}

void EasyMenu::ButtData::AdvancedCIN::set_text(string new_text) {
    if (new_text != buffer_) {
        buffer_ = new_text;
        is_need_output_refresh_ = true;
        return;
    }
    return;
}

void EasyMenu::ButtData::AdvancedCIN::set_max_inn_length(int32_t new_max_length) {
    if (max_length_ < 1 || max_length_ > 50)
        return;
    max_length_ = new_max_length;
    return;
}

void EasyMenu::ButtData::AdvancedCIN::set_new_allowed_chars(std::vector<char> new_allowed_vector) {
    allowed_char_vector_ = new_allowed_vector;
    std::sort(allowed_char_vector_.begin(), allowed_char_vector_.end());
    
    if (buffer_.length() > 0) { // перепроверяем на ошибки
        count_of_mistakes = 0;
        for (int i{ 0 }; i < buffer_.length(); i++) {
            if (std::binary_search(allowed_char_vector_.begin(), allowed_char_vector_.end(), buffer_[i]) == false)
                count_of_mistakes++;
        }
    }
    return;
}

void EasyMenu::ButtData::AdvancedCIN::set_new_allowed_chars(std::string new_allowed_chars) {
    allowed_char_vector_.clear();
    for (int i{ 0 }; i < new_allowed_chars.length(); i++)
        allowed_char_vector_.push_back(new_allowed_chars[i]);
    std::sort(allowed_char_vector_.begin(), allowed_char_vector_.end());

    if (buffer_.length() > 0) { // перепроверяем на ошибки
        count_of_mistakes = 0;
        for (int i{ 0 }; i < buffer_.length(); i++) {
            if (std::binary_search(allowed_char_vector_.begin(), allowed_char_vector_.end(), buffer_[i]) == false)
                count_of_mistakes++;
        }
    }
    return;
}

void EasyMenu::ButtData::AdvancedCIN::ban_not_allowed_on() {
    is_ban_not_allowed_ = true;
    return;
}

void EasyMenu::ButtData::AdvancedCIN::ban_not_allowed_off() {
    is_ban_not_allowed_ = false;
    return;
}

void EasyMenu::ButtData::AdvancedCIN::secure_input_on() {
    is_secured_ = true;
    return;
}

void EasyMenu::ButtData::AdvancedCIN::secure_input_off() {
    is_secured_ = false;
    return;
}

void EasyMenu::ButtData::AdvancedCIN::run_cin(int32_t owner_index) {   // для ENTER_BUT
    run_cin(owner_index, '\0');
}

void EasyMenu::ButtData::AdvancedCIN::run_cin(int32_t owner_index, char symbol) {
    if (owner_ptr_->buttons_data_vector_[owner_index].notification.length() > 0) {
        owner_ptr_->go_to_xy(owner_ptr_->x_pos_ + ((owner_ptr_->is_pointer_on_ == true) ? owner_ptr_->pointer_str_.length() : 0) + 6 + 1 + owner_ptr_->buttons_data_vector_[owner_index].name.length() + 1 + buffer_.length() + 2, owner_ptr_->y_pos_ + owner_index + owner_ptr_->is_info_full_);
        for (int32_t i{ 0 }; i < owner_ptr_->buttons_data_vector_[owner_index].notification.length(); i++)
            std::cout << ' ';
    }
    owner_ptr_->go_to_xy(owner_ptr_->x_pos_, owner_ptr_->y_pos_ + owner_index + owner_ptr_->is_info_full_);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN_COLOR);
    if (owner_ptr_->is_pointer_on_ == true)
        std::cout << owner_ptr_->pointer_str_;
    std::cout << "[Ввод]";
    owner_ptr_->go_to_xy(owner_ptr_->x_pos_ + ((owner_ptr_->is_pointer_on_ == true) ? owner_ptr_->pointer_str_.length() : 0) + 6 + 1 + owner_ptr_->buttons_data_vector_[owner_index].name.length() + 1 + buffer_.length(), owner_ptr_->y_pos_ + owner_index + owner_ptr_->is_info_full_);

    run_cin_background(symbol, owner_index);   // запускаем с нулевым вводом

    owner_ptr_->go_to_xy(owner_ptr_->x_pos_ + ((owner_ptr_->is_pointer_on_ == true) ? owner_ptr_->pointer_str_.length() : 0), owner_ptr_->y_pos_ + owner_index + owner_ptr_->is_info_full_);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), owner_ptr_->buttons_data_vector_[owner_index].color_id);
    std::cout << "[Ввод]";
    // место для окончательной проверки (пока простая - на некорректный ввод)
    if (basic_input_check() == false) {
        owner_ptr_->buttons_data_vector_[owner_index].notification = "Исправьте ошибк(у/и) в вводе!";
        owner_ptr_->buttons_data_vector_[owner_index].notification_color_id = RED_COLOR;
    }else
        owner_ptr_->buttons_data_vector_[owner_index].notification = "";
    // место для вывода нового увед. (если есть)
    if (owner_ptr_->buttons_data_vector_[owner_index].notification.length() > 0) {
        owner_ptr_->go_to_xy(owner_ptr_->x_pos_ + ((owner_ptr_->is_pointer_on_ == true) ? owner_ptr_->pointer_str_.length() : 0) + 6 + 1 + owner_ptr_->buttons_data_vector_[owner_index].name.length() + 1 + buffer_.length() + 2, owner_ptr_->y_pos_ + owner_index + owner_ptr_->is_info_full_);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), owner_ptr_->buttons_data_vector_[owner_index].notification_color_id);
        std::cout << owner_ptr_->buttons_data_vector_[owner_index].notification;
        std::cout.flush();
    }
}

void EasyMenu::ButtData::AdvancedCIN::displayCIN(int32_t owner_index) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), owner_ptr_->advanced_input_correct_color_);
    owner_ptr_->go_to_xy(owner_ptr_->x_pos_ + ((owner_ptr_->is_pointer_on_ == true) ? owner_ptr_->pointer_str_.length() : 0) + 7 + owner_ptr_->buttons_data_vector_[owner_index].name.length() + 1, owner_ptr_->y_pos_ + owner_index + owner_ptr_->is_info_full_);
    bool is_last_correct = true;
    for (int32_t i{ 0 }; i < buffer_.length(); i++) {
        if (std::binary_search(allowed_char_vector_.begin(), allowed_char_vector_.end(), buffer_[i]) == true) {
            if (is_last_correct == false) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), owner_ptr_->advanced_input_correct_color_);
                is_last_correct = true;
            }
            if (is_secured_ == true)
                std::cout << '*';
            else 
                std::cout << buffer_[i];
        }
        else {
            if (is_last_correct == true) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), owner_ptr_->advanced_input_uncorrect_color_);
                is_last_correct = false;
            }
            std::cout << buffer_[i];
        }
    }
    // ввели все, что было написано -> выводим коментарий
    if (owner_ptr_->buttons_data_vector_[owner_index].notification.length() > 0) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), owner_ptr_->buttons_data_vector_[owner_index].notification_color_id);
        std::cout << "  " << owner_ptr_->buttons_data_vector_[owner_index].notification;
    }
}

void EasyMenu::ButtData::AdvancedCIN::clear() {
    buffer_ = "";
}

bool EasyMenu::ButtData::AdvancedCIN::basic_input_check() {
    for (int i{ 0 }; i < buffer_.length(); i++) {
        if (std::binary_search(allowed_char_vector_.begin(), allowed_char_vector_.end(), buffer_[i]) == false)
            return false;
    }
    return true;
}

void EasyMenu::ButtData::AdvancedCIN::run_cin_background(char symbol, int32_t owner_index) {
    int32_t byte_system{ -1 }, kb_numb{ -1 };
    int32_t inn_pointer = buffer_.length(); // отдельный указатель ввода
    bool is_last_correct = true;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), owner_ptr_->advanced_input_correct_color_);
    // если у нас есть нач. ввод
    if (symbol != '\0' && buffer_.length() < max_length_) { // нач ввод
        if (std::binary_search(allowed_char_vector_.begin(), allowed_char_vector_.end(), symbol) == true) { // можем вводить в любом случ
            buffer_.push_back(symbol);
            if(is_secured_ == true)
                std::cout << '*';
            else
                std::cout << symbol;
            inn_pointer++;
        }
        else if (is_ban_not_allowed_ == false && symbol != ' ') {  // если общий блок выключен и это не (попавший в неразрешенный space)
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), owner_ptr_->advanced_input_uncorrect_color_);
            is_last_correct = false;            
            buffer_.push_back(symbol);
            std::cout << symbol;
            inn_pointer++;
        }
        std::cout.flush();
    }
    char tmp_char;
    while (true) {
        if (owner_ptr_->keyboard_check(&byte_system, &kb_numb) == true) {
            if (byte_system == BYTE_SYSTEM_IS_ONEBYTE) { // буквы
                switch (kb_numb) {
                case ENTER_BUT: // ввод (как стрелочка вниз)
                    owner_ptr_->pointer_logic(&(owner_ptr_->pointer_), &(owner_ptr_->last_pointer_), owner_ptr_->count_of_buttons_, DOWN_POINTER_BUT);
                    return;
                    break;
                case ESC_BUT:   // выход 
                    return;
                    break;
                case BACKSPACE_BUT: // удаляем 
                    if (buffer_.length() > 0) { // => есть что удалять
                        if (inn_pointer == buffer_.length()) {  // удаляем с конца
                            if (std::binary_search(allowed_char_vector_.begin(), allowed_char_vector_.end(), buffer_[inn_pointer - 1]) == false)
                                count_of_mistakes--; // значит удалили ошибочный ввод
                            buffer_.pop_back();
                            // внешняя часть
                            std::cout << '\b' << ' ' << '\b';
                            std::cout.flush();
                            inn_pointer--;
                        }
                        else if(inn_pointer > 0) { // удаляем не с конца и не в начале
                            if (std::binary_search(allowed_char_vector_.begin(), allowed_char_vector_.end(), buffer_[inn_pointer - 1]) == false)
                                count_of_mistakes--; // значит удалили ошибочный ввод
                            buffer_.erase(buffer_.begin() + inn_pointer - 1);
                            // внешняя часть
                            std::cout << '\b';
                            for (int i{ 0 }; i < buffer_.length() - inn_pointer + 2; i++)
                                std::cout << ' '; // очистили для сдвига
                            owner_ptr_->go_to_xy(owner_ptr_->x_pos_ + ((owner_ptr_->is_pointer_on_ == true) ? owner_ptr_->pointer_str_.length() : 0) + 6 + 1 + owner_ptr_->buttons_data_vector_[owner_index].name.length() + 1 + inn_pointer - 1, owner_ptr_->y_pos_ + owner_index + owner_ptr_->is_info_full_);
                            for (int i{ inn_pointer - 1 }; i < buffer_.length(); i++) {
                                if (std::binary_search(allowed_char_vector_.begin(), allowed_char_vector_.end(), buffer_[i]) == true) {
                                    if (is_last_correct == false) {
                                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), owner_ptr_->advanced_input_correct_color_);
                                        is_last_correct = true;
                                    }
                                    if (is_secured_ == true)
                                        std::cout << '*';
                                    else
                                        std::cout << buffer_[i];
                                }
                                else {
                                    if (is_last_correct == true) {
                                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), owner_ptr_->advanced_input_uncorrect_color_);
                                        is_last_correct = false;
                                    }
                                    std::cout << buffer_[i];
                                }
                            }
                            inn_pointer--;
                            owner_ptr_->go_to_xy(owner_ptr_->x_pos_ + ((owner_ptr_->is_pointer_on_ == true) ? owner_ptr_->pointer_str_.length() : 0) + 6 + 1 + owner_ptr_->buttons_data_vector_[owner_index].name.length() + 1 + inn_pointer, owner_ptr_->y_pos_ + owner_index + owner_ptr_->is_info_full_);
                            std::cout.flush();
                        }
                    }
                    break;
                default:
                    if (kb_numb != TAB_BUT) {   
                        if ((tmp_char = GetCharKey(byte_system, kb_numb)) != '\0') {    // если это реально можно напечатать 
                            if (buffer_.length() < max_length_) {// => можем вводить
                                if (std::binary_search(allowed_char_vector_.begin(), allowed_char_vector_.end(), tmp_char) == true) { // можем вводить в любом случ
                                    if (is_last_correct == false) {
                                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), owner_ptr_->advanced_input_correct_color_);
                                        is_last_correct = true;
                                    }   // меняем цвет для вывода на будущее (если не был нужный)
                                    if (inn_pointer == buffer_.length()) { // вводим разрешенный в конец
                                        buffer_.push_back(tmp_char);
                                        if (is_secured_ == true)
                                            std::cout << '*';
                                        else
                                            std::cout << tmp_char;
                                        inn_pointer++;
                                    }
                                    else {  // вводим разрешенный не в конец
                                        buffer_.insert(buffer_.begin() + inn_pointer, tmp_char);
                                        for (int i{ 0 }; i < buffer_.length() - inn_pointer; i++)
                                            std::cout << ' '; // очищаем для сдвига
                                        owner_ptr_->go_to_xy(owner_ptr_->x_pos_ + ((owner_ptr_->is_pointer_on_ == true) ? owner_ptr_->pointer_str_.length() : 0) + 6 + 1 + owner_ptr_->buttons_data_vector_[owner_index].name.length() + 1 + inn_pointer, owner_ptr_->y_pos_ + owner_index + owner_ptr_->is_info_full_);
                                        for (int i{ inn_pointer }; i < buffer_.length(); i++) { // печатаем на 1 символ больше
                                            if (std::binary_search(allowed_char_vector_.begin(), allowed_char_vector_.end(), buffer_[i]) == true) {
                                                if (is_last_correct == false) {
                                                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), owner_ptr_->advanced_input_correct_color_);
                                                    is_last_correct = true;
                                                }
                                                if (is_secured_ == true)
                                                    std::cout << '*';
                                                else
                                                    std::cout << buffer_[i];
                                            }
                                            else {
                                                if (is_last_correct == true) {
                                                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), owner_ptr_->advanced_input_uncorrect_color_);
                                                    is_last_correct = false;
                                                }
                                                std::cout << buffer_[i];
                                            }
                                        }
                                        inn_pointer++;
                                        owner_ptr_->go_to_xy(owner_ptr_->x_pos_ + ((owner_ptr_->is_pointer_on_ == true) ? owner_ptr_->pointer_str_.length() : 0) + 6 + 1 + owner_ptr_->buttons_data_vector_[owner_index].name.length() + 1 + inn_pointer, owner_ptr_->y_pos_ + owner_index + owner_ptr_->is_info_full_);
                                    }
                                }
                                else if(is_ban_not_allowed_ == false && tmp_char != ' ') {  // если общий блок выключен и это не (попавший в неразрешенный space)
                                    if (is_last_correct == true) {
                                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), owner_ptr_->advanced_input_uncorrect_color_);
                                        is_last_correct = false;
                                    }   // меняем цвет дл вывода на будущее (если не был нужный)
                                    if (inn_pointer == buffer_.length()) { // вводим неразрешенный в конец
                                        buffer_.push_back(tmp_char);
                                        std::cout << tmp_char;
                                        inn_pointer++;
                                    }
                                    else {  // вводим разрешенный не в конец
                                        buffer_.insert(buffer_.begin() + inn_pointer, tmp_char);
                                        for (int i{ 0 }; i < buffer_.length() - inn_pointer; i++)
                                            std::cout << ' '; // очищаем для сдвига
                                        owner_ptr_->go_to_xy(owner_ptr_->x_pos_ + ((owner_ptr_->is_pointer_on_ == true) ? owner_ptr_->pointer_str_.length() : 0) + 6 + 1 + owner_ptr_->buttons_data_vector_[owner_index].name.length() + 1 + inn_pointer, owner_ptr_->y_pos_ + owner_index + owner_ptr_->is_info_full_);
                                        for (int i{ inn_pointer }; i < buffer_.length(); i++) { // печатаем на 1 символ больше
                                            if (std::binary_search(allowed_char_vector_.begin(), allowed_char_vector_.end(), buffer_[i]) == true) {
                                                if (is_last_correct == false) {
                                                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), owner_ptr_->advanced_input_correct_color_);
                                                    is_last_correct = true;
                                                }
                                                std::cout << '*';
                                            }
                                            else {
                                                if (is_last_correct == true) {
                                                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), owner_ptr_->advanced_input_uncorrect_color_);
                                                    is_last_correct = false;
                                                }
                                                std::cout << buffer_[i];
                                            }
                                        }
                                        inn_pointer++;
                                        owner_ptr_->go_to_xy(owner_ptr_->x_pos_ + ((owner_ptr_->is_pointer_on_ == true) ? owner_ptr_->pointer_str_.length() : 0) + 6 + 1 + owner_ptr_->buttons_data_vector_[owner_index].name.length() + 1 + inn_pointer, owner_ptr_->y_pos_ + owner_index + owner_ptr_->is_info_full_);
                                    }
                                    count_of_mistakes++;
                                }
                                std::cout.flush(); // моментальное изменение cout с освобождением буфера
                            }
                        }
                    }
                    break;
                }
            }
            else if (byte_system == BYTE_SYSTEM_IS_NOT_ONEBYTE) {   // стрелочки и т п
                switch (kb_numb)
                {
                case UP_POINTER_BUT:
                    owner_ptr_->pointer_logic(&(owner_ptr_->pointer_), &(owner_ptr_->last_pointer_), owner_ptr_->count_of_buttons_, UP_POINTER_BUT);
                    return;
                    break;
                case DOWN_POINTER_BUT:
                    owner_ptr_->pointer_logic(&(owner_ptr_->pointer_), &(owner_ptr_->last_pointer_), owner_ptr_->count_of_buttons_, DOWN_POINTER_BUT);
                    return;
                    break;
                case LEFT_POINTER_BUT:
                    if (inn_pointer > 0) {
                        inn_pointer--;
                        owner_ptr_->go_to_xy(owner_ptr_->x_pos_ + ((owner_ptr_->is_pointer_on_ == true) ? owner_ptr_->pointer_str_.length() : 0) + 6 + 1 + owner_ptr_->buttons_data_vector_[owner_index].name.length() + 1 + inn_pointer, owner_ptr_->y_pos_ + owner_index + owner_ptr_->is_info_full_);
                    }
                    break;
                case RIGHT_POINTER_BUT:
                    if (inn_pointer < buffer_.length()) {
                        inn_pointer++;
                        owner_ptr_->go_to_xy(owner_ptr_->x_pos_ + ((owner_ptr_->is_pointer_on_ == true) ? owner_ptr_->pointer_str_.length() : 0) + 6 + 1 + owner_ptr_->buttons_data_vector_[owner_index].name.length() + 1 + inn_pointer, owner_ptr_->y_pos_ + owner_index + owner_ptr_->is_info_full_);
                    }
                    break;
                }
            }
        }
        else
            Sleep(5); // для оптимизации
    }
}

char EasyMenu::ButtData::AdvancedCIN::GetCharKey(int byte_system, int kb_numb) {								// передаем знач полученого значения системы байт и полученое знач номера клавиши
    if (byte_system == BYTE_SYSTEM_IS_ONEBYTE) 							// значит данный символ однобайтовый
        if (isprint(kb_numb)) 												// если символ печатаемый, то продолжаем
            return static_cast<char>(kb_numb);								// переводим символ в char
    return '\0';    // значит нельзя получить char (или не та система или в такой сиситеме нет)
}



