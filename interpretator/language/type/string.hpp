namespace interpretator {
    namespace types {
        class String : public InterfaceType {
        public:

            TypesEnum getType() const override {
                return TypesEnum::StringType;
            }

            string getTypeNameInSource() override {
                return "String";
            }
        };
    }
}