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
int main(int argc, char *argv[])
{
    int         i;                  /* Counter                       */



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

    /*
     *  For each filename passed in on the command line, calculate the
     *  SHA-1 value and display it.
     */
    for(i = 0; i < argc; i++)
    {
        /*
         *  We start the counter at 0 to guarantee entry into the for
         *  loop. So if 'i' is zero, we will increment it now.  If there
         *  is no argv[1], we will use STDIN below.
         */
        if (i == 0)
        {
            i++;
        }


       char sha_result[20];
       sha1_file(argv[i], sha_result);
        /*
         *  Reset the SHA-1 context and process input
         */


       char * result_hex = byte_to_hex(sha_result, 20);
       printf( "%s - %s\n", result_hex, argv[i]);
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
    printf("usage: sha <file> [<file> ...]\n");
    printf("\tThis program will display the message digest\n");
    printf("\tfor files using the Secure Hashing Algorithm (SHA-1).\n");
}
