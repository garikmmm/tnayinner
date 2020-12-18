
namespace interpretator {
    namespace operators {
        class Sub : public InterfaceOperator {

        public:

            InterfaceOperator *clone() const override {
                return new Sub(*this);
            }

            static string getOperatorNameInSourceStatic() {
                return "-";
            }

            string getOperatorNameInSource() override {
                return Sub::getOperatorNameInSourceStatic();
            }

            string getOperatorIntermediateCode() const override {
                return "Operator_Sub("
                       + operand1Value->getValueIntermediateCode()
                       + ","
                       + operand2Value->getValueIntermediateCode()
                       + ")";
            }
        };
    }
}