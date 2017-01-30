UNIT=main

OBJS=$(UNIT).o 
TARGET=$(UNIT)

CXX=g++
CC=gcc

ARCH ?= $(shell uname -m)
ifeq ($(ARCH),x86_64)
LIBDIR = -L $(SYSTEMC_HOME)/lib-linux64
else
LIBDIR = -L $(SYSTEMC_HOME)/lib-linux
endif

INCDIR = -I $(SYSTEMC_HOME)/include
LIBS = -lsystemc -lm $(EXTRA_LIBS)

all: $(TARGET)

$(TARGET): $(OBJS)
	 $(CXX) $(CFLAGS) $(INCDIR) $(LIBDIR) -o $@ $(OBJS) $(LIBS)

#%.o: %.cpp
#	 $(CXX) $(CFLAGS) $(INCDIR) -g -c -Wno-deprecated $< -o $@

$(UNIT).o: $(UNIT).cpp User.h Engine.h Control.h
	$(CXX) $(CFLAGS) $(INCDIR) -g -c -Wno-deprecated $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) *~
