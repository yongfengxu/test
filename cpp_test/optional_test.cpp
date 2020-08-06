#include <iostream>

#include <functional>
#include <optional>

std::optional<std::string> create(bool b)
{
    if (b)
    {
        return "Charlie";
    }

    return {};
}


std::optional<std::string> create2(bool b)
{
    return b ? std::optional<std::string>{"Charlie"} : std::nullopt;
}

auto create_ref(bool b)
{
    static std::string value = "Charlie";

    return b ? std::optional<std::reference_wrapper<std::string>>{value} : std::nullopt;
}


int main()
{
    std::cout << create(true).value_or("empty") << std::endl;
    std::cout << create(false).has_value() << std::endl;


    auto v2 = create2(true);
    auto v3 = create2(false);


    if (v2.has_value())
    {
        std::cout << "v2: " << *v2 << " size: " << v2->size() << std::endl;

    }

    if (v3.has_value())
    {
      std::cout << "v3: " << *v3 << std::endl;
    }

    if (v3)
    {
      std::cout << "v3: " << *v3 << std::endl;
    }
}
