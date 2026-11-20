#include "../h_files/tree.h"
#include "../h_files/service.h"
#include "../h_files/dump.h"
#include "../h_files/ascii.h"
#include "../h_files/raylib_f.h"

int main(int argc, const char * const argv[])
{
    if (args_analysis(argc, argv) != SUCCESSFUL_RETURN)
        return INVALID_QUANTITY_OF_ARGUMENTS;

    FILE *fp = NULL;
    if ((fp = fopen(argv[1], "r")) == NULL)
        return FILE_READING_ERROR;

    //print_greeting();

    node_t root = {.value = NULL, .left_child = NULL, .right_child = NULL, .parent = NULL};
    read_tree(fp, &root, NULL);

    video_play_akinator(&root);
    //play_akinator(argv, &root, fp);

    tree_dtor(&root);
    fclose(fp);

    return 0;
}