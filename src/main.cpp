/*
# main.cpp

The "main" source file with most of the boilerplate code. Includes the
`NativesMain` header for initialising plugin-natives.

- `Supports` declares to the SA:MP server which features this plugin uses.
- `Load` is called when the plugin loads and sets up the `logprintf` function.
*/

#include <amx/amx.h>
#include <plugincommon.h>

#include "common.hpp"
#include "natives.hpp"

logprintf_t logprintf;

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
    return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void** ppData)
{
    pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
    logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];

	logprintf("    < cec 1.0 | Copyright 2020 > ");
    logprintf("     Author: Ak-kawit \"leaks666\" Tahae");
	logprintf("   Repository: https://github.com/aktah/cec");
	logprintf(" ");
	logprintf("      --------------------------------");
    return true;
}

extern "C" const AMX_NATIVE_INFO native_list[] = {

	{ "CE_Convert", Natives::CE_Convert },
	{ "CE_Convert_Dialog", Natives::CE_Convert_Dialog },
	{ "CE_CountTag", Natives::CE_CountTag },
	{ "CE_CountVowel", Natives::CE_CountVowel },

    { NULL, NULL }
};

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX* amx)
{
    return amx_Register(amx, native_list, -1);
}

PLUGIN_EXPORT int PLUGIN_CALL Unload()
{
    return 1;
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX* amx)
{
    return 1;
}
