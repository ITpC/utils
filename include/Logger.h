/**
 * Copyright (c) 2007, Pavel Kraynyukhov.
 *  
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without a written agreement
 * is hereby granted under the terms of the General Public License version 2
 * (GPLv2), provided that the above copyright notice and this paragraph and the
 * following two paragraphs and the "LICENSE" file appear in all modified or
 * unmodified copies of the software "AS IS" and without any changes.
 *
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE TO ANY PARTY FOR
 * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING
 * LOST PROFITS, ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS
 * DOCUMENTATION, EVEN IF THE COPYRIGHT HOLDER HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * THE COPYRIGHT HOLDER SPECIFICALLY DISCLAIMS ANY WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
 * ON AN "AS IS" BASIS, AND THE COPYRIGHT HOLDER HAS NO OBLIGATIONS TO
 * PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
 * 
 * 
 * $Id: Logger.h 56 2007-05-22 09:05:13Z Pavel Kraynyukhov $
 * 
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 * 
 **/


#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <Val2Type.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>

#include <exception>

#include <memory>

#include <InterfaceCheck.h>
#include <abstract/LoggerHelpers.h>

#include <LogOutBuffer.h>
#include <abstract/ILogFormatter.h>
#include <StdTextLogFormatter.h>
#include <sys/time.h>
#include <Date.h>

#define XDEBUG 0
#define XTRACE 1
#define XINFO 2
#define XERROR 3
#define XFATAL 4

#ifndef MAX_BUFF_SIZE
#define MAX_BUFF_SIZE 256
#endif

#define LL2STR(x) (\
            (x==XDEBUG) ? "DEBUG" : (\
                (x==XTRACE) ? "TRACE" : (\
                   (x==XINFO) ? "INFO" : (\
                       (x==XERROR) ? "ERROR" : (\
                           (x==XFATAL) ? "FATAL" : "UNDEFINED" )\
                       )\
                   )\
                )\
             )



namespace itc
{
  namespace utils
  {

    template <
    typename TOutAdapter, typename TFormatter, int LOGLEVEL = XDEBUG, bool TSafe = true
    > class Logger
    {
    private:
      std::mutex mMutex;
      std::shared_ptr<TOutAdapter> mOutAdapter;
      LogOutBuffer<TOutAdapter, TSafe> mOutBuffer;
      TFormatter mLogFormatter;
      TFormatter mLogFormatter1;
      

      Int2Type<LOGLEVEL> mLogLevel;
      const char* mLogLevelStr;
      const char* mAppName;

    public:
      typedef itc::utils::abstract::ILogOutputAdapter AbstractLogOutAdapter;
      typedef itc::utils::abstract::ILogFormatter AbstractLogFormatter;
      typedef typename std::shared_ptr<TOutAdapter> SharedTOutAdapter;
      typedef itc::utils::abstract::ILogFormatter::shared_buff shared_buff;

      explicit Logger(SharedTOutAdapter& pOutAdapter, const char* pAppName)
      : mMutex(), mOutAdapter(pOutAdapter), mOutBuffer(mOutAdapter, TSafe),
      mLogFormatter(), mLogFormatter1(), mLogLevelStr(LL2STR(LOGLEVEL)),
      mAppName(pAppName)
      {
        std::lock_guard<std::mutex> sync(mMutex);
        STATIC_CHECKER3MSG(
          CheckRelationship(
            TOutAdapter, subclassof, AbstractLogOutAdapter
          ),
          TOutAdapter, _is_not_a_subclass_of_, AbstractLogOutAdapter
        );

        STATIC_CHECKER3MSG(
          CheckRelationship(
            TFormatter, subclassof, AbstractLogFormatter
          ),
          TFormatter, _is_not_a_subclass_of_, AbstractLogFormatter
        );


        shared_buff formattedMessage(
          mLogFormatter.format(
            MAX_BUFF_SIZE, "%s - %s: Logger::Logger() [ %s ]:%d: start logging of level %s\n",
            getCurrTimeStr(), mAppName, __FILE__, __LINE__, mLogLevelStr
            )
          );
        mOutBuffer.post(formattedMessage);
      }

    private:
      static const char* getCurrTimeStr()
      {
        static char tbuf[22];
        Date aDate;
        Time aTime = aDate.get();

        time_t sec = aTime.mTimestamp.tv_sec;
        time_t msec = aTime.mTimestamp.tv_usec / 1000;

        struct tm* ts = localtime(&sec);

        if (ts == NULL)
        {
          throw std::bad_alloc();
        }
        strftime(tbuf, 22, "%Y%m%d%H%M%S", ts);
        snprintf(tbuf + 14, 6, ".%03jdZ", msec);
        tbuf[21] = 0;

        return tbuf;
      }

      void trace(Int2Type<XDEBUG> fictive, const char* pFilename, const size_t pLineNumber, const shared_buff& message) { }

      void trace(Int2Type<XTRACE> fictive, const char* pFilename, const size_t pLineNumber, const shared_buff& message)
      {
        mOutBuffer.post(mLogFormatter1.format(MAX_BUFF_SIZE, "%s - [TRACE] - %s:%d: %s\n", getCurrTimeStr(), pFilename, pLineNumber, message->data()));
      }

      void trace(Int2Type<XINFO> fictive, const char* pFilename, const size_t pLineNumber, const shared_buff& message) { }

      void trace(Int2Type<XERROR> fictive, const char* pFilename, const size_t pLineNumber, const shared_buff& message) { }

      void trace(Int2Type<XFATAL> fictive, const char* pFilename, const size_t pLineNumber, const shared_buff& message) { }
      //-----------

      void debug(Int2Type<XTRACE> fictive, const char* pFilename, const size_t pLineNumber, const shared_buff& message)
      {
        mOutBuffer.post(mLogFormatter1.format(MAX_BUFF_SIZE, "%s - [DEBUG] - %s:%d: %s\n", getCurrTimeStr(), pFilename, pLineNumber, message->data()));
      }

      void debug(Int2Type<XDEBUG> fictive, const char* pFilename, const size_t pLineNumber, const shared_buff& message)
      {
        mOutBuffer.post(mLogFormatter1.format(MAX_BUFF_SIZE, "%s - [DEBUG] - %s:%d: %s\n", getCurrTimeStr(), pFilename, pLineNumber, message->data()));
      }

      void debug(Int2Type<XINFO> fictive, const char* pFilename, const size_t pLineNumber, const shared_buff& message) { }

      void debug(Int2Type<XERROR> fictive, const char* pFilename, const size_t pLineNumber, const shared_buff& message) { }

      void debug(Int2Type<XFATAL> fictive, const char* pFilename, const size_t pLineNumber, const shared_buff& message) { }
      //-------------------

      void fatal(Int2Type<XTRACE> fictive, const char* pFilename, const size_t pLineNumber, const shared_buff& message)
      {
        mOutBuffer.post(mLogFormatter1.format(MAX_BUFF_SIZE, "%s - [FATAL] - %s:%d: %s\n", getCurrTimeStr(), pFilename, pLineNumber, message->data()));
      }

      void fatal(Int2Type<XFATAL> fictive, const char* pFilename, const size_t pLineNumber, const shared_buff& message)
      {
        mOutBuffer.post(mLogFormatter1.format(MAX_BUFF_SIZE, "%s - [FATAL] - %s:%d: %s\n", getCurrTimeStr(), pFilename, pLineNumber, message->data()));
      }

      void fatal(Int2Type<XINFO> fictive, const char* pFilename, const size_t pLineNumber, const shared_buff& message)
      {
        mOutBuffer.post(mLogFormatter1.format(MAX_BUFF_SIZE, "%s - [FATAL] - %s:%d: %s\n", getCurrTimeStr(), pFilename, pLineNumber, message->data()));
      }

      void fatal(Int2Type<XERROR> fictive, const char* pFilename, const size_t pLineNumber, const shared_buff& message)
      {
        mOutBuffer.post(mLogFormatter1.format(MAX_BUFF_SIZE, "%s - [FATAL] - %s:%d: %s\n", getCurrTimeStr(), pFilename, pLineNumber, message->data()));
      }

      void fatal(Int2Type<XDEBUG> fictive, const char* pFilename, const size_t pLineNumber, const shared_buff& message)
      {
        mOutBuffer.post(mLogFormatter1.format(MAX_BUFF_SIZE, "%s - [FATAL] - %s:%d: %s\n", getCurrTimeStr(), pFilename, pLineNumber, message->data()));
      }
      //-------------------

      void error(Int2Type<XTRACE> fictive, const char* pFilename, const size_t pLineNumber, const shared_buff& message)
      {
        mOutBuffer.post(mLogFormatter1.format(MAX_BUFF_SIZE, "%s - [ERROR] - %s:%d: %s\n", getCurrTimeStr(), pFilename, pLineNumber, message->data()));
      }

      void error(Int2Type<XERROR> fictive, const char* pFilename, const size_t pLineNumber, const shared_buff& message)
      {
        mOutBuffer.post(mLogFormatter1.format(MAX_BUFF_SIZE, "%s - [ERROR] - %s:%d: %s\n", getCurrTimeStr(), pFilename, pLineNumber, message->data()));
      }

      void error(Int2Type<XINFO> fictive, const char* pFilename, const size_t pLineNumber, const shared_buff& message)
      {
        mOutBuffer.post(mLogFormatter1.format(MAX_BUFF_SIZE, "%s - [ERROR] - %s:%d: %s\n", getCurrTimeStr(), pFilename, pLineNumber, message->data()));
      }

      void error(Int2Type<XFATAL> fictive, const char* pFilename, const size_t pLineNumber, const shared_buff& message) { }

      void error(Int2Type<XDEBUG> fictive, const char* pFilename, const size_t pLineNumber, const shared_buff& message)
      {
        mOutBuffer.post(mLogFormatter1.format(MAX_BUFF_SIZE, "%s - [ERROR] - %s:%d: %s\n", getCurrTimeStr(), pFilename, pLineNumber, message->data()));
      }
      //-------------------

      void info(Int2Type<XTRACE> fictive, const shared_buff& message)
      {
        mOutBuffer.post(mLogFormatter1.format(MAX_BUFF_SIZE, "%s - [INFO] - %s\n", getCurrTimeStr(), message->data()));
      }

      void info(Int2Type<XINFO> fictive, const shared_buff& message)
      {
        mOutBuffer.post(mLogFormatter1.format(MAX_BUFF_SIZE, "%s - [INFO] - %s\n", getCurrTimeStr(), message->data()));
      }

      void info(Int2Type<XERROR> fictive, const shared_buff& message) { }

      void info(Int2Type<XFATAL> fictive, const shared_buff& message) { }

      void info(Int2Type<XDEBUG> fictive, const shared_buff& message)
      {
        mOutBuffer.post(mLogFormatter1.format(MAX_BUFF_SIZE, "%s - [INFO] - %s\n", getCurrTimeStr(), message->data()));
      }

      //-------------------

      public:
      void trace(const char* pFilename, const size_t pLineNumber, const char* format, ...)
      {
        std::lock_guard<std::mutex> sync(mMutex);
        va_list args;
        va_start(args, format);
        shared_buff formattedMessage(mLogFormatter.format(MAX_BUFF_SIZE, format, args));
        va_end(args);
        trace(mLogLevel, pFilename, pLineNumber, formattedMessage);
      }

      void debug(const char* pFilename, const size_t pLineNumber, const char* format, ...)
      {
        std::lock_guard<std::mutex> sync(mMutex);
        va_list args;
        va_start(args, format);
        shared_buff formattedMessage(mLogFormatter.format(MAX_BUFF_SIZE, format, args));
        va_end(args);
        debug(mLogLevel, pFilename, pLineNumber, formattedMessage);
      }

      void error(const char* pFilename, const size_t pLineNumber, const char* format, ...)
      {
        std::lock_guard<std::mutex> sync(mMutex);

        va_list args;
        va_start(args, format);
        shared_buff formattedMessage(mLogFormatter.format(MAX_BUFF_SIZE, format, args));
        va_end(args);
        error(mLogLevel, pFilename, pLineNumber, formattedMessage);
      }

      void fatal(const char* pFilename, const size_t pLineNumber, const char* format, ...)
      {
        std::lock_guard<std::mutex> sync(mMutex);

        va_list args;
        va_start(args, format);
        shared_buff formattedMessage(mLogFormatter.format(MAX_BUFF_SIZE, format, args));
        va_end(args);
        fatal(mLogLevel, pFilename, pLineNumber, formattedMessage);
      }

      void info(const char* format, ...)
      {
        std::lock_guard<std::mutex> sync(mMutex);

        va_list args;
        va_start(args, format);
        shared_buff formattedMessage(mLogFormatter.format(MAX_BUFF_SIZE, format, args));
        va_end(args);
        info(mLogLevel, formattedMessage);
      }

      void flush()
      {
        std::lock_guard<std::mutex> sync(mMutex);
        mOutBuffer.flush();
      }

      ~Logger()
      {
        flush();
      }
    };

    class CanNotOpenTheLogException : public std::exception
    {
    private:
      int ERRNO;
    public:

      CanNotOpenTheLogException() throw ()
      {
        ERRNO = errno;
      }

      const char* what() const throw ()
      {
        return strerror(ERRNO);
      }
    };
  }
}

#endif /*__LOGGER_H__*/
