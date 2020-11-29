
namespace interpretator {
    namespace operators {
        class Declare : public InterfaceOperator {
            string variableName;
            types::InterfaceType variableType;

        public:

            void setVariableName(string name) {
                variableName = name;
            }
            void setVariableType(types::InterfaceType type) {
                variableType = type;
            }

            string getOperatorIntermediateCode() override {
                return "OperatorDeclare(" + variableName + "," + variableType.getTypeNameInSource() + ")";
            }
            string getOperatorNameInSource() override {
                return "";
            }
        };
    }
}