CC		= gcc
CFLAGS	= -Wall -O2 -g
LDFLAGS	= -lglfw -lGLU -lGL -lm

BINDIR	= bin/
INCDIR	= inc/
SRCDIR	= src/
OBJDIR	= obj/

#### Modules ####

# Tools file
OBJ_TOOLS = $(OBJDIR)3D_tools.o

# Main module
OBJ_MAIN= $(OBJ_TOOLS)
EXEC_MAIN= tlc


all : $(OBJ_TOOLS)

$(OBJ_TOOLS): 
	$(CC) -c $(SRCDIR)3D_tools.c -o$(OBJ_TOOLS) $(CFLAGS)

main : $(OBJ_MAIN)
	$(CC) $(CFLAGS) $(OBJ_MAIN) -o $(BINDIR)$(EXEC_MAIN) $(LDFLAGS)


clean :
	rm -f *.o
	rm -f $(OBJDIR)*.o
	rm -f $(BINDIR)*
