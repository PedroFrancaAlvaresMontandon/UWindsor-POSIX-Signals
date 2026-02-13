//do nothing is a program with an infinite loop displaying ”Do  nothing program” every one 
//second. It is used in alarm3.c

#include <unistd.h>
#include <stdio.h>

int main() {

	while(1) {
		printf(" Do nothing program.\n");
		sleep(1);
	}


}
