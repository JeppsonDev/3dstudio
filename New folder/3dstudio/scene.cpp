#include "scene.hpp"
#include "actor.hpp"
#include "texture2d.hpp"
#include "depthshader.hpp"

namespace Umu
{   
    Scene::Scene()
    {
        //Initilize member variables
        m_pMainShader = new Shader("vshader.glsl", "fshader.glsl");
        m_pDepthShader = new DepthShader("vdepthshader.glsl", "fdepthshader.glsl");

        m_pMainShader->setInt("u_Texture", 0);
        m_pMainShader->setInt("u_ShadowMap", 1);

        m_pCamera = new Camera();
        m_pLight = new Light(glm::vec3(-3.0f, 2.0f, 0.0f));

        //Load the teddy model
        std::vector<Mesh*> meshes = Mesh::load("models/cube_brick.obj");
        Model *model = new Model(meshes, new Texture2D("models/bricks.bmp"), m_pMainShader);
        Actor *obj = new Actor(model);
        addObject(obj);

        /*
        std::vector<Mesh*> floorMeshes = Mesh::load("models/cube.obj");
        Model *floorModel = new Model(floorMeshes, m_pMainShader);
        Object *floorObj = new Object(floorModel);
        floorObj->getTransform()->translate(glm::vec3(0.5f, 0.2f, 0.0f));
        addObject(floorObj);
        */

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

    bool t,r,s;

    //-----------------------------------------PUBLIC------------------------------------------//
    void Scene::render(Render3D *renderer)
    {
        //Update everything first
        handleFileOpen();
        m_pCamera->update();

        for(uint i = 0; i < m_objects.size(); i++)
        {
            m_objects[i]->update();
        }

        //First we render the depth map
        m_pDepthShader->start();
        glm::mat4 lightSpaceMatrix = m_pCamera->useDirectionalLightProjection(m_pLight->getPosition());
        m_pDepthShader->setMat4("u_LightSpaceMatrix", lightSpaceMatrix);
        
        renderer->bindDepthMap();
        renderer->useShader(m_pDepthShader);
        
        for(uint i = 0; i < m_objects.size(); i++)
        {   
            renderer->renderObject(m_objects[i], true);
        }

        renderer->unbindDepthMap();
        m_pDepthShader->stop();

        //Then we render the scene normally
        m_pMainShader->start();
        m_pMainShader->setMat4("u_LightSpaceMatrix", lightSpaceMatrix);

        renderer->useShader(m_pMainShader);

        for(uint i = 0; i < m_objects.size(); i++)
        {
            renderer->renderObject(m_objects[i], true);
        }
        
        m_pMainShader->stop();
    }

    void Scene::addObject(Object *obj)
    {
        m_objects.push_back(obj);
        
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
            Model *model = new Model(meshes, new Texture2D(), m_pMainShader);
            Object *obj = new Object(model);
            addObject(obj);
        }
    }
    
    void Scene::onObjectOpen(OpenObjectEvent event)
    {
        std::vector<Mesh*> meshes = Mesh::load(event.filepath);
        std::cout << meshes.size() << std::endl;
        Model *model = new Model(meshes, new Texture2D(), m_pMainShader);
        Actor *obj = new Actor(model);
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