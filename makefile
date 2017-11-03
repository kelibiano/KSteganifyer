CC = g++
OBJ = main.o
SRC_DIR = src
OBJ_DIR = obj

steg: $(OBJ)
	$(CC) -o $@ $(OBJ)

%.o: $(SRC_DIR)/%.cpp
	$(CC) -c $<

clean :
	rm *.o
	rm steg
