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
OBJ_MAIN= $(OBJ_TOOLS) $(OBJDIR)draw_scene.o $(OBJDIR)main.o
EXEC_MAIN= $(BINDIR)tlc


all : $(EXEC_MAIN)


$(EXEC_MAIN) : $(OBJ_MAIN)
	$(CC) $(CFLAGS) $(OBJ_MAIN) -o $(EXEC_MAIN) $(LDFLAGS)

clean :
	rm -f *.o
	rm -f $(OBJDIR)*.o
	rm -f $(BINDIR)*


# Rule fo all the C files in the source folder
$(OBJDIR)%.o: $(SRCDIR)%.c $(INCDIR)*.h
	mkdir -p `dirname $@`
	$(CC) -o $@ -I $(INCDIR) -c $< $(CFLAGS)

