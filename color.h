
#ifndef COLOR_H
#define COLOR_H

#include <ostream>

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
