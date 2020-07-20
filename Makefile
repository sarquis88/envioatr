CC := g++
CCFLAG := -Wall -Werror -pedantic -Wextra -Wconversion -g
CPPFLAG = --enable=all --suppress=missingIncludeSystem -q

make:
	@cppcheck $(CPPFLAG) ./
	@printf "Cppcheck passed\n"
	@$(CC) $(CCFLAG) src/main.cpp src/commons.cpp -o bin/main.o 
	@printf "main.cpp compiled\n"
	@$(CC) $(CCFLAG) src/sender.cpp src/commons.cpp src/sender_connection.cpp -o bin/sender.o
	@printf "sender.cpp compiled\n"
	@$(CC) $(CCFLAG) src/receiver.cpp src/commons.cpp src/receiver_connection.cpp -o bin/receiver.o
	@printf "receiver.cpp compiled\n"
clean:
	@rm -f bin/*.o
