

# define the C compiler to use
CC = g++
LD = ld

# define any compile-time flags
CFLAGS = -Wall -g

#define link paths in addition
LFLAGS = -shared -fPIC 



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
	
$(TARGET): $(OBJS) 
	$(CC) $(LFLAGS) $(OBJS) -o $(TARGET) $(LIBS)

all: $(TARGET)
	@echo  Simple compiler named mycc has been compiled

clean:
	$(RM) *.o *~ $(TARGET)

depend: $(SRCS)
	makedepend $(INCLUDES) $^
#
# Makefile For building PITUnicode String
#

# the build target executable:
TARGET = PITConUnicodeString.dll
# define any directories containing header files
INCLUDES = -I./headers -I../PITConCommon/headers 
# define any libraries to link into executable
LIBS =


# define the C source files
SRCS = PITUnicodeString.cpp PITUnicodeStringHelper.cpp

include ../common.mk
# DO NOT DELETE THIS LINE -- make depend needs it
