#include "GameDirector.hpp"
#include "ScriptManager.hpp"
#include <iostream>
#include <LuaBridge.h>

class Test
{
public:
    Test(int i) : i(i) {}

    int testMethod(int test)
    {
        std::cout << "Method called with arg " << test << std::endl;
        return i;
    }

    int i;
};

int main()
{
    try {
        ScriptManager scriptManager;
        lua_State* L = scriptManager.getVM();

        luabridge::getGlobalNamespace(L)
                .beginClass <Test> ("Test")
                    .addFunction("testFunc", &Test::testMethod)
                    .addData("i", &Test::i)
                    .addConstructor <void (*) (int)> ()
                .endClass();

        scriptManager.doFile("script.lua");

    } catch(const Exception& e) {
        std::cout << e.info();
    }

    /*GameDirector director;
    Application  app;

    director.timePerFrame(sf::seconds(1 / 60));
    director.setApp(app);
   // app.addScene("scene.lua");

    director.run();
*/
    return 0;
}