#include "EntityManagerWrapper.hpp"

EntityManagerWrapper::EntityManagerWrapper() : m_manager(nullptr) {}

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


////////////////////////////////////////////////////////////////////////////
EntityWrapper EntityManagerWrapper::getEntityFromBody(const b2Body* body)
{
    return * (EntityWrapper*) body->GetUserData();
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
    entity.setProperty("tableName", entity_name);
    entity.setProperty("type", handle["type"]);

    if (handle["GraphicsComponent"])
        m_addGraphicsComponent(entity.getEntity(), handle["GraphicsComponent"]);

    if (handle["PhysicsComponent"])
        m_addPhysicsComponent(entity.getEntity(), handle["PhysicsComponent"]);

    if (handle["AnimationComponent"])
        m_addAnimationComponent(entity.getEntity(), handle["AnimationComponent"]);

    return entity;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
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

///////////////////////////////////////////////////////////////////////////////////////////////////
void EntityManagerWrapper::m_addPhysicsComponent(entityx::Entity entity, luabridge::LuaRef phandle)
{
    PhysicsComponent::Handle handle = entity.assign <PhysicsComponent> ();
    handle->configTable = phandle;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void EntityManagerWrapper::m_addAnimationComponent(entityx::Entity entity, luabridge::LuaRef ahandle)
{
    AnimationComponent::Handle handle        = entity.assign    <AnimationComponent> ();
    CustomPropertyComponent::Handle cphandle = entity.component <CustomPropertyComponent> ();
    std::string tableName                    = cphandle->property["tableName"];
    std::vector <std::string> keys           = m_animationGetAnimationsKeys(tableName);

    for (auto& animationName : keys)
    {
        LuaTableIterator iter(tableName + ".AnimationComponent." + animationName);
        thor::FrameAnimation frameAnimation;
        float animationTime = 1.0;

        std::tie (frameAnimation, animationTime) = m_animationAddFrames(iter.keys, tableName, animationName);
        handle->animator.addAnimation(animationName, frameAnimation, sf::seconds(animationTime));
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector <std::string> EntityManagerWrapper::m_animationGetAnimationsKeys(const std::string& tableName)
{
    std::vector <std::string> keys;
    LuaTableIterator iter(tableName + ".AnimationComponent");

    for (auto& key : iter.keys)
        keys.push_back (key);

    return keys;
}


////////////////////////////////////////////////////////////////////////////////////
std::tuple <thor::FrameAnimation, float> EntityManagerWrapper::m_animationAddFrames(
        const std::vector <std::string>& keys,
        const std::string& tableName,
        const std::string& animationName)
{
    thor::FrameAnimation frameAnimation;
    float animationTime = 1.0;
    sf::IntRect animationBoundingRect;

    for (auto& key : keys)
    {
        if (key == "time")
        {
            animationTime = m_animationGetDuration(tableName, animationName);
            continue;
        }

        for (int i = 1; i <= 4; i++)
        {
            std::stringstream varName;
            varName << "detail_frameVar" << i;

            std::stringstream command;
            command << tableName << "." << varName.str() << " = " << tableName << ".AnimationComponent."
                    << animationName << "[" << key << "][" << i << "]";

            global.scriptManager.doString(command.str());
            luabridge::LuaRef tempHandle = global.scriptManager.getGlobal(tableName);

            switch (i) {
                case 1:
                    animationBoundingRect.left = tempHandle[varName.str()];
                    break;

                case 2:
                    animationBoundingRect.top = tempHandle[varName.str()];
                    break;

                case 3:
                    animationBoundingRect.width = tempHandle[varName.str()];
                    break;

                case 4:
                    animationBoundingRect.height = tempHandle[varName.str()];
                    break;
            }

            global.scriptManager.doString(tableName + "." + varName.str() + " = nil");
        }

        if (animationBoundingRect.width == 0 || animationBoundingRect.height == 0)
            continue;

        std::cout << "Added frame to animation '" << animationName << "' (" << animationBoundingRect.left
                << ", " << animationBoundingRect.top << ", " << animationBoundingRect.width
                << ", " << animationBoundingRect.height << ")\n";

        frameAnimation.addFrame(1.0, animationBoundingRect);
    }

    return std::tie (frameAnimation, animationTime);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float EntityManagerWrapper::m_animationGetDuration(const std::string& tableName, const std::string& animationName)
{
    std::string varName = "detail_timeVar";

    std::stringstream command;
    command << tableName << "." << varName << " = " << tableName << ".AnimationComponent." << animationName << ".time";

    global.scriptManager.doString(command.str());
    luabridge::LuaRef tempHandle = global.scriptManager.getGlobal(tableName);
    float animationTime = tempHandle[varName];
    global.scriptManager.doString(tableName + varName + " = nil");

    return animationTime;
}