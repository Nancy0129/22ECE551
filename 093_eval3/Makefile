CPPFLAGS=-std=gnu++98 -pedantic -Wall -Werror -ggdb3
PROGS=cyoa-step1 cyoa-step2 cyoa-step3 cyoa-step4
OBJS=$(patsubst %,%.o,$(PROGS)) story.o page.o cyoa.o
all: $(PROGS)
cyoa-step%: cyoa-step%.o 
	g++ -o $@ $^
%.o: %.cpp story.h page.h cyoa.h
	g++ $(CPPFLAGS) -c $<
.PHONY: clean
clean:
	rm -f *~ $(PROGS) $(OBJS)

