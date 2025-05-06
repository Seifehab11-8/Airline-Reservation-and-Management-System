#ifndef _PERSON_HPP
#define _PERSON_HPP
#include <string>
class Person {
    protected:
    std::string name;
    std::string id;
    std::string role;
    public:
    Person() = default;
    Person(const Person& other) = default;
    Person(Person &&other) = default;
    virtual ~Person() = default;
    void setName(std::string name);
    void setID(std::string id);
    void setRole(std::string role);
    std::string getName() const;
    std::string getID() const;
    std::string getRole() const;
};

#endif