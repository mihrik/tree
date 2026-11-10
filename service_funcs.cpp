#include "h_files/tree.h"
#include "h_files/service.h"

error_codes args_analysis(int argc, const char * const argv[])
{
    assert(argv);

    if (argc == 2)
    {
        return SUCCESSFUL_RETURN;
    }
    else
    {
        return INVALID_QUANTITY_OF_ARGUMENTS;
    }
}