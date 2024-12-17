
#ifndef COLOR_H
#define COLOR_H

#include <ostream>

/*
ANSI Color Table with Brightness:

Color          | Color Code | Normal           | Bright            | Dim
-------------- | ---------- | ---------------- | ----------------- | ----------------
Black          | 30         | \x1b[30;22m     | \x1b[30;1m       | \x1b[30;2m
Red            | 31         | \x1b[31;22m     | \x1b[31;1m       | \x1b[31;2m
Green          | 32         | \x1b[32;22m     | \x1b[32;1m       | \x1b[32;2m
Yellow         | 33         | \x1b[33;22m     | \x1b[33;1m       | \x1b[33;2m
Blue           | 34         | \x1b[34;22m     | \x1b[34;1m       | \x1b[34;2m
Purple         | 35         | \x1b[35;22m     | \x1b[35;1m       | \x1b[35;2m
Cyan           | 36         | \x1b[36;22m     | \x1b[36;1m       | \x1b[36;2m
White          | 37         | \x1b[37;22m     | \x1b[37;1m       | \x1b[37;2m
*/


namespace Color {
    enum Code {
        FG_RED      = 31,
        FG_GREEN    = 32,
        FG_YELLOW   = 33,
        FG_BLUE     = 34,
        FG_DEFAULT  = 39,
        FG_MAGENTA  = 35,
        BG_RED      = 41,
        BG_GREEN    = 42,
        BG_BLUE     = 44,
        BG_MAGENTA  = 45,
        BG_DEFAULT  = 49,
        RESET       = 0,
        BOLD        = 1
    };
    class Modifier {
            Code code;
        public:
            Modifier(Code pCode) : code(pCode) {}
            friend std::ostream&
            operator<<(std::ostream& os, const Modifier& mod) {
                return os << "\033[" << std::to_string( mod.code ) << "m";
            }
    };

    static Color::Modifier red(Color::FG_RED);
    static Color::Modifier bg_red(Color::BG_RED);
    static Color::Modifier green(Color::FG_GREEN);
    static Color::Modifier yellow(Color::FG_YELLOW);
    static Color::Modifier blue(Color::FG_BLUE);
    static Color::Modifier bg_blue(Color::BG_BLUE);
    static Color::Modifier magenta(Color::FG_MAGENTA);
    static Color::Modifier bg_magenta(Color::BG_MAGENTA);
    static Color::Modifier def(Color::FG_DEFAULT);
    static Color::Modifier reset(Color::RESET);
    static Color::Modifier bold(Color::BOLD);

}


#endif
