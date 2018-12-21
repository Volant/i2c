#include <stdint.h>

extern int main (int argc, char* argv[]);

void __attribute__ ((section(".text"),noreturn,weak)) _start (void) {

	int argc;
	char** argv;
	int code = main(argc, argv);

	for (;;);
}

