#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*
Explanation:

if=path     (input file)
of=path     (output file)

If if and of are not exists, dd reads from stdin and writes into stdout as default behaviour.

default behaviour-> block size 512 byte, copy entire file from if to of

bs=size     (size implies block size in bytes such as 512, 1024 etc.)
count=c     (count is block size count. For example c=2, size=512 => 1024-byte will be copied)

conv=conversion_type

possible conversion types,
    -ucase: lower case -> upper case
    -lcase: upper case -> lower case
    -excl:  error occurs if of exists

multiple conversion types can exist with comma delimiter

dd command replaces the destination file by default, it overrides. To prevent it use excl.
*/


int main(int argc, char* argv[])
{
    fprintf(stdout, "[HW2 Q1: kind of dd program]\n");

    int flag_if, flag_of, flag_bs, flag_count, flag_conv;
    flag_if = flag_of = flag_bs = flag_count = flag_conv = 0;

    char arg_if[1024], arg_of[1024], arg_bs[20], arg_count[20], arg_conv[200];

    for(int i=1; i < argc; ++i)
    {
        if(strncmp(argv[i], "if=", 3) == 0)
        {
            if(sizeof(argv[i]) > 1023)
            {
                fprintf(stderr, "Size of if option is too long\n");
                exit(EXIT_FAILURE);
            }

            flag_if = 1;
            strcpy(arg_if, &argv[i][3]);
        }

        else if(strncmp(argv[i], "of=", 3) == 0)
        {
            if(sizeof(argv[i]) > 1023)
            {
                fprintf(stderr, "Size of of option is too long\n");
                exit(EXIT_FAILURE);
            }

            flag_of = 1;
            strcpy(arg_of, &argv[i][3]);
        }

        else if(strncmp(argv[i], "bs=", 3) == 0)
        {
            if(sizeof(argv[i]) > 19)
            {
                fprintf(stderr, "Size of bs option is too long\n");
                exit(EXIT_FAILURE);
            }

            flag_bs = 1;
            strcpy(arg_bs, &argv[i][3]);
        }

        else if(strncmp(argv[i], "count=", 6) == 0)
        {
            if(sizeof(argv[i]) > 19)
            {
                fprintf(stderr, "Size of count option is too long\n");
                exit(EXIT_FAILURE);
            }

            flag_bs = 1;
            strcpy(arg_bs, &argv[i][6]);
        }

        else if(strncmp(argv[i], "conv=", 5) == 0)
        {
            if(sizeof(argv[i]) > 199)
            {
                fprintf(stderr, "Size of conv option is too long\n");
                exit(EXIT_FAILURE);
            }

            flag_conv = 1;
            strcpy(arg_conv, &argv[i][5]);
        }

        else
        {
            fprintf(stderr, "[Undefined option: %s]\n", argv[i]);
            fprintf(stderr, "Possible options are as follows,\n"
            "if=path\n"                   
            "of=path\n"
            "bs=size\n"
            "count=c\n"
            "conv=conv_type");
        }
    }

    
    puts("\n");
 
    return 0;
}