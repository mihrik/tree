#include "../h_files/ascii.h"

void print_ascii(FILE *art_addres, int times)
{
    assert(art_addres);
    char one_line[300];
    struct timespec time = {.tv_sec = 0, .tv_nsec = 9000000};
    while(fgets(one_line, 300, art_addres))
    {
        nanosleep(&time, NULL);
        printf("\033[%dC", times);
        fputs(one_line, stdout);
    }

    puts("\n");
}

void print_greeting(void)
{
    FILE *fp_art = NULL;
    assert(fp_art = fopen("ascii_arts/akinator", "r"));
    print_ascii(fp_art, 10);
    assert(!fclose(fp_art));
}

void nice_output(const char *output)
{
    FILE *fp = NULL;
    assert(output);
    int i = 1;
    while(*output)
    {
        char name_of_file[100] = "symbols/";

        if (*output == ' ')
        {
            output++;
            i++;
            continue;
        }

        unsigned char first = (unsigned char) *output;
        int bytes = 1;

        if (first == 0xD0 || first == 0xD1)
            bytes = 2;

        memcpy(name_of_file + 8, output, (size_t)bytes);
        name_of_file[8 + bytes] = '\0';

        assert(fp = fopen(name_of_file, "r"));
        print_ascii(fp, i * 7);
        printf("\033[6A");

        i++;
        output += bytes;
    }
    puts("\n\n\n\n\n\n\n\n");
    assert(!fclose(fp));
}


void print_phrase(const char* const file_name)
{
    FILE *fp_art = NULL;
    char phrase[100] = "ascii_arts/";
    strcat(phrase, file_name);
    assert(fp_art = fopen(phrase, "r"));
    print_ascii(fp_art, 10);
    assert(!fclose(fp_art));
}

void print_goodbye(void)
{
    print_phrase("goodbye");
}
