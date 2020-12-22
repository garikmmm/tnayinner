
namespace interpreter::values {
        class Expression : public InterfaceValue {
            operators::InterfaceOperator *op;
        public:
            void setOperator(interpreter::operators::InterfaceOperator *v) {
                op = v;
            }

            interpreter::operators::InterfaceOperator *getOperator() {
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