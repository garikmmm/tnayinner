#include <fstream>
#include <string>
#include <iostream>
#include <streambuf>

#include "iSerializable.h"
#include "student.h"

int main() {

    student* codeRepublicStudent1 = new student;
    codeRepublicStudent1->name = "Valodik";
    codeRepublicStudent1->age = 20;
    codeRepublicStudent1->score = 4.8;
    student* codeRepublicStudent2 = new student;
    codeRepublicStudent2->name = "Parandzem";
    codeRepublicStudent2->age = 18;
    codeRepublicStudent2->score = 4.9;
    std::vector<student*> v;
    v.push_back(codeRepublicStudent1);
    v.push_back(codeRepublicStudent2);

    // write to file
    std::string s = codeRepublicStudent1->serializeList(v);
    std::ofstream out("db.txt");
    out << s;
    out.close();
    std::cout << "Initial string:" << std::endl;
    std::cout << s << std::endl;

    // read from file
    std::ifstream t("db.txt");
    std::stringstream buffer;
    buffer << t.rdbuf();
    t.close();

    // unserialize
    std::vector<student *> unserializedList = codeRepublicStudent1->unSerializeList(buffer.str());
    // print
    std::cout << "Serialized -> Unserialized -> Serialized string:" << std::endl;
    std::cout << codeRepublicStudent1->serializeList(unserializedList) << std::endl;
    return 0;
}

