
namespace interpretator {
    namespace types {
        class Integer : public InterfaceType {
        public:
            TypesEnum getType() const override {
                return TypesEnum::IntegerType;
            }

            string getTypeNameInSource() override {
                return "Int";
            }
        };
    }
}