#include "GUI.h"

#include "imgui/imgui.h"

#include "Config/Config.h"
#include "Hooks/Hooks.h"
#include "ImGuiCustom/ImGuiCustom.h"

#include <array>
#include <vector>



//if (ImGui::BeginTabItem("Configs")) {
//    ImGui::TextUnformatted("Config is saved as \"config.txt\" inside GOESP directory in Documents");
//    if (ImGui::Button("Load"))
//        config->load();
//    if (ImGui::Button("Save"))
//        config->save();
//    ImGui::EndTabItem();
//}



GUI::GUI() noexcept
{
    SetupStyle();
}

void GUI::render() noexcept
{
    T::renderMenu();
}

void GUI::SetupStyle() {
    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
	style.Alpha = 1.0f;
	style.WindowPadding = ImVec2(8, 8);
	style.WindowRounding = 4.0f;
	style.WindowBorderSize = 1.0f;
	style.WindowMinSize = ImVec2(32, 32);
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
	style.ChildRounding = 4.0f;
	style.ChildBorderSize = 1.0f;
	style.PopupRounding = 4.0f;
	style.PopupBorderSize = 1.0f;
	style.FramePadding = ImVec2(4, 2);
	style.FrameRounding = 2.0f;
	style.FrameBorderSize = 1.0f;
	style.ItemSpacing = ImVec2(8, 4);
	style.ItemInnerSpacing = ImVec2(4, 4);
	style.IndentSpacing = 6.0f;
	style.ColumnsMinSpacing = 6.0f;
	style.ScrollbarSize = 6.0f;
	style.ScrollbarRounding = 9.0f;
	style.GrabMinSize = 0.0f;
	style.GrabRounding = 4.0f;
	style.TabRounding = 4.0f;
	style.TabBorderSize = 1.0f;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.SelectableTextAlign = ImVec2(0.0f, 0.5f);
	style.MouseCursorScale = 0.75f;

    //color navigation :
    /*[definition N][purpose][color][rgb]
        1 primitive :
        -primtv 0 (text)-white : 255, 255, 255
        - primtv 1 (background)-darkslategrey : 20, 20, 30
        - primtv 2 (disabled)-silver : 192, 192, 192
        - primtv 3 (control bg) - cadetblue : 30, 35, 50
        - primtv 4 (border)-black : 0, 0, 0
        - primtv 5 (hover)-matterhorn : 75, 75, 75
        *
        2 accents :
        -accent 0 (main)-blueviolet : 140, 40, 225
        * accent 1 (dark)-indigo : 55, 0, 100
        * accent 3 (darker)-darkviolet : 75, 50, 105
     */

        style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);					// primtv 0
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.75f, 0.75f, 0.75f, 0.85f);			// primtv 2
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.22f, 0.00f, 0.40f, 0.85f);			// accent 1

    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.14f, 0.20f, 1.00f);				// primtv 3
    style.Colors[ImGuiCol_ChildBg] = ImVec4(0.08f, 0.08f, 0.12f, 0.60f);				// primtv 1
    style.Colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.12f, 0.85f);				// primtv 1

    style.Colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.10f);					// primtv 4
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);			// clear

    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.11f, 0.14f, 0.20f, 1.00f);				// primtv 3
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.22f, 0.00f, 0.40f, 1.00f);			// accent 1
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.55f, 0.15f, 0.90f, 1.00f);			// accent 0

    //style.Colors[ImGuiCol_ControlBg] = ImVec4(0.11f, 0.14f, 0.20f, 1.00f);				// primtv 3
    //style.Colors[ImGuiCol_ControlBgHovered] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);		// primtv 5
    //style.Colors[ImGuiCol_ControlBgActive] = ImVec4(0.75f, 0.75f, 0.75f, 0.10f);		// primtv 2

    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.55f, 0.15f, 0.90f, 0.20f);				// accent 0
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.22f, 0.00f, 0.40f, 0.50f);			// accent 1
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.22f, 0.00f, 0.40f, 0.20f);		// accent 1

    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.08f, 0.08f, 0.12f, 0.70f);				// primtv 1

    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.11f, 0.14f, 0.20f, 0.30f);			// primtv 3
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.30f, 0.20f, 0.40f, 1.00f);			// accent 3
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.30f, 0.30f, 0.30f, 0.90f);	// primtv 5
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.75f, 0.75f, 0.75f, 0.10f);	// primtv 2

    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.55f, 0.15f, 0.90f, 1.00f);				// accent 0

    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.55f, 0.15f, 0.90f, 1.00f);				// accent 0
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.22f, 0.00f, 0.40f, 1.00f);		// accent 1

    style.Colors[ImGuiCol_Button] = ImVec4(0.11f, 0.14f, 0.20f, 1.00f);					// primtv 3
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);			// primtv 5
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.55f, 0.15f, 0.90f, 1.00f);			// accent 0

    style.Colors[ImGuiCol_Header] = ImVec4(0.55f, 0.15f, 0.90f, 1.00f);					// accent 0
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);			// primtv 5
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.11f, 0.14f, 0.20f, 1.00f);			// primtv 3

    style.Colors[ImGuiCol_Separator] = ImVec4(0.11f, 0.14f, 0.20f, 1.00f);				// primtv 3
    style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);		// primtv 5
    style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.55f, 0.15f, 0.90f, 1.00f);		// accent 0

    style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.55f, 0.15f, 0.90f, 1.00f);				// accent 0
    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.30f, 0.30f, 0.30f, 0.70f);		// primtv 5
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.22f, 0.00f, 0.40f, 1.00f);		// accent 1

    style.Colors[ImGuiCol_Tab] = ImVec4(0.08f, 0.08f, 0.12f, 0.80f);					// primtv 1
    style.Colors[ImGuiCol_TabHovered] = ImVec4(0.30f, 0.30f, 0.30f, 0.80f);				// primtv 5
    style.Colors[ImGuiCol_TabActive] = ImVec4(0.55f, 0.15f, 0.90f, 0.70f);				// accent 0
    style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.30f, 0.30f, 0.30f, 0.70f);			// primtv 5
    style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.55f, 0.15f, 0.90f, 0.60f);		// accent 0

    style.Colors[ImGuiCol_PlotLines] = ImVec4(0.55f, 0.15f, 0.90f, 1.00f);				// accent 0
    style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.55f, 0.15f, 0.90f, 0.50f);		// accent 0
    style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.55f, 0.15f, 0.90f, 1.00f);			// accent 0
    style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.55f, 0.15f, 0.90f, 0.50f);	// accent 0

    style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.30f, 0.20f, 0.40f, 0.80f);			// accent 3
    //style.Colors[ImGuiCol_Triangle] = ImVec4(0.55f, 0.15f, 0.90f, 1.00f);				// accent 0

    style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.25f);		// primtv 4

    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr;
    io.LogFilename = nullptr;
    io.Fonts->Flags |= ImFontAtlasFlags_NoPowerOfTwoHeight;
}

void GUI::updateColors() noexcept
{
    switch (config->menuColors) {
    case 0: SetupStyle(); break;
    case 1: ImGui::StyleColorsDark(); break;
    case 2: ImGui::StyleColorsLight(); break;
    case 3: ImGui::StyleColorsClassic(); break;
    }
}

void T::drawAimbotTab() noexcept 
{
    ImGui::Columns(2, nullptr, false);
    {
        ImGui::BeginChild("aimbot.aimbot", ImVec2(), true, ImGuiWindowFlags_MenuBar);
        {
            if (ImGui::BeginMenuBar())
            {
                ImGui::TextUnformatted("AntiAim");
                ImGui::EndMenuBar();
            }
            //
            /*ImGui::Checkbox("Enabled", &config->antiAim.enabled);
            ImGui::Checkbox("##pitch", &config->antiAim.pitch);
            ImGui::SameLine();
            ImGui::SliderFloat("Pitch", &config->antiAim.pitchAngle, -89.0f, 89.0f, "%.2f");
            ImGui::Checkbox("Yaw", &config->antiAim.yaw);*/
            //

		}
        ImGui::EndChild();
	}
    ImGui::NextColumn();
    {
        ImGui::BeginChild("trigger.aimbot", ImVec2(), true, ImGuiWindowFlags_MenuBar);
        {
            if (ImGui::BeginMenuBar())
            {
                ImGui::TextUnformatted("Trigger");
                ImGui::EndMenuBar();
            }

            ImGui::Checkbox("Enable", &config->trigger_bool);



		}
        ImGui::EndChild();
	}
    ImGui::Columns(1);
}

void T::drawGlowTab() noexcept
{
    //ImGui::Checkbox("Enable", &config->glow);
    //ImGui::Separator();//���������(���������� ��)
    ImGui::Columns(2, nullptr, false);
    { // Alies 
        ImGui::BeginChild("alies.glow", ImVec2(), true, ImGuiWindowFlags_MenuBar);
        {
            if (ImGui::BeginMenuBar())
            {
                ImGui::TextUnformatted("Alies");
                ImGui::EndMenuBar();
            }
            ImGuiCustom::colorPicker("Enable", config->GlowAlies);  

            ImGui::Checkbox("Health Based", &config->GlowHealth_Team);
            ImGui::Checkbox("Full Bloom", &config->FullBloomTeam);
            ImGui::Checkbox("Glow Only", &config->GlowOnly_Team);
		}
        ImGui::EndChild();
	}
    ImGui::NextColumn();
    { // Enemy
        ImGui::BeginChild("enemy.glow", ImVec2(), true, ImGuiWindowFlags_MenuBar);
        {
            if (ImGui::BeginMenuBar())
            {
                ImGui::TextUnformatted("Enemy");
                ImGui::EndMenuBar();
            }
            ImGuiCustom::colorPicker("Enable", config->GlowEnemy);

            ImGui::Checkbox("Health Based", &config->GlowHealth_Enemy);
            ImGui::Checkbox("Full Bloom", &config->FullBloomEnemy);
            ImGui::Checkbox("Glow Only", &config->GlowOnly_Enemy);
        }
        ImGui::EndChild();
	}
    ImGui::Columns(1);
}

void T::drawMiscTab() noexcept
{
    ImGui::Columns(2, nullptr, false);
    {
        ImGui::BeginChild("misc1.misc", ImVec2(), true, ImGuiWindowFlags_MenuBar);
        {
            if (ImGui::BeginMenuBar())
            {
                ImGui::TextUnformatted("misc");
                ImGui::EndMenuBar();
            }
            ImGui::Checkbox("Bunny Hop", &config->bunnyhop);
            ImGui::Checkbox("Anti-Flash", &config->antiflash);
            ImGui::Checkbox("Radar Hack", &config->radar_bool);

            ImGui::Separator();

            ImGuiCustom::colorPicker("HitMarker", config->hitMarker);
            ImGui::Checkbox("Hit Sound", &config->hitSound);

            ImGui::Separator();

            ImGuiCustom::colorPicker("KillMarker", config->killMarker);
            ImGui::Checkbox("Kill Sound", &config->killSound);

            ImGui::Separator();

            ImGui::Checkbox("FOV", &config->fovEnable);
            ImGui::SliderFloat("FOV value", &config->FOV, 0, 180);
        }
        ImGui::EndChild();
    }
    ImGui::NextColumn();
    {
        ImGui::BeginChild("misc2.misc", ImVec2(), true, ImGuiWindowFlags_MenuBar);
        {
            if (ImGui::BeginMenuBar())
            {
                ImGui::TextUnformatted("misc");
                ImGui::EndMenuBar();
            }
            ImGuiCustom::colorPicker("Reload Progress", config->reloadProgress);
            ImGuiCustom::colorPicker("Recoil Crosshair", config->recoilCrosshair);
            ImGuiCustom::colorPicker("Noscope Crosshair", config->noscopeCrosshair);

            ImGui::Checkbox("Purchase List", &config->purchaseList.enabled);
            ImGui::SameLine();

            ImGui::PushID("Purchase List");
            if (ImGui::Button("..."))
                ImGui::OpenPopup("");

            if (ImGui::BeginPopup("")) {
                ImGui::SetNextItemWidth(75.0f);
                ImGui::Combo("Mode", &config->purchaseList.mode, "Details\0Summary\0");
                ImGui::Checkbox("Only During Freeze Time", &config->purchaseList.onlyDuringFreezeTime);
                ImGui::Checkbox("Show Prices", &config->purchaseList.showPrices);
                ImGui::Checkbox("No Title Bar", &config->purchaseList.noTitleBar);
                ImGui::EndPopup();
            }
            ImGui::PopID();

            ImGui::PushID("Observer List");
            ImGui::Checkbox("Observer List", &config->observerList.enabled);
            ImGui::SameLine();

            if (ImGui::Button("..."))
                ImGui::OpenPopup("");

            if (ImGui::BeginPopup("")) {
                ImGui::Checkbox("No Title Bar", &config->observerList.noTitleBar);
                ImGui::EndPopup();
            }
            ImGui::PopID();

            ImGui::Separator();

            if (ImGui::Button("Unload"))
                hooks->uninstall();
        }
        ImGui::EndChild();
    }
    ImGui::Columns(1);
}

void T::drawConfigTab() noexcept
{
    ImGui::TextUnformatted("Build date: " __DATE__ );
    ImGui::TextUnformatted("Config is saved as \"config.txt\" inside CPN directory in Documents");
    if (ImGui::Button("Load"))
        config->load();
    if (ImGui::Button("Save"))
        config->save();
}

void T::drawStyleTab() noexcept
{
    ImGui::BeginChild("style.style", ImVec2(), true, ImGuiWindowFlags_MenuBar);
    {
        if (ImGui::BeginMenuBar())
        {
            ImGui::TextUnformatted("Style");
            ImGui::EndMenuBar();
        }

        ImGui::PushItemWidth(-1); //150.0f
        if (ImGui::Combo("Menu colors", &config->menuColors, "Default\0Dark\0Light\0Classic\0Custom\0"))
            GUI::updateColors();
        ImGui::PopItemWidth();

        if (config->menuColors == 4) {
            ImGuiStyle& style = ImGui::GetStyle();
            for (int i = 0; i < ImGuiCol_COUNT; i++) {
                //if (i && i & 3) ImGui::SameLine(220.0f * (i & 3));

                //ImGuiCustom::colorPicker(ImGui::GetStyleColorName(i), (float*)&style.Colors[i]);
                ImGuiCustom::colorPicker(ImGui::GetStyleColorName(i), (float*)&style.Colors[i]);
            }
        }
	}
    ImGui::EndChild();
}

void T::drawESPTab() noexcept
{
    static std::size_t currentCategory;
    static auto currentItem = "All";

    constexpr auto getConfigShared = [](std::size_t category, const char* item) noexcept -> Shared& {
        switch (category) {
        case 0: default: return config->enemies[item];
        case 1: return config->allies[item];
        case 2: return config->weapons[item];
        case 3: return config->projectiles[item];
        case 4: return config->lootCrates[item];
        case 5: return config->otherEntities[item];
        }
    };

    constexpr auto getConfigPlayer = [](std::size_t category, const char* item) noexcept -> Player& {
        switch (category) {
        case 0: default: return config->enemies[item];
        case 1: return config->allies[item];
        }
    };

    if (ImGui::ListBoxHeader("##list", { 170.0f, -1 })) { //
        constexpr std::array categories{ "Enemies", "Allies", "Weapons", "Projectiles", "Loot Crates", "Other Entities" };

        for (std::size_t i = 0; i < categories.size(); ++i) {
            if (ImGui::Selectable(categories[i], currentCategory == i && std::string_view{ currentItem } == "All")) {
                currentCategory = i;
                currentItem = "All";
            }

            if (ImGui::BeginDragDropSource()) {
                switch (i) {
                case 0: case 1: ImGui::SetDragDropPayload("Player", &getConfigPlayer(i, "All"), sizeof(Player), ImGuiCond_Once); break;
                case 2: ImGui::SetDragDropPayload("Weapon", &config->weapons["All"], sizeof(Weapon), ImGuiCond_Once); break;
                case 3: ImGui::SetDragDropPayload("Projectile", &config->projectiles["All"], sizeof(Projectile), ImGuiCond_Once); break;
                default: ImGui::SetDragDropPayload("Entity", &getConfigShared(i, "All"), sizeof(Shared), ImGuiCond_Once); break;
                }
                ImGui::EndDragDropSource();
            }

            if (ImGui::BeginDragDropTarget()) {
                if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Player")) {
                    const auto& data = *(Player*)payload->Data;

                    switch (i) {
                    case 0: case 1: getConfigPlayer(i, "All") = data; break;
                    case 2: config->weapons["All"] = data; break;
                    case 3: config->projectiles["All"] = data; break;
                    default: getConfigShared(i, "All") = data; break;
                    }
                }

                if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Weapon")) {
                    const auto& data = *(Weapon*)payload->Data;

                    switch (i) {
                    case 0: case 1: getConfigPlayer(i, "All") = data; break;
                    case 2: config->weapons["All"] = data; break;
                    case 3: config->projectiles["All"] = data; break;
                    default: getConfigShared(i, "All") = data; break;
                    }
                }

                if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Projectile")) {
                    const auto& data = *(Projectile*)payload->Data;

                    switch (i) {
                    case 0: case 1: getConfigPlayer(i, "All") = data; break;
                    case 2: config->weapons["All"] = data; break;
                    case 3: config->projectiles["All"] = data; break;
                    default: getConfigShared(i, "All") = data; break;
                    }
                }

                if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Entity")) {
                    const auto& data = *(Shared*)payload->Data;

                    switch (i) {
                    case 0: case 1: getConfigPlayer(i, "All") = data; break;
                    case 2: config->weapons["All"] = data; break;
                    case 3: config->projectiles["All"] = data; break;
                    default: getConfigShared(i, "All") = data; break;
                    }
                }
                ImGui::EndDragDropTarget();
            }

            ImGui::PushID(i);
            ImGui::Indent();

            const auto items = [](std::size_t category) noexcept -> std::vector<const char*> {
                switch (category) {
                case 0:
                case 1: return { "Visible", "Occluded" };
                case 2: return { "Pistols", "SMGs", "Rifles", "Sniper Rifles", "Shotguns", "Machineguns", "Grenades", "Melee", "Other" };
                case 3: return { "Flashbang", "HE Grenade", "Breach Charge", "Bump Mine", "Decoy Grenade", "Molotov", "TA Grenade", "Smoke Grenade", "Snowball" };
                case 4: return { "Pistol Case", "Light Case", "Heavy Case", "Explosive Case", "Tools Case", "Cash Dufflebag" };
                case 5: return { "Defuse Kit", "Chicken", "Planted C4", "Hostage", "Sentry", "Cash", "Ammo Box", "Radar Jammer", "Snowball Pile" };
                default: return { };
                }
            }(i);

            const auto categoryEnabled = getConfigShared(i, "All").enabled;

            for (std::size_t j = 0; j < items.size(); ++j) {
                static bool selectedSubItem;
                if (!categoryEnabled || getConfigShared(i, items[j]).enabled) {
                    if (ImGui::Selectable(items[j], currentCategory == i && !selectedSubItem && std::string_view{ currentItem } == items[j])) {
                        currentCategory = i;
                        currentItem = items[j];
                        selectedSubItem = false;
                    }

                    if (ImGui::BeginDragDropSource()) {
                        switch (i) {
                        case 0: case 1: ImGui::SetDragDropPayload("Player", &getConfigPlayer(i, items[j]), sizeof(Player), ImGuiCond_Once); break;
                        case 2: ImGui::SetDragDropPayload("Weapon", &config->weapons[items[j]], sizeof(Weapon), ImGuiCond_Once); break;
                        case 3: ImGui::SetDragDropPayload("Projectile", &config->projectiles[items[j]], sizeof(Projectile), ImGuiCond_Once); break;
                        default: ImGui::SetDragDropPayload("Entity", &getConfigShared(i, items[j]), sizeof(Shared), ImGuiCond_Once); break;
                        }
                        ImGui::EndDragDropSource();
                    }

                    if (ImGui::BeginDragDropTarget()) {
                        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Player")) {
                            const auto& data = *(Player*)payload->Data;

                            switch (i) {
                            case 0: case 1: getConfigPlayer(i, items[j]) = data; break;
                            case 2: config->weapons[items[j]] = data; break;
                            case 3: config->projectiles[items[j]] = data; break;
                            default: getConfigShared(i, items[j]) = data; break;
                            }
                        }

                        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Weapon")) {
                            const auto& data = *(Weapon*)payload->Data;

                            switch (i) {
                            case 0: case 1: getConfigPlayer(i, items[j]) = data; break;
                            case 2: config->weapons[items[j]] = data; break;
                            case 3: config->projectiles[items[j]] = data; break;
                            default: getConfigShared(i, items[j]) = data; break;
                            }
                        }

                        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Projectile")) {
                            const auto& data = *(Projectile*)payload->Data;

                            switch (i) {
                            case 0: case 1: getConfigPlayer(i, items[j]) = data; break;
                            case 2: config->weapons[items[j]] = data; break;
                            case 3: config->projectiles[items[j]] = data; break;
                            default: getConfigShared(i, items[j]) = data; break;
                            }
                        }

                        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Entity")) {
                            const auto& data = *(Shared*)payload->Data;

                            switch (i) {
                            case 0: case 1: getConfigPlayer(i, items[j]) = data; break;
                            case 2: config->weapons[items[j]] = data; break;
                            case 3: config->projectiles[items[j]] = data; break;
                            default: getConfigShared(i, items[j]) = data; break;
                            }
                        }
                        ImGui::EndDragDropTarget();
                    }
                }

                if (i != 2)
                    continue;

                ImGui::Indent();

                const auto subItems = [](std::size_t item) noexcept -> std::vector<const char*> {
                    switch (item) {
                    case 0: return { "Glock-18", "P2000", "USP-S", "Dual Berettas", "P250", "Tec-9", "Five-SeveN", "CZ75-Auto", "Desert Eagle", "R8 Revolver" };
                    case 1: return { "MAC-10", "MP9", "MP7", "MP5-SD", "UMP-45", "P90", "PP-Bizon" };
                    case 2: return { "Galil AR", "FAMAS", "AK-47", "M4A4", "M4A1-S", "SG 553", "AUG" };
                    case 3: return { "SSG 08", "AWP", "G3SG1", "SCAR-20" };
                    case 4: return { "Nova", "XM1014", "Sawed-Off", "MAG-7" };
                    case 5: return { "M249", "Negev" };
                    case 6: return { "Flashbang", "HE Grenade", "Smoke Grenade", "Molotov", "Decoy Grenade", "Incendiary", "TA Grenade", "Fire Bomb", "Diversion", "Frag Grenade", "Snowball" };
                    case 7: return { "Axe", "Hammer", "Wrench" };
                    case 8: return { "C4", "Healthshot", "Bump Mine", "Zone Repulsor", "Shield" };
                    default: return { };
                    }
                }(j);

                const auto itemEnabled = getConfigShared(i, items[j]).enabled;

                for (const auto subItem : subItems) {
                    auto& subItemConfig = config->weapons[subItem];
                    if ((categoryEnabled || itemEnabled) && !subItemConfig.enabled)
                        continue;

                    if (ImGui::Selectable(subItem, currentCategory == i && selectedSubItem && std::string_view{ currentItem } == subItem)) {
                        currentCategory = i;
                        currentItem = subItem;
                        selectedSubItem = true;
                    }

                    if (ImGui::BeginDragDropSource()) {
                        ImGui::SetDragDropPayload("Weapon", &subItemConfig, sizeof(Weapon), ImGuiCond_Once);
                        ImGui::EndDragDropSource();
                    }

                    if (ImGui::BeginDragDropTarget()) {
                        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Player")) {
                            const auto& data = *(Player*)payload->Data;
                            subItemConfig = data;
                        }

                        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Weapon")) {
                            const auto& data = *(Weapon*)payload->Data;
                            subItemConfig = data;
                        }

                        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Projectile")) {
                            const auto& data = *(Projectile*)payload->Data;
                            subItemConfig = data;
                        }

                        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Entity")) {
                            const auto& data = *(Shared*)payload->Data;
                            subItemConfig = data;
                        }
                        ImGui::EndDragDropTarget();
                    }
                }

                ImGui::Unindent();
            }
            ImGui::Unindent();
            ImGui::PopID();
        }
        ImGui::ListBoxFooter();
    }

    ImGui::SameLine();

    if (ImGui::BeginChild("##child", { 400.0f, 0.0f })) {
        auto& sharedConfig = getConfigShared(currentCategory, currentItem);

        ImGui::Checkbox("Enabled", &sharedConfig.enabled);
        ImGui::SameLine(ImGui::GetWindowContentRegionMax().x - 260.0f);
        ImGui::SetNextItemWidth(220.0f);
        if (ImGui::BeginCombo("Font", config->systemFonts[sharedConfig.font.index].c_str())) {
            for (size_t i = 0; i < config->systemFonts.size(); i++) {
                bool isSelected = config->systemFonts[i] == sharedConfig.font.name;
                if (ImGui::Selectable(config->systemFonts[i].c_str(), isSelected, 0, { 250.0f, 0.0f })) {
                    sharedConfig.font.index = i;
                    sharedConfig.font.name = config->systemFonts[i];
                    config->scheduleFontLoad(sharedConfig.font.name);
                }
                if (isSelected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }

        ImGui::Separator();

        constexpr auto spacing = 250.0f;
        ImGuiCustom::colorPicker("Snapline", sharedConfig.snapline);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(90.0f);
        ImGui::Combo("##1", &sharedConfig.snapline.type, "Bottom\0Top\0Crosshair\0");
        ImGui::SameLine(spacing);
        ImGuiCustom::colorPicker("Box", sharedConfig.box);
        ImGui::SameLine();

        ImGui::PushID("Box");

        if (ImGui::Button("..."))
            ImGui::OpenPopup("");

        if (ImGui::BeginPopup("")) {
            ImGui::SetNextItemWidth(95.0f);
            ImGui::Combo("Type", &sharedConfig.box.type, "2D\0" "2D corners\0" "3D\0" "3D corners\0");
            ImGui::SetNextItemWidth(275.0f);
            ImGui::SliderFloat3("Scale", sharedConfig.box.scale.data(), 0.0f, 0.50f, "%.2f");
            ImGui::EndPopup();
        }

        ImGui::PopID();

        ImGuiCustom::colorPicker("Name", sharedConfig.name);
        ImGui::SameLine(spacing);

        if (currentCategory < 2) {
            auto& playerConfig = getConfigPlayer(currentCategory, currentItem);

            ImGuiCustom::colorPicker("Weapon", playerConfig.weapon);
            ImGuiCustom::colorPicker("Flash Duration", playerConfig.flashDuration);
            ImGui::SameLine(spacing);
            ImGuiCustom::colorPicker("Skeleton", playerConfig.skeleton);
            ImGui::Checkbox("Audible Only", &playerConfig.audibleOnly);
            ImGui::SameLine(spacing);
            ImGui::Checkbox("Spotted Only", &playerConfig.spottedOnly);
        } else if (currentCategory == 2) {
            auto& weaponConfig = config->weapons[currentItem];
            ImGuiCustom::colorPicker("Ammo", weaponConfig.ammo);
        } else if (currentCategory == 3) {
            auto& trails = config->projectiles[currentItem].trails;

            ImGui::Checkbox("Trails", &trails.enabled);
            ImGui::SameLine(spacing + 77.0f);
            ImGui::PushID("Trails");

            if (ImGui::Button("..."))
                ImGui::OpenPopup("");

            if (ImGui::BeginPopup("")) {
                constexpr auto trailPicker = [](const char* name, Trail& trail) noexcept {
                    ImGui::PushID(name);
                    ImGuiCustom::colorPicker(name, trail);
                    ImGui::SameLine(150.0f);
                    ImGui::SetNextItemWidth(95.0f);
                    ImGui::Combo("", &trail.type, "Line\0Circles\0Filled Circles\0");
                    ImGui::SameLine();
                    ImGui::SetNextItemWidth(95.0f);
                    ImGui::InputFloat("Time", &trail.time, 0.1f, 0.5f, "%.1fs");
                    trail.time = std::clamp(trail.time, 1.0f, 60.0f);
                    ImGui::PopID();
                };

                trailPicker("Local Player", trails.localPlayer);
                trailPicker("Allies", trails.allies);
                trailPicker("Enemies", trails.enemies);
                ImGui::EndPopup();
            }

            ImGui::PopID();
        }

        ImGui::SetNextItemWidth(95.0f);
        ImGui::InputFloat("Text Cull Distance", &sharedConfig.textCullDistance, 0.4f, 0.8f, "%.1fm");
        sharedConfig.textCullDistance = std::clamp(sharedConfig.textCullDistance, 0.0f, 999.9f);
    }

    ImGui::EndChild();
}

// future implementation

bool drawPlayerCategories(const char* (&currentCategory), const char* (&currentItem)) noexcept
{
    bool selected = false;

    constexpr auto dragDrop = [](Player& player) {
        if (ImGui::BeginDragDropSource()) {
            ImGui::SetDragDropPayload("Player", &player, sizeof(Player), ImGuiCond_Once);
            ImGui::EndDragDropSource();
        }

        if (ImGui::BeginDragDropTarget()) {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Player"))
                player = *(Player*)payload->Data;

            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Weapon"))
                player = *(Weapon*)payload->Data;

            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Projectile"))
                player = *(Projectile*)payload->Data;

            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Entity"))
                player = *(Shared*)payload->Data;

            ImGui::EndDragDropTarget();
        }
    };

    auto category = [&](const char* name, std::unordered_map<std::string, Player>& cfg) {
        if (ImGui::Selectable(name, std::string_view{ currentCategory } == name && std::string_view{ currentItem } == "All")) {
            currentCategory = name;
            currentItem = "All";
            selected = true;
        }

        dragDrop(cfg["All"]);

        ImGui::Indent();

        for (const auto item : std::array{ "Visible", "Occluded" }) {
            if (!cfg["All"].enabled || cfg[item].enabled) {
                if (ImGui::Selectable(item, std::string_view{ currentCategory } == name && std::string_view{ currentItem } == item)) {
                    currentCategory = name;
                    currentItem = item;
                    selected = true;
                }
                dragDrop(cfg[item]);
            }
        }

        ImGui::Unindent();
    };

    category("Allies", config->allies);
    category("Enemies", config->enemies);

    return selected;
}

bool drawWeaponCategories(const char* (&currentCategory), const char* (&currentItem)) noexcept
{
    bool selected = false;

    constexpr auto dragDrop = [](Weapon& weapon) {
        if (ImGui::BeginDragDropSource()) {
            ImGui::SetDragDropPayload("Weapon", &weapon, sizeof(Weapon), ImGuiCond_Once);
            ImGui::EndDragDropSource();
        }

        if (ImGui::BeginDragDropTarget()) {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Player"))
                weapon = *(Player*)payload->Data;

            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Weapon"))
                weapon = *(Weapon*)payload->Data;

            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Projectile"))
                weapon = *(Projectile*)payload->Data;

            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Entity"))
                weapon = *(Shared*)payload->Data;

            ImGui::EndDragDropTarget();
        }
    };

    if (ImGui::Selectable("Weapons", std::string_view{ currentCategory } == "Weapons" && std::string_view{ currentItem } == "All")) {
        currentCategory = "Weapons";
        currentItem = "All";
        selected = true;
    }

    dragDrop(config->weapons["All"]);

    ImGui::PushID("Weapons");
    ImGui::Indent();

    constexpr std::array items{ "Pistols", "SMGs", "Rifles", "Sniper Rifles", "Shotguns", "Machineguns", "Grenades", "Melee", "Other" };

    for (std::size_t i = 0; i < items.size(); ++i) {
        if (!config->weapons["All"].enabled || config->weapons[items[i]].enabled) {
            if (ImGui::Selectable(items[i], std::string_view{ currentCategory } == "Weapons" && std::string_view{ currentItem } == items[i])) {
                currentCategory = "Weapons";
                currentItem = items[i];
                selected = true;
            }

            dragDrop(config->weapons[items[i]]);
        }

        const auto subItems = [](std::size_t item) noexcept -> std::vector<const char*> {
            switch (item) {
            case 0: return { "Glock-18", "P2000", "USP-S", "Dual Berettas", "P250", "Tec-9", "Five-SeveN", "CZ75-Auto", "Desert Eagle", "R8 Revolver" };
            case 1: return { "MAC-10", "MP9", "MP7", "MP5-SD", "UMP-45", "P90", "PP-Bizon" };
            case 2: return { "Galil AR", "FAMAS", "AK-47", "M4A4", "M4A1-S", "SG 553", "AUG" };
            case 3: return { "SSG 08", "AWP", "G3SG1", "SCAR-20" };
            case 4: return { "Nova", "XM1014", "Sawed-Off", "MAG-7" };
            case 5: return { "M249", "Negev" };
            case 6: return { "Flashbang", "HE Grenade", "Smoke Grenade", "Molotov", "Decoy Grenade", "Incendiary", "TA Grenade", "Fire Bomb", "Diversion", "Frag Grenade", "Snowball" };
            case 7: return { "Axe", "Hammer", "Wrench" };
            case 8: return { "C4", "Healthshot", "Bump Mine", "Zone Repulsor", "Shield" };
            default: return { };
            }
        }(i);

        ImGui::Indent();
        for (const auto subItem : subItems) {
            if ((config->weapons["All"].enabled || config->weapons[items[i]].enabled) && !config->weapons[subItem].enabled)
                continue;

            if (ImGui::Selectable(subItem, std::string_view{ currentCategory } == "Weapons" && std::string_view{ currentItem } == subItem)) {
                currentCategory = "Weapons";
                currentItem = subItem;
                selected = true;
            }

            dragDrop(config->weapons[subItem]);
        }
        ImGui::Unindent();
    }

    ImGui::Unindent();
    ImGui::PopID();
    return selected;
}















#pragma region menu_windows
void T::renderMenu() noexcept
{
    ImGuiIO& io = ImGui::GetIO();
    const ImVec2 vecScreenSize = io.DisplaySize;

    ImGuiStyle& style = ImGui::GetStyle();
    ImDrawList* pDrawList = ImGui::GetForegroundDrawList();

    //ImGui::PushFont(F::Whitney);
    io.MouseDrawCursor = gui->open;

    if (gui->open)
    {
        ImGui::SetNextWindowPos(ImVec2(vecScreenSize.x * 0.5f, vecScreenSize.y * 0.5f), ImGuiCond_Once, ImVec2(0.5f, 0.5f));
        ImGui::SetNextWindowSize(ImVec2(800, 500), ImGuiCond_Always); //500 320
        ImGui::Begin("CPN", &gui->open, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse);
        {
            ImVec2 vecPos = ImGui::GetCursorScreenPos();
            float flWindowWidth = ImGui::GetWindowWidth();

            // header separate line
            pDrawList->AddRectFilledMultiColor(ImVec2(vecPos.x - 8.f, vecPos.y - 6.f), ImVec2(vecPos.x + flWindowWidth - flWindowWidth / 3.f - 8.f, vecPos.y - 8.f), IM_COL32(75, 50, 105, 255), IM_COL32(110, 100, 130, 255), IM_COL32(110, 100, 130, 255), IM_COL32(75, 50, 105, 255));
            pDrawList->AddRectFilledMultiColor(ImVec2(vecPos.x + flWindowWidth - flWindowWidth / 3.f - 8.f, vecPos.y - 6.f), ImVec2(vecPos.x + flWindowWidth - 8.f, vecPos.y - 8.f), IM_COL32(110, 100, 130, 255), IM_COL32(75, 50, 105, 255), IM_COL32(75, 50, 105, 255), IM_COL32(110, 100, 130, 255));

            // add tabs
            static std::array<CTab, 5U> const arrTabs =
            {
                CTab{ "Aimbot", &drawAimbotTab },
                CTab{ "Glow", &drawGlowTab },
                CTab{ "ESP", &drawESPTab },
                CTab{ "Misc", &drawMiscTab },
                CTab{ "Config", &drawConfigTab }
                /*CTab{ "Style", &drawStyleTab }*/
            };

            Render<arrTabs.size()>("main_tabs", arrTabs, &iMainTab, style.Colors[ImGuiCol_TabActive]);

            ImGui::End();
        }
    }

    //ImGui::PopFont();
}
#pragma endregion

#pragma region menu_tabs
template <std::size_t S>
void T::Render(const char* szTabBar, const std::array<CTab, S> arrTabs, int* nCurrentTab, const ImVec4& colActive, ImGuiTabBarFlags flags)
{
    // is empty check
    if (arrTabs.empty())
        return;

    // set active tab color
    ImGui::PushStyleColor(ImGuiCol_TabActive, colActive);
    if (ImGui::BeginTabBar(szTabBar, flags))
    {
        for (std::size_t i = 0U; i < arrTabs.size(); i++)
        {
            // add tab
            if (ImGui::BeginTabItem(arrTabs.at(i).szName))
            {
                // set current tab index
                *nCurrentTab = i;
                ImGui::EndTabItem();
            }
        }

        // render inner tab
        if (arrTabs.at(*nCurrentTab).pRenderFunction != nullptr)
            arrTabs.at(*nCurrentTab).pRenderFunction();

        ImGui::EndTabBar();
    }
    ImGui::PopStyleColor();
}
#pragma endregion