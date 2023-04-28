#include "../inc/window.h"


/* Error handling, can be called in a callback way */
void onError(int error, const char *description)
{
	fprintf(stderr, "GLFW Error: %s\n", description);
}