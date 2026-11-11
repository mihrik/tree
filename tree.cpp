#include "h_files/tree.h"
#include "h_files/service.h"
#include "h_files/dump.h"

int main(int argc, const char * const argv[])
{
    if (args_analysis(argc, argv) != SUCCESSFUL_RETURN)
        return INVALID_QUANTITY_OF_ARGUMENTS;

    FILE *fp = fopen(TREE_DATA_FILE, "r");

    node_t root = {.value = 0, .left_child = NULL, .right_child = NULL, .parent = NULL};

    read_tree(fp, &root, NULL);
    fclose(fp);

    fp = fopen(TREE_DATA_FILE, "w");
    akinator(&root);

    print_tree(fp, &root);

    print_html(&root, FNAME, PIC_NAME);

    tree_dtor(&root);
    fclose(fp);

    return 0;
}