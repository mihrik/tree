#include "h_files/tree.h"
#include "h_files/service.h"

error_codes node_ctor(node_t *root, node_elem_t value, directions dir)
{
    if (root == NULL)
        return NULL_ROOT_MEANING;

    node_t *tmp = (node_t *) calloc(1, sizeof(node_t));
    if (tmp == NULL)
        return MEMORY_ALLOCATION_ERROR;

    tmp->value = value;
    tmp->left_child = NULL;
    tmp->right_child = NULL;
    tmp->parent = root;

    switch(dir)
    {
        case LEFT :
                    {
                        root->left_child = tmp;

                        break;
                    }
        case RIGHT:
                    {
                        root->right_child = tmp;

                        break;
                    }
        default   : {
                        return WRONG_DIRECTION;
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
        fprintf(fp, " (");
        fprintf(fp, deb_spec, root->value);

        if (root->left_child)
            print_tree(fp, root->left_child);

        if (root->right_child)
            print_tree(fp, root->right_child);

        fprintf(fp, ")");
    }

    return SUCCESSFUL_RETURN;
}

error_codes akinator(node_t *node)
{
    printf(deb_spec "?\n", node->value);

    int answer = get_option();
    if (answer == 'y')
    {
//i love u baby
        if (node->left_child == NULL && node->right_child == NULL)
        {
            puts("I guessed. As always)");
            return SUCCESSFUL_RETURN;
        }
        else
        {
            akinator(node->left_child);
        }
    }
    else
    {
        if (node->left_child == NULL && node->right_child == NULL)
        {
                puts("What value are you looking for?");
                printf("Type it:");

                node_elem_t new_val = 0;
                node_elem_t old_val = node->value;

                scanf(deb_spec, &new_val);

                printf("What's the difference between " deb_spec " and " deb_spec "?\n", node->value,  new_val);

                scanf(deb_spec, &node->value);

                node_ctor(node, new_val, LEFT);
                node_ctor(node, old_val, RIGHT);

                return SUCCESSFUL_RETURN;
        }
        else
        {
            akinator(node->right_child);
        }
    }

    return SUCCESSFUL_RETURN;
}

error_codes read_tree(FILE *fp, node_t *node, node_t *prev_node)
{
    int file_char = 0;

    if ((file_char = getc(fp)) == EOF)
        return SUCCESSFUL_RETURN;
    ungetc(file_char, fp);

    node->parent = prev_node;

    while ((file_char = getc(fp)) != '(');

    fscanf(fp, deb_spec, &node->value);

    while (1)
    {
        while ((file_char = getc(fp)) == ' ');

        switch (file_char)
        {
            case EOF:
                        {
                            return SUCCESSFUL_RETURN;
                        }
            case '(':
                        {
                            ungetc(file_char, fp);
                            node_t *tmp = (node_t *) calloc(1, sizeof(node_t));
                            if (tmp == NULL)
                                return MEMORY_ALLOCATION_ERROR;

                            tmp->left_child = NULL;
                            tmp->right_child = NULL;
                            tmp->parent = NULL;


                            if (node->left_child == NULL)
                            {
                                node->left_child = tmp;
                                read_tree(fp, node->left_child, node);
                            }
                            else
                            {
                                node->right_child = tmp;
                                read_tree(fp, node->right_child, node);
                            }
                            break;
                        }
            case ')':
                        {
                            return SUCCESSFUL_RETURN;
                        }

        }
    }

    return SUCCESSFUL_RETURN;
}