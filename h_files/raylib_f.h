#ifndef RAYLIB_F_H
#define RAYLIB_F_H

#include "raylib.h"
#include "../h_files/tree.h"
#include "../h_files/dump.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

const double EPSILON = 1e-5;
const int BUTTON_LENGTH = 250;
const int BUTTON_HEIGHT = 100;

//bool first_opt = (touch.x >= 100 && touch.x <= 350 && touch.y <= 300 && touch.y >= 200 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) || button_on[0];
typedef struct button_t
{
    float start_x;
    float end_x;
    float start_y;
    float end_y;
    const char *label;
} button_t;

typedef enum command
{
    SHOW_DATA_BASE  = 0,
    PLAY_AKINATOR   = 1,
    CHECK_TREE      = 2,
    DEFINE          = 3,
    COMPARE         = 4,
    COOL_PHRASE     = 5,
    BUTTON_QUANTITY = 6
} command;

button_t set_button(float start_x, float end_x, float start_y, float end_y, const char label[]);
bool in_button(button_t button, Vector2 touch);
void draw_button(button_t button, Font font);
void common_menu(Texture2D picture, Font font, button_t buttons[]);
bool is_zero(float num);
int get_button(button_t buttons[], Vector2 touch, bool button_on[]);
void check_tree_first_click(FILE **png, int *pic_num, node_t *start_root, Texture2D *tree);
void check_tree_next_clicks(Texture2D picture, Font font, char definition1[], Texture2D *tree, FILE **png, char output[], size_t *button_cnt, bool **button_on);
void exec_third_opt(Texture2D picture, Font font, char definition1[], Texture2D *tree, FILE **png, char output[], size_t *button_cnt, bool **button_on, int *pic_num, node_t *start_root);
void exec_second_opt(bool **button_on, Texture2D picture, node_t **cur_root, size_t *button_cnt, Font font, Vector2 touch, node_t *start_root, int **akinator_stages);
int video_play_akinator(node_t *root);
void exec_first_opt(bool **button_on, Texture2D picture, Font font, char text[]);
void common_akinator_case(node_t **cur_root, size_t *button_cnt, Font font, Vector2 touch);
void leaf_akinator_case(node_t *start_root, node_t **cur_root, Font font, size_t *button_cnt, bool **button_on, Vector2 touch, int **akinator_stages);
void word_asking(bool *first_word_get, Font font, size_t *cur_input_index, Texture2D picture, char **user_input, char **definition1, size_t *button_cnt);
void not_found(bool *first_word_get, bool **button_on, Texture2D picture, Font font, char *output, size_t *button_cnt);
void make_definition(node_t *cur_node, char **output, size_t *cur_input_index);
void exec_sixth_opt(bool **button_on, Texture2D picture, Font font);
void compare_first_frame(node_t *start_root, char definition1[], char definition2[], node_t **cur_root, node_t **root2);
void compare_word_not_exist(size_t *button_cnt, char **output, char **definition1, char **definition2, bool *first_word_get, bool *second_word_get, bool **button_on, Texture2D picture, Font font);
void compare_all_good(node_t **cur_root, size_t *button_cnt, node_t **root2, char **output, size_t *cur_input_index, Texture2D picture, Font font, char **definition1, char **definition2, bool **button_on, bool *first_word_get, bool *second_word_get, node_t *start_root);
void exec_fifth_opt(node_t **cur_root, size_t *button_cnt, node_t **root2, char **output, size_t *cur_input_index, Texture2D picture, Font font, char **definition1, char **definition2, bool **button_on, bool *first_word_get, bool *second_word_get, node_t *start_root, char **user_input);
void define_all_good(size_t *button_cnt, node_t **cur_root, node_t *start_root, Texture2D picture, Font font, char **output, size_t *cur_input_index, char **definition1, bool **button_on, bool *first_word_get);
void exec_fourth_opt(size_t *button_cnt, node_t **cur_root, node_t *start_root, Texture2D picture, Font font, char **output, size_t *cur_input_index, char **definition1, bool **button_on, bool *first_word_get, char **user_input);
void choose_game_mode(size_t *button_cnt, node_t **cur_root, node_t *start_root, Texture2D picture, Font font, char **output, size_t *cur_input_index, char **definition1, char **definition2, bool **button_on, bool *first_word_get, bool *second_word_get, char **user_input, char *text, int active_button, Vector2 touch, int **akinator_stages, FILE **png, Texture2D *tree, int *pic_num, node_t **root2, button_t buttons[]);

#endif