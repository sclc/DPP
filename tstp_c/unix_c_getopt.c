/*
 * UNIX getopt API test
 * reference:
 * 1. http://www.gnu.org/software/libc/manual/html_node/Getopt.html 
 * 2. http://www.gnu.org/software/libc/manual/html_node/Example-of-Getopt.html#Example-of-Getopt
 * 3. http://www.mm2d.net/main/prog/c/getopt-01.html
 * 4. http://www.cplusplus.com/reference/cctype/isprint/
 * tested:
 * 1. ./a.out f f fdfsf -a ggdfgd
 * 2. ./a.out -eabc
 * 3. ./a.out -e abc
 * 4. ./a.out -c
 * 5. ./a.out -f
 * notice:
 * 1. e: accept e string form argument, e:: only accept dstring form argument
 */

#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>

int main (int argc, char** argv)
{
	int aflag = 0;
	int bflag = 0;
	int dflag = 0;
	int eflag = 0;
	char *cvalue = NULL;
	char *dvalue = NULL;
	char *evalue = NULL;
	int index;
	int c;

	while ( (c = getopt(argc, argv, "abc:d:e::")) != -1 )
	{
		switch (c) {
			case 'a':
				aflag = 1;
				break;
			case 'b':
				bflag = 1;
				break;
			case 'c':
				cvalue = optarg;
				break;
			case 'd':
				dflag = 1;
				dvalue = optarg;
				break;
			case 'e':
				eflag = 1;
				evalue = optarg;
				break;
			case '?':
				if (optopt == 'c')
					fprintf(stderr, "Option -%c requires an argument.\n", optopt);
				else if (optopt == 'd')
					fprintf(stderr, "Option -%c requires an argument.\n", optopt);
				else if (isprint(optopt))
					fprintf(stderr, "Unknown option '-%c'. \n", optopt);
				else
					fprintf(stderr, 
						"Unknown option character '\\x%x'.\n",
						optopt);
				return 1;
			default:
				abort ();
		}
	}
	printf("aflag=%d, bflag=%d, dflag=%d, eflag=%d, cvalue=%s, dvalue=%s, evalue=%s \n",
		aflag, bflag, dflag, eflag, cvalue, dvalue, evalue);

	for (index=optind; index<argc; index++)
		printf("Non-option argument %s\n", argv[index]);

	return 0;
}
