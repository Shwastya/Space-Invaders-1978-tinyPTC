##################################################
### MACROS
##################################################
define COMPILE
$(2) : $(3) $(4)
	$(1) -c -o $(2) $(3) $(5)
endef

define C2O
$(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(patsubst $(SRC)%,$(OBJ)%,$(1))))
endef

define C2H
$(patsubst %.c,%.h,$(patsubst %.cpp,%.hpp,$(1)))
endef
##################################################
### CONFIG
##################################################
APP		:= game
CFLAGS	:= -Wall -pedantic 
CCFLAGS	:= $(CFLAGS) -std=c++17
CC			:= g++ # Compilador en uso
C			:= gcc # compilador de c
MKDIR		:= mkdir -p # -p crea toda la linea de carpetas de una sola
SRC		:= src
OBJ		:= obj
LIBDIR	:= lib
LIBS		:= $(LIBDIR)/picoPNG/libpicopng.a $(LIBDIR)/tinyPTC/libtinyptc.a -lX11
INCDIRS	:= -I$(SRC) -I$(LIBDIR)

ifdef DEBUG
	CCFLAGS += -g
else
	CCFLAGS += -O3
endif


ALLCPPS		:= $(shell find src/ -type f -iname *.cpp)
ALLCS			:= $(shell find src/ -type f -iname *.c)
ALLOBJ		:= $(foreach F,$(ALLCPPS) $(ALLCS),$(call C2O,$(F)))
SUBDIRS		:= $(shell find $(SRC) -type d)
OBJSUBDIRS 	:= $(patsubst $(SRC)%,$(OBJ)%,$(SUBDIRS))

.PHONY: info libs libs-clean libs-cleanall

# Generate Library
$(APP) : $(OBJSUBDIRS) $(ALLOBJ)
	$(CC) -o $(APP) $(ALLOBJ) $(LIBS)


# Generate rules for all objects
$(foreach F,$(ALLCPPS),$(eval $(call COMPILE,$(CC),$(call C2O,$(F)),$(F),$(call C2H,$(F)),$(CCFLAGS) $(INCDIRS))))
$(foreach F,$(ALLCS),$(eval $(call COMPILE,$(C),$(call C2O,$(F)),$(F),$(call C2H,$(F)),$(CFLAGS) $(INCDIRS))))

info :
	$(info $(SUBDIRS))
	$(info $(OBJSUBDIRS))
	$(info $(ALLCPPS))
	$(info $(ALLCS))
	$(info $(ALLCSOBJ))

$(OBJSUBDIRS) : 
	$(MKDIR) $(OBJSUBDIRS)

## CLEAN rules
clean:
	$(RM) -r "./$(OBJ)"

cleanall: clean
	$(RM) "./$(APP)"

## LIB rules
libs:
	$(MAKE) -C $(LIBDIR)
libs-clean:
	$(MAKE) -C $(LIBDIR) clean
libs-cleanall:
	$(MAKE) -C $(LIBDIR) cleanall
