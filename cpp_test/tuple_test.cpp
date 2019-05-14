#include <tuple>
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>


using MyIds = std::tuple<int, int, std::vector<int> >;


void show_tuple(const MyIds& ids)
{
    std::cout << "id1 = " << std::get<0>(ids) 
              << " id2 = " << std::get<1>(ids)  << std::endl;

    for (const auto& id : std::get<2>(ids))
    {
        std:: cout << "id3 = " << id << std::endl;
    }
}


 
std::tuple<double, char, std::string> get_student(int id)
{
    if (id == 0) return std::make_tuple(3.8, 'A', "Lisa Simpson");
    if (id == 1) return std::make_tuple(2.9, 'C', "Milhouse Van Houten");
    if (id == 2) return std::make_tuple(1.7, 'D', "Ralph Wiggum");
    throw std::invalid_argument("id");
}
 
int main()
{
    std::vector<int> dd = {1, 2, 3};
    MyIds ids = std::make_tuple(1, 2, dd);

    show_tuple(ids);


    auto student0 = get_student(0);
    std::cout << "ID: 0, "
              << "GPA: " << std::get<0>(student0) << ", "
              << "grade: " << std::get<1>(student0) << ", "
              << "name: " << std::get<2>(student0) << '\n';
 
    double gpa1;
    char grade1;
    std::string name1;
    std::tie(gpa1, grade1, name1) = get_student(1);
    std::cout << "ID: 1, "
              << "GPA: " << gpa1 << ", "
              << "grade: " << grade1 << ", "
              << "name: " << name1 << '\n';
 
    // C++17 structured binding:
    auto [ gpa2, grade2, name2 ] = get_student(2);
    std::cout << "ID: 2, "
              << "GPA: " << gpa2 << ", "
              << "grade: " << grade2 << ", "
              << "name: " << name2 << '\n';
}
