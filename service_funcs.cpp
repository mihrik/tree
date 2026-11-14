#include "h_files/tree.h"
#include "h_files/service.h"

error_codes args_analysis(int argc, const char * const argv[])
{
    assert(argv);

    if (argc == 2)
    {
        return SUCCESSFUL_RETURN;
    }
    else
    {
        return INVALID_QUANTITY_OF_ARGUMENTS;
    }
}

int get_option(get_opt_mode mode)
{
    char phrase[MAX_PHRASE_SIZE] = {};
    bool read_successfully = false;
    bool wrong_condition = false;
    int ch = '\0';

    while (!read_successfully)
    {
        assert(fgets(phrase, MAX_PHRASE_SIZE, stdin));

        if (mode == Y_or_N)
            wrong_condition = (phrase[0] != tolower('y') && phrase[0] != tolower('n'));
        else if (mode == ABCDEF)
            wrong_condition = (phrase[0] != tolower('a') && phrase[0] != tolower('b') && phrase[0] != tolower('c') && phrase[0] != tolower('d') && phrase[0] != tolower('e') && phrase[0] != tolower('f'));

        if (wrong_condition)
        {
            phrase[strlen(phrase) - 1] = '\0';
            if (mode == Y_or_N)
            {
                PRINT_COLOR(RED, "%s не является допустимым вводом, введите y или n\n", phrase);
            }
            else if (mode == ABCDEF)
                PRINT_COLOR(RED, "%s не является допустимым вводом, введите a, b, c, d, e или f\n", phrase);
        }
        else
        {
            if (phrase[1] == '\n' || check_clear_buf(phrase + 1))
            {
                ch = phrase[0];
                read_successfully = true;
            }
            else
            {
                phrase[strlen(phrase) - 1] = '\0';
                if (mode == Y_or_N)
                {
                    PRINT_COLOR(RED, "%s не является допустимым вводом, введите y или n\n", phrase);
                }
                else if (mode == ABCDEF)
                    PRINT_COLOR(RED, "%s не является допустимым вводом, введите a, b, c, d, e или f\n", phrase);
            }
        }

    }

    return ch;
}

int check_clear_buf(char *buffer)
{
    assert(buffer);

    bool all_space = true;
    while (*buffer && *buffer != '\n')
    {
        if (*buffer != ' ')
        {
            all_space = false;
            break;
        }
        buffer++;
    }
    return all_space;
}

void clear_buf(void)
{
    while (getchar() != '\n');
}