#include "../h_files/raylib_f.h"


// ---------------------------------------------------------------------------------------------------------------------

int video_play_akinator(node_t *root)
{
    InitWindow(800, 700, "Akinator");
    SetTargetFPS(60);

    int codepoints[351] = {};
    int cnt = 0;

    node_t *start_root = root;
    node_t *cur_root = root;
    node_t *root2 = root;

    for (size_t i = 32; i <= 126; i++)
        codepoints[cnt++] = (int)i;

    for (size_t i = 0x0400; i <= 0x04FF; i++)
        codepoints[cnt++] = (int)i;

    Font font = LoadFontEx("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 30, codepoints, cnt);


    InitAudioDevice();
    Music song = LoadMusicStream("Music Full.mp3");
    PlayMusicStream(song);

    Texture2D picture = LoadTexture("Logo_akinator.png");
    Texture2D tree = {};

    bool *button_on = (bool *) calloc(10, sizeof(bool));
    bool first_word_get = false;
    bool second_word_get = false;
    char *definition1 = (char *) calloc(MAX_DEFINE_LEN, sizeof(char));
    char *definition2 = (char *) calloc(MAX_DEFINE_LEN, sizeof(char));
    int *akinator_stages = (int *) calloc(5, sizeof(int));
    char *user_input = (char *) calloc(MAX_PHRASE_LEN, sizeof(char));
    char *output = (char *) calloc(MAX_PHRASE_LEN * 2, sizeof(char));
    size_t cur_input_index = 0;

    char *text = LoadFileText("txt_files/tree_data.txt");

    FILE *png = NULL;

    size_t button_cnt = 0;
    int pic_num = 0;

    button_t buttons[BUTTON_QUANTITY + 1] = {};
    buttons[SHOW_DATA_BASE] = set_button(100, 200, BUTTON_LENGTH, BUTTON_HEIGHT, "Просмотреть базу данных");
    buttons[PLAY_AKINATOR]  = set_button(450, 200, BUTTON_LENGTH, BUTTON_HEIGHT, "Запустить игру");
    buttons[CHECK_TREE]     = set_button(100, 350, BUTTON_LENGTH, BUTTON_HEIGHT, "Просмотреть дерево");
    buttons[DEFINE]         = set_button(450, 350, BUTTON_LENGTH, BUTTON_HEIGHT, "Дать определение");
    buttons[COMPARE]        = set_button(100, 500, BUTTON_LENGTH, BUTTON_HEIGHT, "Сравнить объекты");
    buttons[COOL_PHRASE]    = set_button(450, 500, BUTTON_LENGTH, BUTTON_HEIGHT, "Мишаня крут");
    buttons[BUTTON_QUANTITY]= {};

    while (!WindowShouldClose())
    {
        UpdateMusicStream(song);

        Vector2 touch = GetTouchPosition(0);

        int active_button = get_button(buttons, touch, button_on);

        choose_game_mode(&button_cnt, &cur_root, start_root, picture, font, &output, &cur_input_index, &definition1, &definition2, &button_on, &first_word_get, &second_word_get, &user_input, text, active_button, touch, &akinator_stages, &png, &tree, &pic_num, &root2, buttons);

        EndDrawing();
    }

    free(button_on);
    free(definition2);
    free(definition1);
    free(akinator_stages);
    free(user_input);
    free(output);
    UnloadFont(font);
    StopMusicStream(song);
    UnloadMusicStream(song);
    UnloadTexture(picture);
    CloseWindow();
    UnloadFileText(text);
    CloseAudioDevice();

    return 0;
}

//------------------------------------------------------------------------------------------

void exec_first_opt(bool **button_on, Texture2D picture, Font font, char text[])
{
    *button_on[0] = true;

    BeginDrawing();

    ClearBackground(YELLOW);
    DrawTexture(picture, 400 - picture.width / 2, 50, WHITE);

    DrawTextEx(font, text, {20, 300}, 20, 1, BLACK);

    if (IsKeyPressed(KEY_X))
    {
        *button_on[0] = false;
    }
}

void common_akinator_case(node_t **cur_root, size_t *button_cnt, Font font, Vector2 touch)
{
    char phrase[MAX_PHRASE_LEN] = {};
    snprintf(phrase, sizeof(phrase), "Тот, кого вы загадали %s?", (*cur_root)->value);

    DrawRectangle(100, 350, 250, 100, GOLD);
    DrawRectangle(450, 350, 250, 100, GOLD);


    DrawTextEx(font, phrase, {100, 200}, 30, 1, BLACK);
    DrawTextEx(font, "Да", {550, 380}, 30, 1, BLACK);
    DrawTextEx(font, "Нет", {200, 380}, 30, 1, BLACK);

    if (*button_cnt == 2)
        voice_message(phrase);

    if ((touch.x >= 100 && touch.x <= 350 && touch.y <= 450 && touch.y >= 350) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        *cur_root = (*cur_root)->right_child;
        *button_cnt = 0;
    }
    else if ((touch.x >= 450 && touch.x <= 700 && touch.y <= 450 && touch.y >= 350 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)))
    {
        *cur_root = (*cur_root)->left_child;
        *button_cnt = 0;
    }
}

void leaf_akinator_case(node_t *start_root, node_t **cur_root, Font font, size_t *button_cnt, bool **button_on, Vector2 touch, int **akinator_stages)
{
    char phrase[MAX_PHRASE_LEN] = {};
    snprintf(phrase, sizeof(phrase), "Вы загадали %s?", (*cur_root)->value);

    if ((*akinator_stages)[0] == 0)
    {
        DrawRectangle(100, 350, 250, 100, GOLD);
        DrawRectangle(450, 350, 250, 100, GOLD);
        DrawTextEx(font, phrase, {100, 200}, 30, 1, BLACK);
        DrawTextEx(font, "Да", {550, 380}, 30, 1, BLACK);
        DrawTextEx(font, "Нет", {200, 380}, 30, 1, BLACK);
    }

    if (*button_cnt == 2)
        voice_message(phrase);

    if ((touch.x >= 100 && touch.x <= 350 && touch.y <= 450 && touch.y >= 350) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        cur_root = NULL;
        *button_cnt = 0;
        (*akinator_stages)[1] = true;
    }
    else if ((touch.x >= 450 && touch.x <= 700 && touch.y <= 450 && touch.y >= 350 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) || (*akinator_stages)[0] > 0)
    {
        (*akinator_stages)[0] += 1;

        if ((*akinator_stages)[0] > 1)
        {
            if ((*akinator_stages)[0] == 2)
                DrawTextEx(font, "Я угадал, как и всегда!", {100, 200}, 30, 1, BLACK);

            if ((*akinator_stages)[0] == 3)
            {
                DrawTextEx(font, "Я угадал, как и всегда!", {100, 200}, 30, 1, BLACK);
                voice_message("Я угадал, как и всегда!");

                (*akinator_stages)[0] = 0;
                *cur_root = (node_t *)start_root;
                (*button_on)[1] = false;
                *button_cnt = 0;
            }
        }
    }
}

void common_menu(Texture2D picture, Font font, button_t buttons[])
{
    BeginDrawing();

    ClearBackground(YELLOW);
    DrawTexture(picture, 400 - picture.width / 2, 50, WHITE);

    size_t i = 0;

    while (!(is_zero(buttons[i].start_x) && is_zero(buttons[i].end_x) && is_zero(buttons[i].start_y) && is_zero(buttons[i].end_y)))
    {
        draw_button(buttons[i++], font);
    }
}

void word_asking(bool *first_word_get, Font font, size_t *cur_input_index, Texture2D picture, char **user_input, char **definition1, size_t *button_cnt)
{
    if (!(*first_word_get))
    {
        DrawTextEx(font, "Напишите слово, которое хотите определить", {100, 200}, 25, 1, BLACK);
        if (*button_cnt == 3)
            voice_message("Напишите слово, которое хотите определить");

        int elem = GetCharPressed();
        if (elem != 0)
        {
            int bytes = 0;
            const char *utf8 = CodepointToUTF8(elem, &bytes);

            if (*cur_input_index + (size_t)bytes < MAX_PHRASE_LEN)
            {
                memcpy(*user_input + *cur_input_index, utf8, (size_t)bytes);
                *cur_input_index += (size_t)bytes;
                (*user_input)[*cur_input_index] = '\0';
            }
        }
        if (IsKeyPressed(KEY_BACKSPACE) && *cur_input_index > 0)
        {
            do
            {
                --(*cur_input_index);
            }
            while (*cur_input_index > 0 && ((unsigned char)(*user_input)[*cur_input_index] & 0xC0) == 0x80);

            (*user_input)[*cur_input_index] = '\0';
        }
        if (IsKeyPressed(KEY_ENTER))
        {
           strcpy(*definition1, *user_input);

            *first_word_get = true;
            for (size_t i = 0; i < MAX_PHRASE_LEN; i++)
                (*user_input)[i] = '\0';
            *cur_input_index = 0;
            *button_cnt = 0;
        }

        ClearBackground(YELLOW);
        DrawTexture(picture, 400 - picture.width / 2, 50, WHITE);
        DrawTextEx(font, *user_input, {100, 500}, 30, 1, BLACK);
    }
}

void not_found(bool *first_word_get, bool **button_on, Texture2D picture, Font font, char *output, size_t *button_cnt)
{
    ClearBackground(YELLOW);
    DrawTexture(picture, 400 - picture.width / 2, 50, WHITE);
    DrawTextEx(font, output, {300, 400}, 30, 1, BLACK);

    if (*button_cnt == 3)
        voice_message(output);

    if (*button_cnt == 180)
    {
        (*button_on)[3] = false;
        (*button_on)[4] = false;
        *button_cnt = 0;
        *output = {};
        *first_word_get = false;
    }
}

void make_definition(node_t *cur_node, char **output, size_t *cur_input_index)
{
    char buffer[MAX_PHRASE_LEN] = {};

    if (cur_node == NULL)
        return;
    if ((cur_node)->parent == NULL)
        return;

    if ((cur_node)->parent->parent != NULL)
    {
        if ((cur_node) == (cur_node)->parent->right_child)
        {
            sprintf(buffer, " не %s и", (cur_node)->parent->value);
            strcat(*output, buffer);
        }
        else
        {
            sprintf(buffer, " %s и", (cur_node)->parent->value);
            strcat(*output, buffer);
        }
    }
    else
    {
        if ((cur_node) == (cur_node)->parent->right_child)
        {
            sprintf(buffer, " не %s.\n", (cur_node)->parent->value);
            strcat(*output, buffer);
        }
        else
        {
            sprintf(buffer, " %s.\n", (cur_node)->parent->value);
            strcat(*output, buffer);
        }
    }

    make_definition(cur_node->parent, output, cur_input_index);
}

button_t set_button(float start_x, float start_y, float size_x, float size_y, const char label[])
{
    button_t button = {};

    button.start_x = start_x;
    button.start_y = start_y;
    button.end_x   = start_x + size_x;
    button.end_y   = start_y + size_y;
    button.label   = label;

    return button;
}

bool in_button(button_t button, Vector2 touch)
{
    if (touch.x >= button.start_x && touch.x <= button.end_x && touch.y >= button.start_y && touch.y <= button.end_y && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        return true;

    return false;
}

void draw_button(button_t button, Font font)
{
    Vector2 text_par = MeasureTextEx(font, button.label, 19, 1);
    DrawRectangle((int)button.start_x, (int)button.start_y, (int)(button.end_x - button.start_x), (int)(button.end_y - button.start_y), GOLD);
    DrawTextEx(font, button.label, {button.start_x + (button.end_x - button.start_x - text_par.x) / 2, button.start_y + (button.end_y - button.start_y - text_par.y) / 2} , 19, 1, WHITE);
}

bool is_zero(float num)
{
    return num < EPSILON;
}

int get_button(button_t buttons[], Vector2 touch, bool button_on[])
{
    int i = 0;

    while (!(is_zero(buttons[i].start_x) && is_zero(buttons[i].end_x) && is_zero(buttons[i].start_y) && is_zero(buttons[i].end_y)))
    {
        if (in_button(buttons[i], touch) || button_on[i])
        {
            return i;
        }

        i++;
    }

    return 666;
}

void check_tree_first_click(FILE **png, int *pic_num, node_t *start_root, Texture2D *tree)
{
    *png = fopen(FNAME, "w+");

    (*pic_num)++;

    char pic_file_name[MAX_FILE_NAME_LEN] = {};
    sprintf(pic_file_name, "txt_files/%s%d.txt", PIC_NAME, *pic_num);

    char png_file_name[MAX_FILE_NAME_LEN] = {};
    sprintf(png_file_name, "png_files/%s%d.png", PIC_NAME, *pic_num);

    prepare_png(start_root, pic_file_name);
    char system_command[MAX_COMMAND_NAME_LEN] = {};
    sprintf(system_command, "dot %s -Tpng -o %s", pic_file_name, png_file_name);
    system(system_command);

    *tree = LoadTexture(png_file_name);
}

void check_tree_next_clicks(Texture2D picture, Font font, char definition1[], Texture2D *tree, FILE **png, char output[], size_t *button_cnt, bool **button_on)
{
    BeginDrawing();

    ClearBackground(YELLOW);
    DrawTexture(picture, 400 - picture.width / 2, 50, WHITE);
    DrawTextEx(font, definition1, {300, 300}, 30, 1, BLACK);
    DrawTextEx(font, output, {100, 500}, 30, 1, BLACK);
    DrawTexture(*tree, 150 , 200, WHITE);

    if (IsKeyPressed(KEY_X))
    {
        fclose(*png);
        UnloadTexture(*tree);
        *button_cnt = 0;
        (*button_on)[2] = false;
    }
}

void exec_third_opt(Texture2D picture, Font font, char definition1[], Texture2D *tree, FILE **png, char output[], size_t *button_cnt, bool **button_on, int *pic_num, node_t *start_root)
{
    (*button_on)[2] = true;

    if (*button_cnt == 1)
    {
        check_tree_first_click(png, pic_num, start_root, tree);
    }
    else
    {
        check_tree_next_clicks(picture, font, definition1, tree, png, output, button_cnt, button_on);
    }

    (*button_cnt)++;
}

void exec_second_opt(bool **button_on, Texture2D picture, node_t **cur_root, size_t *button_cnt, Font font, Vector2 touch, node_t *start_root, int **akinator_stages)
{
    (*button_on)[1] = true;

    BeginDrawing();

    ClearBackground(YELLOW);
    DrawTexture(picture, 400 - picture.width / 2, 50, WHITE);

    bool common_node = (*cur_root != NULL && (*cur_root)->left_child != NULL && (*cur_root)->right_child != NULL);
    bool leaf = (*cur_root != NULL && (*cur_root)->left_child == NULL && (*cur_root)->right_child == NULL);

    if (common_node)
    {
        common_akinator_case(cur_root, button_cnt, font, touch);
    }
    else if (leaf)
    {
        leaf_akinator_case(start_root, cur_root, font, button_cnt, button_on, touch, akinator_stages);
    }

    (*button_cnt)++;
}

void exec_sixth_opt(bool **button_on, Texture2D picture, Font font)
{
    (*button_on)[5] = true;

    BeginDrawing();

    ClearBackground(YELLOW);

    DrawTexture(picture, 400 - picture.width / 2, 50, WHITE);
    DrawTextEx(font, "И это правда блин", {300, 300}, 30, 1, BLACK);

    if (IsKeyPressed(KEY_X))
    {
        (*button_on)[5] = false;
    }
}

void compare_first_frame(node_t *start_root, char definition1[], char *definition2, node_t **cur_root, node_t **root2)
{
    *cur_root = find_value(start_root, definition1);
    *root2 = find_value(start_root, definition2);
}

void compare_word_not_exist(size_t *button_cnt, char **output, char **definition1, char **definition2, bool *first_word_get, bool *second_word_get, bool **button_on, Texture2D picture, Font font)
{
    if (*button_cnt == 1)
    {
        strcpy(*output, *definition1);
        strcat(*output, " - не найдено");
    }
    not_found(first_word_get, button_on, picture, font, *output, button_cnt);

    if (*button_cnt == 0)
    {
        *second_word_get = false;
        for (size_t i = 0; i < MAX_DEFINE_LEN; i++)
            (*definition1)[i] = '\0';
        for (size_t i = 0; i < MAX_DEFINE_LEN; i++)
            (*definition2)[i] = '\0';
    }
}

void compare_all_good(node_t **cur_root, size_t *button_cnt, node_t **root2, char **output, size_t *cur_input_index, Texture2D picture, Font font, char **definition1, char **definition2, bool **button_on, bool *first_word_get, bool *second_word_get, node_t *start_root)
{
    if (*button_cnt == 1)
    {
        *cur_root = find_common(*cur_root, *root2);
        make_definition(*cur_root, output, cur_input_index);
    }

    ClearBackground(YELLOW);
    DrawTexture(picture, 400 - picture.width / 2, 50, WHITE);
    char buffer[MAX_DEFINE_LEN * 3] = {};
    strcat(buffer, *definition1);
    strcat(buffer, " и ");
    strcat(buffer, *definition2);
    strcat(buffer, " - оба");
    strcat(buffer, *output);
    DrawTextEx(font, buffer, {100, 500}, 30, 1, BLACK);

    if (*button_cnt == 2)
        voice_message(buffer);

    if (*button_cnt == 180)
    {
        (*button_on)[4] = false;
        *button_cnt = 0;
        for (size_t i = 0; i < MAX_PHRASE_LEN * 2; i++)
            (*output)[i] = '\0';
        *first_word_get = false;
        *second_word_get = false;
        *cur_root = start_root;
        *root2 = start_root;
        for (size_t i = 0; i < MAX_DEFINE_LEN; i++)
            (*definition1)[i] = '\0';
        for (size_t i = 0; i < MAX_DEFINE_LEN; i++)
            (*definition2)[i] = '\0';
    }
}

void exec_fifth_opt(node_t **cur_root, size_t *button_cnt, node_t **root2, char **output, size_t *cur_input_index, Texture2D picture, Font font, char **definition1, char **definition2, bool **button_on, bool *first_word_get, bool *second_word_get, node_t *start_root, char **user_input)
{
    (*button_on)[4] = true;

    BeginDrawing();

    if (!(*first_word_get))
    {
        word_asking(first_word_get, font, cur_input_index, picture, user_input, definition1, button_cnt);
    }
    else if (!(*second_word_get))
    {
        word_asking(second_word_get, font, cur_input_index, picture, user_input, definition2, button_cnt);
    }
    else
    {
        if (*button_cnt == 1)
        {
            compare_first_frame(start_root, *definition1, *definition2, cur_root, root2);
        }

        if (*cur_root == NULL)
        {
            compare_word_not_exist(button_cnt, output, definition1, definition2, first_word_get, second_word_get, button_on, picture, font);
        }
        else if (*root2 == NULL)
        {
            compare_word_not_exist(button_cnt, output, definition2, definition1, second_word_get, first_word_get, button_on, picture, font);
        }
        else
        {
            compare_all_good(cur_root, button_cnt, root2, output, cur_input_index, picture, font, definition1, definition2, button_on, first_word_get, second_word_get, start_root);
        }
    }

    (*button_cnt)++;
}

void define_all_good(size_t *button_cnt, node_t **cur_root, node_t *start_root, Texture2D picture, Font font, char **output, size_t *cur_input_index, char **definition1, bool **button_on, bool *first_word_get)
{
    if (*button_cnt == 1)
    {
        make_definition(*cur_root, output, cur_input_index);
    }

    ClearBackground(YELLOW);
    DrawTexture(picture, 400 - picture.width / 2, 50, WHITE);
    DrawTextEx(font, *definition1, {300, 300}, 30, 1, BLACK);
    DrawTextEx(font, *output, {100, 500}, 30, 1, BLACK);

    if (*button_cnt == 2)
        voice_message(*output);

    if (*button_cnt == 180)
    {
        (*button_on)[3] = false;
        *button_cnt = 0;
        for (size_t i = 0; i < MAX_PHRASE_LEN * 2; i++)
            (*output)[i] = '\0';
        *first_word_get = false;
        *cur_root = start_root;
        for (size_t i = 0; i < MAX_DEFINE_LEN; i++)
            (*definition1)[i] = '\0';

    }
}

void exec_fourth_opt(size_t *button_cnt, node_t **cur_root, node_t *start_root, Texture2D picture, Font font, char **output, size_t *cur_input_index, char **definition1, bool **button_on, bool *first_word_get, char **user_input)
{
    (*button_on)[3] = true;

    BeginDrawing();

    if (!(*first_word_get))
    {
        word_asking(first_word_get, font, cur_input_index, picture, user_input, definition1, button_cnt);
    }
    else
    {
        if (*button_cnt == 1)
        {
            *cur_root = find_value(start_root, *definition1);
        }

        if (*cur_root == NULL)
        {
            if (*button_cnt == 1)
            {
                strcpy(*output, *definition1);
                strcat(*output, " - не найдено");
            }
            not_found(first_word_get, button_on, picture, font, *output, button_cnt);
        }
        else
        {
            define_all_good(button_cnt, cur_root, start_root, picture, font, output, cur_input_index, definition1, button_on, first_word_get);
        }
    }

    (*button_cnt)++;
}

void choose_game_mode(size_t *button_cnt, node_t **cur_root, node_t *start_root, Texture2D picture, Font font, char **output, size_t *cur_input_index, char **definition1, char **definition2, bool **button_on, bool *first_word_get, bool *second_word_get, char **user_input, char *text, int active_button, Vector2 touch, int **akinator_stages, FILE **png, Texture2D *tree, int *pic_num, node_t **root2, button_t buttons[])
{
    switch  (active_button)
    {
        case SHOW_DATA_BASE:
                {
                    exec_first_opt(button_on, picture, font, text);

                    break;
                }
        case PLAY_AKINATOR:
                {
                    exec_second_opt(button_on, picture, cur_root, button_cnt, font, touch, start_root, akinator_stages);

                    break;
                }
        case CHECK_TREE:
                {
                    exec_third_opt(picture, font, *definition1, tree, png, *output, button_cnt, button_on, pic_num, start_root);

                    break;
                }
        case DEFINE:
                {
                    exec_fourth_opt(button_cnt, cur_root, start_root, picture, font, output, cur_input_index, definition1, button_on, first_word_get, user_input);

                    break;
                }
        case COMPARE:
                {
                    exec_fifth_opt(cur_root, button_cnt, root2, output, cur_input_index, picture, font, definition1, definition2, button_on, first_word_get, second_word_get, start_root, user_input);

                    break;
                }
        case COOL_PHRASE:
                {
                    exec_sixth_opt(button_on, picture, font);

                    break;
                }
        default:
                {
                    common_menu(picture, font, buttons);
                }
    }
}