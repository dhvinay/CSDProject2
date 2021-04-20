ifeq ($(OS),Windows_NT)
	HOST = Win32
	PREFX = .\\
	EXEXT = .exe
else
	OS = $(shell uname -s)
	ifeq ($(OS),Linux)
		HOST = Linux
	endif
	ifeq ($(OS),Darwin)
		HOST = MacOSX
	endif
	PREFX = ./
	EXEXT = 
endif


TARGET_sf = Win32

ifdef VERBOSE
Q = 
else
Q =  @
endif

vecho = @echo

export CC = gcc
export AR = ar

CFLAGS = -std=c99
ARFLAGS = rcs

INCDIRS = 
OROOT ?= ./build
OBJODIR ?=  ./bin

ifeq ($(CI), )
	TEST_PREQS = debug
	TEST_EXEC_OPTS = --build-dir=$(OROOT)
else
	TEST_PREQS = all
	TEST_EXEC_OPTS = --build-dir=$(OROOT) --isolated
endif

ifeq ($(HOST),$(TARGET_sf))
	#  
	# Begin Library sf
	#  
	
	ALL_CFLAGS_sf = $(CFLAGS) -DWINVER=0x0601 -D_WIN32_WINNT=0x0601
	
	EXT_INCDIRS_sf = 
	ALL_INCDIR_FLAGS_sf = $(addprefix -I,$(INCDIRS)) $(addprefix -I,$(EXT_INCDIRS_sf))
	ALL_INCS_sf = NewImplModule.h new.h cg.h $(foreach idir,$(INCDIRS),$(wildcard $(idir)/*.h)) $(foreach eidir,$(EXT_INCDIRS_sf),$(wildcard $(eidir)/*.h))
	
	ALL_SRCS_sf = NewImplModule.c new.c cg.c
	
	ALL_OBJS_sf = $(patsubst %.c,$(OBJODIR)/%.o,$(notdir $(ALL_SRCS_sf)))
	
	#  
	# End Library sf
	#  
endif


.PHONY: all debug clean
debug: CFLAGS +=-g
debug: all
all: libsf.a

clean: 
	$(if $(wildcard $(OBJODIR)), $(vecho) "RM $(notdir $(OBJODIR))")
	$(Q) $(RM) -r $(OBJODIR)
	$(Q) $(RM) -r $(OROOT)
ifeq ($(HOST),$(TARGET_sf))
	$(if libsf.a, $(vecho) "RM libsf.a")
	$(Q) $(RM) libsf.a
endif



$(OBJODIR): 
	$(Q) mkdir -p $@ 
define CompileSources
$$(patsubst %.c,$(OBJODIR)/%.o,$$(notdir $(1))): $(1) $$(ALL_INCS_$(2)) Makefile
	$(vecho) "CC $$<"
	$(Q) $(CC) $$(ALL_CFLAGS_$(2)) $$(ALL_INCDIR_FLAGS_$(2)) -c -o $$@ $$<
endef 
$(foreach asrc, $(sort $(ALL_SRCS_sf)), $(eval $(call CompileSources,$(asrc),sf)))

$(ALL_OBJS_sf): | $(OBJODIR)

libsf.a: $(ALL_OBJS_sf)
ifeq ($(HOST),$(TARGET_sf))
	$(vecho) "AR $(notdir $@)"
	$(Q) $(AR) $(ARFLAGS) $@ $^
else
	$(vecho) "Cannot build $(TARGET_sf)-specific 'libsf.a' library under $(HOST)."
endif




