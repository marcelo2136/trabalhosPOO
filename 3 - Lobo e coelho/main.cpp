#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

void setSize(sf::Sprite& sprite, int width, int height){
    auto dim = sprite.getLocalBounds();
    sprite.setScale((float) width/dim.width, (float) height/dim.height);

}

struct object{
    int x {0};
    int y {0};
    int step {0};
    sf::Sprite sprite;

    object (int x, int y, int step, sf::Texture& texture):
        x {x}, y {y}, step{step}, sprite(texture){

    }
    void draw(sf::RenderWindow& app){
        this->sprite.setPosition(x*step, y*step);
        setSize(this->sprite, step, step);
        app.draw(this->sprite);
    }
};

sf::Texture LoadTexture(std::string origem){

    sf::Texture texture;
    if (!texture.loadFromFile(origem)){
        std::cout << "Textura nao foi carregada" << '\n';
        exit(1);
    }
    return texture;
}

void moveObject(sf::Keyboard::Key key, object& entity, std::vector<sf::Keyboard::Key> move_keys){

    if (key == move_keys[0]){
        entity.x--;
    }
    else if (key == move_keys[1]){
        entity.y--;
    }
    else if (key == move_keys[2]){
        entity.x++;
    }
    else if (key == move_keys[3]){
        entity.y++;
    }

}

struct Board{
    int linhas {0};
    int colunas {0};
    int step {0};
    sf::Sprite sprite;
    sf::RectangleShape rect;

    Board (int x, int y, int step, sf::Texture& texture):
        linhas {x}, colunas {y}, step{step}, sprite(texture){

        this->rect.setSize(sf::Vector2f(step, step));
        this->rect.setFillColor(sf::Color::Transparent);
        this->rect.setOutlineColor(sf::Color::White);
        this->rect.setOutlineThickness(2);
    }
    void draw(sf::RenderWindow& app){

        auto dim = app.getSize();

        setSize(this->sprite, dim.x, dim.y);
        app.draw(this->sprite);

        for (int i = 0; i < colunas; i++) {
            for (int j = 0; j < linhas; j++) {
                rect.setPosition(i * step, j * step);
                app.draw(rect);
            }
        }

    }
};

int main()
{
    const int STEP {100};

    sf::Texture lobinho(LoadTexture("lobo.png"));
    object lobo(1, 1, STEP, lobinho);

    sf::Texture coeio(LoadTexture("coelho.png"));
    object coelho(5, 3, STEP, coeio);

    sf::Texture grass(LoadTexture("fundo.jpg"));
    Board fundo(6, 8, STEP, grass);



    sf::RenderWindow app(sf::VideoMode(STEP*fundo.colunas, STEP*fundo.linhas), "SFML window");



    while (app.isOpen())
    {
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();
            else if (event.type == sf::Event::KeyPressed) {
                moveObject(event.key.code, lobo, {sf::Keyboard::A, sf::Keyboard::W, sf::Keyboard::D, sf::Keyboard::S});
                moveObject(event.key.code, coelho, {sf::Keyboard::Left, sf::Keyboard::Up, sf::Keyboard::Right, sf::Keyboard::Down});
            }
        }


        app.clear();
        fundo.draw(app);
        lobo.draw(app);
        coelho.draw(app);
        app.display();
    }

    return EXIT_SUCCESS;
}
