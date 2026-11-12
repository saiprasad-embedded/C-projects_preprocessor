Make file
CC = gcc
CFLAGS = -Wall -Wextra
TARGET = mypreprocessor
SOURCES = main.c comment_removal.c macro_handler.c file_inclusion.c
OBJECTS = $(SOURCES:.c=.o)
all: $(TARGET)
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)
%.o: %.c preprocessor.h
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJECTS) $(TARGET) temp_input.c temp1.txt temp2.txt temp3.txt