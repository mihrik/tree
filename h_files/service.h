#ifndef SERVICE_H
#define SERVICE_H

#include "tree.h"
#include <string.h>
#include "colors.h"
#include "ctype.h"

const int MAX_PHRASE_SIZE = 100;

int check_clear_buf(char *buffer);
error_codes args_analysis(int argc, const char * const argv[]);
int get_option(void);

#endif