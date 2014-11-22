#ifndef BASICSYSTEM_HPP
#define BASICSYSTEM_HPP

#include <entityx/entityx.h>

class BasicSystem
{
public:
    BasicSystem() : m_entityManager(nullptr) {}

    void setEntityManager(entityx::EntityX* ent)
    {
        m_entityManager = ent;
    }

protected:
    entityx::EntityX* m_entityManager;
};

#endif