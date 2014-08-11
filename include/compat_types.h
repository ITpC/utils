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
 * $Id: compat_types.h 56 2007-05-22 09:05:13Z Pavel Kraynyukhov $
 * 
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 * 
 **/

#ifndef __COMPAT_TYPES__
#define __COMPAT_TYPES__
#ifdef _MSC_VER
#include <windows.h>
#endif
#include <sys/types.h>
#include <stdint.h>

#ifdef _MSC_VER
#   ifndef int8_t
        typedef INT8 int8_t;
#   endif
#   ifndef int16_t
        typedef INT16 int16_t;
#   endif
#   ifndef int32_t
        typedef INT32 int32_t;
#   endif
#   ifndef int64_t
        typedef INT64 int64_t;
#   endif
#   ifndef uint8_t
        typedef UINT8 uint8_t;
#   endif
#   ifndef uint16_t
        typedef UINT16 uint16_t;
#   endif
#   ifndef uint32_t
        typedef UINT32 uint32_t;
#   endif
#   ifndef uint64_t
        typedef UINT64 uint64_t;
#   endif
#   ifndef long32_t
        typedef LONG32 long32_t;
#   endif
#   ifndef ulong32_t
        typedef ULONG32 ulong32_t;
#   endif
#endif

#endif

