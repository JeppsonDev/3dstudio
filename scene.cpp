#include "scene.hpp"

namespace Umu
{
    Scene::Scene()
    {
        //Initilize member variables
        m_pShaders[0] = new Shader("vshader.glsl", "fshader.glsl");
        m_pShaders[1] = new Shader("vgourad.glsl", "fgourad.glsl");
        m_pShaders[2] = new ToonShader("vtoon.glsl", "ftoon.glsl");
        m_pMainShader = m_pShaders[0];

        m_pSkyboxShader = new SkyboxShader("vskybox.glsl", "fskybox.glsl");
        m_pDepthShader = new DepthShader("vdepth.glsl", "fdepth.glsl");
        m_pOutlineShader = new Shader("vshader.glsl", "fshader.glsl");

        m_pCamera = new Camera();
        m_pLight = new Light();
        m_pSkybox = new Skybox();
        m_pShadowMap = new ShadowMap();

        //Load the teddy model
        std::vector<Mesh*> meshes = Mesh::load("models/teddy.obj");
        Model *model = new Model(meshes, new Texture2D("models/bricks.bmp"));
        Actor *obj = new Actor(m_objects.size(), model);
        addObject(obj);

        std::vector<Mesh*> floorMeshes = Mesh::loadPlane();
        Model *floorModel = new Model(floorMeshes, new Texture2D("models/bricks.bmp"));
        Object *floorObj = new Object(m_objects.size(), floorModel);
        floorObj->getTransform()->translate(glm::vec3(0.0f, -0.5f, 0.0f));
        floorObj->getTransform()->scale(glm::vec3(5.0f, 0.1f, 5.0f));
        addObject(floorObj);

        //Register events
        Gui::getOpenObjectObserver()->registerEvent(std::bind(&Scene::onObjectOpen, this, std::placeholders::_1));
        m_pCamera->getOnCameraUpdateObserver()->registerEvent(std::bind(&Scene::onCameraUpdate, this, std::placeholders::_1));
        Gui::getOnUpdateLightObserver()->registerEvent(std::bind(&Scene::onLightUpdate, this, std::placeholders::_1));
        Gui::getOnUpdateShaderEvent()->registerEvent(std::bind(&Scene::onShaderUpdate, this, std::placeholders::_1));
        Global::getOnUpdateWindowObserver()->registerEvent(std::bind(&Scene::onUpdateWindow, this, std::placeholders::_1));
        Gui::getOnSelectObjectObserver()->registerEvent(std::bind(&Scene::onSelectObjectEvent, this, std::placeholders::_1));
    }

    Scene::~Scene()
    {
        std::cout << "Freeing scene" << std::endl;
        
        for(unsigned int i = 0; i < m_objects.size(); i++)
        {
            delete m_objects[i];
        }

        m_objects.clear();
        
        delete m_pCamera;
        delete m_pLight;
        delete m_pSkybox;
        delete m_pDepthShader;
        delete m_pShadowMap;
        delete m_pSkyboxShader;
        delete m_pShaders[0];
        delete m_pShaders[1];
        delete m_pShaders[2];
        delete m_pOutlineShader;
    }
    
    //-----------------------------------------PUBLIC------------------------------------------//   
    void Scene::render(Render3D *renderer)
    {
        //Update
        update();

        //Render depth map
        glCullFace(GL_FRONT);
        glm::mat4 lightSpaceMatrix = m_pShadowMap->calculateLightSpace(m_pLight->getPosition());

        m_pDepthShader->start();
        m_pDepthShader->setMat4("u_LightSpaceMatrix", lightSpaceMatrix);
        m_pDepthShader->stop();

        renderShadowMap(renderer);
        glCullFace(GL_BACK);

        //Scuffed solution for rendering outlines
        if(m_pMainShader == m_pShaders[2])
        {
            glEnable(GL_CULL_FACE);
            glCullFace(GL_FRONT);
            glm::mat4 copies[m_objects.size()];
            for(uint i = 0; i < m_objects.size(); i++)
            {
                copies[i] = m_objects[i]->getTransform()->getMatrix();
                if(m_objects[i]->isEnabled())
                {
                    float biggestScale = 1.0;
                    for(int j = 0; j < m_objects[i]->getModel()->getMeshNum(); j++)
                    {
                        float scale = m_objects[i]->getModel()->getMesh(j)->getMaterial(0)->outlineThickness;
                        if(scale > biggestScale)
                        {
                            biggestScale = scale;    
                        }
                    }
                    m_objects[i]->getTransform()->scale(glm::vec3(biggestScale, biggestScale, biggestScale));
                }
            }
            renderScene(renderer, m_pOutlineShader, true);
            for(uint i = 0; i < m_objects.size(); i++)
            {
                m_objects[i]->getTransform()->setMatrix(copies[i]);
            }
            glCullFace(GL_BACK);
            glDisable(GL_CULL_FACE);
        }

        //Render scene
        m_pMainShader->start();
        m_pMainShader->setMat4("u_LightSpaceMatrix", lightSpaceMatrix);
        m_pMainShader->stop();
        renderScene(renderer, m_pMainShader);
        
        //Render skybox last
        m_pSkybox->render(m_pCamera, m_pSkyboxShader);
    }

    void Scene::addObject(Object *obj)
    {
        m_objects.push_back(obj);

        std::cout << "added new object. Object count: " << m_objects.size() << std::endl;

        Gui::addObject(obj->getId());
    }

    //-----------------------------------------PRIVATE------------------------------------------//
    void Scene::update()
    {
        handleFileOpen();
        m_pCamera->update();

        for(uint i = 0; i < m_objects.size(); i++)
        {
            m_objects[i]->update();
        }
    }

    void Scene::renderScene(Render3D *renderer, Shader *shader, bool onlyRenderEnabledObjects)
    {
        for(uint i = 0; i < m_objects.size(); i++)
        {
            if(onlyRenderEnabledObjects)
            {
                if(!m_objects[i]->isEnabled())
                {
                    continue;
                }
            }
            renderer->renderObject(m_objects[i], shader, m_pShadowMap);
        }
    }

    void Scene::renderShadowMap(Render3D *renderer)
    {
        m_pShadowMap->prepare();
        renderScene(renderer, m_pDepthShader);
        m_pShadowMap->unprepare();
    }
    
    void Scene::handleFileOpen()
    {
        if(OpenGLInput::isKeyPressed("o"))
        {
            std::cout << "Insert a relative path for new model: ";
            std::string newModelPath;
            std::getline(std::cin, newModelPath);
            
            std::vector<Mesh*> meshes = Mesh::load(newModelPath);
            Model *model = new Model(meshes);
            Actor *obj = new Actor(m_objects.size(), model);
            addObject(obj);
        }
    }
    
    void Scene::onObjectOpen(OpenObjectEvent event)
    {
        std::vector<Mesh*> meshes = Mesh::load(event.filepath);
        Model *model = new Model(meshes);
        Actor *obj = new Actor(m_objects.size(), model);
        addObject(obj);
    }

    void Scene::onCameraUpdate(OnCameraUpdateEvent event)
    {
        m_pMainShader->start();
        m_pMainShader->setVec3("u_CameraPosition", event.position);
        m_pMainShader->setMat4("u_View", event.viewMatrix);
        m_pMainShader->setMat4("u_Projection", event.projectionMatrix);
        m_pMainShader->stop();

        m_pOutlineShader->start();
        m_pOutlineShader->setVec3("u_CameraPosition", event.position);
        m_pOutlineShader->setMat4("u_View", event.viewMatrix);
        m_pOutlineShader->setMat4("u_Projection", event.projectionMatrix);
        m_pOutlineShader->stop();
    }

    void Scene::onLightUpdate(OnUpdateLightEvent event)
    {
        m_pLight->setPosition(glm::vec3(event.position[0], event.position[1], event.position[2]));
        m_pLight->setAmbientLight(glm::vec3(event.ambientColor[0], event.ambientColor[1], event.ambientColor[2]));
        m_pLight->setLightIntensity(glm::vec3(event.lightColor[0], event.lightColor[1], event.lightColor[2]));
        
        m_pMainShader->start();
        m_pMainShader->setVec3("u_LightPosition", m_pLight->getPosition());
        m_pMainShader->setVec3("u_AmbientLight", m_pLight->getAmbientLight());
        m_pMainShader->setVec3("u_LightIntensity", m_pLight->getLightIntensity());
        m_pMainShader->stop();
    }

    void Scene::onShaderUpdate(OnUpdateShaderEvent event)
    {
        m_pMainShader = m_pShaders[event.type];
    }

    void Scene::onUpdateWindow(OnUpdateWindowEvent event)
    {
        m_pCamera->updateProjection();
    }

    void Scene::onSelectObjectEvent(OnSelectObjectEvent event)
    {
        for(uint i = 0; i < m_objects.size(); i++)
        {
            if(m_objects[i]->getId() == event.objectId)
            {
                m_objects[i]->setEnabled(event.flag);
            }
        }
    }
}
