#include <iostream>
#include <vector>

//FUNÇÕES DE BUSCA
// Função que verifica a existência
bool exist(std::vector<int> vet, int numb){
    bool existe {false};

    for(int i = 0; i < vet.size(); i++){
        if(vet[i] == numb){
            existe = true;
        }
    }
    return existe;
}

//Função que verifica a quantidade
int quant(std::vector<int> vet, int numb){
    int quantidade {0};

    for(int i = 0; i < vet.size(); i++){
        if(vet[i] == numb){
            quantidade++;
        }
    }
    return quantidade;
}

//Função que faz a busca de um valor (retorna a posição)
int proc_valor(std::vector<int> vet, int numb){
    int pos {-1};

    for(int i = 0; i < vet.size(); i++){
        if(vet[i] == numb){
            pos = i;
            break;
        }
    }
    return pos;
}

//Função que faz a busca de um valor a partir de determinada posição (retorna a posição)
int proc_valor_por_posicao(std::vector<int> vet, int numb, int inicio){
    int pos {-1};

    for(int i = inicio; i < vet.size(); i++){
        if(vet[i] == numb){
            pos = i;
            break;
        }
    }
    return pos;
}


//FUNÇÕES DE MELHOR CASO
//Função que procura o menor valor
int menor_valor(std::vector<int> vet){
    int small {0};

    for(int i = 0; i < vet.size(); i++){
        if(i == 0){
            small = vet[i];
            }
        if(vet[i] < small && i > 0){
            small = vet[i];
            }
    }
    return small;
}

//Retorna a posição do menor valor
int menor_valor_pos(std::vector<int> vet){
    int small {0};

    
    for(int i = 0; i < vet.size(); i++){
        if(i == 0){
            small = i;
            }
        if(vet[i] < vet[small] && i > 0){
            small = i;
            }
    }
    return small;
}

//Retorna posição do menor valor (com posição inicial)
int menor_valor_pos_com_inicio(std::vector<int> vet, int inicio){
    int small {0};

    for(int i = inicio; i < vet.size(); i++){
        if(i == inicio){
            small = i;
            }
        if(vet[i] < vet[small] && i > 0){
            small = i;
            }
    }
    return small;
}

//Retorna homem mais calmo
int homem_mais_calmo(std::vector<int> vet){
    int small {-1};
    bool man {false};
    
    for(int i = 0; i < vet.size(); i++){
        if (vet[i] > 0 && man == false){
            small = i;
            man = true;
        }
        if(vet[i] < vet[small] && vet[i] > 0){
            small = i;
            }
    }
    return small;
}

int main() {

    //std::cout << exist({-1, 1, 2}, 2) << '\n';
    //std::cout << quant({-1, 1, 2}, 2) << '\n';
    //std::cout << proc_valor({-1, 1, 2, 3}, 1) << '\n';
    //std::cout << proc_valor_por_posicao({-1, 1, 2}, 1, 0) << '\n';

    //std::cout << menor_valor({-1, -3, 1, -12}) << '\n';
    //std::cout << menor_valor_pos({-1, -10, 1, -12}) << '\n';
    //std::cout << menor_valor_pos_com_inicio({-1, -99, 1, -12}, 0) << '\n';
    //std::cout << homem_mais_calmo({-1, 3, 14, -12}) << '\n';
    
    return 0;
}
