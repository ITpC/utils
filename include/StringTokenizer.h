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
#  define __STRINGTOKENIZER__H__
#  include <vector>
#  include <string>
#  include <string.h>
#  include <algorithm>
#  include <list>

namespace itc
{
  namespace utils
  {

    /**
     * @brief StringTokenizer is a tokenizer container
     * 
     * @method scan - an input string scanner
     **/
    class StringTokenizer
    {
     private:
      std::list<std::string> tokens;

     public:

      explicit StringTokenizer() = default;

      /**
       *@brief a scanner is a C++11 string tokenizer, which  takes input string 
       * 'data' and splits it into list of tokens based on 'delimiters' 
       * parameter. If symlexemes parameter is not empty this tokenizer will 
       * assume the symbols of this parameter are the 
       * separate lexems/tokens (as they are the terminal symbols).
       * 
       * @param data is the input sequence of symbols [std::string]
       * @param delimiters is the set of delimiters [std::string]
       * @param symlexemes is optional set of the terminal symbols those may be 
       * required for grammar [std::string].
       * 
       * @brief If you provide an empty string in delimiters, then those symbols in
       * symlexemesm if there any, will act as delimiters. However they will be placed
       * into resulting list.
       **/
      const std::list<std::string>& scan(
        const std::string& data,
        const std::string& delimiters,
        const std::string& symlexemes = ""
        )
      {
        std::string token;
        tokens.clear();

        std::for_each(
          data.begin(), data.end(),
          [this, &delimiters, &token, &symlexemes](const char c){
            bool nodelim = true;

            for(size_t i = 0; i < delimiters.size(); i++)
            {
              if(c == delimiters[i])
              {
                if(!token.empty())
                {
                  tokens.push_back(token);
                    token.clear();
                }
                nodelim = false;
                break;
              }
            }

            bool oslex = false;

            if(nodelim)
            {
              for(size_t i = 0; i < symlexemes.size(); i++)
              {
                if(c == symlexemes[i])
                {
                  oslex = true;
                  if(!token.empty())
                  {
                    tokens.push_back(token);
                      token.clear();
                  }
                  token.append(1u, c);
                    tokens.push_back(token);
                    token.clear();
                }
              }
            }
            if(nodelim && (!oslex))
            {
              token.append(1u, c);
            }
          }
        );
        if(!token.empty())
        {
          tokens.push_back(token);
          token.clear();
        }
        return tokens;
      }
    };
  }
}
#endif
