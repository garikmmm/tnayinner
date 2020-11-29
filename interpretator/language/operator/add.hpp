
namespace interpretator {

    namespace operators {

        class Add : public InterfaceOperator {

        public:
            string getOperatorNameInSource() override {
                return "+";
            }
        };
    }
}