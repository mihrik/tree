#ifndef SERVICE_H
#define SERVICE_H

#include "tree.h"
#include <string.h>
#include "colors.h"
#include "ctype.h"

const int MAX_PHRASE_SIZE = 100;

typedef enum get_opt_mode
{
    Y_or_N = 1,
    ABCDEF = 2
} get_opt_mode;

int check_clear_buf(char *buffer);
error_codes args_analysis(int argc, const char * const argv[]);
int get_option(get_opt_mode mode);
void clear_buf(void);

#endif