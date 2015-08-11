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
 * $Id: PString.h 73 2007-06-07 13:25:56Z Pavel Kraynyukhov $
 * 
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 * 
 **/

#ifndef __PSTRING_H__
#define __PSTRING_H__

#include <compat_types.h>
#include <string>
#include <missing.h>
#include <functional>


namespace itc {
    namespace utils {

        /**
         * @brief  Pascal style string.
         *
         * By default maximal string length 254 symbols, last symbol in string has allways value 0,
         * just to be compatible with C strings. Common use case - part of the record of some binary file.
         * No endian checks ! HW-platform dependent ! Only to store some temp platform-untransportable data.
         * Good compromise of memory consumption and performance. However the behavior of comarison operators
         * is to compare the hashes of the string. So one could check really fast if one string equals or not
         * to another one. Operator < and > also comparing the hashes. To compare lexographically one must use
         * methods less and greater.
         *
         * @param size_type defines an appropriate type to handle the length of the string.
         * @param MaxStorageSize sets the maximal number of the characters those are stored in the string.
         *
         **/
        template <typename size_type, size_t MaxStorageSize = 255 > class PString {
        private:
            size_type mLength;
            char mString[MaxStorageSize];
            uint32_t mHash;

            void mkHash() {
                std::hash<std::string> str2hash;
                mHash = str2hash(mString);
            }

            void Init(const char* pCStr) {
                if (pCStr == NULL) {
                    mLength = 0;
                    mString[0] = 0;
                } else {
                    mLength = strlen(pCStr);
                    if (mLength >= MaxStorageSize) {
                        mLength = MaxStorageSize - sizeof (char);
                    } else if (mLength != 0) {
                        memcopy(mString, pCStr, mLength);
                    }
                    mString[mLength] = 0;
                }
                mkHash();
            }

            void Init(const std::string& pStr) {
                register size_t tmpl = pStr.length();

                if (tmpl && (tmpl < MaxStorageSize)) {
                    mLength = tmpl;
                    memcopy(mString, pStr.c_str(), tmpl);
                    mString[tmpl] = 0;
                    mkHash();
                } else {
                    if (tmpl) {
                        mLength = MaxStorageSize - sizeof (char);
                        memcopy(mString, pStr.c_str(), mLength);
                        mString[mLength] = 0;
                        mkHash();
                    } else {
                        mLength = 0;
                        mString[mLength] = 0;
                    }
                }
            }

            void Init(const PString& ref) {
                mLength = ref.mLength;
                memcopy(mString, ref.mString, mLength);
                mHash = ref.mHash;
            }

        public:

            PString(const char* pCStr) {
                Init(pCStr);
            }

            PString(const std::string& pStr) {
                Init(pStr);
            }

            PString(const PString& ref) {
                Init(ref);
            }

            PString() : mLength(0) {
                mString[0] = 0;
                mHash = 0;
            }

            const char* c_str() {
                return mString;
            }

            std::string str() {
                return std::string(mString);
            }

            const PString& operator=(const PString& ref) {
                Init(ref);
                return *this;
            }

            const PString& operator=(const char* pCStr) {
                Init(pCStr);
                return (*this);
            }

            const PString& operator=(const std::string& pStr) {
                Init(pStr);
                return (*this);
            }

            const PString& operator+=(const PString& ref) {
                register size_type tmpl = mLength + ref.mLength;

                if (tmpl < MaxStorageSize) {
                    memcopy(&mString[mLength], ref.mString, ref.mLength);
                    mString[tmpl] = 0;
                } else {
                    mLength = MaxStorageSize - mLength;
                    memcopy(&mString[mLength], ref.mString, mLength);
                    mString[mLength] = 0;
                }
                mkHash();
                return *this;
            }

            const PString operator=+(const PString& ref) {
                *this += ref;
                return *this;
            }

            const PString operator+(const PString& ref) {
                return (*this+ref);
            }

            const bool operator>(const PString& ref) {
                return mHash > ref.mHash;
            }

            const bool operator<(const PString& ref) {
                return mHash < ref.mHash;
            }

            const bool operator==(const PString& ref) {
                return mHash == ref.mHash;
            }

            const bool operator!=(const PString& ref) {
                return mHash != ref.mHash;
            }

            uint32_t getHash() {
                return mHash;
            }

            size_type length() {
                return mLength;
            }

            bool less(const Pstring& ref) {
                if (mLength == ref.mLength) {
                    return (strncmp(mString, ref.mString, mLength) == -1);
                }
                if (mLength < ref.mLength) {
                    int ret = strncmp(mString, ref.mString, mLength);
                    if ((ret == 0) && (ret == -1)) {
                        return true;
                    } else return false;
                }
                if (mLength > ref.mLength) {
                    int ret = strncmp(mString, ref.mString, mLength);
                    if (ret == -1) {
                        return true;
                    }
                    return false;
                }
            }

            bool greater(const Pstring& ref)
            {
                if ((mHash != ref.Mhash) && (!less(ref)))
                {
                        return true;
                }
                return false;
            }
        };
    }
}
#endif /*__PSTRING_H__*/
