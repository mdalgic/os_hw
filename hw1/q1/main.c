#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>

#define DEFAULT_LINE_AMOUNT 10
#define VERSION 1.0




int main(int argc, char* argv[])
{
    fprintf(stdout, "[HW1 Q1]\n");

    int result;
    int flag_bytes, flag_lines, flag_verbose, flag_help, flag_version, flag_error;
    char *arg_bytes, *arg_lines;

    struct option options[] = {
        {"bytes",   required_argument,  NULL, 'c'}, 
        {"lines",   required_argument,  NULL, 'n'}, 
        {"verbose", no_argument,        NULL, 'v'},
        {"help",    no_argument,        NULL, 1},
        {"version", no_argument,        NULL, 2},
        {0, 0, 0, 0},
    };

    flag_bytes = flag_lines = flag_verbose = flag_help = flag_version = flag_error = 0;

    // prevent default error messages
    opterr = 0;

    while ((result = getopt_long(argc, argv, "c:n:v", options, NULL)) != -1) {
        switch (result) {

            // bytes
            case 'c':
                flag_bytes = 1;
                arg_bytes = optarg;
                break;

            // lines
            case 'n':
                flag_lines = 1;
                arg_lines = optarg;
                break;

            // verbose
            case 'v':
                flag_verbose = 1;
                break;

            // help
            case 1:
                flag_help = 1;
                break;

            // version
            case 2:
                flag_version = 1;
                break;


            // undefined option or argument not exist though it is required
            case '?':
                if(optopt == 'c')
                    fprintf(stderr, "-c/--bytes option requires argument!\n");
                else if(optopt == 'n')
                    fprintf(stderr, "-n/--lines option requires argument!\n");
                else if (optopt != 0)
                    fprintf(stderr, "invalid option: -%c\n", optopt);
                else
                    // using optind in this way is not standard but valid for glibc
                    fprintf(stderr, "invalid long option: %s\n", argv[optind -1]);

                flag_error = 1;
                break;

        }
    }    


    if(flag_error)   
        exit(EXIT_FAILURE);

    // if both are defined
    if (flag_bytes & flag_lines)
    {
        fprintf(stderr, "-c and -n options can not be used together!\n");
        exit(EXIT_FAILURE);
    }

    // if neither is defined
    if ((flag_bytes | flag_lines) == 0)
    {   
        // fprintf(stdout, "Neither was defined\n");

        flag_lines = 1;
        // arg_lines = DEFAULT_LINE_AMOUNT;
    }


    if(flag_bytes)
    {

    }

    if(flag_lines)
    {

    }

    if(flag_verbose)
    {
        // optind is the index of the starting point of arguments without option
        if (optind != argc)
        {
            fprintf(stdout, "-------Files--------\n");

            for (int i = optind; i < argc; ++i)
                puts(argv[i]);
            
            fprintf(stdout, "--------------------\n");
        }
    }


    if(flag_help)
    {
            printf("Usage: head [OPTION]... [FILE]...\n"
           "Print the first 10 lines of each specified FILE to standard output. With more than one FILE, precede each with a header giving the file name.\n"
           "\n"
           "Options:\n"
           "  -c, --bytes=[-]NUM        print the first NUM bytes of each file; with the leading '-', print all but the last NUM bytes of each file\n"
           "  -n, --lines=[-]NUM        print the first NUM lines of each file; with the leading '-', print all but the last NUM lines of each file\n"
           "  -v, --verbose             always output headers giving file names\n"
           "      --help                display this help and exit\n"
           "      --version             output version information and exit\n"
           "\n"
           "With no FILE, or when FILE is -, read standard input.\n");
    }

    if(flag_version)
    {
        fprintf(stdout, "Version: %lf\n", VERSION);
    }
 
 
 
 
    return 0;
}