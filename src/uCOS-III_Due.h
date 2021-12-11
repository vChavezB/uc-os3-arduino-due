#ifndef UC_OS3_ARDUINO_H
#define UC_OS3_ARDUINO_H

#include "uc-OS3/os.h"
#include "uc-LIB/lib_mem.h"

#define OS_ASSERT(result,expected_value) \
  do { \
    if ((result) != (expected_value)) { \
      Serial.print("Error: ");\
      Serial.println(result,HEX);\
      while(1);\
    } \
  } while (0)


#endif