#include "gui.hpp"

namespace Umu
{
    Observer<UpdatePerspectiveEvent> *Gui::m_updatePerspectiveObserver = new Observer<UpdatePerspectiveEvent>();
    Observer<UpdateOrthographicEvent> *Gui::m_updateOrthographicObserver = new Observer<UpdateOrthographicEvent>();
    Observer<OpenObjectEvent> *Gui::m_openObjectObserver = new Observer<OpenObjectEvent>();
    Observer<OnUpdateLightEvent> *Gui::m_onUpdateLightObserver = new Observer<OnUpdateLightEvent>();
    Observer<OnTextureToggle> *Gui::m_onTextureToggle = new Observer<OnTextureToggle>();
    Observer<OnTextureOpen> *Gui::m_onTextureOpen = new Observer<OnTextureOpen>();
    Observer<OnUpdateMaterialEvent> *Gui::m_onUpdateMaterialEvent = new Observer<OnUpdateMaterialEvent>();
    Observer<OnUpdateShaderEvent> *Gui::m_onUpdateShaderEvent = new Observer<OnUpdateShaderEvent>();
    Observer<OnSelectObjectEvent> *Gui::m_onSelectObjectObserver = new Observer<OnSelectObjectEvent>();
    std::vector<int> Gui::m_objects;

    static UpdatePerspectiveEvent updatePerspectiveEvent;
    static OpenObjectEvent openObjectEvent;
    static UpdateOrthographicEvent updateOrthographicEvent;
    static OnUpdateLightEvent updateLightEvent;
    static OnTextureToggle textureToggleEvent;
    static OnTextureOpen textureOpenEvent;
    static OnUpdateMaterialEvent onUpdateMaterialEvent;
    static OnUpdateShaderEvent onUpdateShaderEvent;
    static OnSelectObjectEvent onSelectObjectEvent;

    static bool first = true;
    static std::vector<bool> checkboxes;

    //-----------------------------------------PUBLIC------------------------------------------//
    void Gui::render()
    {
        
        IM_ASSERT(ImGui::GetCurrentContext() != NULL && "Missing dear imgui context.");

        static ImGuiSliderFlags flags = ImGuiSliderFlags_AlwaysClamp;

        ImGui::Begin("3D Studio"); 

        renderObjFileCategory();
        renderProjectionCategory(flags);
        renderLightCategory(flags);
        renderChooseShaderCategory();
        renderObjectsInSceneCategory();

        if(first)
        {
            Gui::getOnUpdateLightObserver()->invokeEvents(updateLightEvent);
            Gui::getUpdatePerspectiveObserver()->invokeEvents(updatePerspectiveEvent);
            Gui::getOnUpdateMaterialObserver()->invokeEvents(onUpdateMaterialEvent);
            first = false;
        }

        ImGui::End();
    }

    void Gui::destroy()
    {
        delete m_updatePerspectiveObserver;
        delete m_updateOrthographicObserver;
        delete m_openObjectObserver;
        delete m_onUpdateLightObserver;
        delete m_onTextureToggle;
        delete m_onTextureOpen;
        delete m_onUpdateMaterialEvent;
        delete m_onUpdateShaderEvent;
        delete m_onSelectObjectObserver;
    }
    
    Observer<UpdatePerspectiveEvent> *Gui::getUpdatePerspectiveObserver()
    {
        return m_updatePerspectiveObserver;
    }
    
    Observer<UpdateOrthographicEvent> *Gui::getUpdateOrthographicObserver()
    {
        return m_updateOrthographicObserver;
    }

    Observer<OpenObjectEvent> *Gui::getOpenObjectObserver()
    {
        return m_openObjectObserver;
    }

    Observer<OnUpdateLightEvent> *Gui::getOnUpdateLightObserver()
    {
        return m_onUpdateLightObserver;
    }

    Observer<OnTextureToggle> *Gui::getOnTextureToggle()
    {
        return m_onTextureToggle;
    }

    Observer<OnTextureOpen> *Gui::getOnTextureOpen()
    {
        return m_onTextureOpen;
    }

    Observer<OnUpdateMaterialEvent> *Gui::getOnUpdateMaterialObserver()
    {
        return m_onUpdateMaterialEvent;
    }

    Observer<OnUpdateShaderEvent> *Gui::getOnUpdateShaderEvent()
    {
        return m_onUpdateShaderEvent;
    }

    Observer<OnSelectObjectEvent> *Gui::getOnSelectObjectObserver()
    {
        return m_onSelectObjectObserver;
    }

    //-----------------------------------------PRIVATE------------------------------------------//  
    void Gui::renderObjFileCategory()
    {
        std::string objFileName;
        std::string objFilePath;

        if (ImGui::CollapsingHeader("OBJ File")) 
        {
            ImGui::Text("OBJ file: %s", objFileName.c_str());
            if (ImGui::Button("Open File"))
            {
                igfd::ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".obj", ".");
            }
            
            if (igfd::ImGuiFileDialog::Instance()->FileDialog("ChooseFileDlgKey")) 
            {
                if (igfd::ImGuiFileDialog::Instance()->IsOk == true) 
                {
                    objFileName = igfd::ImGuiFileDialog::Instance()->GetCurrentFileName();
                    objFilePath = igfd::ImGuiFileDialog::Instance()->GetCurrentPath();

                    //Invoke event
                    openObjectEvent.filepath = objFilePath + "/" + objFileName; 
                    Gui::getOpenObjectObserver()->invokeEvents(openObjectEvent);
                    Gui::getOnUpdateMaterialObserver()->invokeEvents(onUpdateMaterialEvent);

                    std::cout << "OBJ file: " << objFileName << std::endl << "Path: " << objFilePath << "/" << objFileName << std::endl;
                }
                // close
                igfd::ImGuiFileDialog::Instance()->CloseDialog("ChooseFileDlgKey");
            }
        }  
    }

    void Gui::renderProjectionCategory(ImGuiSliderFlags flags)
    {
        if (ImGui::CollapsingHeader("Projection")) 
        {
            const char* items[] = {"Perspective", "Parallel" };
            static int proj_current_idx = 0;

            if (ImGui::Combo("projektion", &proj_current_idx, items, IM_ARRAYSIZE(items), IM_ARRAYSIZE(items)));

            if (proj_current_idx == 0) 
            {
                ImGui::SliderFloat("Field of view",&updatePerspectiveEvent.fov, 20.0f, 160.0f, "%1.0f", flags);
                ImGui::SliderFloat("Far",&updatePerspectiveEvent.farplane, 1.0f, 1000.0f, "%1.0f", flags);

                Gui::getUpdatePerspectiveObserver()->invokeEvents(updatePerspectiveEvent);
            }
            
            if (proj_current_idx == 1) 
            {
                ImGui::SliderFloat("Top",&updateOrthographicEvent.top, 1.0f, 100.0f, "%.1f", flags);
                ImGui::SliderFloat("Far",&updateOrthographicEvent.farplane, 1.0f, 1000.0f, "%1.0f", flags);
                ImGui::SliderFloat("Oblique scale",&updateOrthographicEvent.obliquescale, 0.0f, 1.0f, "%.1f", flags);
                ImGui::SliderAngle("Oblique angle",&updateOrthographicEvent.obliqueanglerad, 15, 75, "%1.0f", flags);
                
                Gui::getUpdateOrthographicObserver()->invokeEvents(updateOrthographicEvent);
            }
        }
    }
    
    void Gui::renderLightCategory(ImGuiSliderFlags flags)
    {
        static std::string textureFileName;
        static std::string textureFilePath;

        if (ImGui::CollapsingHeader("Light")) 
        {
            ImGui::Text("Light source position");
            ImGui::PushItemWidth(100);
            ImGui::InputFloat("x", &updateLightEvent.position[0], 0.5f, 1.0f, "%1.1f"); ImGui::SameLine();
            ImGui::InputFloat("y", &updateLightEvent.position[1], 0.5f, 1.0f, "%1.1f"); ImGui::SameLine();
            ImGui::InputFloat("z", &updateLightEvent.position[2], 0.5f, 1.0f, "%1.1f");
            ImGui::PopItemWidth();

            ImGui::Text("Light source intensity:");
            ImGui::ColorEdit3("Light", updateLightEvent.lightColor);
            
            ImGui::Text("Ambient light intensity:");
            ImGui::ColorEdit3("Ambient", updateLightEvent.ambientColor);

            Gui::getOnUpdateLightObserver()->invokeEvents(updateLightEvent);
        }
        
        if (ImGui::CollapsingHeader("Object Material")) 
        {
            bool updated1 = false;
            bool updated2 = false;
            bool updated3 = false;

            ImGui::Text("Ambient coefficient:");
            updated1 = ImGui::ColorEdit3("Ambient color", onUpdateMaterialEvent.materialAmbient);
            
            ImGui::Text("Diffuse coefficient:");
            updated2 = ImGui::ColorEdit3("Diffuse color", onUpdateMaterialEvent.materialDiffuse);
            
            ImGui::Text("Specular coefficient:");
            updated3 = ImGui::ColorEdit3("Specular color", onUpdateMaterialEvent.materialSpecular);

            bool updated5 = ImGui::SliderFloat("Shininess", &onUpdateMaterialEvent.materialShininess, 1.0f, 1000.0f, "%1.0f", flags);
            
            bool updated4 = ImGui::SliderFloat("Outline Thickness", &onUpdateMaterialEvent.outlineThickness, 0.00f, 5.0f, "%0.01f", flags);

            bool update = updated1 || updated2 || updated3 || updated4 || updated5;

            if(update)
            {
                Gui::getOnUpdateMaterialObserver()->invokeEvents(onUpdateMaterialEvent);   
            }
        }
        
        if (ImGui::CollapsingHeader("Object Texture")) 
        {
            ImGui::Checkbox("Show texture", &textureToggleEvent.textureShow);
            ImGui::Text("Texture file: %s", textureFileName.c_str());
            if (ImGui::Button("Open Texture File"))
                igfd::ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Select Texture File",
                                                            ".bmp,.dds,.hdr,.pic,.png,.psd,.jpg,.tga", ".");
            
            if (igfd::ImGuiFileDialog::Instance()->FileDialog("ChooseFileDlgKey")) 
            {
                if (igfd::ImGuiFileDialog::Instance()->IsOk == true) 
                {
                    textureFileName = igfd::ImGuiFileDialog::Instance()->GetCurrentFileName();
                    textureFilePath = igfd::ImGuiFileDialog::Instance()->GetCurrentPath();

                    textureOpenEvent.filepath = textureFilePath + "/" + textureFileName;

                    Gui::getOnTextureOpen()->invokeEvents(textureOpenEvent);
                } 
                else 
                {
                    std::cout << "Could not open the file" << std::endl;
                }

                igfd::ImGuiFileDialog::Instance()->CloseDialog("ChooseFileDlgKey");
            }

            Gui::getOnTextureToggle()->invokeEvents(textureToggleEvent);
        }
    }

    void Gui::renderChooseShaderCategory()
    {
        if (ImGui::CollapsingHeader("Shader")) 
        {
            std::vector<std::string> items;
            items.push_back("Phong");
            items.push_back("Gourad");
            items.push_back("Toon");
            static unsigned int id = 0;

            if(ImGui::BeginListBox("Choose Shader"))
            {
                for (unsigned int i = 0; i < items.size(); i++)
                {
                    bool isSelected = (id == i);
                    if (ImGui::Selectable(items[i].c_str(), isSelected))
                    {
                        id = i;
                    }

                    if(isSelected)
                    {
                        onUpdateShaderEvent.type = id;
                        getOnUpdateShaderEvent()->invokeEvents(onUpdateShaderEvent);
                        Gui::getOnUpdateLightObserver()->invokeEvents(updateLightEvent);
                        Gui::getOnUpdateMaterialObserver()->invokeEvents(onUpdateMaterialEvent);
                    }
                }

                ImGui::EndListBox();
            }
        }
    }

    void Gui::renderObjectsInSceneCategory()
    {
        if (ImGui::CollapsingHeader("Objects")) 
        {
            static unsigned int id = 0;

            if(ImGui::BeginListBox("Objects in scene"))
            {
                for (unsigned int i = 0; i < m_objects.size(); i++)
                {
                    //const bool isSelected = (id == i);

                    /*
                    if (ImGui::Selectable(std::to_string(m_objects[i]).c_str(), isSelected))
                    {
                        id = i;
                    }
                    */

                    char s[8];
                    s[0] = 'T';
                    s[1] = 'o';
                    s[2] = 'g';
                    s[3] = 'g';
                    s[4] = 'l';
                    s[5] = 'e';
                    s[6] = *std::to_string(m_objects[i]).c_str();
                    s[7] = '\0';

                    bool a = checkboxes[i];
                    
                    if(ImGui::Checkbox(s, &a))
                    {
                        id = m_objects[i];
                        onSelectObjectEvent.objectId = id;
                        onSelectObjectEvent.flag = a;
                        checkboxes[i] = a;
                        Gui::getOnSelectObjectObserver()->invokeEvents(onSelectObjectEvent);
                    }
                }

                ImGui::EndListBox();
            }
        }
    }

    void Gui::addObject(int objectId)
    {
        m_objects.push_back(objectId);
        checkboxes.push_back(true);
    }
}