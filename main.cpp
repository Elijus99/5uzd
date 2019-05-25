#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <regex>
#include <vector>

using std::string;
using std::cout;
using std::endl;

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
        std::map<string, string> LineMap;
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
                        LineMap[word] = LineMap[word] + ", " + std::to_string(lineNum);
                    }
                }
                else LineMap[word] = std::to_string(lineNum);
            }
            lineNum++;

        }
        std::ofstream out("rezultatai.txt");
        for (auto pair : WordMap) {
            if (pair.second > 1) {
                cout << "Word '" << pair.first << "' repeats " << pair.second << " times in these lines: " << LineMap[pair.first] << endl;
            }
        }
        cout << endl;
        cout << "URLS:" << endl;
        for (auto i : urls) {
            cout << i << endl;
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
