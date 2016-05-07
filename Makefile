CPP_CODE_FILES := $(wildcard *.cpp)
CPP_OBJ_FILES := $(addsuffix .o,$(basename $(CPP_CODE_FILES)))
H_FILES := $(wildcard *.h)
TARGET := solver
COMPILER = clang++
FLAGS = -g3 -Wall -Werror -Wextra -pedantic -std=c++11

.PHONY: all test run kill

all: build

build: $(TARGET)

$(TARGET): $(CPP_OBJ_FILES)
	$(COMPILER) $(CPP_OBJ_FILES) -o $(TARGET)

%.o: %.cpp $(H_FILES)
	$(COMPILER) $< $(FLAGS) -c -o $@

clean:
	-rm -rf *.o $(TARGET)

kill:
	pkill -f ./$(TARGET)

run: $(TARGET) userlist.txt port.txt
	./$(TARGET) $(shell cat port.txt) -n -d < userlist.txt

userlist.txt:
	python -c "print 'user1 password1\nuser2 password2\nuser3 password3\nuser4 password4'" > userlist.txt

port.txt:
	@python -c "import os; id=os.getuid(); port = (id % (65535-1024)) + 1024; print port" > port.txt
	@echo "Assigned port to `cat port.txt`"

