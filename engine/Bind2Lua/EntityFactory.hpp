#ifndef ENTITYFACTORY_HPP
#define ENTITYFACTORY_HPP

namespace bind2lua
{
    Application* detail_application;

    ////////////////////////////////////////////////////////////////////////////////////
    inline void addGraphicsComponent(entityx::Entity entity, luabridge::LuaRef gchandle)
    {
        std::string filename = gchandle["filename"].cast <std::string> ();
        GraphicsComponent::Handle handle = entity.assign <GraphicsComponent> ();
        handle->renderOrder = gchandle["renderOrder"].cast <int> ();
        handle->sprite.setTexture(*detail_application->resourceManager().load <sf::Texture> (filename, thor::Resources::fromFile <sf::Texture> (filename)));
        handle->sprite.setOrigin(handle->sprite.getLocalBounds().width / 2,
                                 handle->sprite.getLocalBounds().height / 2);
    }

    /////////////////////////////////////////////////////////////////////////////////
    inline void addPhysicsComponent(entityx::Entity entity, luabridge::LuaRef phandle)
    {
        PhysicsComponent::Handle handle = entity.assign <PhysicsComponent> ();
        handle->configTable = phandle;
    }

    /////////////////////////////////////
    inline EntityWrapper createEntity()
    {
        return EntityWrapper(detail_application->entities.create());
    }


    ////////////////////////////////////////////////////////
    inline EntityWrapper createEntityF(const std::string& entity_name)
    {
        luabridge::LuaRef handle = global.scriptManager.getGlobal(entity_name);
        EntityWrapper entity = createEntity();

        if (handle["GraphicsComponent"])
            addGraphicsComponent(entity.getEntity(), handle["GraphicsComponent"]);

        if (handle["PhysicsComponent"])
            addPhysicsComponent(entity.getEntity(), handle["PhysicsComponent"]);

        return entity;
    }


    /////////////////////
    inline void entity()
    {
        global.scriptManager.globalNamespace()
                .beginNamespace("vgb")
                .beginClass <EntityWrapper> ("EntityWrapper")
                .addProperty("body", &EntityWrapper::getBody)
                .endClass()

                .endNamespace();
    }
}

#endif