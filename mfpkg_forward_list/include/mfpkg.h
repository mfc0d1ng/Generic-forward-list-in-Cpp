#ifndef MFPKG_H
#define MFPKG_H

#include <initializer_list>

namespace basic_mfpkg
{
    class basic_forward_list;
};

namespace mfpkg
{
    template <typename _Tp> class forward_list;
};

#include "forward_list/basic_forward_list.h"
#include "forward_list/forward_list.h"

#endif
