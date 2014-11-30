#ifndef BOX2DREG_HPP
#define BOX2DREG_HPP

namespace bind2lua
{
    inline void box2d()
    {
        global.scriptManager.globalNamespace()
                .beginNamespace("vgb")
                .beginClass <b2Body> ("b2Body")
                .addFunction("applyForceToCenter", &b2Body::ApplyForceToCenter)
                .endClass()

                .beginClass <b2Vec2> ("b2Vec2")
                .addConstructor <void (*) (float32, float32)> ()
                .addData("x", &b2Vec2::x)
                .addData("y", &b2Vec2::y)
                .endClass()
                .endNamespace();
    }
}

#endif