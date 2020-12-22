
namespace interpreter::values {
        class IntegerConstant : public InterfaceValue {
            int value;
        public:
            void setValue(int v) {
                value = v;
            }

            string getValueTypeName() override {
                return "IntegerConstant";
            }

            string getValueIntermediateCode() override {
                return "Value_I(" + std::to_string(value) + ")";
            }
        };
    }