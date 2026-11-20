#ifndef COLORS_H
#define COLORS_H

#define RED_ "\033[91m"
#define EXTRA_RED__ "\033[31m"
#define GREEN_ "\033[92m"
#define ORANGE_ "\033[33m"
#define BLUE_ "\033[94m"
#define YELLOW_ "\033[93m"
#define PURPLE_ "\033[95m"
#define EXTRA_BLUE_ "\033[34m"
#define LIGHT_BLUE_ "\033[96m"
#define EXTRA_GREEN_ "\033[32m"
#define RESET_COLOR "\033[0m"
#define BOLD_BLUE_ "\033[94;1m"
#define BOLD_RED_ "\033[91;1m"
#define PRINT_COLOR(x, ...)  {    \
    printf(x __VA_ARGS__);        \
    printf(RESET_COLOR);          \
}

#endif