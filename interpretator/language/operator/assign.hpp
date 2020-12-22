
namespace interpreter::operators {
        class Assign : public InterfaceOperator {

        public:
            InterfaceOperator *clone() const override {
                return new Assign(*this);
            }

            static string getOperatorNameInSourceStatic() {
                return "=";
            }

            string getOperatorNameInSource() override {
                return Assign::getOperatorNameInSourceStatic();
            }

            string getOperatorIntermediateCode() const override {
                return "Operator_Assign(" + operand1Value->getValueIntermediateCode()
                            + "," +
                            operand2Value->getValueIntermediateCode() + ")";
            }
        };
    }