#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

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

        void favorite(){
            prefix = "@";
        }

        void unfavorite(){
            prefix = "-";
        }

        bool isfav(){
            if(prefix == "-")
                return false;
            else if(prefix == "@")
                return true;
        }

        bool addFone(int id, std::string label, std::string numb){
            if (validate(numb)!=false){
                Fone fone(id, label, numb);
                this->fones.push_back(fone);
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

        std::vector<Fone> getFones(){
            return fones;
        }

        std::string getName(){
            return nome;
        }

        int getFonesSize(){
            return (int) fones.size();
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
    std::map<std::string, Contact> agenda;

public:

    void addContact(std::stringstream& ss){
        std::string label, numb, name, token;
        ss >> name;
        Contact newContact(name);
        while(!ss.eof()){
            ss >> token;
            std::stringstream ss2(token);
            getline(ss2, label, ':');
            if(!ss2.eof()){
                getline(ss2, numb);
                newContact.addFone(newContact.getFonesSize(), label, numb);
            }
        }

        auto it = agenda.find(name);

        if (it == agenda.end()){
            agenda.insert(std::make_pair(name, newContact));
        }else{
            std::vector<Fone> fones = newContact.getFones();
            for(auto fone : fones){
                agenda[name].addFone(it->second.getSize(), fone.getLabel(), fone.getNumber());
            }
        }

    }

     void searchContact(std::string patern){
        std::vector<Contact> cont;
        for (auto& [nome, contato] : agenda){
            std::string strg;
            strg += contato;
            if(strg.find(patern) != std::string::npos){
                std::cout << contato;
            }
        }
    }

    void favorite(std::stringstream& ss){
        std::string name;
        ss >> name;
        auto it = agenda.find(name);
        if(it!=agenda.end()){
            it->second.favorite();
        }else{
            std::cout << "Contato inexistente\n";
        }

    }

    void unfavorite(std::stringstream& ss){
        std::string name;
        ss >> name;
        auto it = agenda.find(name);
        if(it!=agenda.end()){
            it->second.unfavorite();
        }else{
            std::cout << "Contato inexistente\n";
        }

    }

    void printFav(){
        for(auto& [nome, contact] : agenda){
            if(contact.isfav() == true)
                std::cout << contact;
        }
    }

    void rmContact(std::stringstream& ss){
        std::string key;

        ss >> key;
        auto it = agenda.find(key);
        if(it == agenda.end()){
            std::cout << "CONTATO INVALIDO" << '\n';
        }else{
            if(!ss.eof()){
                int id;
                ss >> id;
                it->second.rmFone(id);
            }
            else{
                agenda.erase(it);
            }
        }
    }

    void showContacts(){
        for(auto& [nome, contact] : agenda){
            std::cout << contact;
        }

    }
};

int main(){

    Agenda agenda;

    while(true){
        std::string line;
        //std::getline(std::cin, line, '$');
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
        else if (cmd == "star"){
            agenda.favorite(ss);
        }
        else if (cmd == "unstar"){
            agenda.unfavorite(ss);
        }
        else if (cmd == "starred"){
            agenda.printFav();
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
