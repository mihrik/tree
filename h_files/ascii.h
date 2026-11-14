#ifndef ASCII_H
#define ASCII_H

#include "tree.h"
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

void print_ascii(FILE *art_addres, int times);
void print_greeting(void);
void nice_output(const char *output);
void print_phrase(const char* const file_name);
void print_goodbye(void);

#endif