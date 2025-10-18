#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Window/WindowBase.hpp>

class WindowManager {
public:
    WindowManager() {
      window.create(sf::VideoMode({800, 800}), "Chess", sf::Style::Titlebar | sf::Style::Close);
      resizeWindow();
    }
    sf::RenderWindow& getWindow() { return window; }

    void resizeWindow() {
      auto view = window.getDefaultView();
      auto size = window.getSize();
      view.setSize({
        static_cast<float>(size.x),
        static_cast<float>(size.y)
      });
      window.setView(view);
    }

    bool isOpen() const { return window.isOpen(); }
private:
    sf::RenderWindow window;
};
