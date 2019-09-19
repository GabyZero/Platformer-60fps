# Makefile #

# Compilation #
CC = g++
EXECUTABLE = exec
CPPFLAGS = -Wall -Wextra -pedantic -g -std=c++17 -Wreorder -fdiagnostics-show-option   #-lpthread# 
LDFLAGS = -std=c++17 -lsfml-graphics -lsfml-window -lsfml-system #-lpthread


# Directory #
OBJDIR = bin
SRCDIR = src
INCDIR = include

# Finding #
SRC = $(shell find $(SRCDIR)/ -type f -name '*.cpp')
OBJS = $(SRC:.cpp=.o)
OBJS := $(subst src/,,$(OBJS))
OBJS := $(addprefix $(OBJDIR)/, $(OBJS))


# Rules
all : $(EXECUTABLE)


$(EXECUTABLE) : $(OBJS)
	$(CC) $^ $(LDFLAGS) -o $@\


$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CC) $(CPPFLAGS) $(INCLUDES) -I $(INCDIR) -o $@ -c $<


clean:
	@rm -f $(OBJDIR)/*.o
	@rm -f $(EXECUTABLE)
	@rm -f $(SRCDIR)/*.cpp~
	@rm -f $(INCDIR)/*.h~
	@rm -f $(OBJDIR)/*.o~
	@rm -f $(OBJS)
	@rm -f *~
