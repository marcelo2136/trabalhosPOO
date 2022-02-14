#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#include <iomanip>

const std::vector<float> ratios {20.f, 1.01f};

class Conta{
    std::string dono;
    int id;
protected:
    float balanco;
    std::string tipo;
public:
    Conta(int id, std::string dono){
        this->balanco = 0;
        this->id = id;
        this->dono = dono;

    }

    void deposito(float quantia){
        balanco += quantia;
    }

    void saque(float quantia){
        balanco -= quantia;
    }

    virtual void update(){
    }

    void transferencia(Conta * conta, float valor){
        saque(valor);
        conta->deposito(valor);
    }

    int getId(){
        return id;
    }
    float getBalanco(){
        return balanco;
    }
    std::string getCliente(){
        return dono;
    }
    std::string getTipo(){
        return tipo;
    }
    friend std::ostream& operator<<(std::ostream& os, Conta& conta){
        os << conta.id << ':' << conta.dono << ':' << conta.balanco << ':' << conta.tipo;
        return os;
    }

};

class ContaPoupanca : public Conta{
public:
    ContaPoupanca(int id, std::string dono) : Conta{id, dono}{
        tipo = "CP";
    }

    void update(){
        balanco *= ratios[1];
    }
};

class ContaCorrente : public Conta{
public:
    ContaCorrente(int id, std::string dono) : Conta{id, dono}{
        tipo = "CC";
    }

    void update(){
        balanco -= ratios[0];
    }
};

class Pessoa{
    std::map<int, Conta*> contas;
    std::string nome;
public:
    Pessoa(Conta * conta1, Conta * conta2, std::string nome){
        this->nome = nome;
        contas.insert(std::make_pair(contas.size(), conta1));
        contas.insert(std::make_pair(contas.size(), conta2));
    }

    friend std::ostream& operator<<(std::ostream& os, Pessoa& pessoa){
        os << "- " << pessoa.nome << " [";
        for (auto it : pessoa.contas){
            os << it.first;
            auto it2 = pessoa.contas.find(it.first);
            it2++;
            if(it2 != pessoa.contas.end())
                os << ", ";
        }
        os << ']';
        return os;
    }
};

class Banco{
    std::map<int, Conta*> contas;
    std::map<std::string, Pessoa*> clientes;
public:
    void criarCliente(std::string name){
        contas[(int)contas.size()] = new ContaCorrente ((int)contas.size(), name);
        contas[(int)contas.size()] = new ContaPoupanca ((int)contas.size(), name);
        clientes[name] = new Pessoa(contas[(int)contas.size()-2], contas[(int)contas.size()-1], name);

    }

    void depositar(int id, float quantia){
        auto it = contas.find(id);
        if (it==contas.end())
            std::cout << "FAIL: conta nao existe\n";
        else if (quantia < 0.f)
            std::cout << "FAIL: dinheiro negativo nao existe\n";
        else
            contas[id]->deposito(quantia);
    }

    void sacar(int id, float quantia){
        auto it = contas.find(id);
        if (it==contas.end())
            std::cout << "FAIL: conta nao existe\n";
        else if (it->second->getBalanco() < quantia)
            std::cout << "FAIL: saldo insuficiente\n";
        else if (quantia < 0.f)
            std::cout << "FAIL: dinheiro negativo nao existe\n";
        else
            contas[id]->saque(quantia);
    }

    void transferir(int id1, int id2, float quantia){
        auto it1 = contas.find(id1);
        auto it2 = contas.find(id2);
        if (it1==contas.end() || it2==contas.end())
            std::cout << "FAIL: conta nao encontrada\n";
        else if (it1->second->getBalanco() < quantia)
            std::cout << "FAIL: saldo insuficiente\n";
        else if (quantia < 0.f)
            std::cout << "FAIL: dinheiro negativo nao existe\n";
        else
            contas[id1]->transferencia(it2->second, quantia);
    }

    void update(){
        for (auto it : contas){
            it.second->update();
        }
    }

    friend std::ostream& operator<<(std::ostream& os, Banco& banco){
        os << "Clientes: \n";
        for (auto it : banco.clientes){
            os << it.second << '\n';
        }
        os << std::setprecision(2) << std::fixed;
        for (auto it : banco.contas){
            os << *it.second << '\n';
        }
        return os;
    }

};


int main(){
    Banco banco;

    while(true){
        std::string line;
        //std::getline(std::cin, line, '$');
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::string cmd;

        ss >> cmd;

        if (cmd == "add"){
            std::string name;
            ss >> name;
            banco.criarCliente(name);
        }
        else if (cmd == "deposito"){
            int id;
            float quantia;
            ss >> id;
            ss >> quantia;
            banco.depositar(id, quantia);
        }
        else if (cmd == "saque"){
            int id;
            float quantia;
            ss >> id;
            ss >> quantia;
            banco.sacar(id, quantia);
        }
        else if (cmd == "transf"){
            int id1, id2;
            float quantia;
            ss >> id1;
            ss >> id2;
            ss >> quantia;
            banco.transferir(id1, id2, quantia);
        }
        else if (cmd == "update"){
            banco.update();
        }
        else if (cmd == "show"){
            std::cout << banco;
        }
        else if (cmd == "end"){
            break;
        }
        else{
            std::cout << "comando nao existe" << '\n';
        }
    }


    return 0;
}

/*

V    Cadastrar um cliente com idCliente único
V        Quando o cliente é cadastrado no sistema, automaticamente é aberta uma conta corrente e uma conta poupança para ele.
V    Mensalmente:
V        Contas corrente vão receber uma tarifa de 20 reais podendo inclusive ficar negativas.
V        Contas poupança vão aumentar de 1 porcento.
V    Sua agência deve ter um mapa de clientes e um mapa de contas.
V    O cliente só tem duas contas, mas imagine que no futuro ele poderá ter várias.
V    As contas devem ser tratadas utilizando polimorfismo.
*/
