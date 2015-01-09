#include "GameDirector.hpp"

#ifndef LUABINDER_HPP
#define LUABINDER_HPP

#include "Application.hpp"

class GameDirector;

inline void import(const char* filename)
{
    global.scriptManager.doFile(filename);
}

class LuaBinder
{
public:
    void bind(GameDirector* gm);

private:
    void m_box2d();
        void m_b2transform();
        void m_b2body();
        void m_b2vec();
        void m_b2fixture();
        void m_b2world();

    void m_thor();
        void m_animation();

    void m_engineCore(GameDirector* gm);
        void m_gameDirector(GameDirector* gm);
        void m_scriptManager();
        void m_sceneManager();
        void m_fileSystem(FileSystem* fs);
        void m_tileMapSystem(TileMapSystem* tms);
        void m_renderSystem(RenderSystem* rs);
        void m_physicsSystem(PhysicsSystem* ps);
        void m_entityManager(entityx::EntityX* manager);
        void m_entity();
        void m_camera(Camera* cam);
        void m_resourceManager(ResourceManager* rm);
        void m_inputManager(InputManager* im);
        void m_utils();


    EntityManagerWrapper m_manager;
};

#endif