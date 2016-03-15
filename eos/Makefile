#############################################
# Compiler settings ( flags)				#
#############################################
INCLUDE_DIR=include/eos/include
EOS_HEADERS=include/eos
COMPILER_PATH=d:\Tools\Atmel\Atmel Toolchain\AVR32 GCC\Native\3.4.1067\avr32-gnu-toolchain\bin
COMPILER_PREFIX=avr32-
COMPILER=$(COMPILER_PREFIX)gcc.exe
CC=$(COMPILER_PATH)\$(COMPILER)







HOST_C_FLAGS += -Wall -g -O2 -I$(INCLUDE_DIR) -I$(EOS_HEADERS) -D __AVR__ 
HOST_LD_FLAGS +=
LIBFLAGS=$(HOST_LD_FLAGS)
DEBUGVAR=DEBUG

#############################################
# Define all folders and subfolders			#
#	Folders meaning:						#
#											#
#		apps = folder where applications 	#
#				will be wrote				#
#		arch = will contain the HAL and 	#
#				other c and asm files 		#
#				related to each				# 
#				architecture.				#
#		drivers								#
#		include = headers for kernel& 		#
#				apps development			#
#		kernel = operating system 			#
#		core/ basic functionalities			#
#	( scheduler, process, threads, 			#
#				memory protection)			#
#		lib = libs for apps					#
#		scripts = scripts for configuring os#
#############################################
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
	entry\
	process\
	scheduler
		

OBJECTS=\
	$(OUTPUT)/entry.o\
	$(OUTPUT)/process.o\
	$(OUTPUT)/scheduler.o
	
#############################################
# Compile and Link Targets					#
#############################################
all: clean link_compile objprepare
		$(CC) $(CFLAGS)\
	   	-Wl,-Map=$(OUTPUT)/eos.map -Wl,--start-group\
	 	-Wl,-lm  -Wl,--end-group\
	  	-Wl,--gc-sections -mmcu=atmega32\
	   	$(OBJECTS) $(DEBUGFLAGS) -o $(OUTPUT)/eos.elf\
	
objprepare:
	"$(COMPILER_PATH)\avr32-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  $(OUTPUT)/eos.elf $(OUTPUT)/eos.hex
	"$(COMPILER_PATH)\avr32-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex $(OUTPUT)/eos.elf $(OUTPUT)/eos.eep || exit 0
	"$(COMPILER_PATH)\avr32-objdump.exe" -h -S $(OUTPUT)/eos.elf > $(OUTPUT)/eos.lss
	"$(COMPILER_PATH)\avr32-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures $(OUTPUT)/eos.elf $(OUTPUT)/eos.srec
	"$(COMPILER_PATH)\avr32-size.exe" $(OUTPUT)/eos.elf 	
	  
	 

link_compile: $(TARGETS)

clean:
#	rm -f $(OUTPUT)/*
	
entry: 
	$(CC) $(CFLAGS) -c $(KERNEL_DIR)/entry.c $(DEBUGFLAGS) -o $(OUTPUT)/entry.o 

process:
	$(CC) $(CFLAGS) -c $(KERNEL_DIR)/process.c $(DEBUGFLAGS) -o $(OUTPUT)/process.o

scheduler:
	$(CC) $(CFLAGS) -c $(KERNEL_DIR)/scheduler.c $(DEBUGFLAGS) -o $(OUTPUT)/scheduler.o

#############################################
# Special Targets							#
#############################################

run_lint:


	