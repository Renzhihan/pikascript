#define __OOC_CPP__
#define __OOC_DEBUG__

#include "BaseObj.h"
#include "PikaCompiler.h"
#include "PikaParser.h"
#include "PikaVM.h"
#include "TinyObj.h"
#include "dataArgs.h"
#include "dataMemory.h"
#include "dataStrs.h"

extern "C" {
#include "PikaMain.h"
#include "PikaMath_Operator.h"
#include "PikaStdLib_MemChecker.h"
#include "PikaStdLib_SysObj.h"
#include "pikaScript.h"
#include "pika_config_gtest.h"
#include "pika_hal.h"
#include <stdio.h>

extern PikaMemInfo g_PikaMemInfo;
/* the log_buff of printf */
extern char log_buff[LOG_BUFF_MAX][LOG_SIZE];
}

#define TEST_SINGLE_FILE(_test_suite_, _test_name_, _file_name_)               \
  TEST(_test_suite_, _test_name_) {                                            \
    g_PikaMemInfo.heapUsedMax = 0;                                             \
    PikaObj *pikaMain = newRootObj("pikaMain", New_PikaMain);                  \
    extern unsigned char pikaModules_py_a[];                                   \
    obj_linkLibrary(pikaMain, pikaModules_py_a);                               \
    /* run */                                                                  \
    __platform_printf("BEGIN\r\n");                                            \
    pikaVM_runSingleFile(pikaMain, _file_name_);                               \
    /* assert */                                                               \
    /* deinit */                                                               \
    obj_deinit(pikaMain);                                                      \
    EXPECT_EQ(pikaMemNow(), 0);                                                \
  }

#define TEST_SINGLE_FILE_PASS(_test_suite_, _test_name_, _file_name_)          \
  TEST(_test_suite_, _test_name_) {                                            \
    g_PikaMemInfo.heapUsedMax = 0;                                             \
    PikaObj *pikaMain = newRootObj("pikaMain", New_PikaMain);                  \
    extern unsigned char pikaModules_py_a[];                                   \
    obj_linkLibrary(pikaMain, pikaModules_py_a);                               \
    /* run */                                                                  \
    __platform_printf("BEGIN\r\n");                                            \
    pikaVM_runSingleFile(pikaMain, _file_name_);                               \
    /* assert */                                                               \
    EXPECT_STREQ(log_buff[0], "PASS\r\n");                                     \
    EXPECT_STREQ(log_buff[1], "BEGIN\r\n");                                    \
    /* deinit */                                                               \
    obj_deinit(pikaMain);                                                      \
    EXPECT_EQ(pikaMemNow(), 0);                                                \
  }

#define TEST_RUN_LINES(_test_suite_, _test_name_, _lines_)                     \
  TEST(_test_suite_, _test_name_) {                                            \
    PikaObj *self = newRootObj("root", New_PikaStdLib_SysObj);                 \
    obj_run(self, (_lines_)); /* collect */ /* assert */                       \
    obj_deinit(self);                                                          \
    EXPECT_EQ(pikaMemNow(), 0);                                                \
  }

#if USE_GOOGLE_TEST
#include "gtest/gtest.h"
#define TEST_START
#define TEST_END
#else
#include "test_purec.h"
#endif
