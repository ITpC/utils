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
 * $Id: missing.h 81 2007-07-01 11:50:43Z Pavel Kraynyukhov $
 * 
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 * 
 **/

#ifndef __MISSING_H__
#define __MISSING_H__

#include <string.h>
#include <string>
#include <sstream>
#include <ctype.h>
#include <boost/regex.hpp>
#include <exception>
#include <stdexcept>
#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>

namespace itc {
    namespace utils {

        //minimizes copieng, preallocate necessary heap at once.
        //Do not iuse this function in your projects. This is a historical
        //artifact, and stays here for compatibility with older projects.
        //This function is deprecated, and will be obsolet soon.
        static inline boost::shared_array<char> toUpper(const std::string& ref) {
            std::string::size_type len = ref.length();
            boost::shared_array<char> mArray(new char[len + 1]);
            char* mArrayPtr = mArray.get();

            for (std::string::size_type i = 0; i < len; i++) {
                mArrayPtr[i] = (char) toupper(ref.c_str()[i]);
            }
            mArrayPtr[len] = 0;
            return mArray;
        }

        //minimizes copieng, preallocate necessary heap at once.
        //Do not iuse this function in your projects. This is a historical
        //artifact, and stays here for compatibility with older projects.
        //This function is deprecated, and will be obsolet soon.
        static inline boost::shared_array<char> toLower(const std::string& ref) {
            std::string::size_type len = ref.length();
            boost::shared_array<char> mArray(new char[len + 1]);
            char* mArrayPtr = mArray.get();

            for (std::string::size_type i = 0; i < len; i++) {
                mArrayPtr[i] = (char) tolower(ref.c_str()[i]);
            }
            mArrayPtr[len] = 0;
            return mArray;
        }

        // std::regex has a bug with following regex in 4.8.3. An exception will
        // be trown on application start. Repaced back with boost::regex 11.12.2014
        const boost::regex aNumRegEx(
                std::string("^[-]?[0-9]*[.]?[0-9]+([eE][+-][0-9]+)?$"),
                boost::regex::egrep
        );

        const boost::regex anIntRegEx(
                std::string("^[-]?[0-9]*$"),
                boost::regex::egrep
        );

        const boost::regex aHexRegEx(
                std::string("^[0-9a-fA-F]*$"),
                boost::regex::egrep
        );
        
        static inline const bool isnumber(const std::string& str) 
        {
            if (boost::regex_match(str, aNumRegEx)) {
                return true;
            }
            return false;
        }

        static inline const bool ishex(const std::string& str) 
        {
            if (boost::regex_match(str, aHexRegEx)) {
                return true;
            }
            return false;
        }

        static inline const bool isint(const std::string& str) 
        {
            if (boost::regex_match(str, anIntRegEx)) {
                return true;
            }
            return false;
        }
        
        static inline double s2double(const std::string& ref) {
            std::istringstream aConverter(ref);
            double ret;
            aConverter >> ret;
            return ret;
        }

        static inline float s2float(const std::string& ref) {
            std::istringstream aConverter(ref);
            float ret;
            aConverter >> ret;
            return ret;
        }

        static inline long s2long(const std::string& ref) {
            std::istringstream aConverter(ref);
            long ret;
            aConverter >> ret;
            return ret;
        }

        static inline int s2int(const std::string& ref) {
            std::istringstream aConverter(ref);
            int ret;
            aConverter >> ret;
            return ret;
        }

        static inline unsigned s2uint(const std::string& ref) {
            std::istringstream aConverter(ref);
            unsigned ret;
            aConverter >> ret;
            return ret;
        }

        template <typename T> T str2number(const std::string& ref)
        {
            std::istringstream aConverter(ref);
            T ret;
            aConverter >> ret;
            return ret;            
        }
        
        static inline long long s2dlong(const std::string& ref) {
            std::istringstream aConverter(ref);
            long long ret;
            aConverter >> ret;
            return ret;
        }

        static inline std::string num2s(const int val) {
            std::ostringstream aConverter;
            if (aConverter << val) {
                return aConverter.str();
            }
            throw std::runtime_error("Conversion to string is failed in itc::utils::num2s(const int&)");
        }

        static inline std::string num2s(const unsigned val) {
            std::ostringstream aConverter;
            if (aConverter << val) {
                return aConverter.str();
            }
            throw std::runtime_error("Conversion to string is failed in itc::utils::num2s(const unsigned&)");
        }

        static inline std::string num2s(const float val) {
            std::ostringstream aConverter;
            if (aConverter << val) {
                return aConverter.str();
            }
            throw std::runtime_error("Conversion to string is failed in itc::utils::num2s(const float&)");
        }

        static inline std::string num2s(const double val) {
            std::ostringstream aConverter;
            if (aConverter << val) {
                return aConverter.str();
            }
            throw std::runtime_error("Conversion to string is failed in itc::utils::num2s(const double&)");
        }

        static inline std::string num2s(const long long val) {
            std::ostringstream aConverter;
            if (aConverter << val) {
                return aConverter.str();
            }
            throw std::runtime_error("Conversion to string is failed in itc::utils::num2s(const long long&)");
        }

    }
}

#if defined (__MINGW32__) || defined (__CYGWIN__)

inline char* rindex(const char* x, int c) {
    if (x) {
        int l = strlen(x) - 1;

        if (l == 0) return NULL;

        char* ptr = (char*) (&x[l]);
        do {
            if (ptr && ((*ptr) == c))
                return ptr;
        } while ((--ptr) > x);
        return NULL;
    }
    return NULL;
}

inline char* index(const char* x, int c) {
    if (x) {
        int len = strlen(x);
        if (!len) return NULL;

        char* ptr = (char*) x;
        while (ptr < (x + len)) {
            if ((*ptr) == c)
                return ptr;
            ptr++;
        }
        return NULL;
    }
    return NULL;
}

inline char *strndup(const char *s, size_t n) {
    size_t len = strlen(s);
    if (len > n) {
        char *ret = new char[n + 1];
        memset(ret, 0, n + 1);
        memcpy(ret, s, n);
        return ret;
    } else {
        char *ret = new char[len + 1];
        memset(ret, 0, len + 1);
        memcpy(ret, s, len);
        return ret;
    }
}
#endif

static inline char* itoa(const int i) {
    static char buff[21];
    memset(buff, 0, 21);
    snprintf(buff, 20, "%d", i);
    return buff;
}

static inline char* ftoa(const float i) {
    static char buff[33];
    memset(buff, 0, 33);
    snprintf(buff, 32, "%f", i);
    return buff;
}

#endif /*__MISSING_H__*/
