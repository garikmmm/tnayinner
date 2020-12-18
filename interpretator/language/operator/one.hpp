
namespace interpretator {
    namespace operators {
        class One : public InterfaceOperator {

        public:
            InterfaceOperator *clone() const override {
                return new One(*this);
            }

            static string getOperatorNameInSourceStatic() {
                return "1";
            }

            string getOperatorNameInSource() override {
                return One::getOperatorNameInSourceStatic();
            }

            string getOperatorIntermediateCode() const override {
                return "Operator_1(" + operand1Value->getValueIntermediateCode()
                       + ")";
            }
        };
    }
}