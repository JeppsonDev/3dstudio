#include "gui.hpp"

namespace Umu
{
    Observer<UpdatePerspectiveEvent> *Gui::m_updatePerspectiveObserver = new Observer<UpdatePerspectiveEvent>();
    Observer<UpdateOrthographicEvent> *Gui::m_updateOrthographicObserver = new Observer<UpdateOrthographicEvent>();
    Observer<OpenObjectEvent> *Gui::m_openObjectObserver = new Observer<OpenObjectEvent>();
    Observer<OnUpdateLightEvent> *Gui::m_onUpdateLightObserver = new Observer<OnUpdateLightEvent>();
    Observer<OnTextureToggle> *Gui::m_onTextureToggle = new Observer<OnTextureToggle>();

    UpdatePerspectiveEvent updatePerspectiveEvent;
    OpenObjectEvent openObjectEvent;
    UpdateOrthographicEvent updateOrthographicEvent;
    OnUpdateLightEvent updateLightEvent;
    OnTextureToggle textureToggleEvent;

    static bool first = true;

    //-----------------------------------------PUBLIC------------------------------------------//
    void Gui::render()
    {
        
        IM_ASSERT(ImGui::GetCurrentContext() != NULL && "Missing dear imgui context.");

        static ImGuiSliderFlags flags = ImGuiSliderFlags_AlwaysClamp;

        ImGui::Begin("3D Studio"); 

        renderObjFileCategory();
        renderProjectionCategory(flags);
        renderLightCategory(flags);

        //TODO: We're updating light on first frame... there HAS to be a better way to do this
        if(first)
        {
            Gui::getOnUpdateLightObserver()->invokeEvents(updateLightEvent);
            first = false;
        }

        ImGui::End();
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
        static bool textureShow = false;

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
            ImGui::Text("Ambient coefficient:");
            ImGui::ColorEdit3("Ambient color", updateLightEvent.materialAmbient);
            
            ImGui::Text("Diffuse coefficient:");
            ImGui::ColorEdit3("Diffuse color", updateLightEvent.materialDiffuse);
            
            ImGui::Text("Specular coefficient:");
            ImGui::ColorEdit3("Specular color", updateLightEvent.materialSpecular);

            ImGui::SliderFloat("Shininess", &updateLightEvent.materialShininess, 1.0f, 1000.0f, "%1.0f", flags);

            Gui::getOnUpdateLightObserver()->invokeEvents(updateLightEvent);
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
                    std::cout << "Texture file: " << textureFileName << std::endl << "Path: " << textureFilePath << std::endl;
                } 
                else 
                {
                    // Return a message to the user if the file could not be opened
                }

                igfd::ImGuiFileDialog::Instance()->CloseDialog("ChooseFileDlgKey");
            }

            Gui::getOnTextureToggle()->invokeEvents(textureToggleEvent);
        }
    }
}