
#
# Makefile For building PITUnicode String
#

# the build target executable:
TARGET = KStegCore.exe
# define any directories containing header files
INCLUDES = -I./headers
# define any libraries to link into executable
LIBS =


# define the C source files
SRCS = CWorkItemImpl.cpp CWICompositeImpl.cpp IWIIterator.cpp CFolder.cpp CFile.cpp main.cpp

# define the C compiler to use
CC = g++
LD = ld
MKDR = @mkdir
RMDR = @rmdir
# define any compile-time flags
CFLAGS = -Wall -g

#define link paths in addition
TYPE = #-shared -fPIC 
LFLAGS = $(TYPE)

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
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

Folders : 
	$(MKDR) $(BIN_FLDR)

$(TARGET): Folders $(OBJS) 
	$(CC) $(LFLAGS) $(OBJS) -o $(BIN_FLDR)/$(TARGET) $(LIBS)

all: clean $(TARGET) cleanObj
	$(RM) ./*.o

clean: cleanObj
	$(RM) $(BIN_FLDR)/*.*
	$(RMDR) $(BIN_FLDR)

cleanObj : 
	$(RM) ./*.o
	
depend: $(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
