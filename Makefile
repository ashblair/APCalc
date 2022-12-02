# call make w/ one of the following defined for cross compilation:
#CROSS := i686
#CROSS := x86_64

BFDHEAD := elf64-x86-64

ifneq ($(CROSS),)
	FULLCROSS := $(CROSS)-w64-mingw32.$(LINK_TYPE)-
	EXE_PFX := wine 
	EXE_SFX := _$(CROSS)-w64-mingw32.$(LINK_TYPE).exe
	RELEASE_DIR := true
	ifeq ($(CROSS), i686)
		BFDHEAD := pei-i386
	else
		BFDHEAD := pei-x86-64
	endif
	OTHERFLAGS := -fpermissive -mwindows
endif

CC=$(FULLCROSS)gcc
LD=$(FULLCROSS)ld
AR=$(FULLCROSS)ar
PKG_CONFIG=$(FULLCROSS)pkg-config
CXX		  := $(FULLCROSS)g++
CPPSTANDARD:= -std=c++17

OBJCPY 	:= $(FULLCROSS)objcopy --input binary --output $(BFDHEAD) --binary-architecture i386
RSCCPY	:= $(FULLCROSS)windres -O coff
REL 	:= rel
DBG		:= dbg

ifneq ($(RELEASE_DIR),)
	OBJDIR := $(REL)
	OTHEROBJDIR := $(DBG)
else
	OBJDIR := $(DBG)
	OTHEROBJDIR := $(REL)
	DEBUGFLAG := -ggdb
endif

CXX_FLAGS := $(CPPSTANDARD) $(OTHERFLAGS) $(DEBUGFLAG)

BIN		:= bin/$(OBJDIR)
OBIN	:= bin/$(OTHEROBJDIR)
SRC		:= src
INC		:= inc
OBJ     := obj/$(OBJDIR)
OOBJ	:= obj/$(OTHEROBJDIR)
RSC 	:= rsc
DEP		:= dep
CWD		:= $(PWD)
CFLAGS	:= `$(PKG_CONFIG) gtkmm-3.0 --cflags`
LIBRARIES	:= `$(PKG_CONFIG) gtkmm-3.0 --libs`
# -lcuda library for parallel processing

EXECUTABLE := $(notdir $(CWD))$(EXE_SFX)

ICONFILE := $(CWD)/share/icons/small.ico
USETERMINAL := true
LOGFILE := $(CWD)/log.txt

#derived file variables:
allinBIN := $(notdir $(shell find ./$(BIN) -maxdepth 1 -type f))
allinOTHERBIN := $(notdir $(shell find ./$(OBIN) -maxdepth 1 -type f))
allinOBJ := $(notdir $(shell find ./$(OBJ) -maxdepth 1 -type f))
allinOTHEROBJ := $(notdir $(shell find ./$(OOBJ) -maxdepth 1 -type f))
allinDEP := $(notdir $(shell find ./$(DEP) -maxdepth 1 -type f))
allinRSC := $(notdir $(shell find ./$(RSC) -maxdepth 1 -type f))
allinSRC := $(notdir $(shell find ./$(SRC) -maxdepth 1 -type f))
sources :=  $(filter %.cpp, $(allinSRC))
sourceobjs := $(addsuffix .o, $(basename $(notdir $(sources))))
incdepends := $(addsuffix .d, $(basename $(notdir $(sources))))
resourceobj:= $(addsuffix .o, $(allinRSC))
delobjs := $(filter-out $(resourceobj), $(filter-out $(sourceobjs), $(allinOBJ)))
deldeps := $(filter-out $(incdepends), $(allinDEP))
workobjects := $(addprefix $(OBJ)/, $(sourceobjs))
workdeps := $(addprefix $(DEP)/, $(incdepends))
workobjrsc := $(addprefix $(OBJ)/, $(resourceobj))
allobjs := $(workobjects) $(workobjrsc)
rundesktopfile := $(EXECUTABLE).desktop
runshellfile := $(EXECUTABLE).sh

.PHONY: all
all: logsetup compile

.PHONY: run
run: all
	$(EXE_PFX)./$(BIN)/$(EXECUTABLE)

.PHONY: compile
compile: prepobjs prepdepends make_src make_rsc make_bin
	@printf \# > $(rundesktopfile)
	@echo !/usr/bin/env xdg-open >> $(rundesktopfile)
	@echo [Desktop Entry] >> $(rundesktopfile)
	@echo Name=Run $(EXECUTABLE) >> $(rundesktopfile)
	@echo Comment=A Nemo Work-around >> $(rundesktopfile)
	@echo Exec=$(CWD)/$(EXECUTABLE).sh >> $(rundesktopfile)
	@echo Icon=$(ICONFILE) >> $(rundesktopfile)
	@echo Terminal=$(USETERMINAL) >> $(rundesktopfile)
	@echo Type=Application >> $(rundesktopfile)
	@printf \# > $(runshellfile)
	@echo !/bin/bash >> $(runshellfile)
	@echo cd $(CWD) >> $(runshellfile)
	@echo $(EXE_PFX)./$(BIN)/$(EXECUTABLE) >> $(runshellfile)
	@echo echo \"Press 'Enter' To Exit\" >> $(runshellfile)
	@echo read extKey >> $(runshellfile)
	@chmod a+x $(EXECUTABLE).*

.PHONY: clean
clean:
	-@if [ $(words $(allinBIN)) -gt  0 ]; then rm -f $(BIN)/*; fi
	-@if [ $(words $(allinOTHERBIN)) -gt 0 ]; then rm -f $(OBIN)/*; fi
	-@if [ $(words $(allinOBJ)) -gt  0 ]; then rm -f $(OBJ)/*; fi
	-@if [ $(words $(allinOTHEROBJ)) -gt 0 ]; then rm -f $(OOBJ)/*; fi 
	-@if [ $(words $(allinDEP)) -gt  0 ]; then rm -f $(DEP)/*; fi 

# remove all objects that don't have a source or resource
.PHONY: prepobjs
prepobjs:
	-@for X in $(delobjs) ; do rm -f $(OBJ)/$$X ; done

#remove all depend files that don't have a source
.PHONY: prepdepends
prepdepends:
	-@for X in $(deldeps) ; do rm -f $(DEP)/$$X; done

.PHONY: make_bin
make_bin: $(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(allobjs)
	@$(CXX) $(CXX_FLAGS) $^ -o $@ $(LIBRARIES)
	@echo linked all objects into $@ >> $(LOGFILE)

.PHONY: make_rsc
make_rsc: $(workobjrsc)

$(OBJ)/%.o:$(RSC)/%
	@if [ $(suffix $<) = ".rc" ]; then \
	$(RSCCPY) $< $@ ; \
	else \
	$(OBJCPY) $< $@ ; fi ;
	@echo resource $< made into object $@ >> $(LOGFILE) ;

.PHONY: make_src
make_src: compile_src

.PHONY: compile_src
compile_src: $(workobjects)

$(OBJ)/%.o:$(SRC)/%.cpp
	@$(CXX) $(CXX_FLAGS) -I$(INC) $(CFLAGS) $< -c -o $@
	@echo new object file compiled [$@] >> $(LOGFILE)
	@STEM=$(basename $(notdir $@)) ; \
	$(CXX) -I$(INC) -MM $< -MF $(DEP)/$${STEM}.d ; \
	sed -i "s,$${STEM}.o,$(OBJ)/$${STEM}.o $(OOBJ)/$${STEM}.o," $(DEP)/$${STEM}.d ; \
	echo new depend file compiled [$(DEP)/$${STEM}.d] >> $(LOGFILE)

$(workdeps):

include $(workdeps)

.PHONY: logsetup
logsetup:
	@echo BUILD LOG `date` > $(LOGFILE)
	@echo -----\>User Variables: >> $(LOGFILE)
	@echo [CXX=$(CXX)] - [CXX_FLAGS=$(CXX_FLAGS)] >> $(LOGFILE)
	@echo [BIN=$(BIN)] - [OBIN$(OBIN)] - [SRC=$(SRC)] >> $(LOGFILE)
	@echo [INC=$(INC)] - [OBJ=$(OBJ)] - [OOBJ=$(OOBJ)] >> $(LOGFILE)
	@echo [RSC=$(RSC)] - [DEP=$(DEP)] - [CWD=$(CWD)] >> $(LOGFILE)
	@echo [CFLAGS=$(CFLAGS)] >> $(LOGFILE)
	@echo [EXECUTABLE=$(EXECUTABLE)] - [ICONFILE=$(ICONFILE)] >> $(LOGFILE)
	@echo [LIBRARIES=$(LIBRARIES)] >> $(LOGFILE)
	@echo [USETERMINAL=$(USETERMINAL)] - [LOGFILE=$(LOGFILE)] >> $(LOGFILE)
	@echo [CROSS=$(CROSS)] - [BFDHEAD=$(BFDHEAD)] - [DEBUGFLAG=$(DEBUGFLAG)] >> $(LOGFILE)
	@echo [RELEASE_DIR=$(RELEASE_DIR)] - [REL=$(REL)] - [DBG=$(DBG)] >> $(LOGFILE)
	@echo [OBJDIR=$(OBJDIR)] - [OTHEROBJDIR=$(OTHEROBJDIR)] >> $(LOGFILE)
	@echo -----\>Calculated/Environmental Variables: >> $(LOGFILE)
	@echo [sources=$(sources)] >> $(LOGFILE)
	@echo [sourceobjs=$(sourceobjs)] >> $(LOGFILE)
	@echo [incdepends=$(incdepends)] >> $(LOGFILE)
	@echo [resourceobj=$(resourceobj)] >> $(LOGFILE)
	@echo [delobjs=$(delobjs)] >> $(LOGFILE)
	@echo [deldeps=$(deldeps)] >> $(LOGFILE)
	@echo [workobjects=$(workobjects)] >> $(LOGFILE)
	@echo [workdeps=$(workdeps)] >> $(LOGFILE)
	@echo [workobjrsc=$(workobjrsc)] >> $(LOGFILE)
	@echo [allinBIN=$(allinBIN)] >> $(LOGFILE)
	@echo [allinOTHERBIN=$(allinOTHERBIN)] >> $(LOGFILE)
	@echo [allinOBJ=$(allinOBJ)] >> $(LOGFILE)
	@echo [allinOTHEROBJ=$(allinOTHEROBJ)] >> $(LOGFILE)
	@echo [allinDEP=$(allinDEP)] >> $(LOGFILE)
	@echo [allinRSC=$(allinRSC)] >> $(LOGFILE)
	@echo [allinSRC=$(allinSRC)] >> $(LOGFILE)
	@echo [allobjs=$(allobjs)] >> $(LOGFILE)
	@echo -----\>MAKE OUTPUT FOLLOWS: >> $(LOGFILE)
