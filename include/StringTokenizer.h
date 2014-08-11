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
 * $Id: StringTokenizer.h 56 2007-05-22 09:05:13Z Pavel Kraynyukhov $
 * 
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 * 
 **/

#ifndef __STRINGTOKENIZER__H__
#define __STRINGTOKENIZER__H__
#include <vector>
#include <string>
#include <string.h>

namespace itc 
{
    namespace utils {
       /**
        * Decouple a tokens from C++ string separeted by some delimiter.
        * The bordering spaces are trimmed from token automatically. 
        * The spases are detected by isspace c function.
        * @note  the tokens are dinamically allocated and destructor do not care 
        * about deallocation of them. It is responsibility of developer to control 
        * deallocation of these tokens in his sorce code.
        * @note No exceptions supported.
        **/
        class StringTokenizer
        {
            private: 
                typedef std::vector<std::string::size_type> PositionVector;
                
                std::vector<std::string>    Tokens;
                PositionVector              Delimiters;
                std::string::size_type      dlmLen;
                std::string::size_type      textLen;
                size_t                      position;
            public:
               /**
                * @param text - C++ string which has to be tokenized
                * @param delimiter C++ string that represents a delimiter of tokens for given text
                **/
                StringTokenizer(const std::string& text,const std::string& delimiter)
                :    dlmLen(delimiter.length()),textLen(text.length()),position(0)
                {
                    if(textLen>0)
                    {
                        std::string::size_type pos=0;
                        std::string::size_type pos_next=0;
                        bool is_a_delimiter=false;
                        for(size_t i=pos;i<textLen;i++)
                        {
                            for(size_t j=0;j<dlmLen;j++)
                            {
                                if(text.c_str()[i]==delimiter.c_str()[j])
                                {
                                    is_a_delimiter=true;
                                    break;
                                }
                            }
                            if(is_a_delimiter)
                            {
                                if(pos!=pos_next)
                                {
                                    std::string tmp;
                                    tmp.insert(0,text,pos,pos_next-pos);
                                    Tokens.push_back(tmp);
                                }
                                
                                pos_next++;
                                pos = pos_next;
                                is_a_delimiter=false;
                            }
                            else
                            {
                                pos_next++;
                                if(pos_next == textLen )
                                {
                                    std::string tmp;
                                    tmp.insert(0,text,pos,pos_next-pos);
                                    Tokens.push_back(tmp);                  
                                }
                            }
                        }
                    }
                }
                
                ~StringTokenizer()
                {
                    Tokens.clear();
                }
        
                
                /**
                  * @return an amount of tokens.
                  */
                
                inline size_t size()
                {
                    return Tokens.size();
                }
        
                
                /**
                  * @return true if no tokens are determined in given text.
                  */
                inline bool empty()
                {
                    return Tokens.size()==0;
                }
                
        
                /**
                  * @return true when next token is present, false otherwiese.
                  */
                inline bool hasNextToken()
                {
                    return ((Tokens.size())>position);
                }
        
                
                /**
                  * @return next token.
                  * @note here is no availability check, be sure to check presence 
                  * of next token with a method hasNextToken()
                  */
                inline std::string& nextToken()
                {
                    return Tokens[position++];
                }
        
                
                /**
                  * @return number of tokens still remaining to be taken by 
                  * StringTokenizrer::nextToken()
                  */
                inline size_t tokensRemain()
                {
                    return Tokens.size()-position;
                }
                
                inline std::vector<std::string>::iterator begin()
                {
                    return Tokens.begin();
                }
        
                inline std::vector<std::string>::iterator end()
                {
                    return Tokens.end();
                }
        
                inline std::vector<std::string>::reverse_iterator rbegin()
                {
                    return Tokens.rbegin();
                }
        
                inline std::vector<std::string>::reverse_iterator rend()
                {
                    return Tokens.rend();
                }
                
                inline std::string& operator[] (size_t i)
                {
                    return Tokens[i];
                }
                
                inline char* trim(char* src)
                {
                    size_t i=0,j=0;
                    size_t len=strlen(src);
                    if(len==0) return NULL;
                    for(i=0;i<len;i++)
                        if(isspace(src[i]) == 0 )
                            break;
                    
                    for(j=(len-1);j>=0;j--)
                        if(isspace(src[j]) == 0 )
                            break;
        
                    if((i!=0)||(j!=(len-1)))
                    {
                        size_t cplen=(len-i)-(len-(++j));
                        char* tmp=new char[cplen+1];
                        memset(tmp,0,cplen+1);
                        strncpy(tmp,&(src[i]),cplen);
                        return tmp;
                    }
                    return src;
                }
        };
    }
}
#endif
