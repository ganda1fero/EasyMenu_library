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

EasyMenu::EasyMenu() : add(*this), edit(*this), clear(*this), notification(*this), style(*this), get(*this) {
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

EasyMenu::EasyMenu(string button) : EasyMenu() {
    count_of_buttons_++;
    count_of_lines_++;
    buttons_data_vector_.push_back(ButtData(button, BUTTON, butt_color_));
}
EasyMenu::EasyMenu(string first_button, string second_button) : EasyMenu(first_button) {
    count_of_buttons_++;
    count_of_lines_++;
    buttons_data_vector_.push_back(ButtData(second_button, BUTTON, butt_color_));
}
EasyMenu::EasyMenu(vector<string> buttons) : EasyMenu() {
    for (const string& button : buttons) {
        buttons_data_vector_.push_back(ButtData(button, BUTTON, butt_color_));
    }
    count_of_buttons_ = buttons.size();
    count_of_lines_ = buttons.size();
}

// ----------- Хэндлеры
EasyMenu::NotificationHandler::NotificationHandler(EasyMenu& m, int index) : m(m), index(index) {}
EasyMenu::NotificationHandler& EasyMenu::NotificationHandler::notification(string new_notification) {
    m.set_notification(index, new_notification);
    return *this;
}
EasyMenu::NotificationHandler& EasyMenu::NotificationHandler::color(int color_id) {
    m.set_notification_color(index, color_id);
    return *this;
}

EasyMenu::ButtonHandle::ButtonHandle(EasyMenu& m, int index) : m(m), index(index) {}
EasyMenu::ButtonHandle& EasyMenu::ButtonHandle::name(string new_name) {
    m.edit_something(index, new_name);
    return *this;
}
EasyMenu::ButtonHandle& EasyMenu::ButtonHandle::color(int color_id) {
    m.set_color(index, color_id);
    return *this;
}
EasyMenu::NotificationHandler EasyMenu::ButtonHandle::notification(string new_notification) {
    m.set_notification(index, new_notification);
    return NotificationHandler(m, index);
}

EasyMenu::TextHandle::TextHandle(EasyMenu& m, int index) : m(m), index(index) {}
EasyMenu::TextHandle& EasyMenu::TextHandle::text(string new_text) {
    m.edit_something(index, new_text);
    return *this;
}
EasyMenu::TextHandle& EasyMenu::TextHandle::color(int color_id) {
    m.set_color(index, color_id);
    return *this;
}

EasyMenu::CheckboxHandle::CheckboxHandle(EasyMenu& m, int index) : m(m), index(index) {}
EasyMenu::CheckboxHandle& EasyMenu::CheckboxHandle::text(string new_text) {
    m.edit_something(index, new_text);
    return *this;
}
EasyMenu::CheckboxHandle& EasyMenu::CheckboxHandle::color(int color_id) {
    m.set_color(index, color_id);
    return *this;
}
EasyMenu::CheckboxHandle& EasyMenu::CheckboxHandle::state(bool new_state) {
    m.set_checkbox_state(index, new_state);
    return *this;
}
EasyMenu::NotificationHandler EasyMenu::CheckboxHandle::notification(string new_notification) {
    m.set_notification(index, new_notification);
    return NotificationHandler(m, index);
}

EasyMenu::InputHandle::InputHandle(EasyMenu& m, int index) : m(m), index(index) {}
EasyMenu::InputHandle& EasyMenu::InputHandle::name(string new_name) {
    m.edit_something(index, new_name);
    return *this;
}
EasyMenu::InputHandle& EasyMenu::InputHandle::name_color(int color_id) {
    m.set_color(index, color_id);
    return *this;
}
EasyMenu::InputHandle& EasyMenu::InputHandle::length(int new_length) {
    m.set_advanced_cin_max_input_length(index, new_length);
    return *this;
}
EasyMenu::InputHandle& EasyMenu::InputHandle::origional_text(string new_text) {
    m.set_advanced_cin_original_text(index, new_text);
    return *this;
}
EasyMenu::InputHandle& EasyMenu::InputHandle::allowed(string new_allowed) {
    m.set_advanced_cin_new_allowed_chars(index, new_allowed);
    return *this;
}
EasyMenu::InputHandle& EasyMenu::InputHandle::allowed(vector<char> new_allowed) {
    m.set_advanced_cin_new_allowed_chars(index, new_allowed);
    return *this;
}
EasyMenu::InputHandle& EasyMenu::InputHandle::filter(bool new_state) {
    m.set_advanced_cin_ban_not_allowed(index, new_state);
    return *this;
}
EasyMenu::InputHandle& EasyMenu::InputHandle::secure(bool new_state) {
    m.set_advanced_cin_secure_input(index, new_state);
    return *this;
}
EasyMenu::InputHandle& EasyMenu::InputHandle::dictionary(EasyDict* dictionary_ptr) {
    m.set_advanced_cin_new_dictionary_ptr(index, dictionary_ptr);
    return *this;
}
EasyMenu::NotificationHandler EasyMenu::InputHandle::notification(string new_notification) {
    m.set_notification(index, new_notification);
    return NotificationHandler(m, index);
}

EasyMenu::ClearHandle::ClearHandle(EasyMenu& m) : m(m) {}
EasyMenu::ClearHandle& EasyMenu::ClearHandle::text() {
    m.delete_all_text();
    return *this;
}
EasyMenu::ClearHandle& EasyMenu::ClearHandle::notifications() {
    m.delete_all_notifications();
    return *this;
}
EasyMenu::ClearHandle& EasyMenu::ClearHandle::info() {
    m.delete_info();
    return *this;
}

EasyMenu::Info_StyleHandle::Info_StyleHandle(EasyMenu& m) : m(m) {}
EasyMenu::Info_StyleHandle& EasyMenu::Info_StyleHandle::add(string new_info) {
    m.set_info(new_info);
    return *this;
}
EasyMenu::Info_StyleHandle& EasyMenu::Info_StyleHandle::color(int color_id) {
    m.set_info_main_color(color_id);
    return *this;
}
EasyMenu::Info_StyleHandle& EasyMenu::Info_StyleHandle::remove() {
    m.delete_info();
    return *this;
}

EasyMenu::BasicColor_StyleHandle::BasicColor_StyleHandle(EasyMenu& m) : m(m) {}
EasyMenu::BasicColor_StyleHandle& EasyMenu::BasicColor_StyleHandle::button(int color_id) {
    m.set_buttons_main_color(color_id);
    return *this;
}
EasyMenu::BasicColor_StyleHandle& EasyMenu::BasicColor_StyleHandle::text(int color_id) {
    m.set_text_main_color(color_id);
    return *this;
}
EasyMenu::BasicColor_StyleHandle& EasyMenu::BasicColor_StyleHandle::checkbox(int color_id) {
    m.set_checkbox_main_color(color_id);
    return *this;
}
EasyMenu::BasicColor_StyleHandle& EasyMenu::BasicColor_StyleHandle::choise(int color_id) {
    m.set_mark_choose_main_color(color_id);
    return *this;
}
EasyMenu::BasicColor_StyleHandle& EasyMenu::BasicColor_StyleHandle::pointer(int color_id) {
    m.set_pointer_main_color(color_id);
    return *this;
}
EasyMenu::BasicColor_StyleHandle& EasyMenu::BasicColor_StyleHandle::correct_input(int color_id) {
    m.set_advanced_cin_correct_color(color_id);
    return *this;
}
EasyMenu::BasicColor_StyleHandle& EasyMenu::BasicColor_StyleHandle::uncorrect_input(int color_id) {
    m.set_advanced_cin_uncorrect_color(color_id);
    return *this;
}

EasyMenu::Settings_StyleHandle::Settings_StyleHandle(EasyMenu& m) : m(m) {}
EasyMenu::Settings_StyleHandle& EasyMenu::Settings_StyleHandle::x_y_pos(int x, int y) {
    m.set_x_y_position(x, y);
    return *this;
}
EasyMenu::Settings_StyleHandle& EasyMenu::Settings_StyleHandle::choise(bool state) {
    m.set_mark_choose(state);
    return *this;
}
EasyMenu::Settings_StyleHandle& EasyMenu::Settings_StyleHandle::pointer(bool state) {
    m.set_pointer(state);
    return *this;
}
EasyMenu::Settings_StyleHandle& EasyMenu::Settings_StyleHandle::pointer_symbols(string new_pointer) {
    m.set_new_pointer(new_pointer);
    return *this;
}

// ----------- Под-объекты
EasyMenu::AddAPI::AddAPI(EasyMenu& m) : m(m) {}
EasyMenu::ButtonHandle EasyMenu::AddAPI::button(string name) {
    m.push_back_butt(name);
    return ButtonHandle(m, m.count_of_lines_ - 1);
}
EasyMenu::ButtonHandle EasyMenu::AddAPI::button(string name, int index) {
    if (index < 0) {
        index = 0;
    }
    else if (index > m.count_of_lines_ - 1) {
        index = m.count_of_lines_ - 1;
    }
    m.insert_butt(index, name);
    return ButtonHandle(m, index);
}
EasyMenu::TextHandle EasyMenu::AddAPI::text(string text) {
    m.push_back_text(text);
    return TextHandle(m, m.count_of_lines_ - 1);
}
EasyMenu::TextHandle EasyMenu::AddAPI::text(string text, int index) {
    if (index < 0) {
        index = 0;
    }
    else if (index > m.count_of_lines_ - 1) {
        index = m.count_of_lines_ - 1;
    }
    m.insert_text(index, text);
    return TextHandle(m, index);
}
EasyMenu::CheckboxHandle EasyMenu::AddAPI::checkbox(string text, bool state) {
    m.push_back_checkbox(text, state);
    return CheckboxHandle(m, m.count_of_lines_ - 1);
}
EasyMenu::CheckboxHandle EasyMenu::AddAPI::checkbox(string text, int index, bool state) {
    if (index < 0) {
        index = 0;
    }
    else if (index > m.count_of_lines_ - 1) {
        index = m.count_of_lines_ - 1;
    }
    m.insert_checkbox(index, text, state);
    return CheckboxHandle(m, index);
}
EasyMenu::InputHandle EasyMenu::AddAPI::input(string name, string original_text) {
    m.push_back_advanced_cin(name, original_text);
    return InputHandle(m, m.count_of_lines_ - 1);
}
EasyMenu::InputHandle EasyMenu::AddAPI::input(string name, int index, string original_text) {
    if (index < 0) {
        index = 0;
    }
    else if (index > m.count_of_lines_ - 1) {
        index = m.count_of_lines_ - 1;
    }
    m.insert_advanced_cin(index, name, original_text);
    return InputHandle(m, index);
}

EasyMenu::EditAPI::EditAPI(EasyMenu& m) : m(m) {}
EasyMenu::ButtonHandle EasyMenu::EditAPI::button(int index) {
    if (index < 0) {
        index = 0;
    }
    else if (index > m.count_of_lines_ - 1) {
        index = m.count_of_lines_ - 1;
    }
    return ButtonHandle(m, index);
}
EasyMenu::TextHandle EasyMenu::EditAPI::text(int index) {
    if (index < 0) {
        index = 0;
    }
    else if (index > m.count_of_lines_ - 1) {
        index = m.count_of_lines_ - 1;
    }
    return TextHandle(m, index);
}
EasyMenu::CheckboxHandle EasyMenu::EditAPI::checkbox(int index) {
    if (index < 0) {
        index = 0;
    }
    else if (index > m.count_of_lines_ - 1) {
        index = m.count_of_lines_ - 1;
    }
    return CheckboxHandle(m, index);
}
EasyMenu::InputHandle EasyMenu::EditAPI::input(int index) {
    if (index < 0) {
        index = 0;
    }
    else if (index > m.count_of_lines_ - 1) {
        index = m.count_of_lines_ - 1;
    }
    return InputHandle(m, index);
}

EasyMenu::ClearAPI::ClearAPI(EasyMenu& m) : m(m) {}
EasyMenu::ClearHandle EasyMenu::ClearAPI::text() {
    m.delete_all_text();
    return ClearHandle(m);
}
EasyMenu::ClearHandle EasyMenu::ClearAPI::notifications() {
    m.delete_all_notifications();
    return ClearHandle(m);
}
EasyMenu::ClearHandle EasyMenu::ClearAPI::info() {
    m.delete_info();
    return ClearHandle(m);
}
void EasyMenu::ClearAPI::all() {
    m.clear_everything();
}

EasyMenu::NotificationAPI::NotificationAPI(EasyMenu& m) : m(m) {}
EasyMenu::NotificationHandler EasyMenu::NotificationAPI::add(string new_notification, int index) {
    if (index < 0) {
        index = 0;
    }
    else if (index > m.count_of_lines_ - 1) {
        index = m.count_of_lines_ - 1;
    }
    m.set_notification(index, new_notification);
    return NotificationHandler(m, index);
}
EasyMenu::NotificationHandler EasyMenu::NotificationAPI::color(int index, int color_id) {
    if (index < 0) {
        index = 0;
    }
    else if (index > m.count_of_lines_ - 1) {
        index = m.count_of_lines_ - 1;
    }
    m.set_notification_color(index, color_id);
    return NotificationHandler(m, index);
}
EasyMenu::NotificationHandler EasyMenu::NotificationAPI::remove(int index) {
    if (index < 0) {
        index = 0;
    }
    else if (index > m.count_of_lines_ - 1) {
        index = m.count_of_lines_ - 1;
    }
    m.delete_notification(index);
    return NotificationHandler(m, index);
}
void EasyMenu::NotificationAPI::clear() {
    m.delete_all_notifications();
}

EasyMenu::StyleAPI::StyleAPI(EasyMenu& m) : m(m), info(*this), basic_color(*this), settings(*this) {}

EasyMenu::StyleAPI::Info_StyleAPI::Info_StyleAPI(StyleAPI& parent) : parent(parent) {}
EasyMenu::Info_StyleHandle EasyMenu::StyleAPI::Info_StyleAPI::add(string new_info){
    parent.m.set_info(new_info);
    return Info_StyleHandle(parent.m);
}
EasyMenu::Info_StyleHandle EasyMenu::StyleAPI::Info_StyleAPI::color(int color_id) {
    parent.m.set_info_main_color(color_id);
    return Info_StyleHandle(parent.m);
}
EasyMenu::Info_StyleHandle EasyMenu::StyleAPI::Info_StyleAPI::remove() {
    parent.m.delete_info();
    return Info_StyleHandle(parent.m);
}

EasyMenu::StyleAPI::BasicColor_StyleAPI::BasicColor_StyleAPI(StyleAPI& parent) : parent(parent) {}
EasyMenu::BasicColor_StyleHandle EasyMenu::StyleAPI::BasicColor_StyleAPI::button(int color_id) {
    parent.m.set_buttons_main_color(color_id);
    return BasicColor_StyleHandle(parent.m);
}
EasyMenu::BasicColor_StyleHandle EasyMenu::StyleAPI::BasicColor_StyleAPI::text(int color_id) {
    parent.m.set_text_main_color(color_id);
    return BasicColor_StyleHandle(parent.m);
}
EasyMenu::BasicColor_StyleHandle EasyMenu::StyleAPI::BasicColor_StyleAPI::checkbox(int color_id) {
    parent.m.set_checkbox_main_color(color_id);
    return BasicColor_StyleHandle(parent.m);
}
EasyMenu::BasicColor_StyleHandle EasyMenu::StyleAPI::BasicColor_StyleAPI::choise(int color_id) {
    parent.m.set_mark_choose_main_color(color_id);
    return BasicColor_StyleHandle(parent.m);
}
EasyMenu::BasicColor_StyleHandle EasyMenu::StyleAPI::BasicColor_StyleAPI::pointer(int color_id) {
    parent.m.set_pointer_main_color(color_id);
    return BasicColor_StyleHandle(parent.m);
}
EasyMenu::BasicColor_StyleHandle EasyMenu::StyleAPI::BasicColor_StyleAPI::correct_input(int color_id) {
    parent.m.set_advanced_cin_correct_color(color_id);
    return BasicColor_StyleHandle(parent.m);
}
EasyMenu::BasicColor_StyleHandle EasyMenu::StyleAPI::BasicColor_StyleAPI::uncorrect_input(int color_id) {
    parent.m.set_advanced_cin_uncorrect_color(color_id);
    return BasicColor_StyleHandle(parent.m);
}

EasyMenu::StyleAPI::Settings_StyleAPI::Settings_StyleAPI(StyleAPI& parent) : parent(parent) {}
EasyMenu::Settings_StyleHandle EasyMenu::StyleAPI::Settings_StyleAPI::x_y_pos(int x, int y) {
    parent.m.set_x_y_position(x, y);
    return Settings_StyleHandle(parent.m);
}
EasyMenu::Settings_StyleHandle EasyMenu::StyleAPI::Settings_StyleAPI::choise(bool state) {
    parent.m.set_mark_choose(state);
    return Settings_StyleHandle(parent.m);
}
EasyMenu::Settings_StyleHandle EasyMenu::StyleAPI::Settings_StyleAPI::pointer(bool state) {
    parent.m.set_pointer(state);
    return Settings_StyleHandle(parent.m);
}
EasyMenu::Settings_StyleHandle EasyMenu::StyleAPI::Settings_StyleAPI::pointer_symbols(string new_pointer) {
    parent.m.set_new_pointer(new_pointer);
    return Settings_StyleHandle(parent.m);
}

EasyMenu::GetAPI::GetAPI(EasyMenu& m) : m(m) {}
bool EasyMenu::GetAPI::checkbox(int index) {
    return m.get_checkbox_status(index);
}
vector<bool> EasyMenu::GetAPI::checkbox() {
    return m.get_all_checkbox_status();
}
string EasyMenu::GetAPI::input(int index) {
    return m.get_advanced_cin_input(index);
}
vector<string> EasyMenu::GetAPI::input() {
    return m.get_all_advacned_cin_input();
}
bool EasyMenu::GetAPI::input_error(int index) {
    return m.is_advanced_cin_correct(index);
}
bool EasyMenu::GetAPI::input_error() {
    return m.is_all_advanced_cin_correct();
}

// логика
int EasyMenu::run() {
    return easy_run_background();
}

void EasyMenu::remove() {
    pop_back();
}
void EasyMenu::remove(int index) {
    delete_butt(index);
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
                        go_to_xy(x_pos_ + ((is_pointer_on_ == true) ? pointer_str_.length() : 0), y_pos_ + get_pointer_index(pointer_) + is_info_full_);
                        if (buttons_data_vector_[get_pointer_index(pointer_)].is_activated == true) {
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN_COLOR);
                            std::cout << "[#] ";
                        }
                        else {
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_GRAY_COLOR);
                            std::cout << "[ ] ";
                        }
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE_COLOR);
                        std::cout.flush();
                        go_to_xy(x_pos_ + ((is_pointer_on_ == true) ? pointer_str_.length() : 0), y_pos_ + get_pointer_index(pointer_) + is_info_full_);
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

void EasyMenu::push_back_checkbox(string text, bool is_activated) {
    count_of_buttons_++;
    count_of_lines_++;
    buttons_data_vector_.push_back(ButtData(text, CHECKBOX, checkbox_color_, is_activated));
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

void EasyMenu::set_advanced_cin_new_dictionary_ptr(int32_t index, EasyDict* dictionary_ptr) {
    if (index < 0 || index > count_of_lines_ - 1)
        return;
    if (buttons_data_vector_[index].type == ADVANCED_INPUT)
        buttons_data_vector_[index].advanced_cin.set_new_dictionary_ptr(dictionary_ptr);
    return;
}

void EasyMenu::set_advanced_cin_original_text(int index, string new_text) {
    if (index < 0 || index > count_of_lines_ - 1)
        return;
    if (buttons_data_vector_[index].type == ADVANCED_INPUT) {
        buttons_data_vector_[index].advanced_cin.set_text(new_text);
    }
}

void EasyMenu::set_checkbox_state(int index, bool new_state) {
    if (index < 0 || index > count_of_lines_ - 1)
        return;
    if (buttons_data_vector_[index].type == CHECKBOX) {
        if (buttons_data_vector_[index].is_activated != new_state) {
            is_need_screen_update_ = true;
        }
        buttons_data_vector_[index].is_activated = new_state;
    }
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
    if (new_info.length() > 0) {
        is_info_full_ = true;
    }
    else {
        is_info_full_ = false;
    }
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

void EasyMenu::set_mark_choose(bool state) {
    if (mark_choose_ != state) {
        is_need_screen_update_ = true;
        mark_choose_ = state;
    }
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

void EasyMenu::edit_something(int32_t index, string new_text) {
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

void EasyMenu::set_pointer(bool state) {
    if (is_pointer_on_ != state) {
        is_need_screen_update_ = true;
        is_pointer_on_ = state;
    }
}

void EasyMenu::set_advanced_cin_ban_not_allowed(int32_t index, bool state) {
    if (index < 0 || index > count_of_lines_)
        return;
    if (buttons_data_vector_[index].type != ADVANCED_INPUT)
        return;
    if (state) {
        buttons_data_vector_[index].advanced_cin.ban_not_allowed_on();
    }
    else {
        buttons_data_vector_[index].advanced_cin.ban_not_allowed_off();
    }
    
}

void EasyMenu::set_advanced_cin_secure_input(int32_t index, bool state) {
    if (index < 0 || index > count_of_lines_)
        return;
    if (buttons_data_vector_[index].type != ADVANCED_INPUT)
        return;
    if (state) {
        buttons_data_vector_[index].advanced_cin.secure_input_on();
    }
    else {
        buttons_data_vector_[index].advanced_cin.secure_input_off();
    }
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

void EasyMenu::clear_everything() {
    pointer_ = 0;
    last_pointer_ = -1;
    count_of_buttons_ = 0;
    count_of_lines_ = 0;
    byte_system_ = -1;
    kb_numb_ = -1;
    info_ = "";
    is_info_full_ = false;
    is_need_screen_update_ = false;
    is_butt_pressed_ = false;
    is_need_pointer_update_ = false;
    pressed_but_ = -1;

    buttons_data_vector_.clear();
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
    dictionary_ptr_ = nullptr;
    last_predicted_path_ = "";
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

void EasyMenu::ButtData::AdvancedCIN::set_new_dictionary_ptr(EasyDict* dictionary_ptr) {
    last_predicted_path_ = "";
    dictionary_ptr_ = dictionary_ptr;
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

            if (dictionary_ptr_ != nullptr && is_secured_ == false && dictionary_ptr_->is_open() && count_of_mistakes == 0 && (last_predicted_path_ = dictionary_ptr_->predict_last_path(buffer_)).empty() == false) {
                // нашли подсказку, выводим
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_GRAY_COLOR);
                std::cout << last_predicted_path_;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), owner_ptr_->advanced_input_correct_color_);
                owner_ptr_->go_to_xy(owner_ptr_->x_pos_ + ((owner_ptr_->is_pointer_on_ == true) ? owner_ptr_->pointer_str_.length() : 0) + 6 + 1 + owner_ptr_->buttons_data_vector_[owner_index].name.length() + 1 + inn_pointer, owner_ptr_->y_pos_ + owner_index + owner_ptr_->is_info_full_);
            }
        }
        else if (is_ban_not_allowed_ == false && symbol != ' ') {  // если общий блок выключен и это не (попавший в неразрешенный space)
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), owner_ptr_->advanced_input_uncorrect_color_);
            is_last_correct = false;            
            buffer_.push_back(symbol);
            std::cout << symbol;
            inn_pointer++;
            count_of_mistakes++;
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

                    if (last_predicted_path_.empty() == false) {
                        // очищаем старую подсказку (не в конце)
                        owner_ptr_->go_to_xy(owner_ptr_->x_pos_ + ((owner_ptr_->is_pointer_on_ == true) ? owner_ptr_->pointer_str_.length() : 0) + 6 + 1 + owner_ptr_->buttons_data_vector_[owner_index].name.length() + 1 + buffer_.length(), owner_ptr_->y_pos_ + owner_index + owner_ptr_->is_info_full_);
                        for (int i{ 0 }; i < last_predicted_path_.length(); i++)
                            std::cout << ' ';
                        last_predicted_path_.clear();
                    }

                    return;
                    break;
                case ESC_BUT:   // выход 

                    if (last_predicted_path_.empty() == false) {
                        // очищаем старую подсказку (не в конце)
                        owner_ptr_->go_to_xy(owner_ptr_->x_pos_ + ((owner_ptr_->is_pointer_on_ == true) ? owner_ptr_->pointer_str_.length() : 0) + 6 + 1 + owner_ptr_->buttons_data_vector_[owner_index].name.length() + 1 + buffer_.length(), owner_ptr_->y_pos_ + owner_index + owner_ptr_->is_info_full_);
                        for (int i{ 0 }; i < last_predicted_path_.length(); i++)
                            std::cout << ' ';
                        last_predicted_path_.clear();
                    }

                    return;
                    break;
                case BACKSPACE_BUT: // удаляем 
                    if (buffer_.length() > 0) { // => есть что удалять
                        if (inn_pointer == buffer_.length()) {  // удаляем с конца
                            if (last_predicted_path_.empty() == false) {
                                // очищаем старую подсказку
                                for (int i{ 0 }; i < last_predicted_path_.length(); i++)
                                    std::cout << ' ';
                                owner_ptr_->go_to_xy(owner_ptr_->x_pos_ + ((owner_ptr_->is_pointer_on_ == true) ? owner_ptr_->pointer_str_.length() : 0) + 6 + 1 + owner_ptr_->buttons_data_vector_[owner_index].name.length() + 1 + inn_pointer, owner_ptr_->y_pos_ + owner_index + owner_ptr_->is_info_full_);
                                last_predicted_path_.clear();
                            }

                            if (std::binary_search(allowed_char_vector_.begin(), allowed_char_vector_.end(), buffer_[inn_pointer - 1]) == false)
                                count_of_mistakes--; // значит удалили ошибочный ввод
                            buffer_.pop_back();
                            // внешняя часть
                            std::cout << '\b' << ' ' << '\b';
                            inn_pointer--;

                            if (dictionary_ptr_ != nullptr && is_secured_ == false && dictionary_ptr_->is_open() && count_of_mistakes == 0 && (last_predicted_path_ = dictionary_ptr_->predict_last_path(buffer_)).empty() == false) {
                                // нашли подсказку, выводим
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_GRAY_COLOR);
                                std::cout << last_predicted_path_;
                                if (is_last_correct)
                                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), owner_ptr_->advanced_input_correct_color_);
                                else
                                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), owner_ptr_->advanced_input_uncorrect_color_);
                                owner_ptr_->go_to_xy(owner_ptr_->x_pos_ + ((owner_ptr_->is_pointer_on_ == true) ? owner_ptr_->pointer_str_.length() : 0) + 6 + 1 + owner_ptr_->buttons_data_vector_[owner_index].name.length() + 1 + inn_pointer, owner_ptr_->y_pos_ + owner_index + owner_ptr_->is_info_full_);
                            }

                            std::cout.flush();
                        }
                        else if(inn_pointer > 0) { // удаляем не с конца и не в начале
                            if (last_predicted_path_.empty() == false) {
                                // очищаем старую подсказку (не в конце)
                                owner_ptr_->go_to_xy(owner_ptr_->x_pos_ + ((owner_ptr_->is_pointer_on_ == true) ? owner_ptr_->pointer_str_.length() : 0) + 6 + 1 + owner_ptr_->buttons_data_vector_[owner_index].name.length() + 1 + buffer_.length(), owner_ptr_->y_pos_ + owner_index + owner_ptr_->is_info_full_);
                                for (int i{ 0 }; i < last_predicted_path_.length(); i++)
                                    std::cout << ' ';
                                owner_ptr_->go_to_xy(owner_ptr_->x_pos_ + ((owner_ptr_->is_pointer_on_ == true) ? owner_ptr_->pointer_str_.length() : 0) + 6 + 1 + owner_ptr_->buttons_data_vector_[owner_index].name.length() + 1 + inn_pointer, owner_ptr_->y_pos_ + owner_index + owner_ptr_->is_info_full_);
                                last_predicted_path_.clear();
                            }

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

                            if (dictionary_ptr_ != nullptr && is_secured_ == false && dictionary_ptr_->is_open() && count_of_mistakes == 0 && (last_predicted_path_ = dictionary_ptr_->predict_last_path(buffer_)).empty() == false) {
                                // нашли подсказку, выводим (не в конце)
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_GRAY_COLOR);
                                std::cout << last_predicted_path_;
                                if (is_last_correct)
                                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), owner_ptr_->advanced_input_correct_color_);
                                else
                                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), owner_ptr_->advanced_input_uncorrect_color_);
                            }

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
                                        if (last_predicted_path_.empty() == false) {
                                            // очищаем старую подсказку
                                            for (int i{ 0 }; i < last_predicted_path_.length(); i++)
                                                std::cout << ' ';
                                            owner_ptr_->go_to_xy(owner_ptr_->x_pos_ + ((owner_ptr_->is_pointer_on_ == true) ? owner_ptr_->pointer_str_.length() : 0) + 6 + 1 + owner_ptr_->buttons_data_vector_[owner_index].name.length() + 1 + inn_pointer, owner_ptr_->y_pos_ + owner_index + owner_ptr_->is_info_full_);
                                            last_predicted_path_.clear();
                                        }

                                        buffer_.push_back(tmp_char);
                                        if (is_secured_ == true)
                                            std::cout << '*';
                                        else
                                            std::cout << tmp_char;
                                        inn_pointer++;

                                        if (dictionary_ptr_ != nullptr && is_secured_ == false && dictionary_ptr_->is_open() && count_of_mistakes == 0 && (last_predicted_path_ = dictionary_ptr_->predict_last_path(buffer_)).empty() == false) {
                                            // нашли подсказку, выводим
                                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_GRAY_COLOR);
                                            std::cout << last_predicted_path_;
                                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), owner_ptr_->advanced_input_correct_color_);
                                            owner_ptr_->go_to_xy(owner_ptr_->x_pos_ + ((owner_ptr_->is_pointer_on_ == true) ? owner_ptr_->pointer_str_.length() : 0) + 6 + 1 + owner_ptr_->buttons_data_vector_[owner_index].name.length() + 1 + inn_pointer, owner_ptr_->y_pos_ + owner_index + owner_ptr_->is_info_full_);
                                        }
                                    }
                                    else {  // вводим разрешенный не в конец
                                        if (last_predicted_path_.empty() == false) {
                                            // очищаем старую подсказку (не в конце)
                                            owner_ptr_->go_to_xy(owner_ptr_->x_pos_ + ((owner_ptr_->is_pointer_on_ == true) ? owner_ptr_->pointer_str_.length() : 0) + 6 + 1 + owner_ptr_->buttons_data_vector_[owner_index].name.length() + 1 + buffer_.length(), owner_ptr_->y_pos_ + owner_index + owner_ptr_->is_info_full_);
                                            for (int i{ 0 }; i < last_predicted_path_.length(); i++)
                                                std::cout << ' ';
                                            owner_ptr_->go_to_xy(owner_ptr_->x_pos_ + ((owner_ptr_->is_pointer_on_ == true) ? owner_ptr_->pointer_str_.length() : 0) + 6 + 1 + owner_ptr_->buttons_data_vector_[owner_index].name.length() + 1 + inn_pointer, owner_ptr_->y_pos_ + owner_index + owner_ptr_->is_info_full_);
                                            last_predicted_path_.clear();
                                        }

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

                                        if (dictionary_ptr_ != nullptr && is_secured_ == false && dictionary_ptr_->is_open() && count_of_mistakes == 0 && (last_predicted_path_ = dictionary_ptr_->predict_last_path(buffer_)).empty() == false) {
                                            // нашли подсказку, выводим (не в конце)
                                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_GRAY_COLOR);
                                            std::cout << last_predicted_path_;
                                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), owner_ptr_->advanced_input_correct_color_);
                                        }

                                        owner_ptr_->go_to_xy(owner_ptr_->x_pos_ + ((owner_ptr_->is_pointer_on_ == true) ? owner_ptr_->pointer_str_.length() : 0) + 6 + 1 + owner_ptr_->buttons_data_vector_[owner_index].name.length() + 1 + inn_pointer, owner_ptr_->y_pos_ + owner_index + owner_ptr_->is_info_full_);
                                    }
                                }
                                else if(is_ban_not_allowed_ == false && tmp_char != ' ') {  // если общий блок выключен и это не (попавший в неразрешенный space)
                                    if (is_last_correct == true) {
                                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), owner_ptr_->advanced_input_uncorrect_color_);
                                        is_last_correct = false;
                                    }   // меняем цвет дл вывода на будущее (если не был нужный)
                                    if (inn_pointer == buffer_.length()) { // вводим неразрешенный в конец
                                        if (last_predicted_path_.empty() == false) {
                                            // очищаем старую подсказку
                                            for (int i{ 0 }; i < last_predicted_path_.length(); i++)
                                                std::cout << ' ';
                                            owner_ptr_->go_to_xy(owner_ptr_->x_pos_ + ((owner_ptr_->is_pointer_on_ == true) ? owner_ptr_->pointer_str_.length() : 0) + 6 + 1 + owner_ptr_->buttons_data_vector_[owner_index].name.length() + 1 + inn_pointer, owner_ptr_->y_pos_ + owner_index + owner_ptr_->is_info_full_);
                                            last_predicted_path_.clear();
                                        }

                                        buffer_.push_back(tmp_char);
                                        std::cout << tmp_char;
                                        inn_pointer++;
                                    }
                                    else {  // вводим неразрешенный не в конец
                                        if (last_predicted_path_.empty() == false) {
                                            // очищаем старую подсказку (не в конце)
                                            owner_ptr_->go_to_xy(owner_ptr_->x_pos_ + ((owner_ptr_->is_pointer_on_ == true) ? owner_ptr_->pointer_str_.length() : 0) + 6 + 1 + owner_ptr_->buttons_data_vector_[owner_index].name.length() + 1 + buffer_.length(), owner_ptr_->y_pos_ + owner_index + owner_ptr_->is_info_full_);
                                            for (int i{ 0 }; i < last_predicted_path_.length(); i++)
                                                std::cout << ' ';
                                            owner_ptr_->go_to_xy(owner_ptr_->x_pos_ + ((owner_ptr_->is_pointer_on_ == true) ? owner_ptr_->pointer_str_.length() : 0) + 6 + 1 + owner_ptr_->buttons_data_vector_[owner_index].name.length() + 1 + inn_pointer, owner_ptr_->y_pos_ + owner_index + owner_ptr_->is_info_full_);
                                            last_predicted_path_.clear();
                                        }

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
                                    count_of_mistakes++;
                                }
                                std::cout.flush(); // моментальное изменение cout с освобождением буфера
                            }
                        }
                    }
                    else {  // => был нажат TAB
                        if (last_predicted_path_.empty() == false && is_secured_ == false && count_of_mistakes == 0) {
                            // довводим (до макс длины!)
                            int can_write_tmp = max_length_ - buffer_.length(); // получили возможное количество символов

                            if (last_predicted_path_.length() <= can_write_tmp) { // можем ввести целиком
                                // перемещаем указатель на конец слова
                                owner_ptr_->go_to_xy(owner_ptr_->x_pos_ + ((owner_ptr_->is_pointer_on_ == true) ? owner_ptr_->pointer_str_.length() : 0) + 6 + 1 + owner_ptr_->buttons_data_vector_[owner_index].name.length() + 1 + buffer_.length(), owner_ptr_->y_pos_ + owner_index + owner_ptr_->is_info_full_);
                                buffer_ += last_predicted_path_;
                                // дальше вносим посимвольно! (вдруг ошибки ввода)
                                for (uint32_t i{ 0 }; i < last_predicted_path_.length(); i++) {
                                    if (std::binary_search(allowed_char_vector_.begin(), allowed_char_vector_.end(), last_predicted_path_[i]) == true) {
                                        if (is_last_correct == false) {
                                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), owner_ptr_->advanced_input_correct_color_);
                                            is_last_correct = true;
                                        }
                                        std::cout << last_predicted_path_[i];
                                    }
                                    else {
                                        if (is_last_correct == true) {
                                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), owner_ptr_->advanced_input_uncorrect_color_);
                                            is_last_correct = false;
                                        }
                                        std::cout << last_predicted_path_[i];
                                        count_of_mistakes++;
                                    }
                                }
                                last_predicted_path_.clear();
                                inn_pointer = buffer_.length(); // установили inn_pointer на новое место
                            }
                            else { // не можем ввести целиком
                                // очищаем старую подсказку
                                owner_ptr_->go_to_xy(owner_ptr_->x_pos_ + ((owner_ptr_->is_pointer_on_ == true) ? owner_ptr_->pointer_str_.length() : 0) + 6 + 1 + owner_ptr_->buttons_data_vector_[owner_index].name.length() + 1 + buffer_.length(), owner_ptr_->y_pos_ + owner_index + owner_ptr_->is_info_full_);
                                for (int i{ 0 }; i < last_predicted_path_.length(); i++)
                                    std::cout << ' ';

                                // работаем от смещения inn_pointer

                                owner_ptr_->go_to_xy(owner_ptr_->x_pos_ + ((owner_ptr_->is_pointer_on_ == true) ? owner_ptr_->pointer_str_.length() : 0) + 6 + 1 + owner_ptr_->buttons_data_vector_[owner_index].name.length() + 1 + buffer_.length(), owner_ptr_->y_pos_ + owner_index + owner_ptr_->is_info_full_);
                                inn_pointer = buffer_.length();
                                
                                buffer_.reserve(buffer_.length() + last_predicted_path_.length() - 1);
                                for (int i{ 0 }; i < last_predicted_path_.length(); i++) {
                                    if (inn_pointer >= max_length_)
                                        break; // выходим если уже некуда вводить

                                    buffer_.push_back(last_predicted_path_[i]);
                                    inn_pointer++;

                                    if (std::binary_search(allowed_char_vector_.begin(), allowed_char_vector_.end(), last_predicted_path_[i]) == true) {
                                        if (is_last_correct == false) {
                                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), owner_ptr_->advanced_input_correct_color_);
                                            is_last_correct = true;
                                        }
                                        std::cout << last_predicted_path_[i];
                                    }
                                    else {
                                        if (is_last_correct == true) {
                                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), owner_ptr_->advanced_input_uncorrect_color_);
                                            is_last_correct = false;
                                        }
                                        std::cout << last_predicted_path_[i];
                                        count_of_mistakes++;
                                    }
                                }
                                // ввели что смогли
                                last_predicted_path_.clear();
                            }

                            std::cout.flush();
                        }
                    }
                    break;
                }
            }
            else if (byte_system == BYTE_SYSTEM_IS_NOT_ONEBYTE) {   // стрелочки и т п
                switch (kb_numb)
                {
                case UP_POINTER_BUT:
                    if (last_predicted_path_.empty()) {
                        owner_ptr_->pointer_logic(&(owner_ptr_->pointer_), &(owner_ptr_->last_pointer_), owner_ptr_->count_of_buttons_, UP_POINTER_BUT);
                        return;
                    }
                    else if (dictionary_ptr_ != nullptr) {  // значит используем трелочки для подсказок
                        std::string str_buffer = dictionary_ptr_->predict_last_path_offset_up(buffer_);
                        if (str_buffer.empty() == false) {   // нашли новую подсказку                           
                            // очищаем старую подсказку (не в конце)
                            owner_ptr_->go_to_xy(owner_ptr_->x_pos_ + ((owner_ptr_->is_pointer_on_ == true) ? owner_ptr_->pointer_str_.length() : 0) + 6 + 1 + owner_ptr_->buttons_data_vector_[owner_index].name.length() + 1 + buffer_.length(), owner_ptr_->y_pos_ + owner_index + owner_ptr_->is_info_full_);
                            for (int i{ 0 }; i < last_predicted_path_.length(); i++)
                                std::cout << ' ';
                            
                            last_predicted_path_ = str_buffer;
                            owner_ptr_->go_to_xy(owner_ptr_->x_pos_ + ((owner_ptr_->is_pointer_on_ == true) ? owner_ptr_->pointer_str_.length() : 0) + 6 + 1 + owner_ptr_->buttons_data_vector_[owner_index].name.length() + 1 + buffer_.length(), owner_ptr_->y_pos_ + owner_index + owner_ptr_->is_info_full_);

                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_GRAY_COLOR);
                            std::cout << last_predicted_path_;
                            if (is_last_correct)
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), owner_ptr_->advanced_input_correct_color_);
                            else
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), owner_ptr_->advanced_input_uncorrect_color_);
                            owner_ptr_->go_to_xy(owner_ptr_->x_pos_ + ((owner_ptr_->is_pointer_on_ == true) ? owner_ptr_->pointer_str_.length() : 0) + 6 + 1 + owner_ptr_->buttons_data_vector_[owner_index].name.length() + 1 + inn_pointer, owner_ptr_->y_pos_ + owner_index + owner_ptr_->is_info_full_);
                            
                            std::cout.flush();
                        }
                    }
                    break;
                case DOWN_POINTER_BUT:
                    if (last_predicted_path_.empty()) {
                        owner_ptr_->pointer_logic(&(owner_ptr_->pointer_), &(owner_ptr_->last_pointer_), owner_ptr_->count_of_buttons_, DOWN_POINTER_BUT);
                        return;
                    }
                    else if (dictionary_ptr_ != nullptr) {
                        std::string str_buffer = dictionary_ptr_->predict_last_path_offset_down(buffer_);
                        if (str_buffer.empty() == false) {   // нашли новую подсказку                           
                            // очищаем старую подсказку (не в конце)
                            owner_ptr_->go_to_xy(owner_ptr_->x_pos_ + ((owner_ptr_->is_pointer_on_ == true) ? owner_ptr_->pointer_str_.length() : 0) + 6 + 1 + owner_ptr_->buttons_data_vector_[owner_index].name.length() + 1 + buffer_.length(), owner_ptr_->y_pos_ + owner_index + owner_ptr_->is_info_full_);
                            for (int i{ 0 }; i < last_predicted_path_.length(); i++)
                                std::cout << ' ';

                            last_predicted_path_ = str_buffer;
                            owner_ptr_->go_to_xy(owner_ptr_->x_pos_ + ((owner_ptr_->is_pointer_on_ == true) ? owner_ptr_->pointer_str_.length() : 0) + 6 + 1 + owner_ptr_->buttons_data_vector_[owner_index].name.length() + 1 + buffer_.length(), owner_ptr_->y_pos_ + owner_index + owner_ptr_->is_info_full_);

                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_GRAY_COLOR);
                            std::cout << last_predicted_path_;
                            if (is_last_correct)
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), owner_ptr_->advanced_input_correct_color_);
                            else
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), owner_ptr_->advanced_input_uncorrect_color_);
                            owner_ptr_->go_to_xy(owner_ptr_->x_pos_ + ((owner_ptr_->is_pointer_on_ == true) ? owner_ptr_->pointer_str_.length() : 0) + 6 + 1 + owner_ptr_->buttons_data_vector_[owner_index].name.length() + 1 + inn_pointer, owner_ptr_->y_pos_ + owner_index + owner_ptr_->is_info_full_);

                            std::cout.flush();
                        }
                    }
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

//-------------------------------------------------------------------------------------------------------------------

#define EASY_MENU_DICT_VERSION 1

std::unordered_map<std::string, EasyDict::DictData> EasyDict::opened_dicts_; // определили внешний map словарей

// все для EasyMenu_Dictionary (private)

EasyMenu_Dictionary::EasyMenu_Dictionary() {	// конструктор по умолчанию
    dictionary_name_ = "";
    max_word_length_ = 0;
    additional_max_word_length_ = 0;
    is_need_compile_ = false;
    last_prefix_ = "";
    last_prefix_index_ = 0;
}

EasyMenu_Dictionary::EasyMenu_Dictionary(std::string dictionary_name) : EasyMenu_Dictionary() {
    this->dictionary_name_ = dictionary_name;
}

EasyMenu_Dictionary::~EasyMenu_Dictionary() {
    DeleteData();	// очищаем динамиескую память
}

void EasyMenu_Dictionary::str_to_lower(std::string& str) {
    for (char& letter : str) {
        letter = std::tolower(static_cast<unsigned char>(letter));
    }
}

std::string EasyMenu_Dictionary::get_last_word(const std::string& str) {
    if (str.empty())
        return "";

    if (str.back() == ' ')
        return "";
    int end = static_cast<int>(str.length()) - 1;
    int start = end;

    while (start >= 0 && !std::isspace(static_cast<unsigned char>(str[start])))
        start--;	// идем влево до пробела или начала строки

    start++;	// теперь start указывает на пробел или -1

    return str.substr(start, end - start + 1);
}

uint32_t EasyMenu_Dictionary::get_max_word_length() {
    if (main_dict_.empty())
        return 0;

    auto it = std::max_element(main_dict_.begin(), main_dict_.end(),
        [](const Dictionary_note* first_ptr, const Dictionary_note* second_ptr) {
            return first_ptr->word.length() < second_ptr->word.length();
        });
    return (*it)->word.length();
}

void EasyMenu_Dictionary::compile_prefix_dicts() {
    if (additional_main_dict_.empty() == false) {	// переносим все из добавочного (если есть)
        main_dict_.insert(main_dict_.end(), additional_main_dict_.begin(), additional_main_dict_.end());
        additional_main_dict_.clear();
    }

    if (additional_max_word_length_ > max_word_length_)
        max_word_length_ = additional_max_word_length_;

    if (main_dict_.empty())
        return;	// невозмоно скомпилировать (не из чего)

    prefix_dicts_.clear();	// на всякий очищаем (безопасно с пустым)

    additional_max_word_length_ = 0;

    if (max_word_length_ < 1)	// если максимальная длина слов еще не проссчитана
        max_word_length_ = get_max_word_length();

    last_prefix_.clear();
    last_prefix_index_ = 0;

    is_need_compile_ = false;

    // начинаем саму компиляцию
    std::sort(main_dict_.begin(), main_dict_.end(),
        [](const Dictionary_note* first, const Dictionary_note* second) {
            return first->word < second->word;
        });			// отсортировали лексикографически main_dict_

    for (uint32_t i{ 0 }; i < main_dict_.size(); i++)
        main_dict_[i]->main_index = i;	// сохранили индексацию изначального массива (для востановления при передаче)

    prefix_dicts_.resize(max_word_length_ - 1);
    for (uint32_t i{ 0 }; i < main_dict_.size(); i++) {
        for (uint32_t len{ 1 }; len < main_dict_[i]->word.length(); len++) {
            prefix_dicts_[len - 1].push_back(main_dict_[i]);
        }
    }		// записали все подходящие указатели слов в префиксные вектора, сохранив лексикографический порядок

    for (uint32_t i{ 0 }; i < prefix_dicts_.size(); i++) {	// перебор по всем префиксным векторам
        std::sort(prefix_dicts_[i].begin(), prefix_dicts_[i].end(),
            [i](const Dictionary_note* first, const Dictionary_note* second) {
                int cmp = first->word.compare(0, i + 1, second->word, 0, i + 1);
                if (cmp == 0)	// сумма кодов равна
                    return first->popularity > second->popularity;
                return cmp < 0;
            });		// отсортировали дополнительно чисто по (i + 1) длине префикса, если равны => сравнили по популярностии >

        uint32_t tmp_count{ 0 };
        auto new_end_it = std::unique(prefix_dicts_[i].begin(), prefix_dicts_[i].end(),
            [i, &tmp_count](const Dictionary_note* first, const Dictionary_note* second) {
                if (first->word.compare(0, i + 1, second->word, 0, i + 1) != 0) {
                    tmp_count = 1;
                    return false;
                }
                return ++tmp_count > EASY_MENU_MAX_REPEAT_COUNT_;
            });		// пометили через unique что нужно удалить (менее популярные повторки (если их > EASY_MENU_MAX_REPEAT_COUNT_))

        prefix_dicts_[i].erase(new_end_it, prefix_dicts_[i].end());
    }	// по итогу каждый из префиксных массивов лично отсортирован по размеру префиксов + убраны менее популярные (если их > EASY_MENU_MAX_REPEAT_COUNT_)
    return;
}

bool EasyMenu_Dictionary::SaveReadyData() {
    if (dictionary_name_.empty()) // не можем сохранить - нет имени!
        return false;

    const std::string tmp_to_file = dictionary_name_ + "tmp_RD.emd"; // подготовили имя (врмеменное)
    const std::string to_file = dictionary_name_ + "_RD.emd";	// имя для итогового файла

    std::ofstream file(tmp_to_file, std::ios::binary | std::ios::trunc);	// открыли в бинарном виде, удалив что было
    if (file.is_open() == false)
        return false; // не смогли создать файл

    // дальше сохраняем данные
    uint32_t version = EASY_MENU_DICT_VERSION;
    file.write(reinterpret_cast<char*>(&version), sizeof(version));

    file.write(reinterpret_cast<char*>(&max_word_length_), sizeof(max_word_length_));

    file.write(reinterpret_cast<char*>(&is_need_compile_), sizeof(is_need_compile_));

    uint32_t uint32_t_buffer = main_dict_.size();
    file.write(reinterpret_cast<char*>(&uint32_t_buffer), sizeof(uint32_t_buffer));

    for (uint32_t i{ 0 }; i < main_dict_.size(); i++) {	// записываем BaseData
        uint32_t_buffer = main_dict_[i]->word.length();
        file.write(reinterpret_cast<char*>(&uint32_t_buffer), sizeof(uint32_t_buffer));

        file.write(main_dict_[i]->word.data(), uint32_t_buffer);

        file.write(reinterpret_cast<char*>(&main_dict_[i]->popularity), sizeof(main_dict_[i]->popularity));
    }

    uint32_t_buffer = additional_main_dict_.size();
    file.write(reinterpret_cast<char*>(&uint32_t_buffer), sizeof(uint32_t_buffer));

    for (uint32_t i{ 0 }; i < additional_main_dict_.size(); i++) {
        uint32_t_buffer = additional_main_dict_[i]->word.length();
        file.write(reinterpret_cast<char*>(&uint32_t_buffer), sizeof(uint32_t_buffer));
        
        file.write(additional_main_dict_[i]->word.data(), uint32_t_buffer);

        file.write(reinterpret_cast<char*>(&additional_main_dict_[i]->popularity), sizeof(additional_main_dict_[i]->popularity));
    }

    uint32_t_buffer = prefix_dicts_.size();
    file.write(reinterpret_cast<char*>(&uint32_t_buffer), sizeof(uint32_t_buffer));

    for (uint32_t i{ 0 }; i < prefix_dicts_.size(); i++) {
        uint32_t_buffer = prefix_dicts_[i].size();
        file.write(reinterpret_cast<char*>(&uint32_t_buffer), sizeof(uint32_t_buffer));

        for (uint32_t g{ 0 }; g < prefix_dicts_[i].size(); g++)
            file.write(reinterpret_cast<char*>(&prefix_dicts_[i][g]->main_index), sizeof(prefix_dicts_[i][g]->main_index));
    }

    // дальше проверяем корректность
    if (!file) { // значит при записи была ошибка (битый файл!)
        file.close();
        std::remove(tmp_to_file.c_str());	// удаляем временный файл
        return false;
    }
    // значит ошибок не было!

    file.close();

    std::remove(to_file.c_str()); // удаляем, если есть
    if (std::rename(tmp_to_file.c_str(), to_file.c_str()) == 0)
        return true;
    else
        std::remove(tmp_to_file.c_str());	// очистили временный, если не смогли переименовать
    return false; // значит не смогли переименовать
}

bool EasyMenu_Dictionary::ReadReadyData() {
    if (dictionary_name_.empty()) // не можем прочитать - нет имени!
        return false;

    const std::string to_file = dictionary_name_ + "_RD.emd";	// имя для файла

    std::ifstream file(to_file, std::ios::binary | std::ios::in);
    if (file.is_open() == false)
        return false; // не смогли создать файл

    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    // подготовка к безопасному чтению
    uint32_t uint32_t_buffer;
    uint32_t tmp_max_word_length;
    bool tmp_is_need_compile;
    std::vector<Dictionary_note*> tmp_main_dict;
    std::vector<Dictionary_note*> tmp_additional_main_dict;
    std::vector<std::vector<Dictionary_note*>> tmp_prefix_dict;
    try {
        // начинаем читать
        file.read(reinterpret_cast<char*>(&uint32_t_buffer), sizeof(uint32_t_buffer));
        if (uint32_t_buffer != EASY_MENU_DICT_VERSION) {
            file.close();
            return false;
        }

        file.read(reinterpret_cast<char*>(&tmp_max_word_length), sizeof(tmp_max_word_length));

        file.read(reinterpret_cast<char*>(&tmp_is_need_compile), sizeof(tmp_is_need_compile));

        file.read(reinterpret_cast<char*>(&uint32_t_buffer), sizeof(uint32_t_buffer));
        tmp_main_dict.resize(uint32_t_buffer); // именно resize

        for (uint32_t i{ 0 }; i < tmp_main_dict.size(); i++) {
            tmp_main_dict[i] = new Dictionary_note;
            tmp_main_dict[i]->main_index = i; // логически востанавливаем 

            file.read(reinterpret_cast<char*>(&uint32_t_buffer), sizeof(uint32_t_buffer));

            tmp_main_dict[i]->word.resize(uint32_t_buffer);
            file.read(&tmp_main_dict[i]->word[0], tmp_main_dict[i]->word.size());

            file.read(reinterpret_cast<char*>(&tmp_main_dict[i]->popularity), sizeof(tmp_main_dict[i]->popularity));
        }

        file.read(reinterpret_cast<char*>(&uint32_t_buffer), sizeof(uint32_t_buffer));
        tmp_additional_main_dict.resize(uint32_t_buffer);

        for (uint32_t i{ 0 }; i < tmp_additional_main_dict.size(); i++) {
            tmp_additional_main_dict[i] = new Dictionary_note;

            file.read(reinterpret_cast<char*>(&uint32_t_buffer), sizeof(uint32_t_buffer));
            
            tmp_additional_main_dict[i]->word.resize(uint32_t_buffer);
            file.read(&tmp_additional_main_dict[i]->word[0], tmp_additional_main_dict[i]->word.size());

            file.read(reinterpret_cast<char*>(&tmp_additional_main_dict[i]->popularity), sizeof(tmp_additional_main_dict[i]->popularity));
        }

        file.read(reinterpret_cast<char*>(&uint32_t_buffer), sizeof(uint32_t_buffer));
        tmp_prefix_dict.resize(uint32_t_buffer);	// именно resize

        for (uint32_t i{ 0 }; i < tmp_prefix_dict.size(); i++) {
            file.read(reinterpret_cast<char*>(&uint32_t_buffer), sizeof(uint32_t_buffer));
            tmp_prefix_dict[i].resize(uint32_t_buffer);

            for (uint32_t g{ 0 }; g < tmp_prefix_dict[i].size(); g++) {
                file.read(reinterpret_cast<char*>(&uint32_t_buffer), sizeof(uint32_t_buffer));
                tmp_prefix_dict[i][g] = tmp_main_dict[uint32_t_buffer];	// присвоили указатель
            }
        }
        // конец чтения файла

        if (file.good() == false && file.eof() == false) {
            file.close();

            for (uint32_t i{ 0 }; i < tmp_main_dict.size(); i++)
                if (tmp_main_dict[i] != nullptr)
                    delete tmp_main_dict[i];	// очищаем если нужно

            return false;
        }
    }
    catch (...) { // если произошла ошибка (при чтении)
        file.close();

        for (uint32_t i{ 0 }; i < tmp_main_dict.size(); i++)
            if (tmp_main_dict[i] != nullptr)
                delete tmp_main_dict[i];	// очищаем если нужно

        return false;
    }

    // ошибки не было - переносим данные (в основыную)
    file.close();

    DeleteData(); // очищаем всю память (особенно динамическую)

    max_word_length_ = tmp_max_word_length;
    is_need_compile_ = tmp_is_need_compile;
    main_dict_ = tmp_main_dict; // скопировали все указатели
    additional_main_dict_ = tmp_additional_main_dict;   // копировали все указатели
    prefix_dicts_ = tmp_prefix_dict; // скопировали все векторы указателей

    return true;
}

bool EasyMenu_Dictionary::ExportViaCSV() {
    if (dictionary_name_.empty() || main_dict_.empty())
        return false;

    const std::string to_file = dictionary_name_ + ".csv";	// имя для итогового файла

    std::ofstream file(to_file, std::ios::trunc);	// открыли в бинарном виде, удалив что было
    if (file.is_open() == false)
        return false; // не смогли создать файл

    // записываем
    try {
        file << '\"' << main_dict_[0]->word << '\"' << ";\"" << main_dict_[0]->popularity << '\"';

        for (uint32_t i{ 1 }; i < main_dict_.size(); i++)
            file << '\n' << '\"' << main_dict_[i]->word << '\"' << ";\"" << main_dict_[i]->popularity << '\"';

        if (!file) { // значит при записи была ошибка (битый файл!)
            file.close();
            std::remove(to_file.c_str());	// удаляем файл
            return false;
        }
    }
    catch (...) {
        file.close();
        std::remove(to_file.c_str());	// удаляем файл
        return false;
    }

    file.close();

    return true;
}

bool EasyMenu_Dictionary::ImportViaCSV() {
    
    return ImportViaCSV(dictionary_name_);
}

bool EasyMenu_Dictionary::ImportViaCSV(const std::string& file_name) {
    if (dictionary_name_.empty() || file_name.empty()) // не можем прочитать - нет имени!
        return false;

    const std::string to_file = file_name + ".csv";	// имя для файла

    std::ifstream file(to_file, std::ios::in);
    if (file.is_open() == false)
        return false; // не смогли создать файл

    // подготовка к безопасному чтению
    uint32_t tmp_max_word_length = 0;
    bool tmp_is_need_compile = true;
    std::vector<Dictionary_note*> tmp_main_dict;
    try {
        size_t sep_index;
        std::string tmp_bufer;

        // начинаем читать
        while (std::getline(file, tmp_bufer)) {
            sep_index = tmp_bufer.find(';');

            if (sep_index == std::string::npos)
                break;  // скорее всего данные закончились

            if (tmp_bufer[sep_index + 1] != '\"' || tmp_bufer[sep_index - 1] != '\"')
                throw;  // это ошибка формата
            
            if (tmp_bufer[0] != '\"' || tmp_bufer[tmp_bufer.length() - 1] != '\"')
                throw;  // это ошибка формата

            Dictionary_note* tmp_ptr = new Dictionary_note;
            if (sep_index <= 2) throw std::runtime_error("Empty word field");
            tmp_ptr->word = tmp_bufer.substr(1, sep_index - 2);
            std::string number_part = tmp_bufer.substr(sep_index + 2);
            if (number_part.back() == '"')
                number_part.pop_back();
            tmp_ptr->popularity = std::stoi(number_part);

            tmp_main_dict.push_back(tmp_ptr);
        }
    }
    catch (...) {
        // словили какую-то ошибку
        file.close();

        for (uint32_t i{ 0 }; i < tmp_main_dict.size(); i++)
            if (tmp_main_dict[i] != nullptr)
                delete tmp_main_dict[i];	// очищаем если нужно

        return false;
    }

    // ошибки не было - переносим данные (в основыную)
    file.close();

    DeleteData(); // очищаем всю память (особенно динамическую)

    max_word_length_ = tmp_max_word_length;
    is_need_compile_ = tmp_is_need_compile;
    main_dict_ = tmp_main_dict; // скопировали все указатели

    compile_prefix_dicts();

    return true;
}

bool EasyMenu_Dictionary::GetReadyData(std::vector<char>& to_copy) {
    if (SaveReadyData() == false)	// контрольное сохранание
        return false;

    const std::string to_file = dictionary_name_ + "_RD.emd";	// имя для файла

    std::ifstream file(to_file, std::ios::binary | std::ios::ate);
    if (file.is_open() == false)
        return false;

    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    auto file_size = file.tellg(); // прочитали конечную позицию
    if (file_size == 0) {
        file.close();
        return false;
    }

    to_copy.clear();
    to_copy.resize(file_size);

    try {
        file.seekg(0);	// поставили в начало
        file.read(to_copy.data(), file_size);
    }
    catch (...) { // какая-то ошибка
        file.close();
        return false;
    }

    file.close();
    return true; // долши сюда - все хорошо)
}

bool EasyMenu_Dictionary::ReadFromCharData(const std::vector<char>& data) {
    uint32_t data_index = 0;	// для смещения чтения

    // подготовка к безопасному чтению
    uint32_t uint32_t_buffer;
    uint32_t tmp_max_word_length;
    bool tmp_is_need_compile;
    std::vector<Dictionary_note*> tmp_main_dict;
    std::vector<Dictionary_note*> tmp_addictional_dict;
    std::vector<std::vector<Dictionary_note*>> tmp_prefix_dict;

    // начинаем само чтение
    try {
        // начинаем читать
        uint32_t_buffer = *(reinterpret_cast<const uint32_t*>(&data[data_index]));
        data_index += sizeof(uint32_t_buffer);

        if (uint32_t_buffer != EASY_MENU_DICT_VERSION)
            return false;

        tmp_max_word_length = *(reinterpret_cast<const uint32_t*>(&data[data_index]));
        data_index += sizeof(tmp_max_word_length);

        tmp_is_need_compile = *(reinterpret_cast<const bool*>(&data[data_index]));
        data_index += sizeof(tmp_is_need_compile);

        uint32_t_buffer = *(reinterpret_cast<const uint32_t*>(&data[data_index]));
        data_index += sizeof(uint32_t_buffer);
        tmp_main_dict.resize(uint32_t_buffer);	// именно resize

        for (uint32_t i{ 0 }; i < tmp_main_dict.size(); i++) {
            tmp_main_dict[i] = new Dictionary_note;
            tmp_main_dict[i]->main_index = i; // логически востанавливаем 

            uint32_t_buffer = *(reinterpret_cast<const uint32_t*>(&data[data_index]));
            data_index += sizeof(uint32_t_buffer);

            tmp_main_dict[i]->word.resize(uint32_t_buffer); // именно resize
            for (uint32_t g{ 0 }; g < tmp_main_dict[i]->word.size(); g++) {
                tmp_main_dict[i]->word[g] = data[data_index];
                data_index++;
            }

            tmp_main_dict[i]->popularity = *(reinterpret_cast<const uint32_t*>(&data[data_index]));
            data_index += sizeof(tmp_main_dict[i]->popularity);
        }

        uint32_t_buffer = *(reinterpret_cast<const uint32_t*>(&data[data_index]));
        data_index += sizeof(uint32_t_buffer);
        tmp_addictional_dict.resize(uint32_t_buffer);

        for (uint32_t i{ 0 }; i < tmp_addictional_dict.size(); i++) {
            tmp_addictional_dict[i] = new Dictionary_note;

            uint32_t_buffer = *(reinterpret_cast<const uint32_t*>(&data[data_index]));
            data_index += sizeof(uint32_t_buffer);

            tmp_addictional_dict[i]->word.resize(uint32_t_buffer);
            for (uint32_t g{ 0 }; g < tmp_addictional_dict[i]->word.size(); g++) {
                tmp_addictional_dict[i]->word[g] = data[data_index];
                data_index++;
            }

            tmp_addictional_dict[i]->popularity = *(reinterpret_cast<const uint32_t*>(&data[data_index]));
            data_index += sizeof(tmp_addictional_dict[i]->popularity);
        }

        uint32_t_buffer = *(reinterpret_cast<const uint32_t*>(&data[data_index]));
        data_index += sizeof(uint32_t_buffer);
        tmp_prefix_dict.resize(uint32_t_buffer);	// именно resize

        for (uint32_t i{ 0 }; i < tmp_prefix_dict.size(); i++) {
            uint32_t_buffer = *(reinterpret_cast<const uint32_t*>(&data[data_index]));
            data_index += sizeof(uint32_t_buffer);

            tmp_prefix_dict[i].resize(uint32_t_buffer);

            for (uint32_t g{ 0 }; g < tmp_prefix_dict[i].size(); g++) {
                uint32_t_buffer = *(reinterpret_cast<const uint32_t*>(&data[data_index]));
                data_index += sizeof(uint32_t_buffer);

                tmp_prefix_dict[i][g] = tmp_main_dict[uint32_t_buffer];
            }
        }
        // конец чтения
    }
    catch (...) {	// если произошла ошибка (при чтении)
        for (uint32_t i{ 0 }; i < tmp_main_dict.size(); i++)
            if (tmp_main_dict[i] != nullptr)
                delete tmp_main_dict[i];	// очищаем если нужно

        return false;
    }

    // ошибки не было - переносим данные (в основову)
    DeleteData();

    max_word_length_ = tmp_max_word_length;
    is_need_compile_ = tmp_is_need_compile;
    main_dict_ = tmp_main_dict; // скопировали все указатели
    additional_main_dict_ = tmp_addictional_dict; // скопировали все указатели
    prefix_dicts_ = tmp_prefix_dict; // скопировали все векторы указателей

    return true;
}

void EasyMenu_Dictionary::DeleteData() {
    last_prefix_ = "";
    last_prefix_index_ = 0;

    prefix_dicts_.clear();

    is_need_compile_ = false;

    max_word_length_ = 0;
    additional_max_word_length_ = 0;

    for (uint32_t i{ 0 }; i < main_dict_.size(); i++)
        if (main_dict_[i] != nullptr)
            delete main_dict_[i];
    main_dict_.clear();

    for (uint32_t i{ 0 }; i < additional_main_dict_.size(); i++)
        if (additional_main_dict_[i] != nullptr)
            delete additional_main_dict_[i];
    additional_main_dict_.clear();
}

bool EasyMenu_Dictionary::EnterWord(std::string word) {
    if (dictionary_name_.empty())
        return false;	// у нас нет словаря (имя = словарь)

    str_to_lower(word);

    auto it = std::lower_bound(main_dict_.begin(), main_dict_.end(), word,
        [](const Dictionary_note* first, const std::string str_word) {
            return first->word < str_word;
        });

    if (it == main_dict_.end() || (*it)->word != word) {	// в main_dict_ (word) не оказалось
        if (additional_main_dict_.empty()) { // доп словарь пустой - просто добавляем
            Dictionary_note* tmp_ptr = new Dictionary_note;
            tmp_ptr->word = word;
            tmp_ptr->popularity = 1;

            additional_main_dict_.push_back(tmp_ptr);
            if (additional_max_word_length_ < word.length())
                additional_max_word_length_ = word.length();
        }
        else {	// нужно поискать в доп словаре!
            auto add_it = std::lower_bound(additional_main_dict_.begin(), additional_main_dict_.end(), word,
                [](const Dictionary_note* first, const std::string str_word) {
                    return first->word < str_word;
                });

            if (add_it == additional_main_dict_.end() || (*add_it)->word != word) {	// значит такого слова нет, добавляем
                Dictionary_note* tmp_ptr = new Dictionary_note;
                tmp_ptr->word = word;
                tmp_ptr->popularity = 1;

                additional_main_dict_.insert(add_it, tmp_ptr);	// добавили, сохранив сортировку
                if (additional_max_word_length_ < word.length())
                    additional_max_word_length_ = word.length();
            }
            else    // такое слово есть - делаем ++
                (*add_it)->popularity++;
        }
    }
    else	// word найден в main_dict_!
        (*it)->popularity++;	// увеличили счетчик популярности

    is_need_compile_ = true;
    return true;
}

// все для EasyMenu_Dictionary (public)

std::string EasyMenu_Dictionary::PredictWord(const std::string& prefix_str) {	// поиск только для самого популярного
    if (prefix_str.empty())
        return "";

    std::string prefix = get_last_word(prefix_str);

    uint32_t prefix_length = prefix.length();

    if (prefix_length > 0 && prefix_length <= prefix_dicts_.size()) {	// выполняем только если результат возможен
        str_to_lower(prefix);

        auto it = std::lower_bound(prefix_dicts_[prefix_length - 1].begin(), prefix_dicts_[prefix_length - 1].end(), prefix,
            [prefix_length](const Dictionary_note* first, const std::string& pref_str) {
                return first->word.compare(0, prefix_length, pref_str) < 0;
            });		// находим итератор на первый элемент, содержащий префикс (он же самый популярный)

        if (it != prefix_dicts_[prefix_length - 1].end() && (*it)->word.compare(0, prefix_length, prefix, 0, prefix_length) == 0) {	// проверили не находитсчя ли итератор в конце (не нашли) и точно ли полученная строка начинается на префикс
            last_prefix_ = prefix;	// записали успешно найденное (самое популярное) слово из возможных
            last_prefix_index_ = std::distance(prefix_dicts_[prefix_length - 1].begin(), it);	// записали индекс этого слова, для возможности дальнейшего смещения
            last_prefix_offset_ = 0;    // обнулили оффсет
            return (*it)->word;
        }
        else
            return "";
    }
    return "";
}

std::string EasyMenu_Dictionary::PredictLastParthOfWord(const std::string& prefix) {
    if (prefix.empty())
        return "";
    
    std::string tmp_str = get_last_word(prefix);

    std::string full_word = PredictWord(tmp_str);

    if (full_word.empty())
        return "";

    return full_word.substr(tmp_str.length());
}

std::string EasyMenu_Dictionary::ChangeOffsetParth(const std::string& prefix, bool is_up) {
    if (prefix.empty())
        return "";  // пустые данные

    string tmp_str = get_last_word(prefix);
    str_to_lower(tmp_str);

    if (tmp_str != last_prefix_)
        return "";  // не те данные для сдвига

    if (is_up) {    // двигаемся вверх (-> более популярное)
        if (last_prefix_offset_ > 0)  // к изначальному можем двигаться без проверок
            return prefix_dicts_[tmp_str.length() - 1][last_prefix_index_ + (--last_prefix_offset_)]->word.substr(tmp_str.length());
    }
    else {  // двигаемся вниз (-> менее популярное)
        if (last_prefix_offset_ + last_prefix_index_ + 1 < prefix_dicts_[tmp_str.length() - 1].size()) {    // значит потанциально не выходим за предел
            if (prefix_dicts_[tmp_str.length() - 1][last_prefix_index_ + (++last_prefix_offset_)]->word.compare(0, tmp_str.length(), tmp_str) == 0)    // значит префиксы совпадают
                return prefix_dicts_[tmp_str.length() - 1][last_prefix_index_ + last_prefix_offset_]->word.substr(tmp_str.length());
            else // значит не совпало -> откатываем last_prefix_offset_
                --last_prefix_offset_;
            
        }
        else
            return "";  // (вышли за предел вектора)
    }

    return "";  // заглушка для ошибок
}

//---------------------------------------|
// Все для EasyDict (private)

void EasyDict::str_to_lower(std::string& str) {
    for (char& letter : str) {
        letter = std::tolower(static_cast<unsigned char>(letter));
    }
}

std::vector<std::string> EasyDict::split_words(const std::string& str) {
    std::vector<std::string> words;
    words.reserve(3);

    uint32_t start = 0, end = 0;

    while (end < str.length()) {
        while (start < str.length() && std::isspace(static_cast<unsigned char>(str[start]))) {
            start++;	// Пропускаем пробелы
        }

        if (start >= str.length())
            break;

        end = start;
        while (end < str.length() && std::isspace(static_cast<unsigned char>(str[end])) == false) {
            end++;	// Находим конец слова
        }

        words.push_back(str.substr(start, end - start));	// Добавляем слово
        start = end;
    }

    return words;
}

// операторы (public)

EasyDict& EasyDict::operator=(const EasyDict& reference) {
    if (this == &reference)
        return *this;

    close();

    opened_dict_ptr_ = reference.opened_dict_ptr_;

    if (opened_dict_ptr_ != nullptr) {
        auto it = opened_dicts_.find(opened_dict_ptr_->dictionary_name_);
        if (it != opened_dicts_.end())
            it->second.count++;
    }

    return *this;
}

// Все для EasyDict (public)

EasyDict::EasyDict() {
    opened_dict_ptr_ = nullptr;

    std::setlocale(LC_ALL, "");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}

EasyDict::EasyDict(std::string dictionary_name) : EasyDict() {
    open(dictionary_name);
}

EasyDict::EasyDict(const EasyDict& reference) {
    opened_dict_ptr_ = reference.opened_dict_ptr_;

    if (opened_dict_ptr_ != nullptr) {	// увеличиваем счетчик связей
        auto it = opened_dicts_.find(opened_dict_ptr_->dictionary_name_);
        if (it != opened_dicts_.end())
            it->second.count++;
    }
}

EasyDict::~EasyDict() {
    close();
}

bool EasyDict::open(std::string dictionary_name) {
    if (dictionary_name.empty())
        return false;

    if (opened_dict_ptr_ != nullptr)
        close();	// закроем, если был открыт 

    str_to_lower(dictionary_name);

    // пытаемся найти в unordered_map
    auto it = opened_dicts_.find(dictionary_name);
    if (it != opened_dicts_.end()) {	// нашли в открытых
        it->second.count++;	// увеличили счетчик
        opened_dict_ptr_ = it->second.dict_ptr;	// прировняли указатель

        return true;
    }

    // пытаемся прочитать новый (файл)
    EasyMenu_Dictionary* tmp_ptr = new EasyMenu_Dictionary(dictionary_name);

    if (tmp_ptr->ReadReadyData()) {
        // смогли прочитать - добавляем в map
        DictData tmp_data;
        tmp_data.count = 1;
        tmp_data.dict_ptr = tmp_ptr;

        opened_dicts_.emplace(dictionary_name, tmp_data);
        opened_dict_ptr_ = tmp_ptr;

        return true;
    }

    // не смогли найти в map + открыть из файла
    delete tmp_ptr;

    return false;
}

bool EasyDict::open_via_char(std::string dictionary_name, const std::vector<char>& char_vector) {
    if (dictionary_name.empty())
        return false;

    if (opened_dict_ptr_ != nullptr)
        close();	// закроем, если был открыт 

    str_to_lower(dictionary_name);

    // пытаемся найти в unordered_map
    auto it = opened_dicts_.find(dictionary_name);
    if (it != opened_dicts_.end()) {	// нашли в открытых (просто изменяем ОЗУ (без сохранения))
        if (it->second.dict_ptr->ReadFromCharData(char_vector) == false)
            return false;
        it->second.count++;	// увеличили счетчик
        opened_dict_ptr_ = it->second.dict_ptr;	// прировняли указатель

        return true;
    }

    // в map не оказалось => просто созадем (без сохранения)
    EasyMenu_Dictionary* tmp_ptr = new EasyMenu_Dictionary(dictionary_name);

    if (tmp_ptr->ReadFromCharData(char_vector)) {	// смогли прочитать
        // смогли прочитать - добавляем в map
        DictData tmp_data;
        tmp_data.count = 1;
        tmp_data.dict_ptr = tmp_ptr;

        opened_dicts_.emplace(dictionary_name, tmp_data);
        opened_dict_ptr_ = tmp_ptr;

        return true;
    }

    // не смогли найти в map + прочитать из файла
    delete tmp_ptr;

    return false;
}

bool EasyDict::open_via_csv() {
    if (opened_dict_ptr_ == nullptr)
        return false;

    opened_dict_ptr_->ImportViaCSV();
}

bool EasyDict::open_via_csv(const std::string& file_name) {
    if (opened_dict_ptr_ == nullptr)
        return false;

    opened_dict_ptr_->ImportViaCSV(file_name);
}

bool EasyDict::create(std::string dictionary_name) {
    if (dictionary_name.empty())
        return false;

    if (opened_dict_ptr_ != nullptr)
        close();

    str_to_lower(dictionary_name);

    // проверяем, открыт ли такой словарь в map
    auto it = opened_dicts_.find(dictionary_name);
    if (it != opened_dicts_.end()) {	// значит нашли 
        it->second.count++;
        opened_dict_ptr_ = it->second.dict_ptr;

        it->second.dict_ptr->DeleteData();	// очистили ОЗУ в словаре
        it->second.dict_ptr->SaveReadyData();	// сохранили пустой словарь

        return true;
    }

    // в map не оказалось => просто сохраняем (в файл)
    EasyMenu_Dictionary* tmp_ptr = new EasyMenu_Dictionary(dictionary_name);
    if (tmp_ptr->SaveReadyData() == false) {	// не удалось сохранить файл (создать)
        delete tmp_ptr;

        return false;
    }

    // успешно сохранили => добавляем в map
    DictData tmp_data;
    tmp_data.count = 1;
    tmp_data.dict_ptr = tmp_ptr;

    opened_dicts_.emplace(dictionary_name, tmp_data);
    opened_dict_ptr_ = tmp_ptr;

    return true;
}

bool EasyDict::create(std::string dictionary_name, std::string copying_dictionary_name) {
    if (dictionary_name.empty() || copying_dictionary_name.empty())
        return false;

    str_to_lower(dictionary_name);
    str_to_lower(copying_dictionary_name);

    std::vector<char> saved_data;

    // ищем есть ли вообще coping_dictionary_name (начинаем с map)
    auto it = opened_dicts_.find(copying_dictionary_name);
    if (it != opened_dicts_.end()) {	// значит нашли
        if (it->second.dict_ptr->GetReadyData(saved_data) == false)
            return false;	// ошибка получения данных

    }
    else {	// значит не нашли => ищем по файлам
        EasyMenu_Dictionary* tmp_ptr = new EasyMenu_Dictionary(copying_dictionary_name);
        if (tmp_ptr->ReadReadyData() == false) {	// не нашли файл/ошибка чтения
            delete tmp_ptr;

            return false;
        }

        if (tmp_ptr->GetReadyData(saved_data) == false) { // ошибка получения данных
            delete tmp_ptr;

            return false;
        }

        delete tmp_ptr;
    }

    // дошли сюда => данные для копировния сохранены (saved_data) => дальше ищем dictionary_name в map (открытых)
    it = opened_dicts_.find(dictionary_name);
    if (it != opened_dicts_.end()) {	// нашли в map
        it->second.count++;
        opened_dict_ptr_ = it->second.dict_ptr;

        it->second.dict_ptr->DeleteData();	// очистили ОЗУ в словаре
        if (it->second.dict_ptr->ReadFromCharData(saved_data) == false)
            return false;	// не смогли записать (остались пред данные)

        it->second.dict_ptr->SaveReadyData();	// сохранили словарь

        return true;
    }

    // в map не оказалось => просто сохраняем (в файл)
    EasyMenu_Dictionary* tmp_ptr = new EasyMenu_Dictionary(dictionary_name);
    if (tmp_ptr->ReadFromCharData(saved_data) == false) {	// не удалось прочитать сохранение
        delete tmp_ptr;

        return false;
    }

    if (tmp_ptr->SaveReadyData() == false) {	// не удалось сохранить 
        delete tmp_ptr;

        return false;
    }

    // успешно сохранили => добавляем в map
    DictData tmp_data;
    tmp_data.count = 1;
    tmp_data.dict_ptr = tmp_ptr;

    opened_dicts_.emplace(dictionary_name, tmp_data);
    opened_dict_ptr_ = tmp_ptr;

    return true;
}

bool EasyDict::close() {
    if (opened_dict_ptr_ == nullptr)
        return false;

    // тперь ищем в map
    std::string dictionary_name = opened_dict_ptr_->dictionary_name_;
    auto it = opened_dicts_.find(dictionary_name);

    if (it == opened_dicts_.end())
        return false;

    if ((--(it->second.count)) == 0) {
        // больше никто не ссылается на этот словарь - очищаем ОЗУ
        delete it->second.dict_ptr;
        opened_dicts_.erase(it);
    }

    opened_dict_ptr_ = nullptr;

    return true;
}

bool EasyDict::is_open() {
    if (opened_dict_ptr_ == nullptr)
        return false;

    return true;
}

bool EasyDict::is_need_compile() {
    if (opened_dict_ptr_ == nullptr)
        return false;

    return opened_dict_ptr_->is_need_compile_;
}

std::string EasyDict::get_open_name() {
    if (opened_dict_ptr_ == nullptr)
        return "";

    return opened_dict_ptr_->dictionary_name_;
}

bool EasyDict::save() {
    if (opened_dict_ptr_ == nullptr)
        return false;

    return opened_dict_ptr_->SaveReadyData();
}

bool EasyDict::save_via_char(std::vector<char>& char_vector) {
    if (opened_dict_ptr_ == nullptr)
        return false;

    return opened_dict_ptr_->GetReadyData(char_vector);
}

bool EasyDict::save_via_csv() {
    if (opened_dict_ptr_ == nullptr)
        return false;

    return opened_dict_ptr_->ExportViaCSV();
}

bool EasyDict::compile() {
    if (opened_dict_ptr_ == nullptr)
        return false;

    opened_dict_ptr_->compile_prefix_dicts();

    return true;
}

std::string EasyDict::predict_word(std::string prefix) {
    if (opened_dict_ptr_ == nullptr)
        return "";

    return opened_dict_ptr_->PredictWord(prefix);
}

std::string EasyDict::predict_last_path(std::string prefix) {
    if (opened_dict_ptr_ == nullptr)
        return "";

    return opened_dict_ptr_->PredictLastParthOfWord(prefix);
}

std::string EasyDict::predict_last_path_offset_up(std::string prefix) {
    if (opened_dict_ptr_ == nullptr)
        return "";

    return opened_dict_ptr_->ChangeOffsetParth(prefix, true);
}

std::string EasyDict::predict_last_path_offset_down(std::string prefix) {
    if (opened_dict_ptr_ == nullptr)
        return "";

    return opened_dict_ptr_->ChangeOffsetParth(prefix, false);
}

bool EasyDict::enter_words(const std::string& words_str) {
    if (opened_dict_ptr_ == nullptr)
        return false;

    std::vector<std::string> words = split_words(words_str);

    for (uint32_t i{ 0 }; i < words.size(); i++) {
        if (opened_dict_ptr_->EnterWord(words[i]) == false)
            return false;
    }

    return true;
}