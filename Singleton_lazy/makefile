CC = g++
prom = do
obj = singleton.o
INCLUDE = -I ./
OPTION = -Wall -Werror
CPP_FLAGS = '-std=c++11'

$(prom):$(obj)
	@$(CC) $(CPP_FLAGS) -o $@ $<

%.o:%.cpp
	@$(CC) $(CPP_FLAGS) $(INCLUDE) -c $< -o $@

.PHONY : clean
clean :
	@rm -f do *.o