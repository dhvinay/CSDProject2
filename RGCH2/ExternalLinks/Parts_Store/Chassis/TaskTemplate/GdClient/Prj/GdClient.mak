#moduleMake.mak

VPATH +=$(SHARED_SRC)/TaskTemplate/GdClient/Src


CC_INCLUDES += -I$(SHARED_SRC)/TaskTemplate/GdClient/Src


OBJECTS +=GdLib.o \


################################################################################
#Module Dependencies start here

#ifneq ($(findstring look1_iflf_binlc.o, $(OBJECTS)), look1_iflf_binlc.o)
#	
# OBJECTS +=look1_iflf_binlc.o
#
#endif