
// #pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunknown-pragmas"

#include "sciter-x-window.hpp"
// #pragma GCC diagnostic pop

#include <functional>

// native API demo

// native functions exposed to script
//static int native_sum(int a, int b) { return a + b; }
//static int native_sub(int a, int b) { return a - b; }


static sciter::value native_api() {
    sciter::value api_map;
    sciter::value api_math_map;

    std::function<int(int,int)> native_sum = [](int a, int b) { return a + b; };
    std::function<int(int,int)> native_sub = [](int a, int b) { return a - b; };

    api_math_map.set_item(sciter::value("sum"), sciter::vfunc( native_sum ));
    api_math_map.set_item(sciter::value("sub"), sciter::vfunc( native_sub ));

    api_map.set_item(sciter::value("math"), api_math_map);

    /*
        return {
            math: {
                sum: {native_sum},
                sub: {native_sub},
            }
        }
    */
    return api_map;
}


class frame: public sciter::window {
public:
    frame() : window(SW_TITLEBAR | SW_RESIZEABLE | SW_CONTROLS | SW_MAIN | SW_ENABLE_DEBUG) {}

    BEGIN_FUNCTION_MAP
        FUNCTION_0("helloWorld", helloWorld);
        FUNCTION_0("nativeApi", native_api);
    END_FUNCTION_MAP

    sciter::string  helloWorld() { return WSTR("Hello u-minimal World"); }

};

#include "resources.cpp"
#if defined(LINUX)
#  include "sciter-gtk-main.cpp"
#endif

int uimain(std::function<int()> run ) {
    SciterSetOption(NULL, SCITER_SET_DEBUG_MODE, TRUE);

    sciter::archive::instance().open(aux::elements_of(resources)); // bind resources[] (defined in "resources.cpp") with the archive

    frame *pwin = new frame();

    // note: this:://app URL is dedicated to the sciter::archive content associated with the application
    pwin->load( WSTR("this://app/main.html") );

    //pwin->load( WSTR("file:///home/andrew/Desktop/test.htm") );

    pwin->expand();

    return run();
}
