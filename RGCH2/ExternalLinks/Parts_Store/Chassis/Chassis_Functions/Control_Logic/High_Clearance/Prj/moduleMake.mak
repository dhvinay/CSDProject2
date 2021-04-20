#moduleMake.mak

VPATH +=$(CONTROL_LOGIC)/High_Clearance/Src

VPATH +=$(CONTROL_LOGIC)/High_Clearance/MBD/Gen


CC_INCLUDES +=-I$(CONTROL_LOGIC)/High_Clearance/Src

CC_INCLUDES +=-I$(CONTROL_LOGIC)/High_Clearance/MBD/Gen


OBJECTS +=HighClearance_model.o HighClearance_task.o HighClearance_gd.o HighClearance_eeprom.o


################################################################################
#Module Dependencies start here
ifneq ($(findstring look1_iflf_binlca.o, $(OBJECTS)), look1_iflf_binlca.o)
 
OBJECTS +=look1_iflf_binlca.o

endif

