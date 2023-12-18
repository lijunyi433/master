CC = g++
OBJECTS = client.o
OPTION += -Wall -Werror

do : $(OBJECTS)
	@$(CC) -o do $(OBJECTS)

%.o : %.cpp
	@$(CC) -c $< 


.PHONY : clean
clean :
	@rm -f do *.o