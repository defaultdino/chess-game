//
// Created by Adis Veletanlic on 11/2/23.
//
#ifndef CHESSGAME_PIECE_H
#define CHESSGAME_PIECE_H

#include "PlayerColor.h"
#include "../Player/Move.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics.hpp>
#include "../ResourceManager/ResourceManager.h"

class Board;
const int SQUARE_SIZE = 100;
using Position = sf::Vector2i;

enum class PieceType {
    Pawn, Rook, Knight, Bishop, Queen, King
};

class Piece {
private:
    PieceType type;
    Position position;
    PlayerColor color;
    sf::Sprite sprite;

    std::string getTextureKey() const {
        std::string colorStr = (color == PlayerColor::Black) ? "black" : "white";
        std::string typeStr;
        switch (type) {
            case PieceType::Pawn: typeStr = "pawn"; break;
            case PieceType::Rook: typeStr = "rook"; break;
            case PieceType::Knight: typeStr = "knight"; break;
            case PieceType::Bishop: typeStr = "bishop"; break;
            case PieceType::Queen: typeStr = "queen"; break;
            case PieceType::King: typeStr = "king"; break;
        }
        return colorStr + "_" + typeStr;
    }

protected:
    bool currentlyDragged = false;

public:
    virtual ~Piece() = default;

    Piece(Position position, PlayerColor color, PieceType type)
        : position(position), color(color), type(type), sprite(ResourceManager::GetInstance().GetTexture(getTextureKey())) {
        auto& texture = sprite.getTexture();
        sprite.setOrigin({(float)texture.getSize().x / 2, (float)texture.getSize().y / 2});
        sprite.setPosition({(float)position.x * SQUARE_SIZE + 50, (float)position.y * SQUARE_SIZE + 50});
    }

    virtual std::vector<Move> AvailableMoves(const Board& board, const std::optional<Move>& lastMove) const = 0;

    std::vector<Move> FindMovesInDirectionForPiece(int rowIncrement, int colIncrement, const Board& board) const;

    Position GetPosition() const { return position; }
    PlayerColor GetColor() const { return color; }
    PieceType GetType() const { return type; }
    void SetLogicalPosition(const Position& newPosition) { position = newPosition; }
    void SetVisualPosition(const sf::Vector2f& newPosition) { sprite.setPosition(newPosition); }
    void Render(sf::RenderWindow& window) const {
        window.draw(sprite);
    }
    void UpdateVisualPositionFromLogical() {
        sprite.setPosition({(float)position.x * SQUARE_SIZE + 50, (float)position.y * SQUARE_SIZE + 50});
    }
    void SetIsDragged(bool isDragged) { currentlyDragged = isDragged; }
    bool IsDragged() { return currentlyDragged; }

    // Optional: For pawn promotion or type changes
    void setPieceType(PieceType newType) {
        type = newType;
        sprite.setTexture(ResourceManager::GetInstance().GetTexture(getTextureKey()));
    }
};

#endif
