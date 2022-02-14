#include <iostream>
#include <stdlib.h>
#include <time.h>

class Veiculo{
protected:
    int rodas;
    bool motorizado; //se 1 usa tracao motorizada, se 0 tracao animal
    int potencia;
    bool operacional;
public:
    Veiculo(int rodas, bool motorizado, int potencia){
        this->rodas = rodas;
        this->motorizado = motorizado;
        this->operacional = true;
        if (motorizado == false && potencia > 5)
            this->potencia = 5;
        else
            this->potencia = potencia;
    }

    virtual void trocarRodas(){
        std::cout << "Foram gastos " << rodas*2.5 << " minutos para trocar todas as rodas\n";
    }

    virtual void acelerar(){
        if(operacional == true)
            std::cout << "Acelerando...\n";
        else
            std::cout << "Veiculo nao esta operacional\n";
    }

    virtual void quebrar(){
        operacional = false;
        std::cout << "Veiculo quebrou\n";
    }

    virtual void consertar(){
        operacional = true;
        std::cout << "Veiculo consertado\n";
    }

    friend std::ostream& operator<<(std::ostream& os, Veiculo& veiculo){
        std::cout << "|| Veiculo de " << veiculo.rodas << " rodas com " << veiculo.potencia << " HP,";
        if (veiculo.motorizado == 0)
            std::cout << " de tracao animal.";
        else
            std::cout << " motorizado.";
        if (veiculo.operacional == 1)
            std::cout << " Funcionando normalmente ||\n";
        else
            std::cout << " Atualmente quebrado ||\n";
        return os;
    }
};

class Carro : public Veiculo{
protected:
    int assentos;
    std::string modelo;
    std::string marca;
    int portas;
    int marchas;
    int marchaAtual {0}; //0 é neutro;
public:
    Carro(int assentos, std::string modelo, std::string marca, int potencia, int portas = 1, int marchas = 1) : Veiculo(4, 1, potencia){
        this->assentos = assentos;
        this->modelo = modelo;
        this->marca = marca;
        if (portas > 0)
            this->portas = portas;
        else
            std::cout << "Acho que voce precisa de portas para entrar ;)\n";
        if (marchas > 0)
            this->marchas = marchas;
        else
            std::cout << "Acho que o carro precisa de marchas para funcionar ;)\n";
    }

    virtual void acelerar(){
        if (operacional == false)
            std::cout << modelo << " nao esta operacional para acelerar\n";
        else if (marchaAtual == 0)
            std::cout << "Engate a primeira marcha\n";
        else
            std::cout << "Acelerando "<< modelo <<  "...\n";
    }

    virtual void quebrar(){
        operacional = false;
        std::cout << modelo << " quebrou.\n";
    }

    virtual void consertar(){
        operacional = true;
        std::cout << modelo << " consertado.\n";
    }

    void passarMarcha(){
        if (marchaAtual < marchas){
            marchaAtual++;
            std::cout << "Passando a marcha...\n";
        }
    }

    void descerMarcha(){
        if (marchaAtual > 0){
            marchaAtual--;
            std::cout << "Descendo a marcha...\n";
        }
    }

    void printMarcha() const{
        if (marchaAtual == 0){
            std::cout << "Neutro\n";
        }
        else
            std::cout << marchaAtual << "a Marcha\n";
    }

    friend std::ostream& operator<<(std::ostream& os, Carro& carro){
        std::cout << "|| " << carro.marca << ' ' << carro.modelo << " - " << carro.potencia << " HP, " << carro.marchas << " Marchas, " << carro.portas << " Portas, " << carro.assentos << " Assentos.";
        if (carro.operacional == 1)
            std::cout << " Funcionando normalmente ||\n";
        else
            std::cout << " Atualmente quebrado ||\n";
        return os;
    }

};

class CarroDeCorrida : public Carro{
    int potenciaTurbo;
    std::string piloto;
    int numPiloto;
public:
    CarroDeCorrida(int potenciaTurbo, std::string piloto, int numPiloto, std::string modelo, std::string marca, int potencia, int portas = 1, int marchas = 1) : Carro{1, modelo, marca, potencia, portas, marchas} {
        this->potenciaTurbo = potenciaTurbo;
        this->piloto = piloto;
        this->numPiloto = numPiloto;
        if(portas > 2){
            std::cout << "Carros de corrida nao tem mais que duas portas\n";
        }
    }

    void usarTurbo(){
        std::cout << "Turbo Ativado: mais " << potenciaTurbo << " cavalos de potencia\n";
    }

    void trocarRodas(){
        srand(time(NULL));
        int time = rand()% 8 + 3;
        std::cout << "Pitstop: pneus trocados em " << time << " segundos\n";
    }

    void trocarPiloto(std::string nome, int num){
        std::cout << "TROCA DE PILOTOS: Sai " << piloto << " #" << numPiloto << " e entra " << nome << " #" << num << '\n';
        piloto = nome;
        numPiloto = num;
    }

    friend std::ostream& operator<<(std::ostream& os, CarroDeCorrida& carro){
        std::cout << "|| " << carro.marca << ' ' << carro.modelo << " - " << carro.potencia << " HP, com turbo de " << carro.potenciaTurbo << "HP. " << carro.marchas << " Marchas, Pilotado por " << carro.piloto << " #" << carro.numPiloto << '.';
        if (carro.operacional == 1)
            std::cout << " Funcionando normalmente ||\n";
        else
            std::cout << " Atualmente quebrado ||\n";
        return os;
    }

};


int main(){
    Veiculo carroca(2, 0, 2);
    std::cout << carroca;
    carroca.acelerar();
    carroca.quebrar();
    carroca.acelerar();
    carroca.trocarRodas();
    carroca.acelerar();
     std::cout << "\n\n";

    Carro corsinha(4, "Corsa", "Chevrolet", 102, 4, 5);
    std::cout << corsinha;
    corsinha.acelerar();
    corsinha.passarMarcha();
    corsinha.acelerar();
    corsinha.acelerar();
    corsinha.quebrar();
    corsinha.acelerar();
    corsinha.consertar();
    corsinha.trocarRodas();
    corsinha.passarMarcha();
    corsinha.printMarcha();
    corsinha.quebrar();
    std::cout << corsinha << "\n\n";

    CarroDeCorrida ferrari(20, "Tilapia Veloz", 66, "488 GTE", "Ferrari", 600, 2, 7);
    std::cout << ferrari;
    ferrari.passarMarcha();
    ferrari.passarMarcha();
    ferrari.passarMarcha();
    ferrari.acelerar();
    ferrari.trocarRodas();
    ferrari.trocarPiloto("Alexandre Paulera", 10);
    ferrari.acelerar();
    ferrari.usarTurbo();
    ferrari.descerMarcha();
    ferrari.quebrar();
    std::cout << ferrari << "\n\n";
}
