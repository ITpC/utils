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
 * $Id: Date.h 56 2015-02-18 12:24:13Z Pavel Kraynyukhov $
 * 
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 * 
 **/

/* 
 * File:   Time.h
 * Author: pk
 *
 * Created on 18 Февраль 2015 г., 12:24
 */

#ifndef __DATE__H_
#define	__DATE__H_

#include <sys/time.h>
#include <time.h>
#include <exception>
#include <memory>
#include <string>
#include <strings.h>

namespace itc
{
    namespace utils
    {
        struct Time
       {
           struct timeval mTimestamp;

           Time() {}

           Time(const time_t sec, const time_t usec)
           {
               mTimestamp.tv_sec=sec;
               mTimestamp.tv_usec=usec;
           }

           Time(const struct timeval& ref)
           {
               mTimestamp.tv_sec=ref.tv_sec;
               mTimestamp.tv_usec=ref.tv_usec;
           }
           
           Time(const Time& ref)
           {
               mTimestamp.tv_sec=ref.mTimestamp.tv_sec;
               mTimestamp.tv_usec=ref.mTimestamp.tv_usec;
           }
           
           Time& operator=(const Time& ref)
           {
               mTimestamp.tv_sec=ref.mTimestamp.tv_sec;
               mTimestamp.tv_usec=ref.mTimestamp.tv_usec;
               return (*this);
           }

           bool operator<(const Time& ref) const
           {
               return (mTimestamp.tv_sec<ref.mTimestamp.tv_sec) || ((mTimestamp.tv_sec==ref.mTimestamp.tv_sec)&&(mTimestamp.tv_usec<ref.mTimestamp.tv_usec));
           }

           bool operator!=(const Time& ref) const
           {
               return (mTimestamp.tv_sec!=ref.mTimestamp.tv_sec) || (mTimestamp.tv_usec!=ref.mTimestamp.tv_usec);
           }

           bool operator>(const Time& ref) const
           {
               return (mTimestamp.tv_sec>ref.mTimestamp.tv_sec)||((mTimestamp.tv_sec==ref.mTimestamp.tv_sec)&&(mTimestamp.tv_usec>ref.mTimestamp.tv_usec));
           }

           bool operator==(const Time& ref) const
           {
               return (mTimestamp.tv_sec==ref.mTimestamp.tv_sec)&&(mTimestamp.tv_usec==ref.mTimestamp.tv_usec);
           }

           bool operator>=(const Time& ref) const
           {
               return ((*this>ref)||((mTimestamp.tv_sec==ref.mTimestamp.tv_sec)&&(mTimestamp.tv_usec==ref.mTimestamp.tv_usec)));
           }

           bool operator<=(const Time& ref) const
           {
               return ((*this<ref)||((mTimestamp.tv_sec==ref.mTimestamp.tv_sec)&&(mTimestamp.tv_usec==ref.mTimestamp.tv_usec)));
           }


       };

       class Date
       {
       private:
           Time mTime;
       public:
           Date()
           {
               this->update();
           };

           Date(const Date& ref) : mTime(ref.mTime)
           {
           }
           
           Date(const Time& ref) : mTime(ref)
           {
           }
           
           bool operator<(const Date& ref) const
           {
               return mTime<ref.mTime;
           }

           bool operator!=(const Date& ref) const
           {
               return mTime!=ref.mTime;
           }

           bool operator>(const Date& ref) const
           {
               return mTime>ref.mTime;
           }

           bool operator==(const Date& ref) const
           {
               return mTime==ref.mTime;
           }

           bool operator>=(const Date& ref) const
           {
               return mTime>=ref.mTime;
           }
           
           bool operator<=(const Date& ref) const
           {
               return mTime<=ref.mTime;
           }


           Date& operator=(const Date& ref)
           {
               mTime=ref.mTime;
               return (*this);
           }

           const Time& getTime() const
           {
               return mTime;
           }

           void update()
           {
               gettimeofday(&mTime.mTimestamp,NULL);
           }

           const Time& now()
           {
               this->update();
               return mTime;
           }
           
           const Time& get() const
           {
               return mTime;
           }
           
           void set(const Time& ref)
           {
               mTime=ref;
           }
       };
    }
}

#endif	/* __DATE__H_ */

