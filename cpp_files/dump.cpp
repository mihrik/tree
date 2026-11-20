#include "../h_files/dump.h"
#include "../h_files/colors.h"

static int pic_num = 0;
static int node_num = 0;

error_codes print_spears(node_t *root, FILE *png)
{
    node_num++;

    if (node_num != 0)
    {
        if ( root->parent != NULL && root == root->parent->left_child)
        {
            fprintf(png, "node%d [color=\"GREEN_\", penwidth=1, label = \"Да\"];\n", node_num);
        }
        else if (root->parent != NULL)
        {
            fprintf(png, "node%d [color=\"RED_\", penwidth=1, label = \"Нет\"];\n", node_num);
        }
    }

    int cur_node = node_num;

    fprintf(png, "node%d [shape=Mrecord; style = filled; fillcolor = \"#94e8f1\"; color = \"#000000\";\n", node_num);
    fprintf(png, "  label = \"" deb_spec "  \"; ]\n\n", root->value);

    if (root->left_child)
    {
        fprintf(png, "node%d -> ", cur_node);
        print_spears(root->left_child, png);
    }

    if (root->right_child)
    {
        fprintf(png, "node%d -> ", cur_node);
        print_spears(root->right_child, png);
    }

    return SUCCESSFUL_RETURN;
}

error_codes prepare_png(node_t *root, const char fname[])
{
    FILE *png = fopen(fname, "w");

    if (png == NULL)
    {
        PRINT_COLOR(EXTRA_RED__, "UNAVAILABLE FILE: <%s>, while doing prepare_png\n", fname);
        return UNAVAILABLE_FILE;
    }

    fprintf(png, "digraph {\n\n");
    fprintf(png, "splines=line;\n");

    node_num = 0;
    print_spears(root, png);

    fprintf(png, "}\n");

    fclose(png);

    return SUCCESSFUL_RETURN;
}

error_codes print_html(node_t *root, const char fname[], const char pic_name[])
{
    FILE *png = fopen(fname, "w+");

    if (png == NULL)
    {
        PRINT_COLOR(EXTRA_RED__, "UNAVAILABLE FILE: <%s>, while doing prepare_png\n", fname);
        return UNAVAILABLE_FILE;
    }

    pic_num++;

    char pic_file_name[MAX_FILE_NAME_LEN] = {};
    sprintf(pic_file_name, "txt_files/%s%d.txt", pic_name, pic_num);

    char png_file_name[MAX_FILE_NAME_LEN] = {};
    sprintf(png_file_name, "png_files/%s%d.png", pic_name, pic_num);


    prepare_png(root, pic_file_name);
    char system_command[MAX_COMMAND_NAME_LEN] = {};
    sprintf(system_command, "dot %s -Tpng -o %s", pic_file_name, png_file_name);
    system(system_command);

    fprintf(png, "<img src=%s width=1200px>", png_file_name);

    fclose(png);

    return SUCCESSFUL_RETURN;
}