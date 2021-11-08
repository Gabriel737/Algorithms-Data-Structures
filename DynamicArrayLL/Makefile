DEBUG = 
VERSION = -std=c++11
CFLAGS = -Wall -Wextra -pedantic $(DEBUG) $(VERSION)
LFLAGS = -Wall $(DEBUG) $(VERSION)
# for Windows use del for UNIX use \rm -f
RM = del

INCS = List.h
SRCS = List.cpp \
	Tester.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = Tester.exe

all: $(SRCS) $(EXEC)

# To make an object from source
#.cpp.o: 
%.o:%.cpp $(INCS)
	$(CXX) $(CFLAGS) -c $< -o $@

$(EXEC): $(OBJS) 
	$(CXX) $(LFLAGS) $(OBJS) -o $@

clean:
	del   *.o  $(EXEC)
	echo clean done


