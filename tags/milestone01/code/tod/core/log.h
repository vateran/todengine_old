#ifndef TOD_CORE_LOG_LOG_H
#define TOD_CORE_LOG_LOG_H

#include "tod/core/define.h"

#define tod_log_notice(msg) do { tod_printf msg; } while (0);

#endif // TOD_CORE_LOG_LOG_H
