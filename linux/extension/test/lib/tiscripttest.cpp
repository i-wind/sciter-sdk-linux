// tiscripttest.cpp: Defines the entry points for the TIScript extension library test.
//

#define TISCRIPT_EXT_MODULE

#include <iostream>
#include "sciter-x-types.h"
#include "tiscript.hpp"
#include "aux-cvt.h"

#define TEST_BUSY 5

#ifdef __cplusplus
extern "C" {
#endif

void init_test_class(tiscript::VM *vm);

void EXTAPI TIScriptLibraryInit(tiscript_VM* vm, tiscript_native_interface* piface) {
    // std::cerr << "TIScriptLibraryInit ...\n";
    tiscript::ni(piface);
    init_test_class(vm);
}

tiscript::value Test_open(tiscript::VM* vm) {
    std::cerr << "Test_open called ...\n";
    return tiscript::v_null();
}

tiscript::value Test_close(tiscript::VM* vm) {
    std::cerr << "Test_close called ...\n";
    return tiscript::v_null();
}

tiscript::value Test_exec(tiscript::VM* vm) {
    // LPCWSTR value = u"Test_exec called ...";
    const char16_t* value = u"Test_exec called ...";
    return tiscript::v_string(vm, value);
}

// GC detected that the db object is not used by anyone so ...
static void finalize(tiscript::VM *vm, tiscript::value test_obj) {
    std::cerr << "finalize called ...\n";
}

#pragma GCC diagnostic ignored "-Wmissing-field-initializers"

void init_test_class(tiscript::VM* vm) {

    static tiscript::method_def methods[] =  {
        tiscript::method_def("open",  Test_open),
        tiscript::method_def("close", Test_close),
        tiscript::method_def("exec",  Test_exec),
        tiscript::method_def()
    };

    static tiscript::const_def consts[] = {
        tiscript::const_def("BUSY", TEST_BUSY),
        tiscript::const_def()
    };

    static tiscript::class_def test_class =  {
        "Test",
        methods,
        NULL,
        consts,
        0, // get []
        0, // set []
        finalize
    };

    std::cerr << "define_class ...\n";
    tiscript::define_class(vm, &test_class, tiscript::get_current_ns(vm));
}

#ifdef __cplusplus
}  // extern "C"
#endif
