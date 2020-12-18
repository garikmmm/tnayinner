
namespace interpretator {
    namespace operators {
        class Div : public InterfaceOperator {

        public:
            InterfaceOperator *clone() const override {
                return new Div(*this);
            }

            static string getOperatorNameInSourceStatic() {
                return "/";
            }

            string getOperatorNameInSource() override {
                return Div::getOperatorNameInSourceStatic();
            }

            string getOperatorIntermediateCode() const override {
                return "Operator_Div("
                       + operand1Value->getValueIntermediateCode()
                       + ","
                       + operand2Value->getValueIntermediateCode()
                       + ")";
            }
        };
    }
}