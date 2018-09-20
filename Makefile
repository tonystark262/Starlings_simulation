TOPDIR = $(PWD)
SUBDIRS = $(TOPDIR)/src/
OBJDIR = $(TOPDIR)/builds
INCLUDES = -I$(TOPDIR)/include/

LDFLAGS = -lglut -lGLU -lGL -lGLEW

BINDIR = $(TOPDIR)/bin/
LIBDIR = $(TOPDIR)/lib/
TESTDIRS = $(TOPDIR)/tests/
CPP = g++
CPPFLAGS = -Wall -g -Wno-unused -std=c++11 $(INCLUDES) 

OBJ_EXT = .o
EXE_EXT = 
OBJ_OPT = -c

OBJECTS = $(OBJDIR)/boid.o $(OBJDIR)/main.o $(OBJDIR)/mathUtils.o $(OBJDIR)/flock.o $(OBJDIR)/display.o

TARGET = boids

.EXPORT_ALL_VARIABLES:
all: subdirs
	$(CPP) $(CPPFLAGS) $(INCLUDES) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

subdirs: $(SUBDIRS)

$(SUBDIRS): 
	$(MAKE) -C $@

.PHONY: subdirs $(SUBDIRS)

tests: subdirs testdir

testdir: $(TESTDIRS)

$(TESTDIRS):
	$(MAKE) -C $@

.PHONY: testdir $(TESTDIRS)

clean:
	rm -f *~ core;rm -f lib/*
	@for T in $(SUBDIRS); do make -C $$T $@; done
	#@for T in $(TESTDIRS); do make -C $$T $@; done
	rm -f $(TOPDIR)/objects/*.o
	rm -f $(TOPDIR)/include/*~

.PHONY: clean





