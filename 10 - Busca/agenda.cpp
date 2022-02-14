#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <list>
#include <cstring>

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

        std::string getLabel(){
            return label;
        }

        std::string getNumber(){
            return number;
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

        operator std::string() const{
            std::string str =  '[' + std::to_string(id) + ':' + label + ':' + number + ']';
            return str;
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

        std::string getName (){
            return nome;
        }

        friend std::ostream& operator<<(std::ostream& os, Contact& contact){
            std::cout << contact.prefix << ' ';
            std::cout << contact.nome << ' ';
            for(int i = 0; i < (int)contact.fones.size(); i++){
                std::cout << contact.fones[i] << ' ';
                }
            std::cout << '\n';
            return os;
        }

        operator std::string() const{
            std::string str = prefix + ' ' + nome + ' ';
            for(int i = 0; i < (int)fones.size(); i++){
                str += fones[i];
                str += ' ';
                }
            str += '\n';
            return str;
        }

        Contact operator=(Contact& contact){
            Contact contact_ret("");
            contact_ret.nome = contact.nome;

            return contact_ret;
         }

};

class Agenda {
    std::vector<Contact> agenda;

public:
    void addContact(std::stringstream& ss){
        std::string label, numb, name, token;
        ss >> name;
        std::vector<Fone> fones;
        while(!ss.eof()){
            ss >> token;
            std::stringstream ss2(token);
            getline(ss2, label, ':');
            if(!ss2.eof()){
                getline(ss2, numb);
                Fone fone(fones.size(), label, numb);
                fones.push_back(fone);
            }
        }
        bool found {false};
        for(int i = 0; i < (int)agenda.size(); i++){
            if(agenda[i].getName() == name){
                found = true;
                for(int i = 0; i < (int)fones.size(); i++){
                    agenda[i].addFone(agenda[i].getSize(), fones[i].getLabel(), fones[i].getNumber());
                }
            }
        }
        if (found == false){
            Contact cont(name);

            for(int i = 0; i < (int)fones.size(); i++){
                cont.addFone(cont.getSize(), fones[i].getLabel(), fones[i].getNumber());
            }
            if(agenda.size() == 0)
                agenda.push_back(cont);
            else
                insertInPos(cont);



        }
    }

    void insertInPos(Contact cont){
        std::vector<Contact> agendaNova;
        bool check {false};
        for(int i = 0; i < (int)agenda.size(); i++){
            if(agenda[i].getName().compare(cont.getName()) > 0 && check == false){
                agendaNova.push_back(cont);
                agendaNova.push_back(agenda[i]);
                check = true;
            }else{
                agendaNova.push_back(agenda[i]);
            }
        }
        if(check == false){
            agendaNova.push_back(cont);
        }

        agenda.swap(agendaNova);
    }

    void searchContact(std::string patern){
        for (auto cont : agenda){
            std::string strg;
            strg += cont;
            if(strg.find(patern) != std::string::npos){
                std::cout << cont;
            }
        }
    }

    void rmContact(std::stringstream& ss){
        std::vector<Contact> new_agenda;
        std::string key;
        ss >> key;

        for(auto it = agenda.begin(); it != agenda.end(); it++){
            if (it->getName() != key){
                new_agenda.push_back(*it);
            }
        }
        agenda.swap(new_agenda);
    }

    void showContacts(){
        for(int i = 0; i < (int)agenda.size(); i++){
            std::cout << agenda[i];
        }
    }
};

int main(){

    Agenda agenda;

    while(true){
        std::string line;
        std::getline(std::cin, line, '$');
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::string cmd;

        ss >> cmd;

        if (cmd == "add"){
            agenda.addContact(ss);
        }
        else if (cmd == "rm"){
            agenda.rmContact(ss);
        }
        else if (cmd == "show"){
            agenda.showContacts();
        }
        else if (cmd == "search"){
            std::string pattern;
            ss >> pattern;
            agenda.searchContact(pattern);
        }
        else if(cmd == "end"){
            break;
        }
        else{
            std::cout << "comando nao existe" << '\n';
        }

    }

}
