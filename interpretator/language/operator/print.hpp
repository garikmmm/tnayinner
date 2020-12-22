
namespace interpreter::operators {

        class Print : public InterfaceOperator {

        public:
            InterfaceOperator *clone() const override {
                return new Print(*this);
            }

            static string getOperatorNameInSourceStatic() {
                return "Print";
            }

            string getOperatorNameInSource() override {
                return Print::getOperatorNameInSourceStatic();
            }

            string getOperatorIntermediateCode() const override {
                return "Operator_Print(" + operand1Value->getValueIntermediateCode() + ")";
            }
        };
    }