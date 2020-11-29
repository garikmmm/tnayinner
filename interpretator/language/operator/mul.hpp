
namespace interpretator {
    namespace operators {
        class Mul : public InterfaceOperator {

        public:
            string getOperatorNameInSource() override {
                return "*";
            }
        };
    }
}