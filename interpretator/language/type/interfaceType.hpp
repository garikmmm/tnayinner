#include <string>

using namespace std;

namespace interpretator {
    namespace types {
        enum TypesEnum {
            IntegerType,
            StringType,
        };

        class InterfaceType {

        public:
            virtual TypesEnum getType() const = 0;

            virtual string getTypeNameInSource() {
                return "__NOT_IMPLEMENTED__InterfaceType__getTypeNameInSource()";
            }
        };
    }
}