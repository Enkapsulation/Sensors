#pragma once

/*============================================================================*\
* Includes headers
\*============================================================================*/
#include <iostream>
#include <string>

#include "dbg_trace_types.hpp"

/*============================================================================*\
* Import object
\*============================================================================*/
static log_struct LOGCFG
{
   .headers = true,
   .level = DEBUG
};

/*============================================================================*\
* DbgTarce class declarations
\*============================================================================*/
class DbgTrace
{
   private:
      log_type m_log_level = DEBUG;
      bool m_is_msg_end = false;
      std::string m_msg_header;

      std::string getLabel(log_type msg_level);
   
   public:
      DbgTrace(log_type msg_level);

      /*
       *	Settery
       */
      void set_log_level(const log_type& log_level) { m_log_level = log_level; }
      void set_is_msg_end(const bool& is_msg_end) { m_is_msg_end = is_msg_end; }

      /*
       *	gettery
       */
      log_type get_log_level(void) const { return m_log_level; }
      bool get_is_msg_end(void) const { return m_is_msg_end; }

      /*
       *	Operator overloading
       */
      template<class T>
      DbgTrace &operator<<(const T &msg)
      {
         if(m_log_level >= LOGCFG.level)
         {
            std::cout << msg;
            set_is_msg_end(true);
         }
         return *this;
      }

      ~DbgTrace();
};
