// tiscriptsqlite.cpp : Defines the entry points for the DLL and TIScript extension library.
//

#include "tiscriptsqlite.h"

#ifdef __cplusplus
extern "C" {
#endif

void init_db_class( tiscript::VM *vm );
void init_rs_class( tiscript::VM *vm );

void EXTAPI  TIScriptLibraryInit(tiscript_VM* vm, tiscript_native_interface* piface )
{
  tiscript::ni(piface);

  init_db_class( vm );
  init_rs_class( vm );
}

#ifdef __cplusplus
}
#endif
