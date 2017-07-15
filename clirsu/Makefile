EXECUTABLE	:= rsu
WORK	= /home/skymooon/workspace/Qt/upload/clirsu

#. a only write the name ,not need lib  and .a
LIBDIR	:=$(WORK)/J2735
LIBS	:=J2735
# if run in DSRC ,use crssJ2735
# headfile document
INCLUDES	+=.\
	$(WORK)/J2735\
	$(WORK)/lib_json
#except root document ,the other document

SRCDIR	+=$(WORK)/lib_json \
	$(WORK)/J2735


# CROSS_COMPILER	=arm-linux-gnueabihf-
CC	:=$(CROSS_COMPILER)gcc
CXX	:=$(CROSS_COMPILER)g++
CFLAGS	:=-std=c++11 -g -Wall -O3
CPPFLAGS 	:= $(CFLAGS)
CPPFLAGS	+= $(addprefix -I,$(INCLUDES))
CPPFLAGS	+= -MMD

RM-F	:= rm -f

# # You shouldn't need to change anything below this point.
#
SRCS := $(wildcard *.cpp) $(wildcard $(addsuffix /*.cpp, $(SRCDIR)))
OBJS := $(patsubst %.cpp,%.o,$(SRCS))
DEPS := $(patsubst %.o,%.d,$(OBJS))
MISSING_DEPS := $(filter-out $(wildcard $(DEPS)),$(DEPS))
MISSING_DEPS_SOURCES := $(wildcard $(patsubst %.d,%.cpp,$(MISSING_DEPS)))


.PHONY : all deps objs clean veryclean rebuild info

all: $(EXECUTABLE)

deps : $(DEPS)

objs : $(OBJS)

clean :
	@$(RM-F) *.o
	@$(RM-F) *.d
	rm -f $(WORK)/lib_json/*.o
	rm -f $(WORK)/lib_json/*.d
veryclean: clean
	@$(RM-F) $(EXECUTABLE)

rebuild: veryclean all
ifneq ($(MISSING_DEPS),)
$(MISSING_DEPS) :
	@$(RM-F) $(patsubst %.d,%.o,$@)
endif
-include $(DEPS)
$(EXECUTABLE) : $(OBJS)
	$(CXX) -o $(EXECUTABLE) $(OBJS) $(addprefix -L,$(LIBDIR)) $(addprefix -l,$(LIBS))

info:
	@echo $(SRCS)
	@echo $(OBJS)
	@echo $(DEPS)
	@echo $(MISSING_DEPS)
	@echo $(MISSING_DEPS_SOURCES)
