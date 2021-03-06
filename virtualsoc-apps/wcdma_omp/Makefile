
############## Name of output executable file
ifdef EXENAME
EXE=o-optimize/$(EXENAME).exe
else
EXE=o-optimize/app.exe
endif

LIBGOMP_PATH=${VSOC_APP_DIR}/libgomp
#VSOC_APP_DIR=${VSOC_DIR}/apps
VSOC_SRC_DIR=${VSOC_APP_DIR}/../virtualsoc/include

PAR1 =
############## Default compiler and possible option sets
OMP_CC    = arm-elf-gcc
CC        = arm-elf-gcc
LD        = arm-elf-ld
AS        = arm-elf-as
OBJCOPY   = arm-elf-objcopy
OBJDUMP   = arm-elf-objdump

VSOC_CONFIG_PATH	= ${LIBGOMP_PATH}/config/vsoc
SUPPORT_PATH		= ${VSOC_APP_DIR}/support

############## Initialization of global includes and libs
INCDIR = \
		-I. -I.. \
		-I${SUPPORT_PATH} \
		-I${SUPPORT_PATH}/simulator \
		-I${LIBGOMP_PATH} \
		-I${VSOC_CONFIG_PATH} \
		-I${VSOC_SRC_DIR} \

####################### Library FLAGS #############################
## Enables safe memory allocation check
LIBGOMP_FLAGS	+= -DMEMCHECK_MALLOCS
LIBGOMP_FLAGS	+= -DSTACK_IN_SHARED
## Enable timers
# LIBGOMP_FLAGS += -DSTATS_ENABLE

####### Work-specific
## Enable support for work shares: #pragma omp single, sections and (dynamic) loops
## Only one global work share (1)
# LIBGOMP_FLAGS += -DGLOBAL_WS
## Only one work share/team (2)
LIBGOMP_FLAGS	+= -DSINGLE_WS
## Otherwise, full support for several ws and nowait (3)

############ HAL
## ASM implementation of gomp_hal_lock (faster is disabled: see lock.c)
# LIBGOMP_FLAGS	+= -DASM_LOCKS_FN
## ASM implementation of MSGBarrier_SlaveEnter
# LIBGOMP_FLAGS	+= -DASM_BAR_SLAVEENTER_FN

## Different barrier implementations:
## HW barrier (TODO selective HW barrier)
#LIBGOMP_FLAGS	+= -DMPARM -DMPARM_SW_BAR

############## Tasking-specific flags
# LIBGOMP_FLAGS += -DTASKING_ENABLED
# ....

####################### Other FLAGS ##################################
COMMON_CFLAGS = $(INCDIR)  -msoft-float -mcpu=arm7
COMMON_CFLAGS	+= -Winline
COMMON_CFLAGS	+= ${PAR1} ${PAR2}

CFLAGS	    = -O0 -g $(COMMON_CFLAGS) $(LIBGOMP_FLAGS)
LDFLAGS     += -L${VSOC_APP_DIR}/support/lib -lgcc

ASFLAGS    	= -mfpu=softfpa

OMP_CFLAGS   	= -O1 ${COMMON_CFLAGS} -fopenmp $(LIBGOMP_FLAGS)

################### LIBGOMP/APPSUPPORT Sources ########################
CSRCS  += ${LIBGOMP_PATH}/root.c
CSRCS  += ${SUPPORT_PATH}/simulator/appsupport.c
CSRCS  += fir.c
CSRCS  += qpsk.c
## Boot
ASSRCS = ${SUPPORT_PATH}/simulator/boot.s

############################ OpenMP Sources ############################


OMP_CSRCS  += wcdma.c


############################ OBJECTS ###################################

COBJS  = $(CSRCS:.c=.o)
ASOBJS = $(ASSRCS:.s=.o)
OMP_COBJS  = $(OMP_CSRCS:.c=.o)

OBJS   = $(COBJS) $(ASOBJS) $(OMP_COBJS)

############## Actual build process

all: $(EXE)

$(EXE): $(OBJS)
	test -d o-optimize || mkdir o-optimize
	$(OMP_CC) $(OMP_CFLAGS) -c -o $(OMP_COBJS) $(OMP_CSRCS)
	$(LD) -T ${SUPPORT_PATH}/simulator/vsoc.ld -o linked.o $(OBJS) $(LDFLAGS)
	$(OBJCOPY) -O binary linked.o $@
	ln -sf o-optimize/app.exe TargetMem_1.mem

run:
	vsoc.x --tb=32 -c 8 --intc=c --ics=16

run_stat:
	vsoc.x --tb=32 -c 8 --intc=c --ics=16 -s

############## Support routines
.PHONY : clean disassemble
clean:
	rm -f *.o *~
	rm -rf o-optimize/
	rm -r -f ${LIBGOMP_PATH}/*.o
	rm -r -f ${SUPPORT_PATH}/*.o
	rm -f TargetMem*

disassemble: $(EXE)
	$(OBJDUMP) -D linked.o > linked.dis

echo:
	@echo $(VSOC_APP_DIR)
