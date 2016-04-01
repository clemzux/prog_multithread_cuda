#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(){

	int n;
	
	for (n = 0; n<10000; n++)
		if (fork()==0)
			return 0;
	
	return 0;
}
