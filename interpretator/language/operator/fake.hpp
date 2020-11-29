
namespace interpretator {
    namespace operators {
        class Fake : public InterfaceOperator {

        public:
            string getOperatorNameInSource() override {
                return "";
            }
            string getOperatorIntermediateCode() override {
                return "Operator_F(" + getOperatorNameInSource() + "(" + operand1Value.getValueIntermediateCode() + ")";
            }
        };
    }
}