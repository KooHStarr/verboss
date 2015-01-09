#include "TileMapSystem.hpp"


////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TileMapSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
{

}


//////////////////////////////////////////////////
void TileMapSystem::setTileMap(tmx::MapLoader* map)
{
    m_tileMap = map;
    auto& layers = map->GetLayers();
    int layerCount = 0;

    for (auto& layer : layers)
    {
        layerCount++;

        if (layer.type == tmx::ObjectGroup)
        {
            for (auto& object : layer.objects) {
                if (object.GetPropertyString("entity_name") != "")
                    m_addEntityFromFile(object, layerCount);
                else
                    m_addSimpleEntity(object);
            }
        }
    }
}


//////////////////////////////////////////////////
tmx::MapLoader* TileMapSystem::getTileMap() const
{
    return m_tileMap;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TileMapSystem::m_attachPhysicsBodyToEntity(tmx::MapObject& object, EntityWrapper entity, b2BodyType type)
{
    b2World* world                   = m_entityManager->systems.system <PhysicsSystem> ()->getWorld();
    b2Body* body                     = tmx::BodyCreator::Add(object, *world, type);
    PhysicsComponent::Handle phandle = entity.getEntity().component <PhysicsComponent> ();

    if (phandle->configTable["restitution"])
        body->GetFixtureList()->SetRestitution(phandle->configTable["restitution"].cast <float> ());
    /*end of init*/

    if (phandle->body)
        world->DestroyBody(phandle->body);

    phandle->body = body;

    GraphicsComponent::Handle ghandle = entity.getEntity().component <GraphicsComponent> ();
    if (ghandle)
    {
        ghandle->sprite.setRotation(thor::toDegree(body->GetAngle()));
        ghandle->sprite.setPosition(si::pixels(body->GetPosition()));
    }

    if (object.GetPropertyString("controller").size() > 3)
    {
        InputManager* im = global.vgbLuaNamespace["input"];
        im->addController(entity, object.GetPropertyString("controller"));
    }
}


/////////////////////////////////////////////////////////////////////////////
void TileMapSystem::m_addEntityFromFile(tmx::MapObject& object, int layerCount)
{
    EntityManagerWrapper* manager = global.vgbLuaNamespace["entityManager"];
    EntityWrapper wrapper         = manager->createEntityF(object.GetPropertyString("entity_name"));
    entityx::Entity entity        = wrapper.getEntity();
    PhysicsComponent::Handle ph   = entity.component <PhysicsComponent> ();
    GraphicsComponent::Handle gc  = entity.component <GraphicsComponent> ();
    std::string bodyType          = ph->configTable["type"];

    if (gc)
        gc->renderOrder = layerCount;

    if (bodyType == "dynamic")
        m_attachPhysicsBodyToEntity(object, wrapper, b2_dynamicBody);

    else if (bodyType == "static")
        m_attachPhysicsBodyToEntity(object, wrapper, b2_staticBody);

    else if (bodyType == "kinematic")
        m_attachPhysicsBodyToEntity(object, wrapper, b2_kinematicBody);
    else
        throw Exception ("<TileMapSystem::m_addEntityFromFile>", "Bad body type '" + bodyType +
                         "'. From entity file '" + object.GetPropertyString("entity_name") + "'");

    wrapper.setProperty("name", object.GetName());
    wrapper.getBody()->SetUserData(new EntityWrapper(wrapper));
}


/////////////////////////////////////////////////////////////
void TileMapSystem::m_addSimpleEntity(tmx::MapObject& object)
{
    EntityManagerWrapper* manager = global.vgbLuaNamespace["entityManager"];
    EntityWrapper wrapper         = manager->createEntity();
    entityx::Entity entity        = wrapper.getEntity();
    PhysicsComponent::Handle ph   = entity.assign <PhysicsComponent> ();
    b2World* world                = m_entityManager->systems.system <PhysicsSystem> ()->getWorld();
    b2Body *body                  = tmx::BodyCreator::Add(object, *world);

    wrapper.setProperty("name", object.GetName());
    body->SetUserData(new EntityWrapper(wrapper));
    ph->body = body;
}