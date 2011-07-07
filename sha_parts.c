/*
 *  sha.cpp
 *
 *  Copyright (C) 1998, 2009
 *  Paul E. Jones <paulej@packetizer.com>
 *  All Rights Reserved
 *
 *****************************************************************************
 *  $Id: sha.c 12 2009-06-22 19:34:25Z paulej $
 *****************************************************************************
 *
 *  Description:
 *      This utility will display the message digest (fingerprint) for
 *      the specified file(s).
 *
 *  Portability Issues:
 *      None.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef WIN32
#include <io.h>
#endif
#include <fcntl.h>
#include "sha1.h"

/*
 *  Function prototype
 */
void usage();


/*
 *  main
 *
 *  Description:
 *      This is the entry point for the program
 *
 *  Parameters:
 *      argc: [in]
 *          This is the count of arguments in the argv array
 *      argv: [in]
 *          This is an array of filenames for which to compute message
 *          digests
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *
 */
int main(int argc, char *argv[]) {
    int i;   /* Counter */
    /*
     *  Check the program arguments and print usage information if -?
     *  or --help is passed as the first argument.
     */
    if (argc > 1 && (!strcmp(argv[1],"-?") ||
        !strcmp(argv[1],"--help")))
    {
        usage();
        return 1;
    }

    if (argc < 3) {
    	usage();
    	return 0;
    }


    int block_size = strtol(argv[1], NULL, 10);

    /*
     *  For each filename passed in on the command line, calculate the
     *  SHA-1 value and display it.
     */
    for(i = 2; i < argc; i++)
    {

       unsigned char sha_result[SHA_STATE_SIZE];

       //sha1_file(argv[i], sha_result);
       printf("Computing sha1 in %d byte blocks for file %s\n", block_size, argv[i]);
        /*
         *  Reset the SHA-1 context and process input
         */


       int bytes_processed = 0;
       int total_bytes_processed = 0;
       int finished = 0;
       while(!finished) {
    	   sha1_file_progressive(argv[i], total_bytes_processed, block_size, sha_result, &bytes_processed);
    	   finished = bytes_processed < block_size;
    	   total_bytes_processed += bytes_processed;
       }
       char * result_hex = byte_to_hex(sha_result, 20);
       printf( "%s - %s\n", result_hex, argv[i]);
       free(result_hex);

    }

    return 0;
}

/*
 *  usage
 *
 *  Description:
 *      This function will display program usage information to the
 *      user.
 *
 *  Parameters:
 *      None.
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *
 */
void usage()
{
    printf("usage: sha_parts <blocksize> <file> [<file> ...]\n");
    printf("\tThis program will display the message digest\n");
    printf("\tfor files using the Secure Hashing Algorithm (SHA-1).\n");
}
