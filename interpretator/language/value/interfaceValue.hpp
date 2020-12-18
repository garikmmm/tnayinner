#include <string>

using namespace std;

namespace interpretator {
    namespace values {
        class InterfaceValue {

        public:

            virtual string getValueTypeName() {
                return "__NOT_IMPLEMENTED__InterfaceValue__getValueTypeName__";
            }

            virtual string getValueIntermediateCode() {
                return "__NOT_IMPLEMENTED__InterfaceValue__getValueIntermediateCode__";
            }
        };
    }
}