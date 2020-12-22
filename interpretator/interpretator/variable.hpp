using namespace std;

namespace interpretator {
    namespace executor {

        class Variable {

            string variableName;
            void *variableValue;
            types::TypesEnum type;

        public:
            ~Variable() {
                if (types::TypesEnum::IntegerType == type) {
                    delete static_cast<int *>(variableValue);
                } else {
                    delete static_cast<std::string *>(variableValue);
                }
            }

            const string &getVariableName() const {
                return variableName;
            }

            void setVariableName(const string &variableName) {
                Variable::variableName = variableName;
            }

            void *getVariableValue() const {
                return variableValue;
            }

            std::string getVariableStringValue() const {
                return *static_cast<std::string*>(variableValue);
            }

            int getVariableIntegerValue() const {
                return *(int*)variableValue;
            }

            void setVariableValue(void *value) {
                variableValue = value;
            }
            void setVariableStringValue(string* value) {
                variableValue = value;
            }
            void setVariableIntegerValue(int* value) {
                variableValue = value;
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