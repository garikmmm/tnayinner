#include <string>
#include <iostream>

void convertSpaces(std::string &s) {
    int countOfSpaces = 0;
    for(char& c : s) {
        if (' ' == c) {
            ++countOfSpaces;
        }
    }

    int positionToMove = 0;
    std::cout << "s.length(): " << s.length() << std::endl;
    std::cout << "positionToMove: " << positionToMove << std::endl;
    for (int i = s.length() - 1; i > 0 ; --i) {
        if (s[i] == '|') {
            continue;
        }
        if (s[i] == ' ') {
            std::cout << "before s: " << s << std::endl;
            std::cout << "i: " << i << std::endl;
            std::cout << "positionToMove: " << positionToMove << std::endl;
            positionToMove += 3;
            s[s.length() - positionToMove] = '%';
            s[s.length() - positionToMove + 1] = '2';
            s[s.length() - positionToMove + 2] = '0';
            std::cout << "after s: " << s << std::endl;
            continue;
        }
        s[s.length() - 1 - positionToMove] = s[i];
        ++positionToMove;
    }
}

int main() {

    std::string a = "1111 2222 3333||||";
//    std::string a = "2222 3333||";
    std::cout << a << std::endl;

    convertSpaces(a);

    std::cout << a << std::endl;

    return 0;
}