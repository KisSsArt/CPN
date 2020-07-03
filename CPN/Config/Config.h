#pragma once

#include <array>
#include <filesystem>
#include <memory>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "../ConfigStructs.h"

struct ImFont;

class Config {
public:
    explicit Config(const char* folderName) noexcept;
    void load() noexcept;
    void save() noexcept;

    std::unordered_map<std::string, Player> allies;
    std::unordered_map<std::string, Player> enemies;
    std::unordered_map<std::string, Weapon> weapons;
    std::unordered_map<std::string, Projectile> projectiles;
    std::unordered_map<std::string, Shared> lootCrates;
    std::unordered_map<std::string, Shared> otherEntities;

    ColorToggleThickness reloadProgress{ 5.0f };
    ColorToggleThickness recoilCrosshair;
    ColorToggleThickness noscopeCrosshair;

    //new
    int menuColors{ 0 };

    bool antiflash = false;
    bool bunnyhop = false;


    
    //glow
    //bool glow = false;

       //team
    bool GlowOnly_Team = false;
    ColorToggle GlowAlies;
          //team Color
    bool GlowHealth_Team = false;
    bool FullBloomTeam = false;
    
       //enemy
    bool GlowOnly_Enemy = false;
    ColorToggle GlowEnemy;
          //Enemy Color
    bool GlowHealth_Enemy = false;
    bool FullBloomEnemy = false;
    //

    //trigger
    bool trigger_bool = false;

    float FOV = 90;
    bool fovEnable = false;
    bool radar_bool = false;


    PurchaseList purchaseList;
    ObserverList observerList;

    std::vector<std::string> systemFonts{ "Default" };
    std::unordered_map<std::string, ImFont*> fonts;

    void scheduleFontLoad(const std::string& name) noexcept;
    bool loadScheduledFonts() noexcept;

private:
    std::vector<std::string> scheduledFonts;
    std::filesystem::path path;
};

inline std::unique_ptr<Config> config;
