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
 * $Id: RangedNumber.h 73 2007-06-07 13:25:56Z Pavel Kraynyukhov $
 * 
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 * 
 **/
 
#ifndef __RANGEDNUMBER_H__
#define __RANGEDNUMBER_H__

class RangedNumberOutOfBoundsException : public std::exception 
{ 
public: 
        RangedNumberOutOfBoundsException() : std::exception () {} 
        const char* what() const throw()
        { 
            return "There is an operation that tried to change RangedNumber value to be out of bounds. \
                    The operation is rolled back.";
        }
};

template < 
        typename Number, 
             Number low, 
             Number high 
> class RangedNumber
{ 
private: 
        Number mInt; 
public: 
        RangedNumber(){mInt=low;} 
        
        RangedNumber(const Number val) 
        { 
                if((val > high) || (val < low)) 
                        throw RangedNumberOutOfBoundsException(); 
                mInt=val; 
        } 
        
        RangedNumber(const RangedNumber& ref) 
        { 
                if((ref.mInt > high) || (ref.mInt < low)) 
                        throw RangedNumberOutOfBoundsException(); 
                mInt=ref.mInt; 
        }

        RangedNumber& operator=(const RangedNumber& ref) 
        { 
                mInt=ref.mInt; 
                return *this; 
        }

        RangedNumber& operator=(const Number val) 
        { 
                RangedNumber ret(val); 
                mInt=ret.mInt; 
                return (*this); 
        } 
        
        
        RangedNumber& operator-() 
        { 
                if((-mInt > high) || (-mInt < low)) 
                        throw RangedNumberOutOfBoundsException(); 
                mInt=-mInt; 
                return (*this); 
        }

        RangedNumber operator-(const RangedNumber& ref) 
        { 
                RangedNumber ret(mInt-ref.mInt); 
                return ret; 
        }

        RangedNumber operator-(const Number val) 
        { 
                return RangedNumber(mInt-val); 
        } 
        
        RangedNumber& operator++() 
        { 
                Number ret=mInt+1; 
                if((ret > high) || (ret < low)) 
                        throw RangedNumberOutOfBoundsException(); 
                mInt=ret; 
                return (*this); 
        }

        RangedNumber& operator--() 
        { 
                Number ret=mInt-1; 
                if((ret > high) || (ret < low)) 
                        throw RangedNumberOutOfBoundsException(); 
                mInt=ret; 
                return (*this); 
        }

        RangedNumber& operator+=(const RangedNumber& ref) 
        { 
                RangedNumber ret(mInt+ref.mInt); 
                mInt=ret.mInt; 
                return (*this); 
        }

        RangedNumber& operator+=(const Number val) 
        { 
                RangedNumber ret(mInt+val); 
                mInt=ret.mInt; 
                return (*this); 
        }

        RangedNumber& operator-=(const RangedNumber& ref) 
        { 
                RangedNumber ret(mInt-ref.mInt); 
                mInt=ret.mInt; 
                return (*this); 
        }

        RangedNumber& operator-=(const Number val) 
        { 
                RangedNumber ret(mInt-val); 
                mInt=ret.mInt; 
                return (*this); 
        }


        RangedNumber operator+(const RangedNumber& ref) 
        { 
                return RangedNumber(mInt+ref.mInt); 
        }

        RangedNumber operator+(const Number val) 
        { 
                return RangedNumber(mInt+val); 
        }

        Number getInt() 
        { 
                return mInt; 
        }

/* Can't be used because of default behavior of gcc to convert all values of  
        expression to the Number. We will lost a bounds checking. 
        operator Number() 
        { 
                return mInt; 
        } 
*/ 
};


#endif /*__RANGEDNUMBER_H__*/
