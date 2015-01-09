#include "LuaBinder.hpp"

///////////////////////////////////////
void LuaBinder::bind(GameDirector* gm)
{
    // First of all bind independent modules
    m_box2d();
    m_thor();
    // Bind the main engine functions
    m_engineCore(gm);
}


/////////////////////////
void LuaBinder::m_box2d()
{
    m_b2vec();
    m_b2transform();
    m_b2body();
    m_b2fixture();
    m_b2world();
}


///////////////////////////////
void LuaBinder::m_b2transform()
{
    global.scriptManager.globalNamespace()
            .beginNamespace("vgb")
                .beginClass <b2Transform> ("b2Transform")
                .endClass()
            .endNamespace();
}


//////////////////////////
void LuaBinder::m_b2vec()
{
    global.scriptManager.globalNamespace()
            .beginNamespace("vgb")
                .beginClass <b2Vec2> ("b2Vec2")
                    .addConstructor <void (*) (float32, float32)> ()
                    .addData("x", &b2Vec2::x)
                    .addData("y", &b2Vec2::y)
                .endClass()
            .endNamespace();
}


//////////////////////////
void LuaBinder::m_b2body()
{
    global.scriptManager.globalNamespace()
            .beginNamespace("vgb")
                .beginClass <b2Body> ("b2Body")
                    .addFunction("applyForceToCenter", &b2Body::ApplyForceToCenter)
                    .addFunction("applyLinearImpulse", &b2Body::ApplyLinearImpulse)
                    .addFunction("setTransform", &b2Body::SetTransform)

                    .addProperty("position", &b2Body::GetPosition)
                    .addProperty("linearVelocity", &b2Body::GetLinearVelocity, &b2Body::SetLinearVelocity)
                    .addProperty("mass", &b2Body::GetMass)
                    .addProperty("fixedRotation", &b2Body::IsFixedRotation, &b2Body::SetFixedRotation)
                    .addProperty("worldCenter", &b2Body::GetWorldCenter)
                .endClass()
            .endNamespace();
}


/////////////////////////////
void LuaBinder::m_b2fixture()
{
    global.scriptManager.globalNamespace()
            .beginNamespace("vgb")
                .beginClass <b2Fixture> ("b2Fixture")
                    .addProperty("body", &b2Fixture::GetBody)
                .endClass()
            .endNamespace();
}


///////////////////////////
void LuaBinder::m_b2world()
{
    global.scriptManager.globalNamespace()
            .beginNamespace("vgb")
                .beginClass <b2World> ("b2World")
                .endClass()
            .endNamespace();
}

//////////////////////////////////////////////
void LuaBinder::m_engineCore(GameDirector* gm)
{
    /*
    ** concept: vgb.app.resourceManager:loadTileMap(...)
    *           vgb.App.FileSystem:LoadSomething(...)
    *           vgb.App.ResourceManager:....
     */
    m_utils();
    m_entity();
    m_sceneManager();
    m_gameDirector(gm);
    m_scriptManager();
    m_fileSystem(&gm->getApp().fileSystem());
    m_tileMapSystem(gm->getApp().systems.system <TileMapSystem> ().get());
    m_renderSystem (gm->getApp().systems.system <RenderSystem>  ().get());
    m_physicsSystem(gm->getApp().systems.system <PhysicsSystem> ().get());
    m_entityManager(&gm->getApp());
    m_resourceManager(&gm->getApp().resourceManager());
    m_camera(&gm->getApp().camera());
    m_inputManager(&gm->getApp().input());
}


//////////////////////////
void LuaBinder::m_entity()
{
    global.scriptManager.globalNamespace()
            .beginNamespace("vgb")
                .beginClass <EntityWrapper> ("EntityWrapper")
                    .addProperty("body",        &EntityWrapper::getBody)
                    .addFunction("setProperty", &EntityWrapper::setProperty)
                    .addFunction("getProperty", &EntityWrapper::getProperty)
                    .addProperty("animation",   &EntityWrapper::getAnimator)
                .endClass()
            .endNamespace();
}


////////////////////////////////
void LuaBinder::m_sceneManager()
{
    global.scriptManager.globalNamespace()
            .beginNamespace("vgb")
                .beginClass <SceneManager> ("SceneManager")
                    .addFunction("addScene",    &SceneManager::addScene)
                    .addFunction("changeScene", &SceneManager::changeScene)
                    .addFunction("removeScene", &SceneManager::removeScene)
                .endClass()
            .endNamespace();
}


////////////////////////////////////////////////
void LuaBinder::m_gameDirector(GameDirector* gm)
{
    global.scriptManager.globalNamespace()
            .beginNamespace("vgb")
                .beginClass <GameDirector> ("GameDirector")
                    .addFunction("scenes", &GameDirector::scenes)
                .endClass()
            .endNamespace();

    global.vgbLuaNamespace["director"] = gm;
}


//////////////////////////////////////////////////
void LuaBinder::m_scriptManager()
{
    global.scriptManager.globalNamespace()
            .beginNamespace("vgb")
                .addFunction("import", &import)
            .endNamespace();
}


////////////////////////////////////////////
void LuaBinder::m_fileSystem(FileSystem* fs)
{
    global.scriptManager.globalNamespace()
            .beginNamespace("vgb")
                .beginClass <FileSystem> ("FileSystem")
                    .addFunction("addSearchPath", &FileSystem::addSearchPath)
                .endClass()
            .endNamespace();

    global.vgbLuaNamespace["fileSystem"] = fs;
}


///////////////////////////////////////////////////
void LuaBinder::m_tileMapSystem(TileMapSystem* tms)
{
    global.scriptManager.globalNamespace()
            .beginNamespace("vgb")
                .beginClass <TileMapSystem> ("TileMapSystem")
                    .addProperty("tileMap", &TileMapSystem::getTileMap, &TileMapSystem::setTileMap)
                .endClass()

                .beginClass <tmx::MapLoader> ("MapLoader")
                .endClass()
            .endNamespace();

    global.vgbLuaNamespace["tileMapSystem"] = tms;
}


////////////////////////////////////////////////
void LuaBinder::m_renderSystem(RenderSystem* rs)
{
    global.scriptManager.globalNamespace()
            .beginNamespace("vgb")
                .beginClass <RenderSystem> ("RenderSystem")
                    .addFunction("debugRender", &RenderSystem::debugRender)
                    .addFunction("showFPS", &RenderSystem::showFPS)
                .endClass()
            .endNamespace();

    global.vgbLuaNamespace["renderSystem"] = rs;
}


//////////////////////////////////////////////////
void LuaBinder::m_physicsSystem(PhysicsSystem* ps)
{
    global.scriptManager.globalNamespace()
            .beginNamespace("vgb")
                .beginClass <PhysicsSystem> ("PhysicsSystem")
                    .addProperty("world", &PhysicsSystem::getWorld, &PhysicsSystem::setWorld)
                    .addFunction("createWorld", &PhysicsSystem::createWorld)
                    .addFunction("addCollisionCallback", &PhysicsSystem::addCollisionCallback)
                .endClass()
            .endNamespace();

    global.vgbLuaNamespace["physicsSystem"] = ps;
}


////////////////////////////////////////////////////
void LuaBinder::m_entityManager(entityx::EntityX* em)
{
    global.scriptManager.globalNamespace()
            .beginNamespace("vgb")
                .beginClass <EntityManagerWrapper> ("EntityManagerWrapper")
                    .addFunction("getEntityByName", &EntityManagerWrapper::getEntityByName)
                    .addFunction("getEntityFromBody", &EntityManagerWrapper::getEntityFromBody)
                    .addFunction("createEntity", &EntityManagerWrapper::createEntity)
                    .addFunction("createEntityF", &EntityManagerWrapper::createEntityF)
                .endClass()
            .endNamespace();

    m_manager.setManager(em);
    EntityManagerWrapper* wr = &m_manager;
    global.vgbLuaNamespace["entityManager"] = wr;
}


//////////////////////////////////////////////////////
void LuaBinder::m_resourceManager(ResourceManager* rm)
{
    global.scriptManager.globalNamespace()
            .beginNamespace("vgb")
                .beginClass <ResourceManager> ("ResourceManager")
                    .addFunction("loadTileMap", &ResourceManager::loadTileMap)
                .endClass()
            .endNamespace();

    global.vgbLuaNamespace["resourceManager"] = rm;
}


/////////////////////////////////////
void LuaBinder::m_camera(Camera* cam)
{
    global.scriptManager.globalNamespace()
            .beginNamespace("vgb")
                .beginClass <Camera> ("Camera")
                    .addFunction("centerViewEntity", &Camera::centerViewEntity)
                    .addFunction("reset", &Camera::reset)
                .endClass()
            .endNamespace();

    global.vgbLuaNamespace["camera"] = cam;
}


///////////////////////////////////////////////
void LuaBinder::m_inputManager(InputManager* im)
{
    global.scriptManager.globalNamespace()
            .beginNamespace("vgb")
                .beginClass <InputManager> ("InputManager")
                    .addFunction("addEventCallback", &InputManager::addEventCallback)
                    .addFunction("removeEventCallback", &InputManager::removeEventCallback)
                .endClass()
            .endNamespace();

    global.vgbLuaNamespace["input"] = im;
}


/////////////////////////
void LuaBinder::m_utils()
{
    global.scriptManager.globalNamespace()
            .beginNamespace("vgb")
                .addFunction("toMetersCoord", (b2Vec2 (*) (float, float)) &si::meters)
                .addFunction("toPixelCoord", (float (*) (float)) &si::pixels)
                .addFunction("detail_addTableNameKey", &detail_addTableNameKey)
            .endNamespace();
}


////////////////////////
void LuaBinder::m_thor()
{
    m_animation();
}


//////////////////////////////
void LuaBinder::m_animation()
{
    global.scriptManager.globalNamespace()
            .beginNamespace("vgb")
                .beginClass <AnimationComponent::Animator> ("Animator")
                    .addFunction("play", (void (AnimationComponent::Animator::*) (const std::string&, bool)) &AnimationComponent::Animator::playAnimation)
                    .addFunction("stop", &AnimationComponent::Animator::stopAnimation)
                    .addFunction("getCurrent", &AnimationComponent::Animator::getPlayingAnimation)
                    .addFunction("isPlaying", &AnimationComponent::Animator::isPlayingAnimation)
                .endClass()
            .endNamespace();
}