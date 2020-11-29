namespace interpretator {
    namespace types {
        class String : public InterfaceType {
        public:
            virtual string getTypeNameInSource() override {
                return "String";
            }
        };
    }
}