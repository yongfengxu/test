#include <iostream>
#include <vector>
#include <string>


class Person
{
public:
    using Grades = std::vector<std::string>;
    friend void printGrades(const Person& person);
    friend class Printer;

    Grades& getGrades();

private:
    Grades grades{"English", "Maths", "Chinese"};
};

class Printer
{
public:
    void printerGrades(const Person& person);
};

void Printer::printerGrades(const Person& person)
{
    for (const auto& grade : person.grades)
    {
        std::cout << grade << std::endl;
    }
}

Person::Grades& Person::getGrades()
{
    return grades;
}

void printGrades(const Person& person)
{
    for (const auto& grade : person.grades)
    {
        std::cout << grade << std::endl;
    }
}


int main()
{
    Person person;

    Person::Grades gg = person.getGrades();
    for (const auto& grade : gg)
    {
        std::cout << grade << std::endl;
    }

    std::cout << "===printGrades()===" << std::endl;
    printGrades(person);

    std::cout << "===Printer===" << std::endl;

    Printer p;
    p.printerGrades(person);

}
