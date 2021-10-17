TARGET = main

# Define the linker script location and chip architecture.
LD_SCRIPT = STM32L031K6.ld
MCU_SPEC  = cortex-m0

SRCS:=$(shell find $(SRC_DIRS) -name "*.cpp" -or -name "*.c" -or -name "*.s")
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OUT_DIR)/%.o)

# Toolchain definitions (ARM bare metal defaults)
TOOLCHAIN ?= /usr/bin/arm-none-eabi-
CC = $(TOOLCHAIN)gcc
AS = $(TOOLCHAIN)as
LD = $(TOOLCHAIN)ld
OC = $(TOOLCHAIN)objcopy
OD = $(TOOLCHAIN)objdump
OS = $(TOOLCHAIN)size

# Assembly directives.
ASFLAGS += -c
ASFLAGS += -O0
ASFLAGS += -mcpu=$(MCU_SPEC)
ASFLAGS += -mthumb
ASFLAGS += -Wall
# (Set error messages to appear on a single line.)
ASFLAGS += -fmessage-length=0

# C compilation directives
CFLAGS += -mcpu=$(MCU_SPEC)
CFLAGS += -mthumb
CFLAGS += -Wall
#CFLAGS += -gdwarf-4
CFLAGS += -g3
CFLAGS += -Iinclude
CFLAGS += -Iinc

# (Set error messages to appear on a single line.)
CFLAGS += -fmessage-length=0
# (Set system to ignore semihosted junk)
CFLAGS += --specs=nosys.specs

# Linker directives.
LSCRIPT = ./$(LD_SCRIPT)
LFLAGS += -mcpu=$(MCU_SPEC)
LFLAGS += -mthumb
LFLAGS += -Wall
LFLAGS += --specs=nosys.specs
LFLAGS += -nostdlib
LFLAGS += -lgcc
LFLAGS += -T$(LSCRIPT)

VECT_TBL = ./vector_table.S
AS_SRC   = ./core.S
C_SRC    = ./main.c
LED_SRC += ./src/led.c


OBJS =  $(VECT_TBL:.S=.o)
OBJS += $(AS_SRC:.S=.o)
OBJS += $(C_SRC:.c=.o)
OBJS += $(LED_SRC:.c=.o)

.PHONY: all
all: $(TARGET).bin

%.o: %.S
	$(CC) -x assembler-with-cpp $(ASFLAGS) $< -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@

$(TARGET).elf: $(OBJS)
	$(CC) $^ $(LFLAGS) -o $@

$(TARGET).bin: $(TARGET).elf
	$(OC) -S -O binary $< $@
	$(OS) $<

.PHONY: clean
clean:
	rm -f $(OBJS)
	rm -f $(TARGET).elf
	rm -f $(TARGET).bin
