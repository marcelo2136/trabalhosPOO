#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>

bool validate(std::string number){
    std::vector<char> accepted {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '(', ')', '.'};
    bool check {true};

    if((int)number.size() == 0)
        return false;

    for(int i = 0; i < (int)number.size(); i++){
        int check1 = 0;
        for(int j = 0; j < (int)accepted.size(); j++){
            if(number[i] != accepted[j])
                check1++;
        }
        if(check1 == (int)accepted.size()){
            check = false;
            return check;
        }
    }
    return check;
}


class Fone{
    private:
        int id;
        std::string label;
        std::string number;

    public:
        Fone(int id, std::string label = "", std::string number = ""){
            this->id = id;
            this->label = label;
            this->number = number;
        }

        int getId(){
            return id;
        }

        void setId(int newId){
            this->id = newId;
        }


         Fone operator=(Fone& fone){
            Fone fone_ret(0, "", "");
            fone_ret.id = fone.id;
            fone_ret.label = fone.label;
            fone_ret.number = fone.number;

            return fone_ret;
         }

         friend std::ostream& operator<<(std::ostream& os, Fone& fone){
            os << '[' << fone.id << ':' << fone.label << ':' << fone.number << ']';
            return os;
         }

};

class Contact {
    private:
        std::string nome;
        std::vector<Fone> fones;

    protected:
        std::string prefix = "-";

    public:
        Contact(std::string nome = ""){
            this->nome = nome;

        }



        bool addFone(int cont_size2, std::string label, std::string numb){
            if (validate(numb)!=false){
            Fone fone(cont_size2, label, numb);
            this->fones.push_back(fone);
            //std::cout << fones[cont_size2] << '\n';
            return true;
            }else{
                std::cout << "NUMERO INVALIDO" << '\n';
                return false;
            }
        }


        void rmFone(int index){
            std::vector<Fone> fone_aux;
            for(int i = 0; i < (int)fones.size(); i++){
                if(i != index)
                    fone_aux.push_back(fones[i]);
                if(i > index)
                fone_aux[i-1].setId(i-1);
            }
            fones.swap(fone_aux);
        }

        int getSize(){
            return (int)fones.size();
        }

        void printContact(){
            std::cout << prefix << ' ';
            std::cout << nome << ' ';
            for(int i = 0; i < (int)fones.size(); i++){
                std::cout << fones[i] << ' ';
                }
            std::cout << '\n';
        }

         Contact operator=(Contact& contact){
            Contact contact_ret("");
            contact_ret.nome = contact.nome;

            return contact_ret;
         }

};



int main(){

    std::vector<Contact> contacts;
    int cont_size {0};
    int cont_size2 {0};

    while(true){
        std::string line;
        std::getline(std::cin, line, '$');
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::string cmd;
        ss >> cmd;
        if (cmd == "init"){
            std::string name;
            ss >> name;
            Contact newContact(name);

            contacts.push_back(newContact);
            cont_size++;
        }
        else if (cmd == "add"){
            bool add;
            std::string label;
            std::string numb;
            ss >> label;
            ss >> numb;
            add = contacts[cont_size-1].addFone(cont_size2, label, numb);
            if(add == true)
            cont_size2++;

        }
        else if (cmd == "rm"){
            int index;
            ss >> index;
            contacts[cont_size-1].rmFone(index);
        }
        else if (cmd == "show"){
            contacts[cont_size-1].printContact();
        }
        else if(cmd == "end"){
            break;
        }
        else{
            std::cout << "comando nao existe" << '\n';
        }

    }

}
