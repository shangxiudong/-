
TASK := main
OBJ := main.o my_print.o
CC := gcc
CFLAGS := -c
RM := rm -f
.PHONY:all
all:$(TASK)

main: main.o my_print.o
	@echo "link all object files"
	$(CC) $^ -o $@

%.o: %.c
	@echo "compile source file to object file"
	$(CC) $(CFLAGS) $< -o $@

.PHONY:clean
clean:
	@echo "clean all task files and object files"
	$(RM) $(TASK) $(OBJ)
