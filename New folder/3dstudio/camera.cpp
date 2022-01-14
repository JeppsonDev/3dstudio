#include "camera.hpp"

namespace Umu
{
    static bool first = true;

    Camera::Camera()
    {
        m_pOnCameraUpdateObserver = new Observer<OnCameraUpdateEvent>();

        glm::vec3 lookTowards = glm::normalize(m_position - m_referencePosition);

        //Camera up & right
        m_right = glm::normalize(glm::cross(UP, lookTowards));
        m_up = glm::cross(lookTowards, m_right);
        m_front = glm::vec3(0.0f, 0.0f, -1.0f);

        m_viewMatrix = glm::lookAt(
            m_position,
            m_referencePosition,
            UP
        );

        usePerspectiveProjection();

        //m_projectionMatrix = glm::perspective(glm::radians(45.0f), 960.0f/540.0f, 0.1f, 100.0f);

        OpenGLInput::getMouseInputObserver()->registerEvent(std::bind(&Camera::onMouseUpdate, this, std::placeholders::_1));
        Gui::getUpdatePerspectiveObserver()->registerEvent(std::bind(&Camera::onPerspectiveProjectionUpdate, this, std::placeholders::_1));
        Gui::getUpdateOrthographicObserver()->registerEvent(std::bind(&Camera::onOrthographicUpdate, this, std::placeholders::_1));
    }

    Camera::~Camera()
    {
        delete m_pOnCameraUpdateObserver;
    }

    //-----------------------------------------PUBLIC------------------------------------------//
    void Camera::update()
    {
        float speed = 0.05f;
        if(OpenGLInput::isKeyPressed("w"))
        {
            m_position += speed * m_front;
        }
        if(OpenGLInput::isKeyPressed("s"))
        {
            m_position -= speed * m_front;
        }
        if(OpenGLInput::isKeyPressed("a"))
        {
            m_position -= speed * m_right;
        }
        if(OpenGLInput::isKeyPressed("d"))
        {
            m_position += speed * m_right;
        }
        if(OpenGLInput::isKeyPressed("q"))
        {
            m_position += speed * m_up;
        }
        if(OpenGLInput::isKeyPressed("e"))
        {
            m_position -= speed * m_up;   
        }
        
        m_updateViewMatrix = (m_position != m_oldPosition) || m_updateViewMatrix;

        if(m_updateViewMatrix || first) //just makse sure so we update on the first frame...
        {
            m_viewMatrix = glm::lookAt(m_position, m_position + m_front, m_up);
            m_oldPosition = m_position;
            m_pOnCameraUpdateObserver->invokeEvents({m_viewMatrix, m_projectionMatrix});
        }

        //Skip the first frame for the input
        first = OpenGLInput::isKeyPressed("shift");
    }

    void Camera::usePerspectiveProjection()
    {
        //TODO: Don't hardcode screen w&h
        //FIXME: don't hardcode neraplane
        m_projectionMatrix = glm::perspective(glm::radians(m_fov), 960.0f/540.0f, 0.1f, m_farPlane);
    }

    void Camera::useOrthographicProjection()
    {
        //TODO: Don't hardcode screen w&h
        float aspect = 960.0f/540.0f;
        float bottom = -m_top;
        float right = m_top * aspect;
        float left = -right;

        //FIXME: don't hardcode neraplane
        m_projectionMatrix = glm::ortho(left, right, bottom, m_top, 0.1f, m_farPlane);
    
        glm::mat4 H = glm::identity<glm::mat4>();

        H[2][0] = m_oblscale * cos(m_oblrad);
        H[2][1] = m_oblscale * sin(m_oblrad);

        m_projectionMatrix *= H;

    }

    glm::mat4 Camera::useDirectionalLightProjection(glm::vec3 lightPosition)
    {
        //FIXME: don't hardcode neraplane
        glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, -10.0f, 20.0f);

        //Look at center on screen from light position
        glm::mat4 lightView = glm::lookAt(lightPosition, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); 

        glm::mat4 lightSpaceMatrix = lightProjection * lightView;
        
        return lightSpaceMatrix;
    }
    
    glm::mat4 Camera::getViewMatrix()
    {
        return m_viewMatrix;
    }

    glm::mat4 Camera::getProjectionMatrix()
    {
        return m_projectionMatrix;
    }

    Observer<OnCameraUpdateEvent> *Camera::getOnCameraUpdateObserver()
    {
        return m_pOnCameraUpdateObserver;
    }

    //-----------------------------------------PRIVATE------------------------------------------//
    void Camera::onPerspectiveProjectionUpdate(UpdatePerspectiveEvent event)
    {
        m_fov = event.fov;
        m_farPlane = event.farplane;

        usePerspectiveProjection();

        m_pOnCameraUpdateObserver->invokeEvents({m_viewMatrix, m_projectionMatrix});
    }

    void Camera::onOrthographicUpdate(UpdateOrthographicEvent event)
    {
        m_top = event.top;
        m_farPlane = event.farplane;
        m_oblrad = event.obliqueanglerad;
        m_oblscale = event.obliquescale;

        useOrthographicProjection();

        m_pOnCameraUpdateObserver->invokeEvents({m_viewMatrix, m_projectionMatrix});
    }

    void Camera::onMouseUpdate(MouseInputEvent inputEvent)
    {
        if(!OpenGLInput::isKeyPressed("shift"))
        {
            return;
        }

        //Skip the first frame
        if(first)
        {
            first = false;
            return;
        }

        float xoffset = -inputEvent.xMouseDelta;
        float yoffset = inputEvent.yMouseDelta;

        const float sens = 0.1f;
        xoffset *= sens;
        yoffset *= sens;

        m_yaw += xoffset;
        m_pitch += yoffset;

        if(m_pitch > 89.0f)
            m_pitch =  89.0f;
        if(m_pitch < -89.0f)
            m_pitch = -89.0f;

        glm::vec3 direction;
        direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        direction.y = sin(glm::radians(m_pitch));
        direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        
        m_front = glm::normalize(direction);
        m_right = glm::normalize(glm::cross(m_front, UP));
        m_up = glm::normalize(glm::cross(m_right, m_front));  
        m_updateViewMatrix = true;
    }
}