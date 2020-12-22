
namespace interpreter::operators {
        class Mul : public InterfaceOperator {

        public:
            InterfaceOperator *clone() const override {
                return new Mul(*this);
            }

            static string getOperatorNameInSourceStatic() {
                return "*";
            }

            string getOperatorNameInSource() override {
                return Mul::getOperatorNameInSourceStatic();
            }

            string getOperatorIntermediateCode() const override {
                return "Operator_Mul("
                       + operand1Value->getValueIntermediateCode()
                       + ","
                       + operand2Value->getValueIntermediateCode()
                       + ")";
            }
        };
    }