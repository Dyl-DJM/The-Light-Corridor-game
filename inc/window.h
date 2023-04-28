#pragma once

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>


/* Framerate */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;

/* Window properties */
static const unsigned int WINDOW_WIDTH = 1000;
static const unsigned int WINDOW_HEIGHT = 700;
static const char WINDOW_TITLE[] = "The Light Corridor";

/* Error handling, can be called in a callback way */
void onError(int error, const char *description);
