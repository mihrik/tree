#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int node_elem_t;
const node_elem_t POISON = 0x69696969;
#define deb_spec "%d"

const node_elem_t ROOT_VALUE = 50;
const char * const TREE_DATA_FILE = "txt_files/tree_data.txt";

typedef enum error_codes
{
    SUCCESSFUL_RETURN             = 0,
    NULL_ROOT_MEANING             = 1,
    MEMORY_ALLOCATION_ERROR       = 2,
    INVALID_QUANTITY_OF_ARGUMENTS = 3,
    UNAVAILABLE_FILE              = 4
} error_codes;

typedef struct node_t
{
    node_elem_t value;
    node_t *left_child;
    node_t *right_child;
    node_t *parent;
} node_t;

error_codes node_ctor(node_t *root, node_elem_t value);
error_codes node_dtor(node_t **node);
error_codes print_tree(FILE *fp, node_t *root);
error_codes tree_dtor(node_t *root);

#endif