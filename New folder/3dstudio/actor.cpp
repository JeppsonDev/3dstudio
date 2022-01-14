#include "actor.hpp"
#include "openglinput.hpp"

namespace Umu
{
    Actor::Actor(Model *model) : Object(model)
    {

    }

    void Actor::update()
    {
        Object::update();

        if(OpenGLInput::isKeyPressed("up"))
        {
            if(t)
                getTransform()->translate(vec3(0,.1f,0));
            else if(r)
                getTransform()->rotate(vec3(1.0f,0.0f,0.0f), 0.174532925f);
            else if(s)
                getTransform()->scale(vec3(1.0f, 1.1f, 1.0f));
        }

        if(OpenGLInput::isKeyPressed("down"))
        {
            if(t)
                getTransform()->translate(vec3(0,-.1f,0));
            else if(r)
                getTransform()->rotate(vec3(1.0f,0.0f,0), -0.174532925f);
            else if(s)
                getTransform()->scale(vec3(1.0f, 0.9f, 1.0f));
        }

        if(OpenGLInput::isKeyPressed("right"))
        {
            if(t)
                getTransform()->translate(vec3(.1f,0,0));
            else if(r)
                getTransform()->rotate(vec3(0.0f,1.0f,0.0f), -0.174532925f);
            else if(s)
                getTransform()->scale(vec3(1.1f, 1.0f, 1.0f));
        }

        if(OpenGLInput::isKeyPressed("left"))
        {
            if(t)
                getTransform()->translate(vec3(-.1f,0,0));
            else if(r)
                getTransform()->rotate(vec3(0.05f,1.0f,0.0f), 0.174532925f);
            else if(s)
                getTransform()->scale(vec3(0.9f, 1.0f, 1.0f));
        }

        if(OpenGLInput::isKeyPressed("r"))
        {
            r = true;
            t = false;
            s = false;
        }

        if(OpenGLInput::isKeyPressed("t"))
        {
            r = false;
            t = true;
            s = false;
        }

        if(OpenGLInput::isKeyPressed("s"))
        {
            r = false;
            t = false;
            s = true;
        }
    }
}