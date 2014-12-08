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
 * $Id: HString.h 56 2007-05-22 09:05:13Z Pavel Kraynyukhov $
 * 
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 * 
 **/

#ifndef __H_STRING_H__
#define __H_STRING_H__

#include <string>
#include <functional>

namespace itc
{
    namespace utils
    {
        /**
         * @brief std::string wrapper structure with non literal comparison of strings.
         * 
         * The subject of compariosn are the string hashes. This wrapper is normally usless 
         * everywhere, out of the fast search inside of the hash maps when you do not need 
         * to compare literals of the string. It is only usefull when you have such string 
         * as a key and order of storing inside of container is not important. However unicity 
         * of the keys and fast access to elements stored under the keys is very important.
         * Lexographical comparison can be done with methods less and greater.
         * You should think twise before use this class, it is necessary only when you have 
         * long live objects, those are compared very offen.
         * 
         * As far as TR1 standard would be implemented in most popular compilers
         * header reference should change from boost to TR1.
         *
         * changed to c++11 on 03.12.2014
         * 
         **/
        struct HString
        {
            std::hash<std::string> str2hash;
            std::string mHString;
            size_t      mHash;
            
            HString(const char* pCStr) : mHString(pCStr)
            {
                mHash=str2hash(mHString);
            }
        
            HString(const std::string& pStr) : mHString(pStr)
            {
                mHash=str2hash(mHString);
            }
        
            HString(const HString& ref) : mHString(ref.mHString), mHash(ref.mHash)
            {
            }
        
            inline const HString& operator=(const std::string& pStr)
            {
                mHString=pStr;
                mHash=str2hash(mHString);
                return (*this);
            }
        
            inline const HString& operator=(const char* pCStr)
            {
                mHString=pCStr;
                mHash=str2hash(mHString);
                return (*this);
            }
            
            inline operator size_t() const
            {
                return mHash;
            }
            
            inline const bool operator<(const HString& ref) const
            {
                return mHash < ref.mHash;
            }
        
            inline const bool operator>(const HString& ref) const
            {
                return mHash > ref.mHash;
            }
        
            inline const bool operator==(const HString& ref) const
            {
                return mHash == ref.mHash;
            }
        
            inline const bool operator!=(const HString& ref) const
            {
                return mHash == ref.mHash;
            }
            
            inline const char* c_str() const
            {
                return mHString.c_str();
            }
        
            ///Beware of returned reference !
            inline const std::string& str()
            {
                return mHString;
            }
            
            inline const HString& operator+=(const HString& ref)
            {
                mHString+=ref.mHString;
                mHash=str2hash(mHString);
                return *this;
            }
            
            // copy and copy - uneffective :(
            inline HString operator+(const HString& ref)
            {
                HString tmp(*this);
                return (tmp+=ref);
            }
            
            inline const bool less(const HString& ref) const
            {
                if(mHash!=ref.mHash)
                {
                    return mHString < ref.mHString;
                }
                return false;
            }
        
            inline const bool greater(const HString& ref) const
            {
                if(mHash!=ref.mHash)
                {
                    return mHString > ref.mHString;
                }
                return false;
            }
            
            // TODO: find faster way to make string chars uppercase
            inline void toUpper()
            {
                std::string::size_type len=mHString.length();
                for(std::string::size_type i=0;i<len;i++)
                {
                    mHString.replace( i , 1, 1, (char)toupper(mHString.c_str()[i]) );
                }
                mHash=str2hash(mHString);
            }
            
            // TODO: find faster way to make string chars lowercase
            inline void toLower()
            {
                std::string::size_type len=mHString.length();
                for(std::string::size_type i=0;i<len;i++)
                {
                    mHString.replace( i , 1, 1, (char)tolower(mHString.c_str()[i]) );
                }
                mHash=str2hash(mHString);
            }
        };        
    }
    
}

#endif /*__H_STRING_H__*/
