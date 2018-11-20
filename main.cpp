#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include <iomanip>

int main(int argc, char *argv[]) {
    const char *s1 = argv[1];
    const char *s2 = argv[2];
    std::string word;
    std::ifstream input;
    std::map<std::string, int32_t> wordCount;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
    char let;
    int32_t sum = 0;
    input.open(s1);
    while (!input.eof()) {
        input.get(let);
        if (isalnum(let) != 0) {
            word.push_back(let);
        } else if (word != "") {
            if (wordCount.find(word) == wordCount.end()) {
                wordCount[word] = 1;
                
            } else {
                wordCount[word]++;
            }
            word.clear();
            sum++;
        }
    }
    input.close();
    std::ofstream output (s2);
    std::vector<std::pair<std::string, int32_t>> res(wordCount.begin(), wordCount.end());
    std::sort(res.begin(), res.end(), [] (auto &left, auto &right) {
        return left.second > right.second;
    });
    for (int32_t i = 0; i < res.size(); ++i) {
        double freq = 100 * (double)(res[i].second) / (double)sum;
        output << res[i].first <<" : "<< res[i].second << " : "  << std::fixed << std::setprecision(2) << freq << "%" <<  std::endl;
    }
    output.close();
    return 0;
}
