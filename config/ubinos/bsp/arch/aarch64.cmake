#
# Copyright (c) 2019 Sung Ho Park and CSOS
# 
# SPDX-License-Identifier: Apache-2.0
#

set_cache(UBINOS__BSP__CPU_ARCH                                                   "AARCH64"           STRING)
set_cache(UBINOS__BSP__CPU_ENDIAN                                                 "LITTLE"        STRING)

set_cache(UBINOS__BSP__GDBSCRIPT_FILE_INIT                                        "${PROJECT_UBINOS_DIR}/resource/ubinos/bsp/arch/aarch64/gdb_init.gdb"                              PATH)

set_cache(UBINOS__BSP__GDBSCRIPT_FILE_ATTACH                                      "${PROJECT_UBINOS_DIR}/resource/ubinos/bsp/arch/aarch64/gdb_sram_attach.gdb"                      PATH)
set_cache(UBINOS__BSP__GDBSCRIPT_FILE_DEBUG                                       "${PROJECT_UBINOS_DIR}/resource/ubinos/bsp/arch/aarch64/gdb_sram_debug.gdb"                       PATH)
set_cache(UBINOS__BSP__GDBSCRIPT_FILE_RUN                                         "${PROJECT_UBINOS_DIR}/resource/ubinos/bsp/arch/aarch64/gdb_sram_run.gdb"                         PATH)

