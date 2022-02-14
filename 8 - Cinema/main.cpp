#include <iostream>
#include <list>
#include <sstream>

class Pessoa{
    std::string name;
    int id;
public:
    Pessoa(std::string name = "", int id = -1){
        this->name = name;
        this->id = id;
    }

    int getId() const{
        return id;
    }

   std::string getName() const{
        return name;
    }

    friend std::ostream& operator<<(std::ostream& os, const Pessoa& pessoa){
        std::cout << pessoa.name << ':' << pessoa.id;
        return os;
    }

    Pessoa operator=(Pessoa& pessoa){
        Pessoa returned("", 0);
        returned.name = pessoa.name;
        returned.id = pessoa.id;
        return returned;
    }

};

class Sala{
    std::list<std::pair<int, Pessoa>> sala;
    int tamanho;
public:
    Sala(int tamanho){

        this->tamanho = tamanho;
        Pessoa ps;
        for(int i = 0; i < tamanho; i++){
            auto it = sala.begin();
            advance(it, i);
            sala.emplace(it, std::make_pair(i, ps));
            }
    }

    void setSize(int size){
        if (size > 1){
        tamanho = size;
        Pessoa ps;
        for(int i = 0; i < size; i++){
            auto it = sala.begin();
            advance(it, i);
            sala.emplace(it, std::make_pair(i, ps));
            }
        }else{
            std::cout << "FAIL: Tamanho de sala invalido\n";
        }
    }

    void addPessoa(std::stringstream& ss){
        std::string name;
        int id, place;
        ss >> name;
        ss >> id;
        ss >> place;
        Pessoa cliente(name, id);


        auto it = sala.begin();
        advance(it, place);
        bool nameCheck {false};

        for(auto it : sala){
            if(it.second.getName() == name)
                nameCheck = true;
        }
        if(tamanho == 0){
            std::cout << "FAIL: Sala nao foi criada\n";
        }else if (it->second.getId() > 0){
            std::cout << "FAIL: Cadeira ocupada\n";
        }else if(nameCheck == true){
            std::cout << "FAIL: Cliente ja esta na sala\n";
        }else if (place > tamanho || place < 0){
            std::cout << "FAIL: Cadeira invalida\n";
        }else if(id < 0){
            std::cout << "FAIL: ID invalido (negativo)\n";
        }else{

        std::list<std::pair<int, Pessoa>> sala2;

        for (int i = 0; i < tamanho; i++){
            auto it = sala.begin();
            advance(it, i);
            if(i == place)
                sala2.push_back(std::make_pair(i, cliente));
            else
                sala2.push_back(*it);
            }

        sala.swap(sala2);

        }
    }

    void rmPessoa(std::stringstream& ss){
        std::string name;
        ss >> name;
        Pessoa ps;
        bool isPresent {false};

        for(auto it : sala){
            if(it.second.getName() == name){
                isPresent = true;
            }
        }

        if(isPresent == true){
            std::list<std::pair<int, Pessoa>> sala2;

            for (int i = 0; i < tamanho; i++){
                auto it = sala.begin();
                advance(it, i);
                if(it->second.getName() != name){
                    sala2.push_back(*it);
                }else{
                    sala2.push_back(std::make_pair(i, ps));
                }
            }
            sala.swap(sala2);
            }else{
                std::cout << "FAIL: Nome nao encontrado\n";
                }

    }

    friend std::ostream& operator<<(std::ostream& os, const Sala& cine){
        std::cout << "[ ";
        for(int i = 0; i < cine.tamanho; i++){
            auto it = cine.sala.begin();
            advance(it, i);
            if(it->second.getId() > 0 && it->first == i)
                std::cout << it->second << ' ';
            else
                std::cout << "- ";
        }
        std::cout << "]\n";
        return os;
    }

};


int main(){
Sala sala(0);
    while(true){
        std::string line;
        std::getline(std::cin, line, '$');
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::string cmd;

        ss >> cmd;

        if (cmd == "init"){
            int tamanho;
            ss >> tamanho;
            sala.setSize(tamanho);
        }
        else if (cmd == "reservar"){
            sala.addPessoa(ss);
        }
        else if (cmd == "cancela"){
            sala.rmPessoa(ss);
        }
        else if (cmd == "show"){
            std::cout << sala;
        }
        else{
            std::cout << "comando nao existe" << '\n';
        }
    }

    return 0;
}
