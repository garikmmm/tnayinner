using namespace std;

namespace interpretator {
    namespace executor {

        class Variable {

            string variableName;
            void *variableValue;
            types::TypesEnum type;

        public:
            const string &getVariableName() const {
                return variableName;
            }

            void setVariableName(const string &variableName) {
                Variable::variableName = variableName;
            }

            void *getVariableValue() const {
                return variableValue;
            }

            std::string* getVariableStringValue() const {
                return static_cast<std::string*>(variableValue);
            }

            int getVariableIntegerValue() const {
                union void_cast {
                    void* ptr;
                    int value;
                };
                union void_cast u;
                u.ptr = variableValue;
                return u.value;
            }

            void setVariableValue(void *value) {
                variableValue = value;
            }
            void setVariableStringValue(string *value) {
                variableValue = (void*)value;
            }
            void setVariableIntegerValue(int *value) {
                variableValue = (void*)value;
            }

            types::TypesEnum getType() const {
                return type;
            }

            void setType(types::TypesEnum type) {
                Variable::type = type;
            }
        };
    }
}