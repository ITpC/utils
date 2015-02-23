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
           
           const Time& operator=(const Time& ref)
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

           Date(const Date& ref)
           {
               mTime=ref.mTime;
           }
           
           Date(const Time& ref)
           {
               mTime=ref;
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


           const Date& operator=(const Date& ref)
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

