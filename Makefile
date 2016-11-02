#  This makefile is written for RIPSS

MDIR    := $(shell pwd)
WRKDIR  := $(MDIR)/build

.base:
	if ! [ -e $(WRKDIR) ]; then mkdir $(WRKDIR) ; fi;
	touch $(WRKDIR)/.base;

#  Set the source file path
vpath %.cpp src
vpath %.o build
vpath .base build

INCLUDES = -I $(MDIR)/include

CC	= g++
CCFLAG	= -Wall # -Wl,--no-as-needed
# OPTFLAG	= -O2
LIBS	= -lcuba # -lm

%.o: %.cpp .base
	cd $(WRKDIR); $(CC) $(OPTFLAG) $(CCFLAG) $(INCLUDES) -c ../$< -o $*.o

RIPS_OBJ =  rips_main.o         \
	        rips_solver.o       \
			rips_config.o		\
	        cuba_config.o       \
	        function_eta.o      \
	        function_omega2.o   \
	        function_Y.o		\
			integrand_sigma.o   \
			integrand_P.o       \
			integrand_test.o	\
			parser++.o

all: rips

rips:$(RIPS_OBJ)
	$(CC) $(addprefix build/,$(notdir $^)) ${LIBS} -o $@

.PHONY:clean
clean: .base
	rm -rf $(WRKDIR)
	if [ -e rips ]; then rm rips; fi;
