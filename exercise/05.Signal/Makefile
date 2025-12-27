SRC_1 = exercise_1/basic_signal.c
TARGET_1 = exercise_1/basic_signal
SRC_2 = exercise_2/Sign_Alarm.c
TARGET_2 = exercise_2/Alarm_signal
SRC_3 = exercise_3/Sig_user.c
TARGET_3 = exercise_3/Sig_user
SRC_4 = exercise_4/poll.c
TARGET_4 =	exercise_4/Poll


all: 
	make ex1 ex2 ex3 ex4
ex1 : $(SRC)
	gcc -o $(TARGET_1) $(SRC_1)
ex2 : $(SRC)
	gcc -o $(TARGET_2) $(SRC_2)
ex3 : $(SRC)
	gcc -o $(TARGET_3) $(SRC_3)
ex4 : $(SRC)
	gcc -o $(TARGET_4) $(SRC_4)
clean: 
	rm -rf $(TARGET_1)
	rm -rf $(TARGET_2)
	rm -rf $(TARGET_3)
	rm -rf $(TARGET_4)

