#include "h_files/tree.h"
#include "h_files/service.h"
#include "h_files/dump.h"
#include <unistd.h>

#define nice_output puts

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
    free((*node)->value);
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
    free(root->value);
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

error_codes akinator(node_t *node)
{


    SAY(deb_spec "?\n", node->value);

    int answer = get_option(Y_or_N);
    if (answer == 'y')
    {
//i love u baby
        if (node->left_child == NULL && node->right_child == NULL)
        {
            SAY("Я угадал. Как и всегда!\n");
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
            educate_akinator(node);

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
    char user_input[MAX_PHRASE_LEN] = {};
    int file_char = 0;

    if ((file_char = getc(fp)) == EOF)
        return SUCCESSFUL_RETURN;
    ungetc(file_char, fp);

    node->parent = prev_node;

    while ((file_char = getc(fp)) != '(');

    fscanf(fp, "%[^()]", user_input);
    node->value = strdup(user_input);

    while ((file_char = getc(fp)) == ' ');

    if (file_char == EOF)
        return SUCCESSFUL_RETURN;

    if (file_char == '(')
    {
        ungetc(file_char, fp);

        if (node->left_child == NULL)
        {
            node_ctor(node, NULL, LEFT);
            read_tree(fp, node->left_child, node);
        }

        if (node->right_child == NULL)
        {
            node_ctor(node, NULL, RIGHT);
            read_tree(fp, node->right_child, node);
        }

        if ((file_char = getc(fp)) != ')')
            return WRONG_TREE_STRUCTURE;

        return SUCCESSFUL_RETURN;
    }

    return SUCCESSFUL_RETURN;
}

error_codes educate_akinator(node_t *node)
{
    char user_input[MAX_PHRASE_LEN] = {};

    SAY("Какой объект вы ищете?\n");
    SAY("Напишите здесь\n");

    node_elem_t new_val =  NULL;
    node_elem_t old_val = node->value;

    scanf(" %[^\n]" , user_input);

    new_val = strdup(user_input);

    SAY("Чем " deb_spec " отличается от " deb_spec "?", new_val, node->value);
    printf("<" deb_spec ">:", new_val);

    node_ctor(node, new_val, LEFT);
    node_ctor(node, old_val, RIGHT);

    scanf(" %[^\n]" , user_input);

    new_val = strdup(user_input);

    node->value = new_val;

    return SUCCESSFUL_RETURN;
}

error_codes draw_definition(node_t *node)
{
    if (node == NULL)
        return NULL_ROOT_MEANING;
    if (node->parent == NULL)
        return SUCCESSFUL_RETURN;

    if (node->parent->parent != NULL)
    {
        if (node == node->parent->right_child)
            SAY(" не %s и", node->parent->value)
        else
            SAY(" %s и", node->parent->value)
    }
    else
    {
        if (node == node->parent->right_child)
            SAY(" не %s.\n", node->parent->value)
        else
            SAY(" %s.\n", node->parent->value)
    }

    draw_definition(node->parent);

    return SUCCESSFUL_RETURN;
}

node_t * find_value(node_t *root, const char name[])
{
    if (root == NULL)
        return NULL;

    if (strcmp(root->value, name) == 0)
    {
        return root;
    }
    else if (root->left_child && root->right_child)
    {
        node_t *search_left  = find_value(root->left_child, name);
        node_t *search_right = find_value(root->right_child, name);

        if (search_left)
            return search_left;

        else if(search_right)
            return search_right;

        else
            return NULL;
    }
    else
        return NULL;
}

error_codes define(node_t *root, const char name[])
{
    if (root == NULL)
        return NULL_ROOT_MEANING;

    SAY("%s -", name);

    if (draw_definition(find_value(root, name)) != SUCCESSFUL_RETURN)
        SAY(" не найдено.\n");

    return SUCCESSFUL_RETURN;
}

error_codes compare(const char name1[], const char name2[], node_t *root)
{
    node_t *node1 = find_value(root, name1);

    if (node1 == NULL)
    {
        SAY("%s - не найдено.\n", name1);
        return VALUE_NOT_FOUND;
    }

    node_t *node2 = find_value(root, name2);

    if (node2 == NULL)
    {
        SAY("%s - не найдено.\n", name2);
        return VALUE_NOT_FOUND;
    }

    node_t *common_node = find_common(node1, node2);
    if (common_node == NULL)
    {
        SAY("%s и %s не имеют ничего общего.\n", name1, name2);
        return SUCCESSFUL_RETURN;
    }

    SAY("%s и %s - оба", name1, name2);
    draw_definition(common_node);

    return SUCCESSFUL_RETURN;
}

node_t * find_common(node_t *node1, node_t *node2)
{
    if (node1 == NULL || node2 == NULL || node1->parent == NULL)
        return NULL;

    if (find_value(node1, node2->value) != NULL)
        return node1;

    return find_common(node1->parent, node2);
}

void voice_message(const char message[])
{
    char to_voice[MAX_AUDIO_MESSAGE_LEN] = {};

    sprintf(to_voice, "echo \"%s\" | festival --language russian --tts", message);

    system(to_voice);
}

error_codes play_akinator(const char * const argv[], node_t *root, FILE *fp)
{
    int option = 0;

    draw_menu();
    while ((option = get_option(ABCDEF)) != 'f')
    {
        switch (option)
        {
            case 'a':
                     {
                          print_tree(stdout, root);
                          putchar('\n');

                          break;
                     }
            case 'b':
                     {
                          akinator(root);

                          break;
                     }
            case 'c':
                     {
                          print_tree(fp, root);
                          print_html(root, FNAME, PIC_NAME);

                          system("firefox LOGFILE.html");
                          puts("Просмотр дерева завершён");

                          break;
                     }
            case 'd':
                     {
                          char user_input[MAX_AUDIO_MESSAGE_LEN] = {};
                          SAY("Напишите название объекта, который хотите определить\n");

                          scanf("%[^\n]", user_input);
                          clear_buf();
                          define(root, user_input);

                          break;
                     }
            case 'e':
                     {
                          char user_input1[MAX_AUDIO_MESSAGE_LEN] = {};
                          char user_input2[MAX_AUDIO_MESSAGE_LEN] = {};

                          SAY("Напишите название первого объекта\n");
                          scanf("%[^\n]", user_input1);
                          clear_buf();

                          SAY("Напишите название второго объекта\n");
                          scanf("%[^\n]", user_input2);
                          clear_buf();

                          compare(user_input1, user_input2, root);

                          break;
                     }
            default :
                     {
                          PRINT_COLOR(EXTRA_RED, "Неизвестная команда\n");

                          exit(0);
                     }
        }

        draw_menu();
    }

    fp = fopen(argv[1], "w");
    if (fp == NULL)
        return FILE_READING_ERROR;

    return SUCCESSFUL_RETURN;
}

void draw_menu(void)
{
    puts("                                              ===Игровое меню===\n\n");
    PRINT_COLOR(RED, "                                          a) Показать базу данных программы.\n");
    PRINT_COLOR(ORANGE, "                                          b) Запустить акинатора.\n");
    PRINT_COLOR(YELLOW, "                                          c) Визуализация базы данных.\n");
    PRINT_COLOR(GREEN, "                                          d) Определение названия.\n");
    PRINT_COLOR(BLUE, "                                          e) Сравнить два названия.\n");
    PRINT_COLOR(PURPLE, "                                          f) Выйти из игры.\n\n");
}