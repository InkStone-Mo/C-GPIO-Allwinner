PROJECT ?= test

CC ?= arm-linux-gnueabihf-gcc

TEST=$(shell cp ../src/* ./)
SRC = $(shell find . -name '*.c' -type f)
OBJ += $(patsubst %.c,%.o,$(SRC))
SRC_INCLUDE =$(addprefix -I,$(dir $(shell find . -name '*.h' -type f)))

SRC_INCLUDE += -I ../src
LD_LIB += -L ../src
CFLAGS +=  
#-lz
#-ltar

all:$(OBJ)
	@$(CC) $(OBJ) -o $(PROJECT) $(CFLAGS) $(LD_LIB)
	@echo -e "\033[32m LD $(PROJECT) $(CFLAGS) \033[0m"
%.o:%.c
	@echo -e "\033[32m CC $< \033[0m"
	@$(CC) -c $< -o $@ $(SRC_INCLUDE)

clean:
	@echo "$(SRC_INCLUDE)"
	@echo -e "\033[34m $(OBJ) \033[0m"
	@rm -rf $(OBJ) $(PROJECT)
.PHONY:clean
