#include <string>

using namespace std;

namespace interpreter::operators {
        class InterfaceOperator {

        protected:
            values::InterfaceValue *operand1Value;
            string operand1TypeName;

            values::InterfaceValue *operand2Value;
            string operand2TypeName;

            // for log
            int sourceLineNumber;
            string sourceLine;


        public:

            int getSourceLineNumber() const {
                return sourceLineNumber;
            }

            void setSourceLineNumber(int sourceLineNumber) {
                InterfaceOperator::sourceLineNumber = sourceLineNumber;
            }

            const string &getSourceLine() const {
                return sourceLine;
            }

            void setSourceLine(const string &sourceLine) {
                InterfaceOperator::sourceLine = sourceLine;
            }


            virtual InterfaceOperator *clone() const = 0;

//            virtual values::InterfaceValue *execute() const = 0;

            void setOperand1(values::InterfaceValue *value) {
                operand1Value = value;
            }

            void setOperand2(values::InterfaceValue *value) {
                operand2Value = value;
            }

            values::InterfaceValue *getOperand1Value() const {
                return operand1Value;
            }

            values::InterfaceValue *getOperand2Value() const {
                return operand2Value;
            }

            virtual string getOperatorNameInSource() {
                return "__NOT_IMPLEMENTED__InterfaceOperator__getOperatorNameInSource__";
            }

            virtual string getOperatorIntermediateCode() const = 0;
        };
    }