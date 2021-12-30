#include "scene.hpp"

namespace Umu
{
    Scene::Scene()
    {
        //Initilize member variables
        m_pMainShader = new Shader("vshader.glsl", "fshader.glsl");
        m_pCamera = new Camera();
        m_pLight = new Light(glm::vec3(-3.0f, 2.0f, 0.0f));

        //Load the teddy model
        std::vector<Mesh*> meshes = Mesh::load("models/cube_brick.obj");
        Model *model = new Model(meshes, m_pMainShader);
        Object *obj = new Object(model);
        addObject(obj);

        //Register events
        Gui::getOpenObjectObserver()->registerEvent(std::bind(&Scene::onObjectOpen, this, std::placeholders::_1));
        m_pCamera->getOnCameraUpdateObserver()->registerEvent(std::bind(&Scene::onCameraUpdate, this, std::placeholders::_1));
        Gui::getOnUpdateLightObserver()->registerEvent(std::bind(&Scene::onLightUpdate, this, std::placeholders::_1));
    }

    Scene::~Scene()
    {
        for(uint i = 0; i < m_objects.size(); i++)
        {
            delete m_objects[i];
        }

        m_objects.clear();

        delete m_pMainShader;
        delete m_pCamera;
        delete m_pLight;
    }

    //-----------------------------------------PUBLIC------------------------------------------//
    void Scene::render(Render3D *renderer)
    {
        handleFileOpen();

        m_pCamera->update();

        for(uint i = 0; i < m_objects.size(); i++)
        {
            renderer->renderObject(m_objects[i]);
        }
    }

    void Scene::addObject(Object *obj)
    {
        //TODO: Preparation for multiple objects
        if(m_objects.size() > 0)
        {
            delete m_objects[0];
            m_objects[0] = obj;
        }
        else
        {
            m_objects.push_back(obj);
        }
        
        std::cout << "added new object. Object count: " << m_objects.size() << std::endl;
    }

    //-----------------------------------------PRIVATE------------------------------------------//
    void Scene::handleFileOpen()
    {
        if(OpenGLInput::isKeyPressed("o"))
        {
            std::cout << "Insert a relative path for new model: ";
            std::string newModelPath;
            std::getline(std::cin, newModelPath);
            
            std::vector<Mesh*> meshes = Mesh::load(newModelPath);
            Model *model = new Model(meshes, m_pMainShader);
            Object *obj = new Object(model);
            addObject(obj);
        }
    }
    
    void Scene::onObjectOpen(OpenObjectEvent event)
    {
        std::vector<Mesh*> meshes = Mesh::load(event.filepath);
        std::cout << meshes.size() << std::endl;
        Model *model = new Model(meshes, m_pMainShader);
        Object *obj = new Object(model);
        addObject(obj);
    }

    void Scene::onCameraUpdate(OnCameraUpdateEvent event)
    {
        m_pMainShader->start();
        m_pMainShader->setMat4("u_View", event.viewMatrix);
        m_pMainShader->setMat4("u_Projection", event.projectionMatrix);
        m_pMainShader->stop();
    }

    void Scene::onLightUpdate(OnUpdateLightEvent event)
    {
        //TODO: Should we update the light object or not???
        m_pLight->setPosition(glm::vec3(event.position[0], event.position[1], event.position[2]));
        
        m_pMainShader->start();
        m_pMainShader->setVec3("u_LightPosition", m_pLight->getPosition());
        m_pMainShader->setVec3("u_AmbientLight", glm::vec3(event.ambientColor[0], event.ambientColor[1], event.ambientColor[2]));
        m_pMainShader->setVec3("u_LightIntensity", glm::vec3(event.lightColor[0], event.lightColor[1], event.lightColor[2]));
        m_pMainShader->setVec3("u_AmbientConstant", glm::vec3(event.materialAmbient[0],  event.materialAmbient[1], event.materialAmbient[2]));
        m_pMainShader->setVec3("u_DiffuseConstant", glm::vec3(event.materialDiffuse[0], event.materialDiffuse[1], event.materialDiffuse[2]));
        m_pMainShader->setVec3("u_SpecularConstant", glm::vec3(event.materialSpecular[0], event.materialSpecular[1], event.materialSpecular[2]));
        m_pMainShader->setFloat("u_Shininess", event.materialShininess);
        m_pMainShader->stop();
    }
}