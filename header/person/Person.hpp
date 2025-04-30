#ifndef _PERSON_HPP
#define _PERSON_HPP
#include <string>
class Person {
    protected:
    std::string name;
    int id;
    std::string role;
    public:
    Person() = default;
    Person(const Person& other) = default;
    Person(Person &&other) = default;
    virtual ~Person() = default;
    void setName(std::string name);
    void setID(int id);
    void setRole(std::string role);
    std::string getName() const;
    int getID() const;
    std::string getRole() const;
};

#endif