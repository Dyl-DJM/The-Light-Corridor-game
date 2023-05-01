/*
======================================================
=  													 =
=    Created by Nicolas Atrax and Dylan DE JESUS	 =
=													 =
=													 =
=  The Window module is used for the major part      =
=  of the windows properties used to make the 3D	 =
=  and 2D scenes of the project						 =
=													 =
======================================================
*/

#include "../inc/window.h"

/* Error handling, can be called in a callback way */
void onError(int error, const char *description)
{
	fprintf(stderr, "GLFW Error: %s\n", description);
}