![main bar gif](docs/main_bar.gif)
<div align="center">

![C++ badge](https://img.shields.io/badge/C%2B%2B-blue?style=flat&logo=C%2B%2B
) ![windows only](https://img.shields.io/badge/Windows-%20only-black?style=flat&logo=windows
)
</div>

# EasyMenu
A simple C++ library for easy menu construction in console applications with native [fluent API](https://en.wikipedia.org/wiki/Fluent_interface). Windows only.

# Instalation
Install the [latest](https://github.com/ganda1fero/EasyMenu_library/releases/tag/2.1.0) version. Place the [EasyMenu.h](https://github.com/ganda1fero/EasyMenu_library/releases/download/2.1.0/EasyMenu.h) and [EasyMenu.cpp](https://github.com/ganda1fero/EasyMenu_library/releases/download/2.1.0/EasyMenu.cpp) files in the project folder and add the:
```cpp
#include "EasyMenu.h"
```

# Examples
This is not a step-by-step guide, these are just examples. Implementation is limited only by your imagination!

Here is a simple example of building a menu with 2 buttons.
```cpp
#include "EasyMenu.h"

int main() {
    EasyMenu menu;
    menu.add.button("first button");
    menu.add.button("second button");

    switch (menu.run())
    {
    case 0: // clicked first button
        break;
    case 1: // clicked second button
        break;
    }
}
```
![2 buttons gif](docs/2%20buttons.gif)

You can also see examples (clickable).
- [are you ready](docs/are_you_ready.md)
- [authorization](docs/Authorization.md)
- [pizza order](docs/pizza_order.md)
- [comments](docs/comments.md)

# Functional Description
This step-by-step description explains the library *available functionality*

<details>
<summary><b>Run()</b></summary>

---
To start the created menu, use the `run()` method:
```cpp
menu.run();
```
The method returns an int value of the pressed button index. Some rules:
- Method returns the **index of clickable menu element** (text is not included in it
- The menu launch will be skipped if it does not contain at least one clickable element
- Recommended to having at least 1 button in the menu (for example, for exit or enter)
</details>

<details>
<summary><b>Buttons</b></summary>

---
To add a **button** to the menu, use the `add` sub-object, specifying the type of element being added (`button`)
```cpp
menu.add.button();
```

The method has **2 overloads**:
```cpp
add.button(string button_name)  // add button to the end
add.button(string button_name, int index)   // add button by index
```

Index is the ordinal number (starting from 0) of all elements in the menu.
- if index <= 0, the button will be **added to the beginning**
- if index >= count of elements, the button will be **added to the end**

You can also configure the `button` immediately upon creation by continuing to call fluent API methods in ony order:

![description buttons](docs/description%20buttons.gif)

Methods:
```cpp
.name(string new_name)
.color(int color_id)    // defined like: RED_COLOR, WHITE_COLOR...
.notification(string new_notification)
    .color(int color_id) // refers to the notification chain
```
</details>

<details>
<summary><b>Text</b></summary>

---
To add a **text** to the menu, use the `add` sub-object, specifying the type of element being added (`text`)
```cpp
menu.add.text();
```

The method has **2 overloads**:
```cpp
add.text(string text)  // add button to the end
add.text(string text, int index)   // add button by index
```

Index is the ordinal number (starting from 0) of all elements in the menu.
- if index <= 0, the *text* will be **added to the beginning**
- if index >= count of elements, the *text* will be **added to the end**

You can also configure the `text` immediately upon creation by continuing to call fluent API methods in ony order:

![description text](docs/description%20text.gif)

Methods:
```cpp
.text(string new_text)
.color(int color_id)    // defined like: RED_COLOR, WHITE_COLOR...
```
</details>

<details>
<summary><b>Checkboxes</b></summary>

---
To add a **checkbox** to the menu, use the `add` sub-object, specifying the type of element being added (`checkbox`)
```cpp
menu.add.checkbox();
```

The method has **2 overloads**:
```cpp
add.checkbox(string name, bool state = false)  // add checkbox to the end (with state (original = false))
add.checkbox(string name, int index, bool state = false)   // add checkbox by index (with state (original = false))
```

Index is the ordinal number (starting from 0) of all elements in the menu.
- if index <= 0, the *checkbox* will be **added to the beginning**
- if index >= count of elements, the *checkbox* will be **added to the end**

You can also configure the `checkbox` immediately upon creation by continuing to call fluent API methods in ony order:

![description checkboxes](docs/description%20checkboxes.gif)

Methods:
```cpp
.text(string new_text)
.color(int color_id)    // defined like: RED_COLOR, WHITE_COLOR...
.state(bool new_state)
.notification(string new_notification)
    .color(int color_id) // refers to the notification chain
```
</details>

<details>
<summary><b>Input</b></summary>

---
To add a **input** to the menu, use the `add` sub-object, specifying the type of element being added (`input`)
```cpp
menu.add.input();
```

The method has **2 overloads**:
```cpp
add.input(string name, string original_input = "")  // add input to the end (with original input (original = ""))
add.input(string name, int index, string original_input = "")   // add input by index (with original input (original = ""))
```

Index is the ordinal number (starting from 0) of all elements in the menu.
- if index <= 0, the *input* will be **added to the beginning**
- if index >= count of elements, the *input* will be **added to the end**

You can also configure the `input` immediately upon creation by continuing to call fluent API methods in ony order:

![description input](docs/description%20input.gif)

Methods:
```cpp
.name(string new_name)
.allowed(string allowed_str) // all allowed input symbols (can also take vector<char>)
.filter(bool new_state) // if true => not allowed symbols will be blocked
.length(int new_length) // max input length
.name_color(int color_id) // defined like: RED_COLOR, WHITE_COLOR...
.original_text(string new_text)
.secure(bool state) // if true => symbols will be hide (*)
.dictionary(EasyDict* dictionary_ptr) // read about EasyDict
.notification(string new_notification)
    .color(int color_id) // refers to the notification chain
```
</details>

<details>
<summary><b>Clear</b></summary>

---
To **remove 1 menu element**, use the `remove()` method.
- `.remove() // will remove back element`
- `.remove(int index) // will remove element by index`
  - if index <= 0, the **first element** will be removed
  - if index >= count of elements, the **last element** will be removed

To delete by criteria, you must use the `.clear` sub-object with a **selection of the type** of elements to be deleted:
```cpp
.all()  // delete all the menu
.info() // delete info
.notifications()    // delete all notifications
.text() // delete all text
```
</details>

<details>
<summary><b>Edit</b></summary>

---
To edit already created menu elements, you need to use the `.edit` sub-object with a **selection of the type** of object to be edited:
```cpp
.button(int index)
.text(int index)
.checkbox(int index)
.input(int index)
```
After which you can use any fluent API methods in any order.
</details>

<details>
<summary><b>Notifications</b></summary>

---
To manage **notifications**, you need to use the `.notifications` sub-object with an action selection:
```cpp
.add(string new_notification, int index)    // add notification by the index
.clear()    // will be delete all notifications
.color(int index, int color_id) // change notification color by index
.remove(int index) // delete notification by index 
```

Index is the ordinal number (starting from 0) of all elements in the menu.
- if index is not valud or points on element that can't have notification, method will be ignored
</details> 

<details>
<summary><b>Get</b> (<i>getting data</i>) </summary>

---
To retrieve data from a menu (input or checkbox elements), you must use the `.get` sub-object with a **selection of the type of information** to retrieve:
```cpp
.input() // returns vector<string> of all inputs
.input(int index) // returns string of input by index
.input_error() // returns vector<bool> of all inputs state (false if input have not allowed symbols)
.input_error(int index) // returns bool of input state by index (false if input have not allowed symbols)
.checkbox() // returns vector<bool> of all checkbox states
.checkbox() // returns bool of checkbox state by index
```
</details>

<details>
<summary><b>Style</b></summary>

---
To change the general menu data, use the .style sub-object with a choice of operation types:
```cpp
.basic_color    // default colors (when created)
    .button(int color_id)
    .checkbox(int color_id)
    .choise(int color_id)   // color of choise (by default choise display is disabled (can turn on in .style.settings.choise(true)))
    .correct_input(int color_id)    // color of correct symbols
    .uncorrct_input(int color_id)   // color of uncorrect symbols
    .pointer(int color_id)
    .text(int color_id)
.info
    .add(string new_info)
    .color(int color_id)
    .remove()
.settings
    .choise(bool state = false)
    .pointer(bool state = true) // if pointer = false choise will be automatically turned on
    .pointer_symbols(string new_pointer = "-->") // max length is 5
    .x_y_pos(int x, int y) // position of menu (by default (0, 0))
```
</details>