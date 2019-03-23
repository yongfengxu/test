#include <iostream>

class AbsActor;

class Role
{
public:
    ~Role() = default;
    virtual void accept(AbsActor* actor) = 0;

};

class KongfuRole;

class AbsActor
{
public:
    virtual void act(Role* role) {std::cout << "actor can play any role" << std::endl;}
    virtual void act(KongfuRole* role) {std::cout << "actor can play kongfu role" << std::endl;}
};

class KongfuRole : public Role
{
public:
    void accept(AbsActor* actor) override {actor->act(this);}

};

class IdiotRole: public Role
{
public:
    void accept(AbsActor* actor) override {actor->act(this);}
};
class YoungActor : public AbsActor
{
    void act(KongfuRole* role) {std::cout << "young actor like kongfu most" << std::endl;}
};

class OldActor : public AbsActor
{
    void act(KongfuRole* role) override {std::cout << "I'm old, can't play kongfu" << std::endl;}
};

int main()
{
    AbsActor* actor = new OldActor();
    Role* role = new KongfuRole();

    /*
      Output:
      actor can play any role
      I'm old, can't play kongfu
    */

    actor->act(role);
    actor->act(new KongfuRole());

    /*
      Output:
      I'm old, can't play kongfu
    */
    role->accept(actor);

}

