SRC_1 = exercise_1/main.c
TARGET_1 = exercise_1/thread_ex1
SRC_2 = exercise_2/main.c
TARGET_2 = exercise_2/thread_ex2
SRC_3 = exercise_3/main.c exercise_3/src/thread_mutex_cond.c
TARGET_3 = exercise_3/thread_ex3
SRC_4 = exercise_4/main.c
TARGET_4 = exercise_4/thread_ex4
FLAG = -lpthread

all: 
	make ex1 ex2 ex3 ex4
ex1 : $(SRC)
	gcc -o $(TARGET_1) $(SRC_1) $(FLAG)
ex2 : $(SRC)
	gcc -o $(TARGET_2) $(SRC_2) $(FLAG)
ex3 : $(SRC)
	gcc -o $(TARGET_3) $(SRC_3) $(FLAG)
ex4 : $(SRC)
	gcc -o $(TARGET_4) $(SRC_4) $(FLAG)
clean: 
	rm -rf $(TARGET_1)
	rm -rf $(TARGET_2)
	rm -rf $(TARGET_3)
	rm -rf $(TARGET_4)

