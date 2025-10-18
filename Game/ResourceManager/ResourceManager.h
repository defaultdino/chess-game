//
// Created by Adis Veletanlic on 2025-10-17
//

#ifndef CHESSGAME_RESOURCEMANAGER_H
#define CHESSGAME_RESOURCEMANAGER_H

#include <SFML/Graphics/Texture.hpp>
#include <stdexcept>
#include <string>
#include <map>

class ResourceManager {
private:
    std::map<std::string, sf::Texture> textures;
    ResourceManager() {}

public:
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    static ResourceManager& GetInstance() {
        static ResourceManager instance;
        return instance;
    }

    sf::Texture& LoadTexture(const std::string& key, const std::string& path) {
        auto& texture = textures[key];
        if (!texture.loadFromFile(path)) {
            throw std::runtime_error("Failed to load texture: " + path);
        }
        return texture;
    }

    sf::Texture& GetTexture(const std::string& key) {
        auto it = textures.find(key);
        if (it == textures.end()) {
            throw std::runtime_error("Texture not found: " + key);
        }
        return it->second;
    }

    void PreloadChessTextures() {
        LoadTexture("black_pawn", "Assets/Sprites/pawn-black.png");
        LoadTexture("white_pawn", "Assets/Sprites/pawn-white.png");
        LoadTexture("black_rook", "Assets/Sprites/rook-black.png");
        LoadTexture("white_rook", "Assets/Sprites/rook-white.png");
        LoadTexture("black_knight", "Assets/Sprites/knight-black.png");
        LoadTexture("white_knight", "Assets/Sprites/knight-white.png");
        LoadTexture("black_bishop", "Assets/Sprites/bishop-black.png");
        LoadTexture("white_bishop", "Assets/Sprites/bishop-white.png");
        LoadTexture("black_queen", "Assets/Sprites/queen-black.png");
        LoadTexture("white_queen", "Assets/Sprites/queen-white.png");
        LoadTexture("black_king", "Assets/Sprites/king-black.png");
        LoadTexture("white_king", "Assets/Sprites/king-white.png");
    }
};

#endif
