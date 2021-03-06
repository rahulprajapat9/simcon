# makefile (use -pg for profiling)

IDIR = include
CC = g++
DEBUG = -O2
PROFILE =
CFLAGS = -Wall -c $(DEBUG) -I$(IDIR) $(PROFILE)

SDIR = src
ODIR = bin
LIBS = -lm -lpthread
RES  = results

_DEPS = simdata.h utils.h algo.h stateIterator.h state.h config.h policy.h mdp.h khanna.h astar.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = simdata.o utils.o algo.o stateIterator.o state.o policy.o khanna.o mdp.o astar.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) $(CFLAGS) -o $@ $<

all: dir $(ODIR)/main

dir:
	mkdir -p $(ODIR)

$(ODIR)/main: $(OBJ)
	$(CC) -I$(IDIR) -o $@ $^ $(SDIR)/main.cpp $(PROFILE) $(LIBS)

clean:
	rm -rf $(ODIR) *~ $(INCDIR)/*~

distclean: clean
	rm -rf $(RES)/*.pdf
	rm -rf $(RES)/*.txt

plot:
	cd $(RES) && gnuplot workload.p cum_profits.p

rebuild: distclean all

.PHONY: clean
