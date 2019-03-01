#include <string>
#include <iostream>
#include <vector>
#include <chrono>
int main(void)
{
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    std::string text;
    std::string pattern;
    std::cin >> text;
    int count = 1; 
    size_t found;
    std::vector<int> res;
    while (std::cin >> pattern){
        found = text.find(pattern);
        while(found != std::string::npos){
            res.push_back(found+1);
            found = text.find(pattern, found+1);
        }
        if (!res.empty()) {
            std::cout << count << ": ";
            for (int i = 0; i < res.size()-1; ++i)
                std::cout << res[i] << ", ";
            std::cout << res[res.size()-1] << std::endl;
        }
        res.clear();
        ++count;
    }

    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::cout << "Search: std::string::find" << std::endl;
    std::cout << "Time of working ";
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count();
    std::cout << " ms." << std::endl;
    return 0;
}