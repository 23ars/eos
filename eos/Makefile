#############################################
# Compiler settings ( flags)				#
#############################################
INCLUDE_DIR=
EOS_HEADERS=include/eos
COMPILER_PATH=d:\Tools\Freescale\KDS_v3\Toolchain\bin
COMPILER_PREFIX=arm-none-eabi-
COMPILER=$(COMPILER_PREFIX)gcc.exe
ARCHIVER=$(COMPILER_PATH)ar.exe
CC=$(COMPILER_PATH)\$(COMPILER)
AR=$(COMPILER_PATH)\$(COMPILER)
OUTPUT=eos.a

HOST_C_FLAGS += -Wall -g3 -O2 -I$(INCLUDE_DIR) -I$(EOS_HEADERS) -mcpu=cortex-m4 -mthumb -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -std=gnu11


HOST_LD_FLAGS +=
LIBFLAGS=$(HOST_LD_FLAGS)
DEBUGVAR=DEBUG


APP_DIR=app
ARCH_DIR=arch
DOC_DIR=Documentation
DRIVERS_DIR=drivers
KERNEL_DIR=kernel
LIB_DIR=lib
SCRIPTS_DIR=scripts

#############################################
# Compile and Link mode (debug/release)		#
#############################################
ifdef DEBUGVAR
	OUTPUT=Debug
	CFLAGS=$(HOST_C_FLAGS)
	DEBUGFLAGS=-D DEBUG 
	
else
	OUTPUT=Release
	CFLAGS=$(HOST_C_FLAGS)
    DEBUGFLAGS=
endif
#############################################
# Targets and objects						#
#############################################
TARGETS=\
	entry
	
	
		

OBJECTS=\
	$(OUTPUT)/entry.o
	
	
	
#############################################
# Compile and Link Targets					#
#############################################
all: clean link_compile 
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM GNU Archiver'
	$(AR) -r  $(OUTPUT)
	@echo 'Finished building target: $@'
	@echo ' '

	
 

link_compile: $(TARGETS)

clean:
#	rm -f $(OUTPUT)/*
	
entry: 
	@echo 'Invoking: Cross ARM C Compiler'
	$(CC) $(CFLAGS) -MMD -MP -MF"$(KERNEL_DIR)/entry.d" -MT"$(KERNEL_DIR)/entry.o" -c $(KERNEL_DIR)/entry.c $(DEBUGFLAGS) -o $(OUTPUT)/entry.o 
	@echo 'Finished building: $@'
	@echo ' '


#############################################
# Special Targets							#
#############################################

run_lint:


	