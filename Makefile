CC := g++
CCFLAG := -Wall -Werror -pedantic -Wextra -Wconversion -g
CPPFLAG = --enable=all --suppress=missingIncludeSystem -q

make:
	@make main
	@make sender
	@make receiver
main:
	@$(CC) $(CCFLAG) src/main.cpp src/commons.cpp -o bin/main.o 
	@printf "main.cpp compiled\n"
sender:
	@$(CC) $(CCFLAG) src/sender.cpp src/commons.cpp src/sender_connection.cpp -o bin/sender.o
	@printf "sender.cpp compiled\n"
receiver:
	@$(CC) $(CCFLAG) src/receiver.cpp src/commons.cpp src/receiver_connection.cpp -o bin/receiver.o
	@printf "receiver.cpp compiled\n"
clean:
	@rm -f bin/*.o
check:
	@cppcheck $(CPPFLAG) ./
	@printf "Cppcheck passed\n"
