#include <iostream>
#include <map>
#include <set>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <regex>
#include <vector>

using std::string;
using std::cout;
using std::endl;

struct comp
{
    template<typename T>
    bool operator()(const T& l, const T& r) const
    {
        if (l.second != r.second)
            return l.second < r.second;

        return l.first < r.first;
    }
};

bool exist(string fileName);
void readFile(string fileName);
void remove(std::string& str, char character);
void removeSymbols(string& word);

int main()
{
    readFile("text.txt");
    return 0;
}

bool exist(string fileName) {
    std::ifstream in(fileName);
    return in.good();
}
void readFile(string fileName) {
    if (exist(fileName) == 1) {
        std::vector<string> urls;

        std::ifstream in (fileName);
        std::map<string, size_t> WordMap;
        std::map<string, std::vector<int>> LineMap;
        string line;
        size_t lineNum = 1;
        while (getline(in, line)) {
            std::istringstream currentLine(line);
            string word;
            while (currentLine >> word) { 
                if (regex_match(word, std::regex("(http|https)://([^/ :]+):?([^/ ]*)(/?[^ #?]*)\\x3f?([^ #]*)#?([^ ]*)")) || regex_match(word, std::regex("^(https?:\\/\\/)?([\\da-z\\.-]+)\\.([a-z\\.]{2,6})([\\/\\w \\.-]*)*\\/?$"))) {
                    urls.push_back(word);
                    continue;
                }
                removeSymbols(word);
                std::transform(word.begin(), word.end(), word.begin(), ::tolower);
                WordMap[word]++;
                if (WordMap[word] > 1) {
                    string line2 = std::to_string(lineNum);
                    char lineMem = line2.front();
                    if (static_cast<char>(LineMap[word].back() != lineMem)) {
                        LineMap[word].push_back(lineNum);
                    }
                }
                else LineMap[word].push_back(lineNum);
            }
            lineNum++;

        }
        std::set<std::pair<std::string, int>, comp> set(WordMap.begin(), WordMap.end());

        std::ofstream out("rezultatai.txt");
        for (auto pair : set) {
            if (pair.second > 1) {
                out << "Word '" << pair.first << "' repeats " << pair.second << " times in these lines: ";
                LineMap[pair.first].erase(std::unique(LineMap[pair.first].begin(), LineMap[pair.first].end()), LineMap[pair.first].end());
                out << LineMap[pair.first][0];
                for (auto i = 1; i < LineMap[pair.first].size(); i++) {
                    out << ", " << LineMap[pair.first][i];
                }
                out << endl;
            }
        }
        out << endl;
        out << "URLS:" << endl;
        for (auto i : urls) {
            out << i << endl;
        }
    }
    else {
        cout << "File does not exist!" << endl;
    }
}

void remove(std::string& str, char character)
{
    size_t pos;
    while ((pos = str.find(character)) != string::npos)
    {
        str.erase(pos, 1);
    }

}
void removeSymbols(string& word) {
    remove(word, ';');
    remove(word, ':');
    remove(word, '#');
    remove(word, '|');
    remove(word, '}');
    remove(word, '{');
    remove(word, ']');
    remove(word, '[');
    remove(word, '>');
    remove(word, '<');
    remove(word, '*');
    remove(word, '/');
    remove(word, '\\');
    remove(word, ')');
    remove(word, '(');
    remove(word, '_');
    remove(word, '+');
    remove(word, '"');
    remove(word, '=');
    remove(word, '?');
    remove(word, '!');
    remove(word, ',');
    remove(word, '.');
    remove(word, '&');
    remove(word, '~');
    remove(word, '%');
}
