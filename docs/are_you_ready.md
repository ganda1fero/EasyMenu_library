# "Are you ready" `example`

[go back](../README.md)
```cpp
#include "EasyMenu.h"

int main() {
    EasyMenu menu;

    menu.style.info.add("are you ready?");
    menu.add.button("yes").color(GREEN_COLOR);
    menu.add.button("no").color(RED_COLOR);

    menu.run(); // run menu (return clicked button index)
}
```
![are you ready gif](are%20you%20ready.gif)