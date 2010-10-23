#include "tod/core_test/object_test.h"

#include <cassert>
#include <vector>
#include "tod/core/type.h"
#include "tod/core/object.h"
#include "tod/core/node.h"
#include "tod/core/linknode.h"
#include "tod/core/module.h"
#include "tod/core/kernel.h"
#include "tod/core/simplepropertybinder.h"
#include "tod/core/structproperty.h"
#include "tod/core/enumpropertybinder.h"
#include "tod/core/containerproperty.h"
#include "tod/core/methodbinder.h"

using namespace tod;

//-----------------------------------------------------------------------------
class Super : public Object
{
public:
    DECLARE_SUPERCLASS(Super);
};
class Derived1 : public Super
{
public:
    DECLARE_CLASS(Derived1, Super);
};
class Derived2 : public Derived1
{
public:
    DECLARE_CLASS(Derived2, Derived1);
};
IMPLEMENT_SUPERCLASS(Super);
IMPLEMENT_CLASS(Derived1, Super);
IMPLEMENT_CLASS(Derived2, Derived1);
void ObjectTestCase::test_Object()
{
    Super* instance = new Derived2;
    TODUNIT_ASSERT(tod_strcmp(instance->toString(), "Derived2") == 0);
    TODUNIT_ASSERT(instance->isKindOf("Super"));
    TODUNIT_ASSERT(instance->isKindOf("Derived1"));
    TODUNIT_ASSERT(instance->isKindOf("Derived2"));
    TODUNIT_ASSERT(!instance->isKindOf("Super2"));
    TODUNIT_ASSERT(instance->isKindOf(&Derived1::TYPE));
    TODUNIT_ASSERT(instance->isKindOf(&Super::TYPE));

    // Object Memory foot print
    TODUNIT_ASSERT(sizeof(Object) == 4);

    delete instance;
}

//-----------------------------------------------------------------------------
class Weapon : public Object
{
public:
    DECLARE_SUPERCLASS(Weapon)

    void setPrice(const int& price)
    {
        price_ = price;
    }
    const int& getPrice() const
    {
        return price_;
    }
    void setPower(const int& power)
    {
        power_ = power;
    }
    const int& getPower() const
    {
        return power_;
    }

    static void bindProperty()
    {
        BIND_PROPERTY(const int&, price, &Weapon::setPrice, &Weapon::getPrice);
        BIND_PROPERTY(const int&, power, &Weapon::setPower, &Weapon::getPower);
    }

public:
    int price_;
    int power_;
};
IMPLEMENT_SUPERCLASS(Weapon);

class Fighter;
class FighterMethodBinder
{
public:
    static void Fighter_i_attack_i(Fighter* self, Parameter* parameter);
    static void Fighter_v_selfHeal_i(Fighter* self, Parameter* parameter);
    static void Fighter_v_setVelocity_f(Fighter* self, Parameter* parameter);
};


class Actor : public Object
{
public:
    DECLARE_SUPERCLASS(Actor)
};
class Fighter : public Actor
{
public:
    enum CharacterType
    {
        CHARACTERTYPE_FIGHTER,
        CHARACTERTYPE_SORCERESS,
        CHARACTERTYPE_HULK,
    };

public:
    DECLARE_CLASS(Fighter, Actor)
    Fighter()
    {
        hp_ = 0;
    }
    virtual~Fighter()
    {
        for (WeaponList::iterator iter = weaponList_.begin();
             iter != weaponList_.end(); ++iter)
             delete *iter;
        weaponList_.clear();
    }

    int attack(int damage)
    {
        hp_ -= damage;
        return hp_;
    }
    void setVelocity(float v)
    {
        assert(v == 2.0f);
    }
    void selfHeal(int amount)
    {
        hp_ += amount;
    }

    void Hp(const int& hp)
    {
        hp_ = hp;
    }
    const int& Hp() const
    {
        return hp_;
    }
    void setName(const String& name)
    {
        name_ = name;
    }
    const String& getName() const
    {
        return name_;
    }
    void setH1(const int& h)
    {
        h_.h1_ = h;
    }
    const int& getH1() const
    {
        return h_.h1_;
    }
    void setN(const int& n)
    {
        h_.n_.n1_ = n;
    }
    const int& getN() const
    {
        return h_.n_.n1_;
    }
    void setCharacterType(const CharacterType& type)
    {
        characterType_ = type;
    }
    const CharacterType& getCharacterType() const
    {
        return characterType_;
    }
    void insertWeapon(const int& index)
    {
        weaponList_.insert(weaponList_.begin() + index, new Weapon);
    }
    void removeWeapon(const int& index)
    {
        delete weaponList_[index];
        weaponList_.erase(weaponList_.begin() + index);
    }
    Weapon*& findWeapon(const int& index)
    {
        return weaponList_[index];
    }

    static void bindProperty()
    {
        // standard
        BIND_PROPERTY(const int&, hp, &Fighter::Hp, &Fighter::Hp);
        BIND_PROPERTY(const float&, mp, 0, 0);
        BIND_PROPERTY(const double&, str, 0, 0);
        BIND_PROPERTY(const int64_t&, dex, 0, 0);
        BIND_PROPERTY(const String&, name,
            &Fighter::setName, &Fighter::getName);

        // struct hierarchy
        BIND_PROPERTY_STRUCT(test_struct);
            BIND_PROPERTY_TO_STRUCT(test_struct, const int&, h1,
                &Fighter::setH1, &Fighter::getH1);
            BIND_PROPERTY_TO_STRUCT(test_struct, const float&, h2, 0, 0);

            BIND_STRUCT_TO_STRUCT(test_struct, test_n);
                BIND_PROPERTY_TO_STRUCT(test_n, const int&, n,
                    &Fighter::setN, &Fighter::getN);

        // enum
        BIND_ENUM_PROPERTY(CharacterType, character_type,
            &Fighter::setCharacterType, &Fighter::getCharacterType);
            ENUM_PROPERTY_ADD(CharacterType, CHARACTERTYPE_FIGHTER);
            ENUM_PROPERTY_ADD(CharacterType, CHARACTERTYPE_SORCERESS);
            ENUM_PROPERTY_ADD(CharacterType, CHARACTERTYPE_HULK);

        // list
        BIND_CONTAINER_PROPERTY(int, Weapon*, weapon_list,
            &Fighter::insertWeapon, &Fighter::removeWeapon, &Fighter::findWeapon);
    }

    static void bindMethod()
    {
        BIND_METHOD(i_attack_i, &FighterMethodBinder::Fighter_i_attack_i);
        BIND_METHOD(v_selfHeal_i, &FighterMethodBinder::Fighter_v_selfHeal_i);
        BIND_METHOD(v_setVelocity_f, &FighterMethodBinder::Fighter_v_setVelocity_f);
    }

public:
    int hp_;
    float mp_;
    double str_;
    int64_t dex_;
    String name_;

    struct Test
    {
        int h1_;
        float h2_;

        struct N
        {
            int n1_;
        };

        N n_;
    };

    Test h_;

    CharacterType characterType_;
    typedef std::vector<Weapon*>  WeaponList;
    WeaponList weaponList_;
};
IMPLEMENT_SUPERCLASS(Actor);
IMPLEMENT_CLASS(Fighter, Actor);

//-----------------------------------------------------------------------------
void FighterMethodBinder::Fighter_i_attack_i
(Fighter* self, Parameter* parameter)
{
    parameter->out()->get<int>(0) = self->attack(parameter->in()->get<int>(0));
}

//-----------------------------------------------------------------------------
void FighterMethodBinder::Fighter_v_selfHeal_i
(Fighter* self, Parameter* parameter)
{
    self->selfHeal(parameter->in()->get<int>(0));
}

//-----------------------------------------------------------------------------
void FighterMethodBinder::Fighter_v_setVelocity_f
(Fighter* self, Parameter* parameter)
{
    self->setVelocity(parameter->in()->get<float>(0));
}

//-----------------------------------------------------------------------------
void ObjectTestCase::test_CreateObjectByConcreteType()
{
    Module module("TestModule", 0, 0);
    Module* m = &module;
    REGISTER_TYPE(m, Actor);
    REGISTER_TYPE(m, Fighter);

    Fighter* fighter = DOWN_CAST<Fighter*>(module.create("Fighter"));
    TODUNIT_ASSERT(fighter != 0);
    TODUNIT_ASSERT(fighter->isKindOf("Actor"));
    TODUNIT_ASSERT(fighter->isKindOf("Fighter"));
    TODUNIT_ASSERT(fighter->TYPE.getName() == "Fighter");
    TODUNIT_ASSERT(fighter->isKindOf(fighter->getType()));

    delete fighter;
}

//-----------------------------------------------------------------------------
void ObjectTestCase::test_PrimitiveTypeProperty()
{
    Module module("TestModule", 0, 0);
    Module* m = &module;
    REGISTER_TYPE(m, Actor);
    REGISTER_TYPE(m, Fighter);

    Fighter* fighter = DOWN_CAST<Fighter*>(module.create("Fighter"));
    if (!Fighter::TYPE.hasBindedProperty())
        fighter->bindProperty();

    typedef SimpleProperty<const int&> IntProperty;
    IntProperty* property =
        static_cast<IntProperty*>
        (fighter->TYPE.findProperty("hp"));
    property->set(fighter, 10);
    TODUNIT_ASSERT(property->get(fighter) == 10);
    TODUNIT_ASSERT(fighter->Hp() == 10);
    fighter->Hp(20);
    TODUNIT_ASSERT(property->get(fighter) == 20);

    delete fighter;
}

//-----------------------------------------------------------------------------
void ObjectTestCase::test_CustomPrimitiveTypeProperty()
{
    Module module("TestModule", 0, 0);
    Module* m = &module;
    REGISTER_TYPE(m, Actor);
    REGISTER_TYPE(m, Fighter);

    Fighter* fighter = DOWN_CAST<Fighter*>(module.create("Fighter"));
    if (!Fighter::TYPE.hasBindedProperty())
        fighter->bindProperty();

    typedef SimpleProperty<const String&> StringProperty;
    StringProperty* string_property =
        static_cast<StringProperty*>
        (fighter->TYPE.findProperty("name"));
    string_property->set(fighter, "fighter");
    TODUNIT_ASSERT(string_property->get(fighter) == "fighter");
    TODUNIT_ASSERT(fighter->getName() == "fighter");
    fighter->setName("fighter haha");
    TODUNIT_ASSERT(string_property->get(fighter) == "fighter haha");

    delete fighter;
}

//-----------------------------------------------------------------------------
void ObjectTestCase::test_StructTypeProperty()
{
    Module module("TestModule", 0, 0);
    Module* m = &module;
    REGISTER_TYPE(m, Actor);
    REGISTER_TYPE(m, Fighter);

    Fighter* fighter = DOWN_CAST<Fighter*>(module.create("Fighter"));
    if (!Fighter::TYPE.hasBindedProperty())
        fighter->bindProperty();

    typedef SimpleProperty<const int&> IntProperty;
    StructProperty* struct_property = 
        static_cast<StructProperty*>
            (fighter->TYPE.findProperty("test_struct"));
    IntProperty* property = static_cast<IntProperty*>
        (struct_property->findProperty("h1"));
    property->set(fighter, 10);
    TODUNIT_ASSERT(fighter->getH1() == 10);
    fighter->setH1(20);
    TODUNIT_ASSERT(property->get(fighter) == 20);

    StructProperty* n_struct_property =
        static_cast<StructProperty*>
            (struct_property->findProperty("test_n"));
    property = static_cast<IntProperty*>
        (n_struct_property->findProperty("n"));
    property->set(fighter, 10);
    TODUNIT_ASSERT(fighter->getN() == 10);
    fighter->setN(20);
    TODUNIT_ASSERT(property->get(fighter) == 20);

    delete fighter;
}

//-----------------------------------------------------------------------------
void ObjectTestCase::test_EnumTypeProperty()
{
    Module module("TestModule", 0, 0);
    Module* m = &module;
    REGISTER_TYPE(m, Actor);
    REGISTER_TYPE(m, Fighter);

    Fighter* fighter = DOWN_CAST<Fighter*>(module.create("Fighter"));
    if (!Fighter::TYPE.hasBindedProperty())
        fighter->bindProperty();

    typedef EnumProperty<Fighter::CharacterType> FighterCharacterTypeEnumProperty;
    FighterCharacterTypeEnumProperty* property = 
        static_cast<FighterCharacterTypeEnumProperty*>
        (fighter->TYPE.findProperty("character_type"));

    property->set(fighter, Fighter::CHARACTERTYPE_SORCERESS);
    TODUNIT_ASSERT(fighter->getCharacterType() == Fighter::CHARACTERTYPE_SORCERESS);
    fighter->setCharacterType(Fighter::CHARACTERTYPE_FIGHTER);
    TODUNIT_ASSERT(property->get(fighter) == Fighter::CHARACTERTYPE_FIGHTER);
    property->set(fighter, "CHARACTERTYPE_SORCERESS");
    TODUNIT_ASSERT(fighter->getCharacterType() == Fighter::CHARACTERTYPE_SORCERESS);
    property->set(fighter, "CHARACTERTYPE_FIGHTER");
    TODUNIT_ASSERT(fighter->getCharacterType() == Fighter::CHARACTERTYPE_FIGHTER);

    delete fighter;
}

//-----------------------------------------------------------------------------
void ObjectTestCase::test_ListTypeProperty()
{
    Module module("TestModule", 0, 0);
    Module* m = &module;
    REGISTER_TYPE(m, Actor);
    REGISTER_TYPE(m, Fighter);
    REGISTER_TYPE(m, Weapon);

    Fighter* fighter = DOWN_CAST<Fighter*>(module.create("Fighter"));
    if (!Fighter::TYPE.hasBindedProperty())
        fighter->bindProperty();

    typedef ContainerProperty<Fighter, int, Weapon*> WeaponListProperty;
    WeaponListProperty* property = 
        static_cast<WeaponListProperty*>
            (fighter->TYPE.findProperty("weapon_list"));
    property->insert(fighter, 0);
    Weapon* weapon = property->search(fighter, 0);
    if (!Weapon::TYPE.hasBindedProperty())
        weapon->bindProperty();
    TODUNIT_ASSERT(weapon);

    typedef SimpleProperty<const int&> IntProperty;
    IntProperty* price_property = 
        static_cast<IntProperty*>
            (weapon->TYPE.findProperty("price"));
    price_property->set(weapon, 100);
    TODUNIT_ASSERT(weapon->getPrice() == 100);

    TODUNIT_ASSERT(weapon = fighter->findWeapon(0));
    TODUNIT_ASSERT(weapon->getPrice() == 100);

    delete fighter;
}

//-----------------------------------------------------------------------------
void ObjectTestCase::test_DictionaryTypeProperty()
{

}

//-----------------------------------------------------------------------------
void ObjectTestCase::test_ReflectionMethod()
{
    Module module("TestModule", 0, 0);
    Module* m = &module;
    REGISTER_TYPE(m, Actor);
    REGISTER_TYPE(m, Fighter);

    Fighter* fighter = DOWN_CAST<Fighter*>(module.create("Fighter"));
    if (!Fighter::TYPE.hasBindedMethod())
        fighter->bindMethod();

    // normal method invocation
    fighter->Hp(20);
    TODUNIT_ASSERT(fighter->attack(10) == 10);
    TODUNIT_ASSERT(fighter->Hp() == 10);

    // reflective method invocation
    fighter->Hp(30);
    Method* attack_method = Fighter::TYPE.findMethod("attack");
    TODUNIT_ASSERT(attack_method);
    attack_method->getParameter()->in()->get<int>(0) = 10;
    attack_method->invoke(fighter);
    TODUNIT_ASSERT(attack_method->getParameter()->out()->get<int>(0) == 20);
    TODUNIT_ASSERT(fighter->Hp() == 20);
    
    Method* selfheal_method = Fighter::TYPE.findMethod("selfHeal");
    TODUNIT_ASSERT(selfheal_method);
    selfheal_method->getParameter()->in()->get<int>(0) = 100;
    selfheal_method->invoke(fighter);
    TODUNIT_ASSERT(fighter->Hp() == 120);

    Method* setvelocity_method = Fighter::TYPE.findMethod("setVelocity");
    TODUNIT_ASSERT(setvelocity_method);
    setvelocity_method->getParameter()->in()->get<float>(0) = 2.0f;
    setvelocity_method->invoke(fighter);

    delete fighter;
}

//-----------------------------------------------------------------------------
class Warrior : public Node
{
public:
    DECLARE_CLASS(Warrior, Node);
};
IMPLEMENT_CLASS(Warrior, Node);
void ObjectTestCase::test_Node()
{
    Node* root = new Node();
    Node* child1 = new Node();
    Node* child2 = new Node();
    Node* child3 = new Node();
    child1->setName("test1");
    child2->setName("test2");
    child3->setName("test3");

    // reference count test
    root->attach(child1);
    child1->release();
    TODUNIT_ASSERT(child1->getRef() == 1);
    root->attach(child2);
    child2->release();
    TODUNIT_ASSERT(child2->getRef() == 1);
    child2->attach(child3);
    child3->release();
    TODUNIT_ASSERT(child3->getRef() == 1);

    // noh path test
    TODUNIT_ASSERT(child1->getAbsolutePath() == "/test1");
    TODUNIT_ASSERT(child2->getAbsolutePath() == "/test2");
    TODUNIT_ASSERT(child3->getAbsolutePath() == "/test2/test3");

    child3->detach();

    // recursively nodes deletion
    root->release();

    root = new Node();
    Warrior* warrior1 = new Warrior();
    Warrior* warrior2 = new Warrior();
    child1 = new Node();
    child2 = new Node();
    child3 = new Node();
    warrior1->setName("warrior1");
    warrior2->setName("warrior2");
    child1->setName("test1");
    child2->setName("test2");
    child3->setName("test3");

    root->attach(warrior1);
    warrior1->release();
    root->attach(warrior2);
    warrior2->release();
    root->attach(child1);
    child1->release();
    root->attach(child2);
    child2->release();
    root->attach(child3);
    child3->release();
    root->clearChildren<Warrior>();
    TODUNIT_ASSERT(root->getNumChildren() == 3);

    root->release();
}

//-----------------------------------------------------------------------------
class Assasin : public Object
{
public:
    DECLARE_SUPERABSTRACTCLASS(Assasin);    

    virtual void pureMethod()=0;
    int hp_;
};
IMPLEMENT_SUPERABSTRACTCLASS(Assasin);
class Trapsin : public Assasin
{
public:
    DECLARE_CLASS(Trapsin, Assasin);

    override void pureMethod()
    {
        hp_ = 0;
    }
};
IMPLEMENT_CLASS(Trapsin, Assasin);
void ObjectTestCase::test_AbstractNode()
{
    Assasin* trapsin = new Trapsin;
    trapsin->pureMethod();
    TODUNIT_ASSERT(trapsin->hp_ == 0);
    delete trapsin;
}


//-----------------------------------------------------------------------------
class FromTest : public Node
{
public:
    FromTest()
    {

    }
    virtual~FromTest()
    {

    }
    DECLARE_CLASS(FromTest, Node);
    static void bindProperty()
    {
        BIND_PROPERTY(int, hp, &setHp, &getHp);
    }
    void setHp(int hp)
    {
        hp_ = hp;
    }
    int getHp() const
    {
        return hp_;
    }
    int hp_;
};
IMPLEMENT_CLASS(FromTest, Node);
class ToTest : public Node
{
public:
    ToTest()
    {

    }
    virtual~ToTest()
    {

    }
    DECLARE_CLASS(ToTest, Node);
    static void bindProperty()
    {
        BIND_PROPERTY(int, hp, &setHp, &getHp);
        BIND_PROPERTY(float, mp, &setMp, &getMp);
        BIND_PROPERTY(double, dex, &setDex, &getDex);
        BIND_PROPERTY(bool, str, &setStr, &getStr);
    }
    void setHp(int hp)
    {
        hp_ = hp;
    }
    int getHp() const
    {
        return hp_;
    }
    void setMp(float mp)
    {
        mp_ = mp;
    }
    float getMp() const
    {
        return mp_;
    }
    void setDex(double dex)
    {
        dex_ = dex;
    }
    double getDex() const
    {
        return dex_;
    }
    void setStr(bool str)
    {
        str_ = str;
    }
    bool getStr() const
    {
        return str_;
    }
    int hp_;
    float mp_;
    double dex_;
    bool str_;
};
IMPLEMENT_CLASS(ToTest, Node);

void ObjectTestCase::test_LinkNode()
{
    FromTest from;
    from.bindProperty();
    ToTest to;
    to.bindProperty();
    LinkNode link;
    Property* hp_property1 = from.getType()->findProperty("hp");
    Property* hp_property2 = to.getType()->findProperty("hp");
    link.connect(&from, hp_property1, &to, hp_property2);

    from.setHp(10);
    link.update();
    TODUNIT_ASSERT(to.getHp() == 10);

    Property* mp_property2 = to.getType()->findProperty("mp");
    link.connect(&from, hp_property1, &to, mp_property2);

    from.setHp(102);
    link.update();
    TODUNIT_ASSERT(to.getMp() == 102);


    Property* dex_property2 = to.getType()->findProperty("dex");
    link.connect(&from, hp_property1, &to, dex_property2);

    from.setHp(888);
    link.update();
    TODUNIT_ASSERT(to.getDex() == 888);


    Property* str_property2 = to.getType()->findProperty("str");
    link.connect(&from, hp_property1, &to, str_property2);

    from.setHp(345);
    link.update();
    TODUNIT_ASSERT(to.getStr());

    from.setHp(0);
    link.update();
    TODUNIT_ASSERT(!to.getStr());
}
