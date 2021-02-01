class student;

class iSerializable {

public:
    virtual std::string serializeStudent();
    virtual student* unSerializeStudent(std::string line);
    virtual std::string serializeList(std::vector<student*> v);
    virtual std::vector<student*> unSerializeList(std::string);

};


