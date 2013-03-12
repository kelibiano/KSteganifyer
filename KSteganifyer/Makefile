
#
# Makefile For building PITUnicode String
#

# the build target executable:
TARGET = KStegCore.dll
# define any directories containing header files
INCLUDES = -I./headers
# define any libraries to link into executable
LIBS =


# define the C source files
SRCS = CWorkItemImpl.cpp CWICompositeImpl.cpp IWIIterator.cpp CFolder.cpp main.cpp

# define the C compiler to use
CC = g++
LD = ld
MKDR = @mkdir
RMDR = @rmdir
# define any compile-time flags
CFLAGS = -Wall -g

#define link paths in addition
LFLAGS = -shared -fPIC 

OBJ_FLDR = obj
BIN_FLDR = bin

# define the C object files  (with macro)
OBJS = $(SRCS:.cpp=.o)

#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#
.PHONY: depend clean
.SUFFIXES: .o .cpp

%.o : source/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $(OBJ_FLDR)/$@

Folders : 
	$(MKDR) $(OBJ_FLDR)
	$(MKDR) $(BIN_FLDR)

$(TARGET): Folders $(OBJS) 
	$(CC) $(LFLAGS) $(OBJS) -o $(BIN_FLDR)/$(TARGET) $(LIBS)

all: clean $(TARGET)
	@echo  Simple compiler named mycc has been compiled

clean:
	$(RM) $(OBJ_FLDR)/*.*
	$(RM) $(BIN_FLDR)/*.*
	$(RMDR) $(OBJ_FLDR)
	$(RMDR) $(BIN_FLDR)

depend: $(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
