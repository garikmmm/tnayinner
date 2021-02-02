class student;

class iSerializable {

public:
    virtual std::string serializeStudent() const = 0;
    virtual student* unSerializeStudent(std::string) const = 0;
    virtual std::string serializeList(std::vector<student*>) const = 0;
    virtual std::vector<student*> unSerializeList(std::string) const = 0;
};


