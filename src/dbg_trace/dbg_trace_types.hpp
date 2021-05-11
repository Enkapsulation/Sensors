#pragma once

/*============================================================================*\
* Includes
\*============================================================================*/
#include <iostream>

/*============================================================================*\
* local export #defines
\*============================================================================*/
#undef X_LOG_TYPE
#define X_LOG_TYPES \
   X_LOG_TYPE(DEBUG) \
   X_LOG_TYPE(INFO) \
   X_LOG_TYPE(WARN) \
   X_LOG_TYPE(ERROR) 

/*============================================================================*\
* local export types
\*============================================================================*/
enum log_type
{
   UNKNOWN_LOG_TYPES = -1,
   #undef X_LOG_TYPE
   #define X_LOG_TYPE(log_id) log_id,
   X_LOG_TYPES
};

struct log_struct
{
   bool headers;
   log_type level;
};
