
namespace interpretator {
    namespace types {
        class Integer : public InterfaceType {
        public:
            virtual string getTypeNameInSource() override {
                return "Int";
            }
        };
    }
}