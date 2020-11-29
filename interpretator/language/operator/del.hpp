
namespace interpretator {
    namespace operators {
        class Div : public InterfaceOperator {

        public:
            string getOperatorNameInSource() override {
                return "/";
            }
        };
    }
}