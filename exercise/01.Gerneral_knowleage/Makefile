# compiler  and flag
CC = gcc 
Cflags = -wall -wextra -std:c99

#sources
SRC = src/main.c 
LIB = src/bstrutils.c

#object
OBJ =  bstrutils.o

#target
target_static = build/main_static
target_shared = build/main_shared 
STATIC_PATH = library/Static/
SHARE_PATH = library/Shared/
LIBARY_NAME = libbstrutils

all : $(SRC) $(LIB)
	make static
	make shared
	
clean:
	rm -rf $(target_static)
	rm -rf $(target_shared)
	rm -rf $(STATIC_PATH)*.a
	rm -rf $(SHARE_PATH)*.so
	rm -rf  $(OBJ)
	

static : $(SRC) $(LIB)
	$(CC) -o $(OBJ) -c $(LIB)	
	ar rcs $(STATIC_PATH)$(LIBARY_NAME).a $(OBJ)
	$(CC) $(SRC) -L./$(STATIC_PATH) -lbstrutils -o $(target_static)
shared :  $(SRC) $(LIB)
	$(CC) -fPIC -c $(LIB) -o $(OBJ)
	ar rcs $(SHARE_PATH)$(LIBARY_NAME).so $(OBJ)
	$(CC) $(SRC) -L./$(SHARE_PATH) -lbstrutils -o $(target_shared)

.PHONNY: all clean
