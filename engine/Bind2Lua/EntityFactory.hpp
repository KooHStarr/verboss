#ifndef ENTITYFACTORY_HPP
#define ENTITYFACTORY_HPP

namespace bind2lua
{
    Application* app;

    ////////////////////////////////////////////////////////////////////////////////////
    inline void addGraphicsComponent(entityx::Entity entity, luabridge::LuaRef gchandle)
    {
        std::string filename = gchandle["filename"].cast <std::string> ();
        GraphicsComponent::Handle handle = entity.assign <GraphicsComponent> ();
        handle->renderOrder = gchandle["renderOrder"].cast <int> ();
        handle->sprite.setTexture(*app->resourceManager().load <sf::Texture> (filename, thor::Resources::fromFile <sf::Texture> (filename)));
    }

    /////////////////////////////////////
    inline entityx::Entity createEntity()
    {
        return app->entities.create();
    }


    ////////////////////////////////////////////////////////
    inline entityx::Entity createEntityF(const std::string& entity_name)
    {
        luabridge::LuaRef handle = global.scriptManager.getGlobal(entity_name);
        entityx::Entity entity = createEntity();

        if (handle["GraphicsComponent"])
            addGraphicsComponent(entity, handle["GraphicsComponent"]);

        return entity;
    }


    /////////////////////
    inline void entity()
    {
        global.scriptManager.globalNamespace()
                .beginNamespace("vgb")
                .beginClass <entityx::Entity> ("Entity")

                .endClass()
                .endNamespace();
    }
}

#endif