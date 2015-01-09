#ifndef ENTITYMANAGERWRAPPER_HPP
#define ENTITYMANAGERWRAPPER_HPP

#include <tuple>
#include "EntityWrapper.hpp"
#include "EntityComponents/CustomPropertyComponent.hpp"
#include "EntityComponents/GraphicsComponent.hpp"
#include "EntityComponents/AnimationComponent.hpp"
#include "ResourceManager.hpp"
#include "Helpers.hpp"

class EntityManagerWrapper
{
public:
    EntityManagerWrapper();
    EntityWrapper getEntityByName(const std::string& name);
    EntityWrapper getEntityFromBody(const b2Body* body);
    void setManager(entityx::EntityX* manager);
    EntityWrapper createEntity();
    EntityWrapper createEntityF(const std::string& entity_name);

private:
    void m_addGraphicsComponent (entityx::Entity entity, luabridge::LuaRef gchandle);
    void m_addPhysicsComponent  (entityx::Entity entity, luabridge::LuaRef phandle);
    void m_addAnimationComponent(entityx::Entity entity, luabridge::LuaRef ahandle);

    std::vector <std::string>                m_animationGetAnimationsKeys(const std::string& tableName);
    std::tuple <thor::FrameAnimation, float> m_animationAddFrames(const std::vector <std::string>&, const std::string&, const std::string&);
    float                                    m_animationGetDuration(const std::string&, const std::string&);

    entityx::EntityX* m_manager;
};

#endif