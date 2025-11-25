# specify the compiler, compile flags, and any needed libraries
CC = gcc
CC_OPTIONS = -Wall -O # -Wall for warnings, -O for optimization

# Add linking options for libraries (like -lm) here
# LIBS =

# specify all source files here
SRCS = wzip.c

# specify name of executable here
TARGET = wzip

# translate .c files in the SRCS list to .o's
OBJECTS = $(SRCS:.c=.o)

# not mandatory, but having an "all" option is nice
all : $(TARGET)

# generate the target executable using everything we setup before
$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) # $(LIBS)

# generic rule for .o files
%.o: %.c
	$(CC) $(CC_OPTIONS) -c $< -o $@

# clean option
clean:
	rm -f $(OBJECTS) $(TARGET)
