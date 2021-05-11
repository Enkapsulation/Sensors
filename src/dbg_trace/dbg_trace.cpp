/*============================================================================*\
* Includes headers
\*============================================================================*/
#include "dbg_trace.hpp"
#include "dbg_trace_types.hpp"

/*============================================================================*\
* DbgTarce class definitions
\*============================================================================*/

DbgTrace::DbgTrace(log_type msg_level) : m_log_level{msg_level}
{
   if(LOGCFG.headers)
   {
      operator << ("["+getLabel(m_log_level)+"] ");
   }
}

std::string DbgTrace::getLabel(log_type msg_level)
{
   std::string label;

   #undef X_LOG_TYPE
   #define X_LOG_TYPE(log_id) \
         case log_id: \
            label = #log_id; \
            break;

   switch (msg_level)
   {
      X_LOG_TYPES
      default:
         label = "UKNOWN_LABEL";
         break;
   }

   return label;
}

DbgTrace::~DbgTrace()
{
   if(get_is_msg_end()) {
         std::cout << std::endl;
   }
   set_is_msg_end(false);
}
