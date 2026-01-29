# "Pizza order" `example`
[![go back](https://img.shields.io/badge/go%20back-white?style=flat&logo=windows)](../README.md)
```cpp
#include "EasyMenu.h"

int main() {
    EasyMenu menu;

    menu.style.info.add("Create order");		// markup index = - | butt index = - (it's info)
    menu.add.text("some pizza")
    .color(WHITE_COLOR);					// markup index = 0 | but index = - (text doesn't clickable)
    menu.add.checkbox("extra cheese");			// markup index = 1 | but index = 0
    menu.add.checkbox("pickles");				// markup index = 2 | but index = 1
    menu.add.checkbox("tomatos", true);			// markup index = 3 | but index = 2
    menu.add.button("make order");				// markup index = 4 | but index = 3
    menu.add.button("back").color(BLUE_COLOR);	// markup index = 5 | but index = 4

    bool is_run = true;
    while (is_run) {
        switch (menu.run())
        {
        case 3:
            menu.notification.add("processing...", 4).color(GREEN_COLOR);
            menu.get.checkbox();	// get vector<bool> of all checkboxes
            break;
        case 4:
            is_run = false;
            break;
        }
    }
}
```
![pizza order gif](pizza%20order.gif)