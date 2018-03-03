// -*- C++ -*-
//===------------------- support/musl/xlocale.h ------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
// This adds support for the extended locale functions that are currently
// missing from the PDCLIB C library.
//
// This only works when the specified locale is "C" or "POSIX", but that's
// about as good as we can do without implementing full xlocale support
// in PDCLIB
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP_SUPPORT_PDCLIB_XLOCALE_H
#define _LIBCPP_SUPPORT_PDCLIB_XLOCALE_H

#include <cstdlib>
#include <cwchar>
#include <stdarg.h>
#include <support/xlocale/__nop_locale_mgmt.h>
#include <support/xlocale/__posix_l_fallback.h>
#include <support/xlocale/__strtonum_fallback.h>

static inline
int vasprintf(char **strp, const char *fmt, va_list ap)
{
  const size_t buff_size = 256;
  size_t str_size;
  if ((*strp = (char *)malloc(buff_size)) == NULL)
  {
    return -1;
  }
  if ((str_size = vsnprintf(*strp, buff_size, fmt,  ap)) >= buff_size)
  {
    if ((*strp = (char *)realloc(*strp, str_size + 1)) == NULL)
    {
      return -1;
    }
    str_size = vsnprintf(*strp, str_size + 1, fmt,  ap);
  }
  return str_size;
}

#endif // _LIBCPP_SUPPORT_PDCLIB_XLOCALE_H
