# compiler  and flag
CC = gcc 
Cflags = -Wall -Wextra 

#sources
SRC = src/main.c 
LIB = src/filestat.c


#target
target = filestat

all : $(SRC) $(LIB)
	$(CC) $(Cflags) -o $(target) $(SRC) $(LIB)
	
clean:
	rm -rf $(target)
	
.PHONNY: all clean
