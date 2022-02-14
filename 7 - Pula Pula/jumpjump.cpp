#include <iostream>
#include <list>
#include <sstream>

class Kid{
    std::string name;
    int age;
public:
    Kid(std::string name, int age){
        this->name = name;
        this->age = age;
    }

    std::string getName(){
        return name;
    }

    friend std::ostream& operator<<(std::ostream& os, const Kid& kid){
        std::cout << kid.name << ':' << kid.age;
        return os;
    }
};

class Pulapula{
    std::list<Kid> fila;
    std::list<Kid> pulando;
public:
    void arrive(std::stringstream& ss){
        std::string nome;
        int idade;

        ss >> nome;
        ss >> idade;

        Kid crianca(nome, idade);
        fila.push_front(crianca);
    }

    void enter(){
        auto it = fila.end();
        it--;
        pulando.push_front(*it);
        fila.pop_back();
    }

    void leave(){
        auto it = pulando.end();
        it--;
        fila.push_front(*it);
        pulando.pop_back();
    }

    void rmChild(std::stringstream& ss){
        std::string name;
        bool found {false};
        ss >> name;

        std::list<Kid> novaFila;
        for (auto it = fila.begin(); it != fila.end(); it++){
            if(it->getName() != name){
                found = true;
                novaFila.push_back(*it);
            }
        }
        if (found == true)
            fila.swap(novaFila);
        else
            found = false;

        std::list<Kid> novaPulando;
        for (auto it = pulando.begin(); it != pulando.end(); it++){
            if(it->getName() != name){
                found = true;
                novaPulando.push_back(*it);
            }
        }
        if (found == true)
            pulando.swap(novaPulando);
        else
            std::cout << "crianca nao encontrada\n" ;
    }

    friend std::ostream& operator<<(std::ostream& os, const Pulapula& pula){
        std::cout << "=> ";
        for(auto it = pula.fila.begin(); it != pula.fila.end(); it++){
            std::cout << *it << ' ';
        }
        std::cout << " => ";

        std::cout << "[ ";
        for(auto it = pula.pulando.begin(); it != pula.pulando.end(); it++){
            std::cout << *it << ' ';
        }
        std::cout << "]\n";

        return os;
    }

};

int main(){
    Pulapula trampolin;
    while(true){
        std::string line;
        std::getline(std::cin, line, '$');
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::string cmd;

        ss >> cmd;

        if (cmd == "arrive"){
            trampolin.arrive(ss);
        }
        else if (cmd == "enter"){
            trampolin.enter();
        }
        else if (cmd == "leave"){
            trampolin.leave();
        }
        else if (cmd == "remove"){
            trampolin.rmChild(ss);
        }
        else if (cmd == "show"){
            std::cout << trampolin;
        }
        else if(cmd == "end"){
            break;
        }
        else{
            std::cout << "comando nao existe" << '\n';
        }
    }

    return 0;
}
