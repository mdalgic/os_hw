#include <stdio.h>
#include <getopt.h>


int main(int argc, char* argv[])
{
    fprintf(stdout, "HW1 Q1 program was started!\n");





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

    flag_bytes = flag_lines = flag_verbose = flag_help = flag_verbose = flag_error = 0;

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






    // if (err_flag)
    //     exit(EXIT_FAILURE);

    // if (a_flag)
    //     printf("-a option given\n");
    // if (b_flag)
    //     printf("-b option given with argument \"%s\"\n", b_arg);
    // if (all_flag)
    //     printf("--all option given\n");
    // if (length_flag)
    //     printf("--length option given with argument \"%s\"\n", length_arg);
    // if (number_flag)
    //     if (number_arg != NULL)
    //         printf("--number option given with argument \"%s\"\n", number_arg);
    //     else
    //         printf("--number option given without argument\n");
       
    // if (optind != argc) 
    //     printf("Arguments without options:\n");
    // for (int i = optind; i < argc; ++i)
    //     puts(argv[i]);
    
    // return 0;




    return 0;
}