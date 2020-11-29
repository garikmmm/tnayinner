#include <string>

using namespace std;

namespace interpretator {
    namespace values {
        class InterfaceValue {

        public:
//            template <typename T>
//            void setValue(T) {
//            }

            virtual string getValueTypeName() {
                return "__NOT_IMPLEMENTED__";
            }

            virtual string getValueIntermediateCode() {
                return "__NOT_IMPLEMENTED__";
            }
        };
    }
}