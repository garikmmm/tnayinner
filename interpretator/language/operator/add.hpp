
namespace interpreter::operators {

        class Add : public InterfaceOperator {

        public:
            InterfaceOperator *clone() const override {
                return new Add(*this);
            }

            static string getOperatorNameInSourceStatic() {
                return "+";
            }

            string getOperatorNameInSource() override {
                return Add::getOperatorNameInSourceStatic();
            }

            string getOperatorIntermediateCode() const override{
                return "Operator_Add("
                       + operand1Value->getValueIntermediateCode()
                       + ","
                       + operand2Value->getValueIntermediateCode()
                       + ")";
            }
        };
    }