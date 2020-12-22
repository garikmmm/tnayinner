#include <string>

using namespace std;

namespace interpreter::types {
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