#ifndef DUMP_H
#define DUMP_H
#include "tree.h"

const char * const PIC_NAME = "MEOW";
const char * const FNAME = "LOGFILE.html";
const int MAX_FILE_NAME_LEN = 40;
const int MAX_COMMAND_NAME_LEN = 120;

error_codes prepare_png(node_t *root, const char fname[]);
error_codes print_html(node_t *root, const char fname[], const char pic_name[]);
error_codes print_spears(node_t *root, FILE *png);

#endif