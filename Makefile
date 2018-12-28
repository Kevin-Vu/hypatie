# Adapted from Lionel Lacassagne's Makefile

FILE = openssl.c parse_prop.c util_string.c util_file.c switch.c cli.c main.c 

SRC_PATH = src
OBJ_PATH = obj
EXE_PATH = exe
INC_PATH = include

CC = gcc

C_CC_FLAGS = -Wall -Wextra -g -pedantic -std=c99
C_OPTIMISATION_FLAGS = -O3
C_OPENSSL_FLAGS = -lcrypto -lssl
C_INC_FLAGS = -I$(INC_PATH)

CFLAGS = $(C_CC_FLAGS) $(C_OPTIMISATION_FLAGS) $(C_OPENSSL_FLAGS) $(C_INC_FLAGS) 

PRODUCT	= free_dashlane.exe

SRC = $(addprefix ${SRC_PATH}/, $(FILE))
OBJ = $(addprefix ${OBJ_PATH}/, $(addsuffix .o, $(basename $(FILE))))

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(EXE_PATH)/$(PRODUCT): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(INC) $(LIB)

clean:
	rm -f $(OBJ_PATH)/*.o
	rm -f ${EXE_PATH}/${PRODUCT}
