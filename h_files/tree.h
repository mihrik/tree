#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef char * node_elem_t;
const node_elem_t POISON = NULL;
#define deb_spec "%s"
const int MAX_PHRASE_LEN = 50;

const char * const root_value = "Zhivotnoe?";

const node_elem_t ROOT_VALUE = NULL;
const char * const TREE_DATA_FILE = "txt_files/tree_data.txt";

typedef enum error_codes
{
    SUCCESSFUL_RETURN             = 0,
    NULL_ROOT_MEANING             = 1,
    MEMORY_ALLOCATION_ERROR       = 2,
    INVALID_QUANTITY_OF_ARGUMENTS = 3,
    UNAVAILABLE_FILE              = 4,
    WRONG_DIRECTION               = 5
} error_codes;

typedef struct node_t
{
    node_elem_t value;
    node_t *left_child;
    node_t *right_child;
    node_t *parent;
} node_t;

typedef enum directions
{
    LEFT  = 0,
    RIGHT = 1
} directions;

error_codes node_ctor(node_t *root, node_elem_t value, directions dir);
error_codes node_dtor(node_t **node);
error_codes print_tree(FILE *fp, node_t *root);
error_codes tree_dtor(node_t *root);
error_codes akinator(node_t *node);
error_codes read_tree(FILE *fp, node_t *node, node_t *prev_node);

#endif