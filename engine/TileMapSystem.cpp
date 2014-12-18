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
                EntityManagerWrapper* entmanager = global.vgbLuaNamespace["entityManager"];
                entityx::Entity ent;
                EntityWrapper wrap;
                PhysicsComponent::Handle phandle;
                b2World *world = m_entityManager->systems.system < PhysicsSystem > ()->getWorld();

                // create complex entity with box2d body (dynamic or static)
                if (object.GetPropertyString("entity_name") != "") {
                    wrap = entmanager->createEntityF(object.GetPropertyString("entity_name"));
                    ent = wrap.getEntity();

                    GraphicsComponent::Handle gchandle = ent.component <GraphicsComponent> ();
                    gchandle->renderOrder = layerCount;

                    phandle = ent.component<PhysicsComponent>();
                    m_addName(ent, object);

                    if (phandle->configTable["type"] == "dynamic")
                        m_addComplexDynamicBody(object, world, phandle);
                    else
                        m_addComplexStaticBody(object, world, phandle, ent);

                    // create simple entity with static body
                } else {
                    wrap = entmanager->createEntity();
                    ent = wrap.getEntity();
                    m_addName(ent, object);
                    phandle = ent.assign<PhysicsComponent>();
                    b2Body *body = tmx::BodyCreator::Add(object, *world);
                    phandle->body = body;
                }

                if (object.GetPropertyString("controller").size() > 3)
                {
                    InputManager* im = global.vgbLuaNamespace["input"];
                    im->addController(wrap, object.GetPropertyString("controller"));
                }
            }
        }
    }
}


//////////////////////////////////////////////////
tmx::MapLoader* TileMapSystem::getTileMap() const
{
    return m_tileMap;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TileMapSystem::m_addComplexDynamicBody(tmx::MapObject& object, b2World* world, PhysicsComponent::Handle phandle)
{
    b2Body* body = tmx::BodyCreator::Add(object, *world, b2_dynamicBody);

    /*here init the body from lua file*/
    if (phandle->configTable["restitution"])
        body->GetFixtureList()->SetRestitution(phandle->configTable["restitution"].cast <float> ());
    /*end of init*/

    if (phandle->body)
        world->DestroyBody(phandle->body);

    phandle->body = body;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TileMapSystem::m_addComplexStaticBody(tmx::MapObject& object, b2World* world, PhysicsComponent::Handle phandle, entityx::Entity ent)
{
    b2Body* body = tmx::BodyCreator::Add(object, *world);

    /*here init the body from lua file*/
    if (phandle->configTable["restitution"])
        body->GetFixtureList()->SetRestitution(phandle->configTable["restitution"].cast <float> ());
    /*end of init*/

    if (phandle->body)
        world->DestroyBody(phandle->body);

    phandle->body = body;

    GraphicsComponent::Handle ghandle = ent.component <GraphicsComponent> ();
    if (ghandle)
    {
        ghandle->sprite.setRotation(thor::toDegree(body->GetAngle()));
        ghandle->sprite.setPosition(si::pixels(body->GetPosition()));
    }
}


/////////////////////////////////////////////////////////////////////////
void TileMapSystem::m_addName(entityx::Entity ent, tmx::MapObject& object)
{
    CustomPropertyComponent::Handle cph = ent.component <CustomPropertyComponent> ();
    cph->property["name"] = object.GetName();
}