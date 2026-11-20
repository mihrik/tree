#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "colors.h"


const int MAX_DEFINE_LEN = 1000; // TODO TO ANOTHER .h
typedef char * node_elem_t;
const node_elem_t POISON = NULL;
#define deb_spec "%s"
const int MAX_PHRASE_LEN = 150;
const int MAX_AUDIO_MESSAGE_LEN = 150;

const char * const root_value = "Zhivotnoe?";

const node_elem_t ROOT_VALUE = NULL;

typedef enum error_codes
{
    SUCCESSFUL_RETURN             = 0,
    NULL_ROOT_MEANING             = 1,
    MEMORY_ALLOCATION_ERROR       = 2,
    INVALID_QUANTITY_OF_ARGUMENTS = 3,
    UNAVAILABLE_FILE              = 4,
    WRONG_DIRECTION               = 5,
    FILE_READING_ERROR            = 6,
    WRONG_TREE_STRUCTURE          = 7,
    VALUE_NOT_FOUND               = 8,
    OPEN_BRACKET_CASE             = 100
} error_codes;

typedef struct node_t
{
    node_elem_t value;
    node_t *left_child;
    node_t *right_child;
    node_t *parent;
} node_t;
// TODO mart play not readbale
typedef enum directions
{
    LEFT  = 0,
    RIGHT = 1
} directions;

#define SAY(...) {\
    char say_buffer[MAX_PHRASE_LEN] = {};\
    \
    sprintf(say_buffer, __VA_ARGS__);\
    fputs(say_buffer, stdout);\
    voice_message(say_buffer);\
}

error_codes play_akinator(const char * const argv[], node_t *root, FILE *fp);
error_codes node_ctor(node_t *root, node_elem_t value, directions dir);
error_codes node_dtor(node_t **node);
error_codes print_tree(FILE *fp, node_t *root);
error_codes tree_dtor(node_t *root);
error_codes akinator(node_t *node);
error_codes read_tree(FILE *fp, node_t *node, node_t *prev_node);
error_codes educate_akinator(node_t *node);
error_codes read_node(int file_char, FILE *fp, node_t *node);
error_codes draw_definition(node_t *node);
error_codes define(node_t *root, const char name[]);
error_codes compare(const char name1[], const char name2[], node_t *root);
node_t * find_value(node_t *root, const char name[]);
node_t * find_common(node_t *node1, node_t *node2);
void voice_message(const char message[]);
void draw_menu(void);

#endif