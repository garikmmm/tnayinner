#include <vector>
#include <sstream>
#include <numeric>

class student : public iSerializable {
public:
    std::string name;
    int age;
    float score;
    static const char FIELD_SEPARATOR = ',';
    static const char OBJECT_SEPARATOR = '\n';

    student() {}

    std::string serializeStudent() const override {
        return name + FIELD_SEPARATOR + std::to_string(age) + FIELD_SEPARATOR + std::to_string(score);
    }

    student *unSerializeStudent(std::string line) const override {
        std::stringstream sLine(line);
        std::string segment;
        std::vector<std::string> parts;

        while(std::getline(sLine, segment, FIELD_SEPARATOR))
        {
            parts.push_back(segment);
        }
        student* tmp = new student;
        tmp->name = parts[0];
        tmp->age = std::stoi(parts[1]);
        tmp->score = std::stof(parts[2]);
        return tmp;
    }

    std::string serializeList(std::vector<student *> v) const override {
        std::stringstream ss;
        for(size_t i = 0; i < v.size(); ++i)
        {
            if(i != 0) {
                ss << OBJECT_SEPARATOR;
            }
            ss << v[i]->serializeStudent();
        }
        return ss.str();
    }

    std::vector<student *> unSerializeList(std::string lines) const override {
        std::stringstream sLines(lines);
        std::string segment;
        std::vector<student*> result;
        student* tmp;

        while(std::getline(sLines, segment, OBJECT_SEPARATOR))
        {
            tmp = unSerializeStudent(segment);
            result.push_back(tmp);
        }

        return result;
    }

};