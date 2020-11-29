
namespace interpretator {
    namespace operators {
        class Assign : public InterfaceOperator {

        public:
            string getOperatorNameInSource() override {
                return "=";
            }
        };
    }
}