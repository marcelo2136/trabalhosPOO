#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>
#include <thread>

struct Pincel{
    sf::Font font;
    sf::Text text;
    sf::RenderWindow& window;

    Pincel(sf::RenderWindow& window) : window{window}{
        if (!font.loadFromFile("coolvetica rg.ttf")){
                std::cout << "Fail to load font" << '\n';
            }
        text.setFont(font);
        }

        void write(std::string str, int x, int y, int size, sf::Color color){
            text.setString(str);
            text.setCharacterSize(size);
            text.setPosition(x, y);
            text.setFillColor(color);
            window.draw(text);
        }
};

struct Bubble{
    static const int radius {10};
    int x;
    int y;
    char letter;
    int speed;
    bool alive {true};

    Bubble(int x, int y, char letter, int speed): x{x}, y{y}, letter{letter}, speed{speed} {
    }

    void update(){
        this->y += this->speed;
    }

    void draw(sf::RenderWindow& window){
        sf::CircleShape bubble (Bubble::radius);
        bubble.setPosition(x, y);
        bubble.setFillColor(sf::Color::White);
        window.draw(bubble);
        static Pincel pencil(window);
        pencil.write(std::string(1, letter), x + 0.2 * Bubble::radius, y, Bubble::radius *1.5, sf::Color::Blue );

    }

};

struct Board{
    sf::RenderWindow& window;
    std::vector<Bubble> bubbles;
    Pincel pincel;
    int hits {0};
    int misses {0};

    Board(sf::RenderWindow& window) : window(window), pincel(window){
        //bubbles.push_back(Bubble(100, 100, 'A', 1));
        //bubbles.push_back(Bubble(200, 100, 'B', 2));
        //bubbles.push_back(Bubble(300, 100, 'C', 3));
    }

    void update(){
        if (this->checkNewLetter())
            this->add_new_bubble();

        for (Bubble& bubble : bubbles){
            bubble.update();
        }
        this->bolha_fora();
        this->remove_mortas();
    }

    void add_new_bubble(){
        int x = rand() % ((int) this->window.getSize().x - 2*Bubble::radius);
        int y = -2 * Bubble::radius;
        int speed = rand() % 3 + 1;
        char letter = rand() % 26 + 'A';
        bubbles.push_back(Bubble(x, y, letter, speed));
    }

    void draw(){
        pincel.write("Hits: " + std::to_string(this->hits) + "   Misses: " + std::to_string(this->misses), 10, 10, 30, sf::Color::White);
        pincel.write("Size: " + std::to_string(this->bubbles.size()), 10, 40, 20, sf::Color::White);
        for (Bubble& bubble : bubbles){
            bubble.draw(window);
        }
    }

    void remove_mortas(){
        std::vector<Bubble> vivas;
        for(Bubble& bubble : bubbles){
            if(bubble.alive)
                vivas.push_back(bubble);
        }
        this->bubbles = vivas;
    }

    bool checkNewLetter(){
        static const int new_bubble_timeout {30};
        static int new_bubble_timer {0};

        new_bubble_timer--;

        if(new_bubble_timer <= 0){
            new_bubble_timer = new_bubble_timeout;
            return true;
        }else{
            return false;
        }

    }

    void bolha_fora(){
        for(Bubble& bubble : bubbles){
            if(bubble.y + 2 * Bubble::radius > (int) this->window.getSize().y){
                if(bubble.alive){
                bubble.alive = false;
                this->misses++;
                }
            }
        }
    }

    void acerto(char letter){
        for(Bubble& bubble : bubbles){
            if(bubble.letter == letter){
                bubble.alive = false;
                this->hits++;
                break;
            }


        }


    }
};

struct Game{
    sf::RenderWindow window;
    Board board;
    std::function<void()> on_update;

    Game() : window(sf::VideoMode(800, 600), "digitação"), board(window){
        this->on_update = [&](){
            this->gameplay();
        };
        window.setFramerateLimit(60);
    }

    void process_events(){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }else if(event.type == sf::Event::TextEntered){
                char code = static_cast<char>(event.text.unicode);
                code = toupper(code);
                board.acerto(code);
            }
        }
    }

    void gameplay(){
        board.update();
        window.clear(sf::Color::Black);
        board.draw();
        window.display();
        if (board.misses > 15){
            this->on_update = [&](){
            this->game_over();
        };
        }
    }

    void game_over(){
        static Pincel pincel(window);
        window.clear(sf::Color::Red);
        pincel.write("Game Over", 250, 250, 60, sf::Color::White);
        window.display();

    }

    void mainLoop(){
        while (window.isOpen()){
            process_events();
            on_update();
        }
    }
};



int main(){
    Game game;
    game.mainLoop();
    return 0;
}
