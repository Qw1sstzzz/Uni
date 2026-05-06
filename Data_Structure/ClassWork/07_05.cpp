#include <iostream>
#include <functional>
#include <algorithm>
#include <numeric>
#include <vector>
#include <string>

using namespace std::placeholders;

int sum(int a, int b) {
    return a + b;
}

struct Counter {
    int count = 0;
    void operator()(int) {
        count++;
    }
} ;

int main(void) {
    auto plusFive = std::bind(sum, 5, _1);

    std::cout << plusFive(10) << std::endl;


    auto expr = std::bind(
        std::multiplies<int>(),
        std::bind(std::plus<int>(), _1, _2),
        std::bind(std::minus<int>(), _1, _2)
    );

    std::cout << expr(5, 2) << std::endl;

    std::vector<int> v{1, 2, 3, 4};
    std::for_each(v.begin(), v.end(), [](int x){
        std::cout << x << " ";
    });
    std::cout << std::endl;

    Counter c = std::for_each(v.begin(), v.end(), Counter());
    std::cout << c.count << std::endl;


    int sum = std::accumulate(v.begin(), v.end(), 0);
    int pr = std::accumulate(v.begin(), v.end(), 1, std::multiplies<int>());

    std::cout << sum << std::endl << pr << std::endl;

    std::vector<std::string> words{"cat", "dog", "bird"};
    std::vector<int> lengths;
    std::transform(words.begin(), words.end(),
        std::back_inserter(lengths),
        [](const std::string& s) {
            return s.length();
    });

    for (int len : lengths) {
        std::cout << len << ' ';
    }
    std::cout << std::endl;
}


/*
std::vector<std::string> filtered;
std::copy_if(words.begin(), words.end(),
    std::back_inserter(filtered),
    [](const std::string& s) { return s.length() <= 3; });

std::vector<char> first_chars;
std::transform(filtered.begin(), filtered.end(),
    std::back_inserter(first_chars),
    [](const std::string& s) { return s[0]; });




int total_length = std::accumulate(words.begin(), words.end(), 0,
    [](int acc, const std::string& s) {
    return acc + (s.length() <= 3 ? s.length() : 0);
});



std::vector<int> lengths;
std::transform(words.begin(), words.end(),
    std::back_inserter(lengths),
    [](const std::string& s) { return s.length();
});

auto min_it = std::min_element(lengths.begin(), lengths.end());
auto max_it = std::max_element(lengths.begin(), lengths.end());



std::vector<std::string> short_words;
std::copy_if(words.begin(), words.end(),
    std::back_inserter(short_words),
    [](const std::string& s) { return s.length() <= 3; });



auto it = std::find_if(words.begin(), words.end(),
    [](const std::string& s) { return !s.empty() && s[0] == 'c'; });



auto shortest = std::min_element(words.begin(), words.end(),
    [](const std::string& a, const std::string& b) {
        return a.length() < b.length();
    });
auto longest = std::max_element(words.begin(), words.end(),
    [](const std::string& a, const std::string& b) {
        return a.length() < b.length();
    });
*/
