#include <stdlib.h>
#include <string.h>

int	main(void)
{
	void *p = malloc(15);
	p = p - 20;
	memset(p, '\0', 100);
	void *i = malloc(20);	
}
