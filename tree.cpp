#include "h_files/tree.h"
#include "h_files/service.h"
#include "h_files/dump.h"

int main(int argc, const char * const argv[])
{
    if (args_analysis(argc, argv) != SUCCESSFUL_RETURN)
        return INVALID_QUANTITY_OF_ARGUMENTS;

    FILE *fp = fopen(TREE_DATA_FILE, "w+");

    node_t root = {.value = ROOT_VALUE, .left_child = NULL, .right_child = NULL, .parent = NULL};

    node_ctor(&root, 100);
    node_ctor(&root, 0);
    node_ctor(&root, 75);
    node_ctor(&root, 25);
    node_ctor(&root, -20);
    node_ctor(&root, 200);

    print_tree(fp, &root);

    print_html(&root, FNAME, PIC_NAME);

    tree_dtor(&root);

    return 0;
}