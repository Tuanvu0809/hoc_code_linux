CC = gcc 
Cflags = -wall -wextra -std:c99
SRC = main.c 
LIB = bstrutils.c
OBJ =  bstrutils.o
target_static = build/main_static
target_shared = build/main_shared 
STATIC_PATH = library/Static/
SHARE_PATH = library/Shared/
LIBARY_NAME = libbstrutils

all : $(SRC) $(LIB)
	$(CC) -o $(OBJ) -c $(LIB)
	$(CC) -fPIC -c $(LIB) -o $(OBJ)
	ar rcs $(STATIC_PATH)$(LIBARY_NAME).a $(OBJ)
	ar rcs $(SHARE_PATH)$(LIBARY_NAME).so $(OBJ)
	$(CC) $(SRC) -L./$(STATIC_PATH) -lbstrutils -o $(target_static)
	$(CC) $(SRC) -L./$(SHARE_PATH) -lbstrutils -o $(target_shared)
	
clean:
	rm -rf $(target_static)
	rm -rf $(target_shared)
	rm -rf $(STATIC_PATH)*.a
	rm -rf $(SHARE_PATH)*.so
	rm -rf  $(OBJ)
.PHONNY: all clean
