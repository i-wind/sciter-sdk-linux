CXX = g++

CPPFLAGS := -m64 -pipe -O3 -g -Wall -W -Wextra -std=c++11 -I../../../include
CPPFLAGS += -Wno-unused-parameter -Wno-unknown-pragmas
CPPFLAGS += $(shell pkg-config --cflags gtk+-3.0)

LDFLAGS := -m64 -g -Wl,-O3 $(shell pkg-config --libs gtk+-3.0)
LDFLAGS += -L../../../bin.gtk/x64 -ldl -lsciter-gtk

APP = utest
OBJS = $(APP).o resources.o

all: resources.cpp $(APP)

resources.cpp:
	../../../bin.gtk/x64/packfolder res $@ -v "resources"

resources.o: resources.cpp

$(APP): $(OBJS)
	$(CXX) -o $@ $< $(LDFLAGS)

clean:
	rm -f *.o $(APP) resources.cpp

.PHONY: all
