CC := g++
CCFLAG := -Wall -Werror -pedantic -Wextra -Wconversion -g
CPPFLAG = --enable=performance,portability,information,unusedFunction -q

make:
	cppcheck $(CPPFLAG) ./
	$(CC) $(CCFLAG) src/main.cpp src/commons.cpp -o bin/main.o 
	$(CC) $(CCFLAG) src/sender.cpp src/commons.cpp src/sender_connection.cpp -o bin/sender.o
	$(CC) $(CCFLAG) src/receiver.cpp src/commons.cpp src/receiver_connection.cpp -o bin/receiver.o

clean:
	rm -f bin/*.o