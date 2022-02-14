#include <iostream>
#include <map>
#include <set>
#include <sstream>

class Controll;
class User;

class Tweet{
    int id;
    std::string user;
    std::string tweet;
    std::set<std::string> likedBy;
    Tweet * rt {nullptr};
    const std::string deletedtwt = "esse tweet foi deletado";
    bool alive {true};
public:
    Tweet(int id, std::string user, std::string tweet){
        this->id = id;
        this->user = user;
        this->tweet = tweet;
    }
    int getId(){
        return id;
    }

    std::string getAuthor(){
        return user;
    }

    void likeTweet(std::string name){
        likedBy.insert(name);
    }

    void deleteTweet(){
        alive = false;
    }

    void addRt(Tweet * tweet){
        rt = tweet;
    }

    void printRt() const{
        if(rt != nullptr)
            std::cout << "  " << *rt;
    }

    void removeLike(std::string name){
        auto it = likedBy.find(name);
        likedBy.erase(name);
    }

    friend std::ostream& operator<<(std::ostream& os, const Tweet& twt){
        if(twt.alive == true){
        std::cout << twt.id << ':' << twt.user << " (" << twt.tweet << ")";
        if(twt.likedBy.size() > 0){
            std::cout << '[';
            for(auto it = twt.likedBy.begin(); it != twt.likedBy.end(); it++){
                std::cout << *it;
                auto it2 = it;
                it2++;
                if(it2!=twt.likedBy.end())
                    std::cout << ", ";
            }
            std::cout << ']';
        }
        std::cout << '\n';
        twt.printRt();

        }else{
            std::cout << "  " << twt.id << ':' << " (" << twt.deletedtwt << ")\n";
       }

       return os;
    }

};

class Inbox{
    std::map<int, Tweet*> timeline;
    std::map<int, Tweet*> myTweets;
public:

    void addToTimeline(Tweet& tweet){
        timeline.insert(std::make_pair(tweet.getId(), &tweet));
    }

    void addMyTweet(Tweet& tweet){
        myTweets.insert(std::make_pair(tweet.getId(), &tweet));
        addToTimeline(tweet);
    }

    void rmUnfollowTweets(std::string name){
        bool wasDeleted {false};
        for(std::map<int, Tweet*>::const_iterator it = timeline.begin(); it != timeline.end(); it++){
            if (wasDeleted == true){
                wasDeleted = false;
                it = timeline.begin();
            }
            if(it->second->getAuthor() == name){
                timeline.erase(it);
                wasDeleted = true;
            }
        }
    }

    void deleteMyTweets(){
        for (auto it : myTweets){
            it.second->deleteTweet();
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Inbox& inbox){
        for (auto it = inbox.timeline.rbegin(); it != inbox.timeline.rend(); it++){
            std::cout << *it->second;
        }
        return os;
    }

};

class User{
    std::string name;
    std::map<std::string, User*> following;
    std::map<std::string, User*> followers;

    Inbox inbox;

public:
    User(std::string name){
        this->name = name;
    }

    void createTweet(Tweet& tweet){
        inbox.addMyTweet(tweet);

        for(auto& [nome, user] : followers){
            auto it = followers.find(nome);
            if(it != followers.end()){
                user->addToTimeline(tweet);
            }
        }

    }

    void addToTimeline(Tweet& tweet){
        inbox.addToTimeline(tweet);
    }

    void follow(User * followed){
        if(followed->getName() != this->name){
            following.insert(std::make_pair(followed->getName(), followed));
            followed->addFollower(this);
        }else{
            std::cout << "\nNossa, vc esta tentando se seguir? Nossa que alter ego\n";
        }
    }

    void unfollow(User * followed){
        auto it = following.find(followed->getName());

        if(it != following.end()){
            following.erase(it);
            inbox.rmUnfollowTweets(followed->getName());
        }else{
            std::cout << "User invalido\n";
        }
    }

    void addFollower(User * follower){
        followers.insert(std::make_pair(follower->getName(), follower));
    }

    void removeFollower(User * follower){
        followers.erase(follower->getName());
    }

    std::string getName() const{
        return name;
    }

    void deleteMe(){
        for (auto it : followers){
            it.second->unfollow(this);
        }
        followers.clear();
        for (auto it : following){
            it.second->removeFollower(this);
        }
        following.clear();

        inbox.deleteMyTweets();
    }

    void printFollowing() const {
        std::cout << '[';
        if(following.size() > 0){

            for(auto& [nome, user] : following){
                std::cout << nome;

                auto it = following.find(nome);
                it++;
                if (it == following.end()){
                    std::cout << ']';
                }else{
                    std::cout << ", ";
                }
            }
        }else{
            std::cout << ']';
        }
        std::cout << '\n' << "  seguidores  ";

        std::cout << '[';
        if(followers.size() > 0){
            for(auto& [nome, user] : followers){
                std::cout << nome;

                auto it = followers.find(nome);
                it++;
                if (it == followers.end()){
                    std::cout << ']';
                }else{
                    std::cout << ", ";
                }
            }
        }else{
            std::cout << ']';
        }
    }

    void printFollowers() const {
        std::cout << '[';
        if(followers.size() > 0){
            for(auto& [nome, User] : followers){
                std::cout << nome;
                auto it = followers.find(nome);
                it++;
                if (it == followers.end()){
                    std::cout << ']';
                }else{
                    std::cout << ", ";
                }
            }
        }else{
            std::cout << ']';
        }
    }

    void printInbox(){
        std::cout << inbox << '\n';
    }

    friend std::ostream& operator<<(std::ostream& os, const User& user){
        std::cout << user.getName() << '\n' << "  seguidos    ";
        user.printFollowing();
        std::cout << '\n';

        return os;
     }
     friend class Controll;
};

class Controll{
    int nextTweetId {0};
    std::map<std::string, User> users;
    std::map<int, Tweet> tweets;
public:
    void newUser(std::string name){
        User user(name);
        users.insert(std::make_pair(name, User(name)));
    }

    User getUser(std::string name) const{
        return users.at(name);
    }

    void followUser(std::string first, std::string second){
        auto it1 = users.find(first);
        auto it2 = users.find(second);
        if(it1 == users.end() || it2 == users.end())
            std::cout << "User invalido\n";
        else
            it1->second.follow(&it2->second);
    }

    void unfollowUser(std::string first, std::string second){
        auto it1 = users.find(first);
        auto it2 = users.find(second);
        if(it1 == users.end() || it2 == users.end())
            std::cout << "User invalido\n";
        else{
            it1->second.unfollow(&it2->second);
            it2->second.removeFollower(&it1->second);
        }
    }

    void addTweet(std::string username, std::string tweet){
        auto it = users.find(username);
        if (it != users.end()){
            Tweet newTweet(nextTweetId, username, tweet);
            tweets.insert(std::make_pair(nextTweetId, newTweet));
            auto it2 = tweets.find(nextTweetId);
            it->second.createTweet(it2->second);
            nextTweetId++;
        }else{
            std::cout << "User invalido\n";
        }
    }

    void likeTweet(std::string user, int id){
        auto it = tweets.find(id);
        if (it == tweets.end())
            std::cout << "Tweet inexistente\n";
        else
            it->second.likeTweet(user);
    }

    void deleteTwt(int id){
        auto it = tweets.find(id);
        if (it == tweets.end())
            std::cout << "Tweet inexistente\n";
        else
            it->second.deleteTweet();
    }

    void retweet(std::string name, std::string twt, int id2){

        auto it2 = tweets.find(id2);
        if(it2 != tweets.end()){
            addTweet(name, twt);
            auto it1 = tweets.find(tweets.size()-1);
            it1->second.addRt(&it2->second);
        }else
            std::cout << "Tweet inexistente\n";
    }

    void deleteUser(std::string name){
        auto it = users.find(name);

        if(it != users.end()){
            it->second.deleteMe();
            for (auto& it : tweets){
                it.second.removeLike(name);
            }
            users.erase(it);
        }else{
                std::cout << "User inexistente\n";
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Controll& controll){
            for (const auto& [nome, usr] : controll.users){
                std::cout << usr;
            }
        return os;
    }


};


int main(){
    Controll controle;

    while(true){
        std::string line;
        std::getline(std::cin, line, '$');
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::string cmd;

        ss >> cmd;

        if (cmd == "add"){
            std::string name;
            ss >> name;
            controle.newUser(name);
        }
        else if (cmd == "follow"){
            std::string name1, name2;
            ss >> name1;
            ss >> name2;
            controle.followUser(name1, name2);
        }
        else if (cmd == "twittar"){
            std::string name, twt;
            ss >> name;
            ss >> twt;
            controle.addTweet(name, twt);
        }
        else if (cmd == "timeline"){
            std::string name;
            ss >> name;
            controle.getUser(name).printInbox();
        }
        else if (cmd == "like"){
            std::string name;
            int twt;
            ss >> name;
            ss >> twt;
            controle.likeTweet(name, twt);
        }
        else if (cmd == "unfollow"){
            std::string name1, name2;
            ss >> name1;
            ss >> name2;
            controle.unfollowUser(name1, name2);
        }
        else if (cmd == "rt"){
            std::string user, twt;
            int rt;
            ss >> user;
            ss >> rt;
            ss >> twt;
            controle.retweet(user, twt, rt);
        }
        else if (cmd == "rm"){
            std::string user;
            ss >> user;
            controle.deleteUser(user);
        }
        else if (cmd == "show"){
            std::cout << controle;
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
