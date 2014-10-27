#include "GameDirector.hpp"
#include "FileSystem.hpp"

int main(int argc, char** argv)
{
    try {
        ScriptManager scriptManager;

        FileSystem   fileSystem(argv[0]);
        fileSystem.addSearchPath("assets/");
        GameDirector director;
        Application  app;

        director.timePerFrame(sf::seconds(1.f / 60.f));
        director.setScriptManager(scriptManager);
        director.setFileSystem(fileSystem);
        director.setApp(app);

        director.DEBUGrun();

    } catch(const Exception& e) {
        std::cout << e.info() << std::endl << e.what() << std::endl;
        std::cin.get();

    } catch(const luabridge::LuaException& e) {
        std::cout << e.what() << std::endl;
        std::cin.get();
    }

    std::cin.get();
    return 0;
}