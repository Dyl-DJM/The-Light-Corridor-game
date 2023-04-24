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
EXEC_MAIN= $(BINDIR)tlc


all : $(EXEC_MAIN)


$(EXEC_MAIN) : $(OBJ_MAIN)
	$(CC) $(SRCDIR)main.c $(CFLAGS) $(LDFLAGS) -o $(EXEC_MAIN)


clean :
	rm -f *.o
	rm -f $(OBJDIR)*.o
	rm -f $(BINDIR)*


$(OBJDIR)%.o: $(SRCDIR)%.c $(INCDIR)*.h
	mkdir -p `dirname $@`
	$(CC) -o $@ -I $(INCDIR) -c $< $(CFLAGS)
