#include "h_files/tree.h"

error_codes node_ctor(node_t *root, node_elem_t value)
{
    if (root == NULL)
        return NULL_ROOT_MEANING;

    node_t *tmp = (node_t *) calloc(1, sizeof(node_t));
    if (tmp == NULL)
        return MEMORY_ALLOCATION_ERROR;

    tmp->value = value;
    tmp->left_child = NULL;
    tmp->right_child = NULL;

    node_t **parent = &root;

    while (1)
    {
        if (value < (*parent)->value)
        {
            if ((*parent)->left_child == NULL)
            {
                (*parent)->left_child = tmp;
                tmp->parent = *parent;
                break;
            }

            parent = &(*parent)->left_child;
        }
        else
        {
            if ((*parent)->right_child == NULL)
            {
                (*parent)->right_child = tmp;
                tmp->parent = *parent;
                break;
            }

            parent = &(*parent)->right_child;
        }
    }

    return SUCCESSFUL_RETURN;
}

error_codes node_dtor(node_t **node)
{
    assert(node);

    if ((*node) == NULL)
        return SUCCESSFUL_RETURN;

    node_dtor(&(*node)->left_child);
    node_dtor(&(*node)->right_child);

    (*node)->parent = NULL;
    (*node)->value  = POISON;

    node_t *tmp = *node;
    *node = NULL;
    free(tmp);

    return SUCCESSFUL_RETURN;
}

error_codes tree_dtor(node_t *root)
{
    assert(root);

    if (root == NULL)
        return NULL_ROOT_MEANING;

    if (root->left_child)
        node_dtor(&root->left_child);

    if (root->right_child)
        node_dtor(&root->right_child);

    root->left_child = NULL;
    root->right_child = NULL;
    root->parent = NULL;
    root->value = POISON;

    return SUCCESSFUL_RETURN;
}

error_codes print_tree(FILE *fp, node_t *root)
{
    assert(fp);

    if (root != NULL)
    {
        fprintf(fp, "(");
        fprintf(fp, deb_spec, root->value);

        if (root->left_child)
            print_tree(fp, root->left_child);

        if (root->right_child)
            print_tree(fp, root->right_child);

        fprintf(fp, ")");
    }

    return SUCCESSFUL_RETURN;
}