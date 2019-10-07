set(INCLUDE__UBINOS__UBIK                                                       TRUE)


set_cache_default(UBINOS__UBIK__TICK_PER_SEC                                    1000    STRING "Ticks per second")

set_cache_default(UBINOS__UBIK__TASK_NAME_SIZE_MAX                              15      STRING "Maximum name size of task")
set_cache_default(UBINOS__UBIK__TASK_PRIORITY_MAX                               9       STRING "Maximum priority of task")
set_cache_default(UBINOS__UBIK__TASK_MAXWAITSIGOBJ_MAX                          8       STRING "Maximum waiting signal object of task")
set_cache_default(UBINOS__UBIK__TASK_STACK_DEPTH_DEFAULT                        1024    STRING "Default stack depth of task")
set_cache_default(UBINOS__UBIK__TASK_STACK_DEPTH_MIN                            512     STRING "Minimum stack depth of task")
set_cache_default(UBINOS__UBIK__IDLETASK_STACK_DEPTH                            512     STRING "Stack depth of idle task")

set_cache_default(UBINOS__UBIK__MSGQ_MSGSIZE_MAX                                16      STRING "Maximum message size of message queue")

set_cache_default(UBINOS__UBIK__EXCLUDE_TICK_HOOKFUNC                           FALSE   BOOL "Exclude tick hook functions")

set_cache_default(UBINOS__UBIK__EXCLUDE_KERNEL_MONITORING                       FALSE   BOOL "Exclude kernel monitoring feature")
set_cache_default(UBINOS__UBIK__EXCLUDE_TASK_MONITORING                         FALSE   BOOL "Exclude task monitoring feature")
set_cache_default(UBINOS__UBIK__EXCLUDE_TASK_PRIORITY_INHERITANCE               FALSE   BOOL "Exclude task priority inheritance feature")
set_cache_default(UBINOS__UBIK__EXCLUDE_IDLETASK_GARBAGECOLLECT                 FALSE   BOOL "Exclude idle task garbage collect feature")
set_cache_default(UBINOS__UBIK__EXCLUDE_IDLETASK_HOOKFUNC                       FALSE   BOOL "Exclude idle task hook function")
set_cache_default(UBINOS__UBIK__EXCLUDE_CONDV                                   FALSE   BOOL "Exclude condition variable")
set_cache_default(UBINOS__UBIK__EXCLUDE_MSGQ                                    FALSE   BOOL "Exclude message queue")
set_cache_default(UBINOS__UBIK__EXCLUDE_SEM                                     FALSE   BOOL "Exclude semaphore")
set_cache_default(UBINOS__UBIK__EXCLUDE_SIGNAL                                  FALSE   BOOL "Exclude signal")

set_cache_default(UBINOS__UBIK__EXCLUDE_STIMER                                  FALSE   BOOL "Exclude semaphore timer functions")

set_cache_default(UBINOS__UBIK__EXCLUDE_HRTICK                                  FALSE   BOOL "Exclude high resolution tick functions")
set_cache_default(UBINOS__UBIK__EXCLUDE_HRTICK_TICKISR_DELAY_CHECK              FALSE   BOOL "Exclude high resolution tick interrupt service routine delay check feature")

set_cache_default(UBINOS__UBIK__IDLETASK_SPINWAIT_INTERVALTICK                  10      STRING "Spin wait interval tick of idle task")

if(UBINOS__BSP__CPU_ARCH STREQUAL "ARM")

    if(UBINOS__BSP__CPU_TYPE STREQUAL "ARM926EJ_S")
    
    elseif(UBINOS__BSP__CPU_TYPE STREQUAL "CORTEX_M4" OR UBINOS__BSP__CPU_TYPE STREQUAL "CORTEX_M3")

set_cache_default(UBINOS__UBIK__USE_PENDSV_TASK_YIELD                           TRUE    BOOL "Use PendSV for task yield instead of SVC")
    
    else()
    
        message(FATAL_ERROR "Unsupported UBINOS__BSP__CPU_TYPE")
    
    endif()

else()

    message(FATAL_ERROR "Unsupported UBINOS__BSP__CPU_ARCH")

endif()

########

set(_tmp_all_flags "")

if(INCLUDE__UBINOS__UBIK)
	set(_tmp_all_flags "${_tmp_all_flags} -DUBINOS_PRESENT")
endif()

set(CMAKE_ASM_FLAGS "${_tmp_all_flags} ${CMAKE_ASM_FLAGS}")
set(CMAKE_C_FLAGS   "${_tmp_all_flags} ${CMAKE_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${_tmp_all_flags} ${CMAKE_CXX_FLAGS}")
