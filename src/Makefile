SRCS=boid.cpp main.cpp mathUtils.cpp flock.cpp display.cpp

OBJS=$(SRCS:%.cpp=$(OBJDIR)/%$(OBJ_EXT))
OBJSC=$(SRCS:%.c=$(OBJDIR)/%$(OBJ_EXT))

all: $(OBJS) $(OBJSC)

-include $(SRCS:.cpp=.d)
	
clean:
	rm -f *~ core *.d

$(OBJDIR)/%.o:%.cpp
	$(CPP) $(CPPFLAGS) $(INCLUDES) $(OBJ_OPT) $(LDFLAGS) $< -o $@


%.d: %.cpp
	set -e; \
	$(CPP) -MM $(CPPFLAGS) $(INCLUDES) $< \
	| sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' > $@; \
	[ -s $@ ] || rm -f $@