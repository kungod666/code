#include <iostream>
#include <memory>
#include <string>
bool isDigit(const std::string& s)
{
    for(char p : s)
    {
        if(!isdigit(p)) return false;
    }
    return true;
}
class link{
    private:
    int pvalue;
    std::shared_ptr<link> psucc;
    public:
    int val(){return pvalue;}
    std::shared_ptr<link>& succ(){return psucc;}
    explicit link(int value = 0) : pvalue(value),psucc(nullptr){}
};
class list{
    private:
    std::shared_ptr<link> first;
    std::shared_ptr<link> last;
    public:
    list(){
        first = std::make_shared<link>();
        last = nullptr;
        first->succ() = last;
    }
    bool isEmpty();
    void push_back(int new_ele);
    void push_front(int new_ele);
    void erase(int old_ele);
    std::shared_ptr<link> search(int old_ele);
    void display();
};
bool list::isEmpty(){
    if(last == nullptr) return true;
    else return false;
}
void list::push_back(int new_ele){
    std::shared_ptr<link> t = std::make_shared<link>(new_ele);
    if(list::isEmpty()){
        last = t;
        first->succ() = last;
        return;
    }
    last->succ() = t;
    last = t;
}
void list::push_front(int new_ele){
    std::shared_ptr<link> p = std::make_shared<link>(new_ele);
    if(list::isEmpty()){
        last = p;
        first->succ() = last;
        return; 
    }
    p->succ() = (first->succ())->succ();
    first->succ() = p;
}
void list::erase(int old_ele){
    if(isEmpty()){
        std::cout << "List empty\n";
        return;
    }
    if(last->val() == old_ele){
        std::shared_ptr<link> kl = first;
        while(kl->succ() != last){
            kl = kl->succ();
        }
        std::shared_ptr<link> op = last;
        last = kl;
        op.reset();
        if(last == first){
            last = nullptr;
            first->succ() = last;
        }
        return;
    }
    std::shared_ptr<link> cur = first;
    while(cur->succ() != nullptr && cur->succ()->val() != old_ele){/*cur->succ()->val():avoid searching first*/
        cur = cur->succ();
    }
    if(cur == last){
        std::cout << "your element dosnt exist\n";
        return;
    }
    std::shared_ptr<link> target = cur->succ();
    cur->succ() = cur->succ()->succ();
    target.reset();  
}
std::shared_ptr<link> list::search(int old_ele){
    if(isEmpty()){
        std::cout << "List empty\n";
        return nullptr;
    }
    int count = 1;
    bool flag = false;
    std::shared_ptr<link> cur = first;
    while(cur->succ() != nullptr){
        cur = cur->succ();
        if(cur->val() == old_ele){
            flag = true;
            break;
        }
        count++;
    }
    if(!flag){
        std::cout << "No such element\n";
        return nullptr;
    }
    std::cout << "Find element,it pos: " << count << "\n";
    return cur;
}