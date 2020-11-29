#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

namespace interpretator {

    class Parser {
        const bool DEBUG = true;
        const char COMMAND_SEPARATOR = ';';
        const string COMMAND_SEPARATOR_STRING = ";";
        string _sourceContents;

        unordered_map<string, types::InterfaceType> _types;
        unordered_map<string, operators::InterfaceOperator> _operators;
        unordered_map<string, operators::InterfaceOperator> _functions;
        vector<operators::InterfaceOperator> _commands;

        void initializeTypes() {
            types::Integer i;
            types::String s;
            _types[i.getTypeNameInSource()] = i;
            _types[s.getTypeNameInSource()] = s;
        }
        void initializeOperators() {
            operators::Assign assign;
            operators::Add add;
            operators::Div del;
            operators::Mul mul;
            operators::Sub sub;
            _operators[assign.getOperatorNameInSource()]  = assign;
            _operators[add.getOperatorNameInSource()]     = add;
            _operators[del.getOperatorNameInSource()]     = del;
            _operators[mul.getOperatorNameInSource()]     = mul;
            _operators[sub.getOperatorNameInSource()]     = sub;
        }
        void initializeStandardFunctoins() {
        }

        bool isLastCharacterCommandSeparator(string &line) {
            return COMMAND_SEPARATOR == line.back();
        }

        void removeCommentFromLine(string &line) {
            line = line.substr(0, line.find("%", 0));
        }

        bool isEmptyLine(string &line) {
            return line == "" || line == " ";
        }
        string getVariableNameFromPosition(string &line, int position) {
            auto it = line.begin();
            it += position;
            if (isdigit(*it)) {
                if (DEBUG) {
                    cout << "Error: variable name cannot start with digit" << endl;
                }
                throw "Error: variable name cannot start with digit";
            }
            string name = "";
            while (it != line.end() && isalnum(*it)) {
                name += *it;
                ++it;
            }

            return name;
        }

        string getConstantIntegerFromPosition(string &line, int position) {
            auto it = line.begin();
            it += position;
            if (!isdigit(*it)) {
                return "";
            }
            string value = "";
            while (it != line.end() && isdigit(*it)) {
                value += *it;
                ++it;
            }

            return value;
        }

        string getConstantStringFromPosition(string &line, int position) {
            auto it = line.begin();
            it += position;
            if (*it != '"') {
                return "";
            }
            it += 1;
            string value = "\"";
            while (it != line.end() && *it != '"') {
                value += *it;
                ++it;
            }
            if (*it != '"') {
                if (DEBUG) {
                    cout << "Error: String is not closed" << endl;
                }
                throw "Error: String is not closed";
            }

            value += "\"";
            return value;
        }

        void removeSpacesFromLine(string &line) {
            // remove tabs
            line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
            // remove comments
            removeCommentFromLine(line);
            // replace multiple spaces with one space
            utils::removeSpaces(line);
            utils::trim(line);
            // remove spaces near the operators
            for(auto kv : _operators) {
                utils::replaceAll(line, kv.first + " ", kv.first);
                utils::replaceAll(line, " " + kv.first, kv.first);
            }
            // remove space before COMMAND_SEPARATOR
            utils::replaceAll(line, " " + COMMAND_SEPARATOR_STRING, COMMAND_SEPARATOR_STRING);
        }


//        operators::InterfaceOperator& createOperatorByNameInSource(string nameInSource) {
//            switch (nameInSource.at(0)) {
//                case '+':
//                    return operators::Add;
//                    break;
//                case '-':
//                    return operators::Sub;
//                    break;
//                case '*':
//                    return operators::Mul;
//                    break;
//                case '/':
//                    return operators::Div;
//                    break;
//            }
//            if (DEBUG) {
//                cout << "Error: Unknown operator: '" << nameInSource << "'" << endl;
//            }
//            throw "Error: Unknown operator: '" + nameInSource + "'";
//        }

        operators::InterfaceOperator parseExpression(string &expression) {
            // assuming that expression is: variable operator variable operator ...
            bool isTimeForOperator = false;
            operators::InterfaceOperator lastOperator;
            bool isLastOperatorInitialized = false;
            values::InterfaceValue lastValue;
            bool isLastValuerInitialized = false;
            string::size_type i = 0;
            while (i < expression.size()) {
                if (isTimeForOperator) {
                    string operatorCharacter = string(1, expression[i]);
                    std::unordered_map<string, operators::InterfaceOperator>::const_iterator it = _operators.find(operatorCharacter);
                    if ( it == _operators.end() ) {
                        if (COMMAND_SEPARATOR_STRING == operatorCharacter) {
                            break;
                        }
                        if (DEBUG) {
                            cout << "Error: Unknown operator: '" << operatorCharacter << "'" << endl;
                        }
                        throw "Error: Unknown operator: '" + operatorCharacter + "'";
                    }

//                    lastOperator = createOperatorByNameInSource(operatorCharacter);
                    isLastOperatorInitialized = true;
                    lastOperator = it->second;
                    lastOperator.setOperand1(lastValue);

                    isTimeForOperator = false;
                } else {
                    string value = getConstantIntegerFromPosition(expression, i);
                    if ("" != value) { // try constant integer
                        values::IntegerConstant ic;
                        ic.setValue(stoi(value));
                        if (!isLastOperatorInitialized) {
                            isLastValuerInitialized = true;
                            lastValue = ic;
                            i += value.size() - 1;
                        } else {
                            // end of one cycle
                            lastOperator.setOperand2(ic);
                            if (DEBUG) {
                                cout << "INFO: found operator with: '" << lastOperator.getOperatorIntermediateCode() << "'" << endl;
                            }
                            // @todo implement multiple operators in expression
                            return lastOperator;
                        }
                    }
                    if("" == value) { // try constant string
                        value = getConstantStringFromPosition(expression, i);
                        if("" != value) {
                            values::StringConstant sc;
                            sc.setValue(value);
                            if (!isLastOperatorInitialized) {
                                isLastValuerInitialized = true;
                                lastValue = sc;
                                i += value.size() - 1;
                            } else {
                                // end of one cycle
                                lastOperator.setOperand2(sc);
                                if (DEBUG) {
                                    cout << "INFO: found operator with: '" << lastOperator.getOperatorIntermediateCode() << "'" << endl;
                                }
                                // @todo implement multiple operators in expression
                                return lastOperator;
                            }
                        }
                    }

                    if("" == value) { // try variable name
                        value = getVariableNameFromPosition(expression, i);
                        if("" != value) {
                            values::Variable v;
                            v.setVariableName(value);
                            if (!isLastOperatorInitialized) {
                                isLastValuerInitialized = true;
                                lastValue = v;
                                i += value.size() - 1;
                            } else {
                                // end of one cycle
                                lastOperator.setOperand2(v);
                                if (DEBUG) {
                                    cout << "INFO: found operator with: '" << lastOperator.getOperatorIntermediateCode() << "'" << endl;
                                }
                                // @todo implement multiple operators in expression
                                return lastOperator;
                            }
                        }
                    }

                    if("" == value) { // can't find int, string or variable name
                        if (DEBUG) {
                            cout << "Error: can't find int, string or variable name, expression: '" << expression << "'" << endl;
                        }
                        throw "can't find int, string or variable name, expression: '" + expression + "'";
                    }

                    isTimeForOperator = true;
                }
                i++;
            }
            // check if it doesn't contain any operator
            if (!isLastOperatorInitialized && isLastValuerInitialized) {
                operators::Fake f;
                f.setOperand1(lastValue);
                if (DEBUG) {
                    cout << "INFO: found 1 operand, operator: '" << f.getOperatorIntermediateCode() << "'" << endl;
                }
                return f;
            }
            if (DEBUG) {
                cout << "Error: operator with 2 operands not found, expression: '" << expression << "'" << endl;
            }
            throw "Error: operator with 2 operands not found, expression: '" + expression + "'";
        }

        /**
         *
         * supported commands are:
         *   1. Typename variable;                // Int a;
         *   2. Typename variable = expression;   // String a = "asdf";
         *   3. variable = expression;            // a = 7; a = b; a = a + 9; a = b + c;
         *   4. native function call;             // print(a);
         *   5. comment                           // // Lorem ipsum
         *   6. line without any command          //
         *   don't support expression with more than 2 operators // a = a + 2 + 3;
         * @param line
         * @param lineNumber
         */
        void parseCommand(string line, int lineNumber) {
            if (DEBUG) {
                cout << "============" << endl << "Line " << lineNumber << ": " << line << endl;
            }

            removeSpacesFromLine(line);

            if (DEBUG) {
                cout << "Cleaned line: " << line << endl;
            }

            // #5, #6
            if (isEmptyLine(line)) {
                if (DEBUG) {
                    cout << "Skipping: empty line" << endl;
                }
                return;
            }

            operators::Assign commandAssign;

            if (!isLastCharacterCommandSeparator(line)) {
                if (DEBUG) {
                    cout << "Error: line doesn't end with '" << COMMAND_SEPARATOR_STRING << "'" << endl;
                }
                throw "Error on line: " + std::to_string(lineNumber) + ", missing " + COMMAND_SEPARATOR_STRING;
            }

            // #4 find if the command uses a standard language function
            for(auto kv : _functions) {
                std::size_t found = line.find(kv.first);
                if (found == 0) {
                    if (DEBUG) {
                        cout << "Error: Not implemented standard function:" << kv.first << endl;
                    }
//                    throw "Not implemented on line: " + std::to_string(lineNumber);
                    return;
                }
            }

            // #1 or #2 variable declaration with or without expression
            for(auto kv : _types) {
                std::size_t found = line.find(kv.first + " "); // add space after Typename
                if (found == 0) {
                    string variableName = getVariableNameFromPosition(line, kv.first.size() + 1);
                    string variableTypeName = kv.first;
                    if (DEBUG) {
                        cout << "Info: found variable declaration, type:" << variableTypeName
                                << ", name: " << variableName << endl;
                    }
                    operators::Declare commandDeclare;
                    commandDeclare.setVariableName(variableName);
                    commandDeclare.setVariableType(kv.second);
                    _commands.push_back(commandDeclare);

                    string beforeAssign = variableTypeName + " " + variableName;
                    bool isVariableAssigned = line.at(beforeAssign.size()) == commandAssign.getOperatorNameInSource().at(0) ;
                    if (isVariableAssigned) {
                        // beforeAssign + "=" => beforeAssign.size() + 1
                        string assignExpression = line.substr(beforeAssign.size() + 1);
                        if (DEBUG) {
                            cout << "Info: found variable assignment, expression:" << assignExpression << endl;
                        }
                        parseExpression(assignExpression);
                        return;
                    }
                    return;
                }
            }


            // #3
            std::size_t assignPosition = line.find(commandAssign.getOperatorNameInSource().at(0)); // add space after Typename
            if (assignPosition != string::npos) {
                string variableName = line.substr(0, assignPosition);
                string assignExpression = line.substr(assignPosition + 1);

                if (DEBUG) {
                    cout << "Info: found variable assignment, variable: " << variableName << ", expression:" << assignExpression << endl;
                }

                parseExpression(assignExpression);
                _commands.push_back(commandAssign);
            } else {
                if (DEBUG) {
                    cout << "Skipping: found expression without assignment" << endl;
                }
            }

        }

    public:
        Parser() {
            initializeTypes();
            initializeOperators();
            initializeStandardFunctoins();
        }
        void parse(string sourcePath) {
            _sourceContents = utils::getFileContents(sourcePath);
            istringstream ss(_sourceContents);
            string line;
            int lineNumber = 0;
            while(std::getline(ss, line, '\n')) {
                ++lineNumber;
                parseCommand(line, lineNumber);
            }

        }
    };
}