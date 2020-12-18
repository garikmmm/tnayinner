
namespace interpretator {

    namespace values {
        class Expression : public InterfaceValue {
            operators::InterfaceOperator *op;
        public:
            void setOperator(interpretator::operators::InterfaceOperator *v) {
                op = v;
            }

            interpretator::operators::InterfaceOperator *getOperator() {
                return op;
            }

            string getValueTypeName() override {
                return "Expression";
            }

            string getValueIntermediateCode() override {
                return "Value_E(" + op->getOperatorIntermediateCode() + ")";
            }
        };
    }
}