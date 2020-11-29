#include <string>

using namespace std;

namespace interpretator {
    namespace operators {
        class InterfaceOperator {

        protected:
            values::InterfaceValue operand1Value;
            string operand1Name;

            values::InterfaceValue operand2Value;
            string operand2Name;


        public:
            void setOperand1(values::InterfaceValue value) {
                operand1Value = value;
            }

            void setOperand2(values::InterfaceValue value) {
                operand2Value = value;

            }

            virtual string getOperatorNameInSource() {
                return "__NOT_IMPLEMENTED__";
            }

            virtual string getOperatorIntermediateCode() {
                return "Operator_" + getOperatorNameInSource() + "(" + operand1Value.getValueIntermediateCode() + "," + operand2Value.getValueIntermediateCode() + ")";
            }
        };
    }
}