#include <vector>
#include <sstream>
#include <numeric>

class student : public iSerializable {
public:
    std::string name;
    int age;
    float score;
    static const char FIELD_SEPARATOR = ',';
    static const char OBJECT_SEPARATOR = '|';

    std::string serializeStudent() {
        return name + FIELD_SEPARATOR + std::to_string(age) + FIELD_SEPARATOR + std::to_string(score) + FIELD_SEPARATOR;
    }

    student* unSerializeStudent(std::string line) {
        std::stringstream sLine(line);
        std::string segment;
        std::vector<std::string> parts;

        while(std::getline(sLine, segment, '_'))
        {
            parts.push_back(segment);
        }
        student* tmp = new student;
        tmp->name = parts[0];
        tmp->age = std::stoi(parts[1]);
        tmp->score = std::stof(parts[2]);
        return tmp;
    }


    std::string serializeList(std::vector<student> v) {
        std::string result = std::accumulate(std::begin(v), std::end(v), std::string(),
                                             [](std::string &ss, student &s)
                                             {
                                                 std::string item = s.serializeStudent();
                                                 return ss.empty() ? item : ss + OBJECT_SEPARATOR + item;
                                             });
        return result;

    }

    std::vector<student*> unSerializeList(std::string lines) {
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