#moduleMake.mak

VPATH +=$(SHARED_SRC)/TaskTemplate/BaseTask/Src

VPATH +=$(SHARED_SRC)/TaskTemplate/BaseTask/Include


CC_INCLUDES +=-I$(SHARED_SRC)/TaskTemplate/BaseTask/Src

CC_INCLUDES +=-I$(SHARED_SRC)/TaskTemplate/BaseTask/Include


OBJECTS +=  PxRosTask.o TaskTimer.o J1939TP.o EosCanSend.o\


################################################################################
#Module Dependencies start here

#ifneq ($(findstring look1_iflf_binlc.o, $(OBJECTS)), look1_iflf_binlc.o)
#	
# OBJECTS +=look1_iflf_binlc.o
#
#endif
