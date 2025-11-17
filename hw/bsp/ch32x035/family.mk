# https://www.embecosm.com/resources/tool-chain-downloads/#riscv-stable
#CROSS_COMPILE ?= riscv32-unknown-elf-

# Toolchain from https://nucleisys.com/download.php
#CROSS_COMPILE ?= riscv-nuclei-elf-

# Toolchain from https://github.com/xpack-dev-tools/riscv-none-elf-gcc-xpack
CROSS_COMPILE ?= riscv-none-elf-

CH32_FAMILY = ch32x035
SDK_DIR = hw/mcu/wch/ch32x035
SDK_SRC_DIR = $(SDK_DIR)/EVT/EXAM/SRC

include $(TOP)/$(BOARD_PATH)/board.mk

# CH32X035 core uses fence.i instruction which requires zifencei extension
# Use custom CPU_CORE that includes zifencei in architecture flags
CPU_CORE ?= rv32imac_zifencei-ilp32

CFLAGS += \
	-flto \
	-msmall-data-limit=8 \
	-mno-save-restore \
	-fmessage-length=0 \
	-fsigned-char \
	-DCFG_TUSB_MCU=OPT_MCU_CH32X035 \
	-DCFG_TUD_WCH_USBIP_USBFS=1

# https://github.com/openwch/ch32v307/pull/90
CFLAGS += -Wno-error=strict-prototypes

# Check if picolibc is available (Ubuntu/Debian riscv64-unknown-elf toolchain)
PICOLIBC_SPECS = /usr/lib/picolibc/riscv64-unknown-elf/picolibc.specs
ifneq (,$(wildcard $(PICOLIBC_SPECS)))
  # picolibc - use vendor startup instead of picolibc crt0
  CFLAGS += -isystem /usr/lib/picolibc/riscv64-unknown-elf/include
  LDFLAGS_GCC += \
    -nostartfiles -nodefaultlibs \
    -L/usr/lib/picolibc/riscv64-unknown-elf/lib/rv32imac/ilp32 \
    -L/usr/lib/picolibc/riscv64-unknown-elf/lib \
    -lc -lgcc
else
  # newlib/nosys
  LDFLAGS_GCC += -nostdlib -nostartfiles --specs=nosys.specs --specs=nano.specs
endif

SRC_C += \
	src/portable/wch/dcd_ch32_usbfs.c \
	$(SDK_SRC_DIR)/Core/core_riscv.c \
	$(SDK_SRC_DIR)/Peripheral/src/${CH32_FAMILY}_gpio.c \
	$(SDK_SRC_DIR)/Peripheral/src/${CH32_FAMILY}_misc.c \
	$(SDK_SRC_DIR)/Peripheral/src/${CH32_FAMILY}_rcc.c \
	$(SDK_SRC_DIR)/Peripheral/src/${CH32_FAMILY}_usart.c

SRC_S += \
	$(SDK_SRC_DIR)/Startup/startup_${CH32_FAMILY}.S

INC += \
	$(TOP)/$(BOARD_PATH) \
	$(TOP)/$(SDK_SRC_DIR)/Core \
	$(TOP)/$(SDK_SRC_DIR)/Peripheral/inc

LD_FILE ?= $(FAMILY_PATH)/linker/ch32x035.ld

# For freeRTOS port source
FREERTOS_PORTABLE_SRC = $(FREERTOS_PORTABLE_PATH)/RISC-V

OPENOCD_WCH_OPTION=-f $(TOP)/$(FAMILY_PATH)/wch-riscv.cfg
flash: flash-openocd-wch
