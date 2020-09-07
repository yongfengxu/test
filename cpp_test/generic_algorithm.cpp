#include <algorithm>
#include <iostream>
#include <list>
#include <numeric>
#include <vector>

void copy_test()
{
    std::vector<int> v;
    v.reserve(10);

    // can't work
    // fill_n(v.begin(), 10, 1);

    fill_n(back_inserter(v), 10, 1);

    std::cout << "v.size() = " << v.size() << std::endl;
    std::cout << "v.count(1) = " << std::count(v.cbegin(), v.cend(), 1) << std::endl;


    std::list<int> l;

    std::cout << "l.size() = " << l.size() << std::endl;

    int i = accumulate(v.cbegin(), v.cend(), 0);
    std::cout << "The sum is " << i << std::endl;
    copy(v.cbegin(), v.cend(), back_inserter(l));

    std::vector<int> v1;
    replace_copy(std::begin(v), std::end(v), back_inserter(v1), 0, 1);

    replace(std::begin(v), std::end(v), 1, 9);

    auto iter = find(std::begin(v1), std::end(v1), 1);

    if (iter != v.end())
    {
        std::cout << "find it " << *iter << std::endl;
    }
}

template<class T>
void print(const T& v, const std::string& info)
{
    std::cout << "==" << info << "==," << "size = " << v.size() << ", ";
    for (const auto& value : v)
    {
        std::cout << value << " ";
    }

    std::cout << std::endl;
}

void elimDups(std::vector<std::string>& words)
{
    std::cout << "=== raw ===" << std::endl;
    print(words, "raw");

    sort(std::begin(words), std::end(words));
    std::cout << "=== sort ===" << std::endl;
    print(words, "sort");

    auto iter = unique(words.begin(), words.end());

    for (auto a : words)
        std::cout << " AAA " << a << std::endl;

    std::cout << "=== unique ===" << std::endl;
    print(words, "unique");

    words.erase(iter, std::end(words));
    std::cout << "=== erase duplication ===" << std::endl;
    print(words, "earse");
}

bool isShorter(const std::string& s1, const std::string& s2)
{
    if (s1.length() < s2.length())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isMatched(const std::string& s)
{
    return (s.size() >= 5);
}

void test_Sort_V1()
{
    std::vector<std::string> words = {"red", "big", "my", "ai", "to", "love", "you"};
    sort(words.begin(), words.end(), isShorter);
    print(words, "sort");
}

void test_Stable_Sort()
{
    std::vector<std::string> words = {"red", "big", "my", "ai", "to", "love", "you"};
    stable_sort(words.begin(), words.end(), isShorter);
    print(words, "stable_sort");
}

void test_elimDups()
{
    std::vector<std::string> words = {"hello", "world", "my", "love", "I", "love", "you"};
    elimDups(words);

    stable_sort(words.begin(), words.end(), isShorter);
    print(words, "stable_sort");
}

void test_partition()
{
    std::vector<std::string> words = {"greed", "workspace", "my", "love", "I", "Shanghai", "you"};

    auto lastIter = std::partition(words.begin(), words.end(), isMatched);

    print(words, "partation");

    for (const auto& word : words)
    {
        if (word == *lastIter)
        {
            break;
        }
        std::cout << " " << word;
    }
    std::cout << std::endl;
}

int main()
{
    test_elimDups();

    test_Sort_V1();

    test_Stable_Sort();

    test_partition();
}
