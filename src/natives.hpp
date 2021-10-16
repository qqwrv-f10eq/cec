/*
# natives.hpp

Contains all the `PAWN_NATIVE_DECL` for native function declarations.
*/

#ifndef CEC_NATIVES_H
    #define CEC_NATIVES_H

#include <string>
#include <string.h>

#include <amx/amx2.h>

#include "common.hpp"

namespace Natives 
{
    int CE_Convert(AMX* amx, cell* params);
    int CE_Convert_Dialog(AMX* amx, cell* params);
    int CE_CountTag(AMX* amx, cell* params);
    int CE_CountVowel(AMX* amx, cell* params);
}

#endif
