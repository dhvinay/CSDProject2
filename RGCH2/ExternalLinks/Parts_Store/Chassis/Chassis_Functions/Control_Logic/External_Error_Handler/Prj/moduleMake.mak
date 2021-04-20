#moduleMake.mak

VPATH +=$(CONTROL_LOGIC)/External_Error_Handler/Src


CC_INCLUDES +=-I$(CONTROL_LOGIC)/External_Error_Handler/Src


OBJECTS +=Eemm_Conf.o Eemm_Eep.o Eemm_Func.o Eemm_Kwp.o Eemm_Task.o


################################################################################
#Module Dependencies start here

#ifneq ($(findstring look1_iflf_binlca.o, $(OBJECTS)), look1_iflf_binlca.o)
# 
#OBJECTS +=look1_iflf_binlca.o
#
#endif

