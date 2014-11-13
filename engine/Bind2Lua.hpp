#ifndef BIND2LUA_HPP
#define BIND2LUA_HPP

namespace bind2lua
{
    namespace detail
    {
        ScriptManager*   sm;
        ResourceManager* rm;
        Application*     app;

        inline entityx::Entity createEntity(const std::string& entity_name)
        {
            auto entity = app->entities.create();
            luabridge::LuaRef ref = sm->getGlobal(entity_name);

            if (!ref["GraphicsComponent"].isNil())
            {
                luabridge::LuaRef handle = ref["GraphicsComponent"];
                GraphicsComponent::Handle gc = entity.assign <GraphicsComponent> ();

                //replace this by loading from stream

                //std::to_string
                std::stringstream ss;
                ss << entity_name << entity.id();

                gc->sprite.setTexture(*rm->load <sf::Texture> (ss.str(),
                                       thor::Resources::fromFile <sf::Texture> (handle["filename"].cast <std::string>())));
            }

            if (!ref["BodyComponent"].isNil())
            {
                luabridge::LuaRef handle = ref["BodyComponent"];
                BodyComponent::Handle bc = entity.assign <BodyComponent> ();

                luabridge::LuaRef pshandle = sm->getGlobal("vgb")["physicsSystem"];
                PhysicsSystem* ps = pshandle.cast <PhysicsSystem*> ();
                b2World* world = ps->getWorld();

                b2BodyDef bodyDef;
                bodyDef.position = b2Vec2(0, 0);
                bodyDef.type = b2_staticBody;

                b2Body* body  = world->CreateBody(&bodyDef);
                b2PolygonShape shape;
                shape.SetAsBox(tmx::SfToBoxVec(sf::Vector2f(100, 10)).x, tmx::SfToBoxVec(sf::Vector2f(10, 100)).y);
                b2FixtureDef fixtureDef;
                fixtureDef.density = 0.f;
                fixtureDef.shape = &shape;
                body->CreateFixture(&fixtureDef);

                bc->body = body;
            }

            return entity;
        }

        inline void regGui()
        {
            sm->globalNamespace()
                    .beginNamespace("vgb")
                        .beginClass <tgui::Gui> ("tguiGui")
                            .addFunction("loadWidgetsFromFile", &tgui::Gui::loadWidgetsFromFile)
                            .addFunction("render", &tgui::Gui::draw)
                            .addFunction("setGlobalFont", (bool (tgui::Gui::*) (const std::string&)) &tgui::Gui::setGlobalFont)
                        .endClass()
                    .endNamespace();
        }
    }

    inline void scriptManager(ScriptManager* sm)
    {
        detail::sm = sm;

        detail::sm->globalNamespace()
                .beginNamespace("vgb")
                    .beginClass <ScriptManager> ("ScriptManager")
                        .addFunction("import", &ScriptManager::doFile)
                    .endClass()
                .endNamespace();

        luabridge::LuaRef t = detail::sm->getGlobal("vgb");
        t["detail_scriptManager"] = sm;
        detail::sm->doString("function import(filename) vgb.detail_scriptManager:import(filename) end\n");
    }

    inline void gameDirector(GameDirector* dir)
    {
        detail::sm->globalNamespace()
                .beginNamespace("vgb")
                    .beginClass <GameDirector> ("GameDirector")
                        .addFunction("scenes", &GameDirector::scenes)
                    .endClass()
                .endNamespace();

        luabridge::LuaRef t = detail::sm->getGlobal("vgb");
        t["director"] = dir;
    }

    inline void sceneManager()
    {
        detail::sm->globalNamespace()
                .beginNamespace("vgb")
                    .beginClass <SceneManager> ("SceneManager")
                        .addFunction("addScene", &SceneManager::addScene)
                        .addFunction("changeScene", &SceneManager::changeScene)
                        .addFunction("removeScene", &SceneManager::removeScene)
                    .endClass()
                .endNamespace();
    }

    inline void fileSystem(FileSystem* fs)
    {
        detail::sm->globalNamespace()
                .beginNamespace("vgb")
                    .beginClass <FileSystem> ("FileSystem")
                        .addFunction("addSearchPath", &FileSystem::addSearchPath)
                    .endClass()
                .endNamespace();

        luabridge::LuaRef t = detail::sm->getGlobal("vgb");
        t["fileSystem"] = fs;
    }

    inline void gui()
    {
        detail::sm->globalNamespace()
                .beginNamespace("vgb")
                    .beginClass <GameDirector::TGUI_GuiWrapper> ("TGUI_GuiWrapper")
                        .addConstructor <void (*) (void)> ()
                        .addData("gui", &GameDirector::TGUI_GuiWrapper::gui)
                    .endClass()
                .endNamespace();

        detail::regGui();

        detail::sm->doString("function vgb.Gui()\n"
                             "vgb.detail_gui_wrapper = vgb.TGUI_GuiWrapper()\n"
                             "vgb.currentGui = vgb.detail_gui_wrapper.gui\n"
                             "return vgb.currentGui\n end\n");
    }

    inline void application(Application* app)
    {
        //EntityManager
        detail::app = app;

        detail::sm->globalNamespace()
                .beginNamespace("vgb")
                    .beginClass <entityx::EntityManager> ("EntityManager")
                        .addFunction("create", &entityx::EntityManager::create)
                    .endClass()

                    //here registrate a function to create entities from .lua file
                    .addFunction("createEntity", &detail::createEntity)

                    .beginClass <PhysicsSystem> ("PhysicsSystem")
                        .addFunction("create", &PhysicsSystem::create)
                        .addFunction("debugRender", &PhysicsSystem::debugRender)
                    .endClass()
                .endNamespace();

        luabridge::LuaRef t = detail::sm->getGlobal("vgb");
        t["entityManager"] = &app->entities;
        t["physicsSystem"] = app->systems.system <PhysicsSystem> ().get();
    }

    inline void resourceManager(ResourceManager* rm)
    {
        detail::rm = rm;

        detail::sm->globalNamespace()
                .beginNamespace("vgb")
                    .beginClass <ResourceManager> ("ResourceManager")

                    .endClass()
                .endNamespace();

        luabridge::LuaRef t = detail::sm->getGlobal("vgb");
        t["resourceManager"] = rm;
    }

    inline void entity()
    {
        detail::sm->globalNamespace()
                .beginNamespace("vgb")
                    .beginClass <entityx::Entity> ("Entity")

                    .endClass()
                .endNamespace();
    }
}

#endif