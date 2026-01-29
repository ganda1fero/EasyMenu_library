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

- [![are you ready](https://img.shields.io/badge/are%20you%20ready-white?style=flat&logo=windows)](docs/are_you_ready.md)
- [![authorization](https://img.shields.io/badge/authorization-white?style=flat&logo=windows)](docs/Authorization.md)
- [![pizza order](https://img.shields.io/badge/pizza%20order-white?style=flat&logo=windows)](docs/pizza_order.md)
- [![comments](https://img.shields.io/badge/comments-white?style=flat&logo=windows)](docs/comments.md)

# Functional Description
This step-by-step description explains the *available functionality*

<details>
<summary> Run() </summary>

</details>
<details>
<summary> Buttons </summary>

</details>

<details>
<summary> Text </summary>

</details>

<details>
<summary> Checkboxes </summary>

</details>

<details>
<summary> Input </summary>

</details>

<details>
<summary> Clear </summary>

</details>

<details>
<summary> Edit </summary>

</details>

<details>
<summary> Notifications </summary>

</details> 

<details>
<summary> Get (<i>getting data</i>) </summary>

</details>

