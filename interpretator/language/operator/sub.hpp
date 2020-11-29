
namespace interpretator {
    namespace operators {
        class Sub : public InterfaceOperator {

        public:
            string getOperatorNameInSource() override {
                return "-";
            }
        };
    }
}