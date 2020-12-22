
namespace interpreter::values {
        class Variable : public InterfaceValue {
            string variableName;
        public:
            void setVariableName(string v) {
                variableName = v;
            }

            string getVariableName() {
                return variableName;
            }

            string getValueTypeName() override {
                return "Variable";
            }

            string getValueIntermediateCode() override {
                return "Value_V(" + variableName + ")";
            }
        };
    }