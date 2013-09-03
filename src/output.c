#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "output.h"

void output_plain(char *str) {
	printf("%s\n", str);
	fflush( stdout );
}

void output_ontop(char *str) {
	printf("\r%s", str);
	fflush( stdout );
}