#include <fstream>
#include <string>
#include <iostream>

#include "iSerializable.h"
#include "student.h"

int main() {

    student codeRepublicStudent1;
    codeRepublicStudent1.name = "Valodik";
    codeRepublicStudent1.age = 20;
    codeRepublicStudent1.score = 4.8;
    student codeRepublicStudent2;
    codeRepublicStudent1.name = "Parandzem";
    codeRepublicStudent1.age = 18;
    codeRepublicStudent1.score = 4.9;
    std::vector<student> v;
    v.push_back(codeRepublicStudent1);
    v.push_back(codeRepublicStudent2);

    std::string s = codeRepublicStudent1.serializeList(v);
    std::ofstream out("db.txt");
    out << s;
    out.close();


    return 0;

}

