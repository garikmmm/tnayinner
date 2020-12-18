
namespace interpretator {
    namespace operators {
        class Declare : public InterfaceOperator {
            string variableName;
            types::InterfaceType *variableType;

        public:
            InterfaceOperator *clone() const override {
                return new Declare(*this);
            }

            void setVariableName(string name) {
                variableName = name;
            }

            string getVariableName() {
                return variableName;
            }

            void setVariableType(types::InterfaceType *type) {
                variableType = type;
            }

            types::InterfaceType *getVariableType() {
                return variableType;
            }

            string getOperatorIntermediateCode() const override {
                return "Operator_Declare(" + variableName + ",\"" + variableType->getTypeNameInSource() + "\")";
            }

            string getOperatorNameInSource() override {
                return "Declare";;
            }
        };
    }
}