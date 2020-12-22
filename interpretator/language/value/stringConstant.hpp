namespace interpreter::values {
        class StringConstant : public InterfaceValue {
            string value;
        public:
            void setValue(string v) {
                value = v;
            }

            string getValueTypeName() override {
                return "StringConstant";
            }

            string getValueIntermediateCode() override {
                return "Value_S(" + value + ")";
            }
        };
    }