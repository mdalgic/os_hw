#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>


#define DEFAULT_BLOCKSIZE 512

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

note: ucase and lcase are mutually exclusive. If both of them exist, error occurs.
*/



int main(int argc, char* argv[])
{
    fprintf(stdout, "[HW2 Q1: kind of dd program]\n");

    int flag_if, flag_of, flag_bs, flag_count, flag_conv;
    flag_if = flag_of = flag_bs = flag_count = flag_conv = 0;

    char arg_if[1024], arg_of[1024], arg_bs[20], arg_count[20], arg_conv[200];

    int block_size, block_count;
    block_size = block_count = 0;

    int flag_conv_ucase, flag_conv_lcase, flag_conv_excl;
    flag_conv_ucase = flag_conv_lcase = flag_conv_excl = 0;

    // Pulling options and arguments from command line
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

            flag_count = 1;
            strcpy(arg_count, &argv[i][6]);
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

    // Checking and parsing arguments
    // if file should exist
    if(flag_if)
    {
        if(access(arg_if, F_OK) == -1)
        {
            fprintf(stderr, "if: %s does not exist!\n", arg_if);
            exit(EXIT_FAILURE);
        }
    }

    if(flag_bs)
    {
        char *endptr;
        block_size = strtol(arg_bs, &endptr, 10);

        if(block_size <= 0 || *endptr != '\0')
        {
            fprintf(stderr, "Invalid block size %s\n", arg_bs);
            exit(EXIT_FAILURE);
        }
    }

    // if block size is not given
    else
    {
        block_size = DEFAULT_BLOCKSIZE;
    }

    if(flag_count)
    {
        char *endptr;
        block_count = strtol(arg_count, &endptr, 10);

        if(block_count <= 0 || *endptr != '\0')
        {
            fprintf(stderr, "Invalid block count %s\n", arg_count);
            exit(EXIT_FAILURE);
        }
    }

    if(flag_conv)
    {
        char *token = strtok(arg_conv, ",");
        while(token != NULL)
        {
            if(strcmp(token, "ucase") == 0)
            {
                flag_conv_ucase = 1;
            }

            else if(strcmp(token, "lcase") == 0)
            {
                flag_conv_lcase = 1;
            }

            else if(strcmp(token, "excl") == 0)
            {
                flag_conv_excl = 1;
            }

            else
            {
                fprintf(stderr, "Undefined conversion type: %s\n", token);
                exit(EXIT_FAILURE);
            }

            token = strtok(NULL, ",");
        }
    }

    // whether of file should not exist or not depends on excl option
    if(flag_of && flag_conv_excl)
    {
        if(access(arg_of, F_OK) != -1)
        {
            fprintf(stderr, "of: %s is already exist!\n", arg_of);
            exit(EXIT_FAILURE);
        }
    }


    // note: ucase and lcase are mutually exclusive. If both of them exist, error occurs.
    if(flag_conv_ucase && flag_conv_lcase)
    {
        fprintf(stderr, "ucase and lcase cannot be used together\n");
        exit(EXIT_FAILURE);
    }

    // Checking if of and if are same
    if(flag_of && flag_if)
    {
        if(strcmp(arg_of, arg_if) == 0)
        {
            fprintf(stderr, "of and if cannot be same\n");
            exit(EXIT_FAILURE);
        }
    }

    // Copying from if to of
    int fd_if, fd_of;

    if(flag_if)
        fd_if = open(arg_if, O_RDONLY);
    else
        fd_if = open("/dev/stdin", O_RDONLY);

    if(flag_of)
        fd_of = open(arg_of, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else
        fd_of = open("/dev/stdout", O_WRONLY | O_CREAT | O_TRUNC, 0644);


    if(fd_if == -1)
    {
        fprintf(stderr, "Error while opening if file\n");
        exit(EXIT_FAILURE);
    }

    if(fd_of == -1)
    {
        fprintf(stderr, "Error while opening of file\n");
        exit(EXIT_FAILURE);
    }

    char buffer[block_size];
    int read_bytes, write_bytes;

    int total_bytes_read, total_bytes_written;
    total_bytes_read = total_bytes_written = 0;

    int iterations = 1;

    while((read_bytes = read(fd_if, buffer, block_size)) > 0)
    {
        total_bytes_read += read_bytes;

        if(flag_conv_ucase)
        {
            for(int i=0; i < read_bytes; ++i)
            {
                buffer[i] = toupper(buffer[i]);
            }
        }

        else if(flag_conv_lcase)
        {
            for(int i=0; i < read_bytes; ++i)
            {
                buffer[i] = tolower(buffer[i]);
            }
        }

        write_bytes = write(fd_of, buffer, read_bytes);

        total_bytes_written += write_bytes;

        if(write_bytes == -1)
        {
            fprintf(stderr, "Error while writing to of file\n");
            exit(EXIT_FAILURE);
        }


        // break loop and stop copying if count is reached
        if(flag_count)
        {
            if(iterations == block_count)
                break;
        }

        iterations++;
    }

    if(read_bytes == -1)
    {
        fprintf(stderr, "Error while reading from if file\n");
        exit(EXIT_FAILURE);
    }

    close(fd_if);
    close(fd_of);

    printf("%d bytes read\n", total_bytes_read);
    printf("%d bytes written\n", total_bytes_written);

    puts("\n");
 
    return 0;
}