//
// Created by Adis Veletanlic on 11/3/23.
//

#include "Game.h"
#include "Piece/Knight/Knight.h"
#include "Piece/Piece.h"
#include "Piece/Queen/Queen.h"
#include "Piece/Rook/Rook.h"
#include "Piece/Bishop/Bishop.h"
#include "Piece/Pawn/Pawn.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

void Game::Run() {
    while (windowManager.getWindow().isOpen()) {
        windowManager.getWindow().clear();
        while (const std::optional event = windowManager.getWindow().pollEvent()) {
          if (event->is<sf::Event::Closed>()) {
              windowManager.getWindow().close();
          } if (event->is<sf::Event::Resized>()) {
            windowManager.resizeWindow();
          }
          HandleEvent(event);
        }
        Render();
    }
}

void Game::HandleEvent(const std::optional<sf::Event> event) {
    if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
          auto windowSize = windowManager.getWindow().getSize();

          int scaledX = (mouseButtonPressed->position.x * 800) / windowSize.x;
          int scaledY = (mouseButtonPressed->position.y * 800) / windowSize.y;

          int boardX = std::max(0, std::min(7, scaledX / SQUARE_SIZE));
          int boardY = std::max(0, std::min(7, scaledY / SQUARE_SIZE));

          this->StartDragging({boardX, boardY});
        }
    } else if (const auto* mouseButtonReleased = event->getIf<sf::Event::MouseButtonReleased>()) {
      if (mouseButtonReleased->button == sf::Mouse::Button::Left) {
        auto windowSize = windowManager.getWindow().getSize();

        int scaledX = (mouseButtonReleased->position.x * 800) / windowSize.x;
        int scaledY = (mouseButtonReleased->position.y * 800) / windowSize.y;

        int boardX = std::max(0, std::min(7, scaledX / SQUARE_SIZE));
        int boardY = std::max(0, std::min(7, scaledY / SQUARE_SIZE));

        this->StopDragging({boardX, boardY});
      }
    } else if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>()) {
      if (this->gameState.isDragging) {
        auto windowSize = windowManager.getWindow().getSize();

        int scaledX = (mouseMoved->position.x * 800) / windowSize.x;
        int scaledY = (mouseMoved->position.y * 800) / windowSize.y;

        this->UpdateDragging({scaledX, scaledY});
      }
    }
}

void Game::HandleLeftMouseClick(Position position) {
    auto currentPlayer = this->gameState.CurrentPlayer();
    auto playerTurn = this->gameState.GetPlayerTurn();
    auto clickedPiece = this->gameState.GetBoard()->GetPieceAt(position);

    if (currentPlayer->HasSelectedPiece()) {
        auto selectedPiece = currentPlayer->GetSelectedPiece(*this->gameState.GetBoard()).value();

        if (selectedPiece->GetPosition() == position) {
            currentPlayer->DeselectPiece();
        }
        else if (clickedPiece && clickedPiece->GetColor() == playerTurn) {
            currentPlayer->SelectPiece(position, *this->gameState.GetBoard(), this->moveManager.GetLastMove());
        }
        else {
            this->ExecuteMove(position);
        }
    }
    else if (clickedPiece && clickedPiece->GetColor() == playerTurn) {
        currentPlayer->SelectPiece(position, *this->gameState.GetBoard(), this->moveManager.GetLastMove());
    }
}


bool Game::ExecuteMove(Position position) {
    auto currentPlayer = this->gameState.CurrentPlayer();
    auto selectedPiece = currentPlayer->GetSelectedPiece(*this->gameState.GetBoard());
    if (selectedPiece && this->gameState.IsLegalMove(position, selectedPiece.value())) {
        if (const auto& move = currentPlayer->CanMovePieceTo(position)) {
            this->moveManager.ExecuteMove(*move);
            this->gameState.ExecuteMove(*move);
            this->gameState.ChangePlayerTurn();
            return true;
        }
    }
    return false;
}

void Game::RenderBoard() {
    this->gameState.UpdateBoard(this->windowManager.getWindow(), this->gameState.GetAvailableMovesCurrentPlayer(), this->gameState.GetCurrentPlayerSelectedPiece());
}

void Game::Render() {
    this->windowManager.getWindow().clear();
    RenderBoard();

    auto draggedPiece = this->gameState.CurrentPlayer()->GetSelectedPiece(*this->gameState.GetBoard());
    if (this->gameState.isDragging && draggedPiece.has_value()) {
        draggedPiece.value()->Render(this->windowManager.getWindow());
    }

    this->windowManager.getWindow().display();
}

void Game::StartDragging(sf::Vector2i position) {
    auto currentPlayer = this->gameState.CurrentPlayer();
    auto piece = this->gameState.GetBoard()->GetPieceAt(position);

    if (piece && piece->GetColor() == this->gameState.GetPlayerTurn()) {
        this->gameState.isDragging = true;
        currentPlayer->SelectPiece(position, *this->gameState.GetBoard(), this->moveManager.GetLastMove());

        auto selectedPiece = currentPlayer->GetSelectedPiece(*this->gameState.GetBoard());

        if (selectedPiece.has_value()) {
            selectedPiece.value()->SetIsDragged(true);
        }
    }
}

void Game::StopDragging(Position position) {
    auto currentPlayer = this->gameState.CurrentPlayer();
    auto playerSelectedPiece = currentPlayer->GetSelectedPiece(*this->gameState.GetBoard())->get();

    if (this->gameState.isDragging && playerSelectedPiece && currentPlayer->CanMovePieceTo(position)) {
        Position boardPosition = {position.x, position.y};
        if (this->ExecuteMove(boardPosition)) {
            playerSelectedPiece->SetLogicalPosition(position);
        }
        playerSelectedPiece->UpdateVisualPositionFromLogical();
        playerSelectedPiece->SetIsDragged(false);

    } else if (playerSelectedPiece) {
        currentPlayer->DeselectPiece();
        playerSelectedPiece->UpdateVisualPositionFromLogical();
        playerSelectedPiece->SetIsDragged(false);
    }
    this->gameState.isDragging = false;
}

void Game::UpdateDragging(sf::Vector2i position) {
    auto newPosition = sf::Vector2f(position);
    this->gameState.CurrentPlayer()->GetSelectedPiece(*this->gameState.GetBoard())->get()->SetVisualPosition(newPosition);
}
