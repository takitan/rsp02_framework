#pragma once
#include <cstdint>

#ifndef OFFLINE
#include "mbed.h"
#else
namespace rsp{
namespace rsp02{
namespace fw{
namespace util{
typedef int32_t                  osStatus;
#define osEventSignal           (0x08)
#define osEventMessage          (0x10)
#define osEventMail             (0x20)
#define osEventTimeout          (0x40)
#define osErrorOS               osError
#define osErrorTimeoutResource  osErrorTimeout
#define osErrorISRRecursive     (-126)
#define osErrorValue            (-127)
#define osErrorPriority         (-128)

typedef void *osMailQId;
typedef void *osMessageQId;

typedef struct {
  osStatus                    status;   ///< status code: event or error information
  union {
    uint32_t                       v;   ///< message as 32-bit value
    void                          *p;   ///< message or mail as void pointer
    int32_t                  signals;   ///< signal flags
  } value;                              ///< event value
  union {
    osMailQId                mail_id;   ///< mail id obtained by \ref osMailCreate
    osMessageQId          message_id;   ///< message id obtained by \ref osMessageCreate
  } def;                                ///< event definition
} osEvent;

}
}
}
}

#endif
