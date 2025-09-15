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
    checkbox_color_ = WHITE_COLOR;
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
                        go_to_xy(x_pos_ + (is_pointer_on_ == true) ? 3 : 0, y_pos_ + get_pointer_index(pointer_));
                        if (buttons_data_vector_[get_pointer_index(pointer_)].is_activated == true) {
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN_COLOR);
                            std::cout << "[#] ";
                        }
                        else {
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_GRAY_COLOR);
                            std::cout << "[ ] ";
                        }
                        go_to_xy(x_pos_ + (is_pointer_on_ == true) ? 3 : 0, y_pos_ + get_pointer_index(pointer_));
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE_COLOR);
                        std::cout.flush();
                        go_to_xy(x_pos_ + (is_pointer_on_ == true) ? 3 : 0, y_pos_ + get_pointer_index(pointer_));
                    }
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
                std::cout << "   ";
            std::cout << '[' << buttons_data_vector_[i].name << ']';
            break;
            /*
        case ADVANCED_INPUT:

            break;
            */
        case CHECKBOX:
            if (is_pointer_on_)
                std::cout << "   ";
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
        std::cout << "-->";
        if (mark_choose_) {
            switch (buttons_data_vector_[get_pointer_index(pointer_)].type)
            {
                /*
            case ADVANCED_INPUT:

                break;
                */
            case CHECKBOX:
                go_to_xy(x_pos_ + 3 + 4, y_pos_ + get_pointer_index(pointer_) + is_info_full_);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN_COLOR);
                std::cout << buttons_data_vector_[get_pointer_index(pointer_)].name;
                go_to_xy(x_pos_ + 3, y_pos_ + get_pointer_index(pointer_) + is_info_full_);
                break;
            default:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), butt_color_);
                std::cout << '[';
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), mark_choose_color_);
                std::cout << buttons_data_vector_[get_pointer_index(pointer_)].name;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), butt_color_);
                std::cout << ']';
                go_to_xy(x_pos_ + 3, y_pos_ + get_pointer_index(pointer_) + is_info_full_);
                break;
            }
        }
    }
    else {
        switch (buttons_data_vector_[get_pointer_index(pointer_)].type)
        {
            /*
        case ADVANCED_INPUT:

            break;
            */
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
        std::cout << "   ";
        if (mark_choose_) {
            switch (buttons_data_vector_[get_pointer_index(last_pointer_)].type)
            {
                /*
            case ADVANCED_INPUT:

                break;
                */
            case CHECKBOX:
                go_to_xy(x_pos_ + 3 + 4, y_pos_ + get_pointer_index(last_pointer_) + is_info_full_);
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
            /*
        case ADVANCED_INPUT:

            break;
            */
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

void EasyMenu::insert_butt(int32_t prev_index, string butt_name) {
    if (prev_index < -1)
        prev_index = -1;
    count_of_buttons_++;
    count_of_lines_++;
    buttons_data_vector_.insert(buttons_data_vector_.begin() + prev_index + 1, ButtData(butt_name, BUTTON, butt_color_));
    is_need_screen_update_ = true;
}

void EasyMenu::insert_text(int32_t prev_index, string text) {
    if (prev_index < -1)
        prev_index = -1;
    count_of_lines_++;
    buttons_data_vector_.insert(buttons_data_vector_.begin() + prev_index + 1, ButtData(text, TEXT, text_color_));
    is_need_screen_update_ = true;
}

void EasyMenu::insert_checkbox(int32_t prev_index, string text) {
    if (prev_index < -1)
        prev_index = -1;
    count_of_buttons_++;
    count_of_lines_++;
    buttons_data_vector_.insert(buttons_data_vector_.begin() + prev_index + 1, ButtData(text, CHECKBOX, checkbox_color_));
    is_need_screen_update_ = true;
}

void EasyMenu::insert_checkbox(int32_t prev_index, string text, bool is_activated) {
    if (prev_index < -1)
        prev_index = -1;
    count_of_buttons_++;
    count_of_lines_++;
    buttons_data_vector_.insert(buttons_data_vector_.begin() + prev_index + 1, ButtData(text, CHECKBOX, checkbox_color_, is_activated));
    is_need_screen_update_ = true;
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
        /*
        case ADVANCED_INPUT:
            color_id = 
            break;
        */
        default:
            color_id = WHITE_COLOR;
            break;
        }
    buttons_data_vector_[index].color_id = color_id;
    return;
}

void EasyMenu::set_buttons_main_color(int32_t color_id) {
    if (color_id > 15 || color_id < 0)
        return;
    butt_color_ = color_id;
    is_need_screen_update_ = true;
}

void EasyMenu::set_pointer_main_color(int32_t color_id) {
    if (color_id > 15 || color_id < 0)
        return;
    pointer_color_ = color_id;
    is_need_screen_update_ = true;
}

void EasyMenu::set_checkbox_main_color(int32_t color_id) {
    if (color_id > 15 || color_id < 0)
        return;
    checkbox_color_ = color_id;
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

void EasyMenu::edit(int index, string new_text) {
    if (index >= 0 && index < count_of_lines_) {
        buttons_data_vector_[index].name = new_text;
        is_need_screen_update_ = true;
        return;
    }
    return;
}

void EasyMenu::delete_butt(int index) {
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
        if (buttons_data_vector_[i].type != TEXT)
            tmp++;
        if (tmp == pointer_)
            return i;   // возвращаем нужный индекс 
    }
    return NULL;
}