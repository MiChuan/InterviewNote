#include <stdio.h>

int main()
{
	printf("hello\n");
#ifdef MYDEBUG
	printf("debug\n");
#endif
	return 0;
}