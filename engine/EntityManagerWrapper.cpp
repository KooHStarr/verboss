#include "EntityManagerWrapper.hpp"

////////////////////////////////////////////////////////////////////////////
EntityWrapper EntityManagerWrapper::getEntityByName(const std::string& name)
{
    CustomPropertyComponent::Handle cph;

    for (auto entity : m_manager->entities.entities_with_components(cph))
    {
        if (cph->property["name"] == name)
            return EntityWrapper(entity);
    }

    return createEntity();
}


//////////////////////////////////////////////////////////////////
void EntityManagerWrapper::setManager(entityx::EntityX* manager)
{
    m_manager = manager;
}


/////////////////////////////////////////////////
EntityWrapper EntityManagerWrapper::createEntity()
{
    entityx::Entity ent = m_manager->entities.create();
    ent.assign <CustomPropertyComponent> ();
    return EntityWrapper(ent);
}


/////////////////////////////////////////////////////////////////////////////////
EntityWrapper EntityManagerWrapper::createEntityF(const std::string& entity_name)
{
    luabridge::LuaRef handle = global.scriptManager.getGlobal(entity_name);
    EntityWrapper entity = createEntity();

    if (handle["GraphicsComponent"])
        m_addGraphicsComponent(entity.getEntity(), handle["GraphicsComponent"]);

    if (handle["PhysicsComponent"])
        m_addPhysicsComponent(entity.getEntity(), handle["PhysicsComponent"]);

    return entity;
}


////////////////////////////////////////////////////////////////////////////////////
void EntityManagerWrapper::m_addGraphicsComponent(entityx::Entity entity, luabridge::LuaRef gchandle)
{
    std::string filename = gchandle["filename"].cast <std::string> ();
    GraphicsComponent::Handle handle = entity.assign <GraphicsComponent> ();

    handle->renderOrder = gchandle["renderOrder"].cast <int> ();
    ResourceManager* rm = global.vgbLuaNamespace["resourceManager"];

    handle->sprite.setTexture(*rm->load <sf::Texture> (filename, thor::Resources::fromFile <sf::Texture> (filename)));
    handle->sprite.setOrigin(handle->sprite.getLocalBounds().width / 2,
            handle->sprite.getLocalBounds().height / 2);
}

/////////////////////////////////////////////////////////////////////////////////
void EntityManagerWrapper::m_addPhysicsComponent(entityx::Entity entity, luabridge::LuaRef phandle)
{
    PhysicsComponent::Handle handle = entity.assign <PhysicsComponent> ();
    handle->configTable = phandle;
}