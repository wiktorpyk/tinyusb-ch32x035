if (TOOLCHAIN STREQUAL "gcc")
  set(TOOLCHAIN_COMMON_FLAGS
    -march=rv32imac_zicsr_zifencei
    -mabi=ilp32
    )

  set(FREERTOS_PORT GCC_RISC_V CACHE INTERNAL "")

elseif (TOOLCHAIN STREQUAL "clang")
  set(TOOLCHAIN_COMMON_FLAGS
    -march=rv32imac_zicsr_zifencei
    -mabi=ilp32
    )

  set(FREERTOS_PORT GCC_RISC_V CACHE INTERNAL "")

elseif (TOOLCHAIN STREQUAL "iar")
  message(FATAL_ERROR "IAR is not supported for this CPU")
endif ()
