using namespace std;

namespace interpretator {
    namespace executor {
        class Executor {

        private:
            unordered_map<string, executor::Variable *> _variables;
            const bool DEBUG = false;
            string _sourceContents;

            bool isString(string& s) {
                return '"' == s.front() && '"' == s.back();
            }

            bool isInteger(string& s) {
                return !s.empty() && std::find_if(s.begin(),
                          s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
            }

            string getOperatorName(string &s) {
                std::size_t found = s.find('(');
                if (found == std::string::npos) {
                    return "";
                }
                string operatorName = s.substr(0, found);
                return operatorName;
            }

            vector<string> *getOperatorArguments(string &s) {
                int length = s.length();
                int countOfOpeningBraces = 0;
                int countOfClosingBraces = 0;
                int start = 0;
                int i = 0;

                if ('(' != s[i]) {
                    cout << "Error in intermediate code: after operator name should be (" << endl;
                    throw "Error in intermediate code: after operator name should be ";
                }
                countOfOpeningBraces = 1;
                ++i;

                bool isInString = false;

                vector<string> *result = new vector<string>;
                while (i < length && countOfOpeningBraces != countOfClosingBraces) {
                    if ('"' == s[i]) {
                        isInString = !isInString;
                    }
                    if (!isInString && '(' == s[i]) {
                        ++countOfOpeningBraces;
                    }
                    if (!isInString && ')' == s[i]) {
                        ++countOfClosingBraces;
                    }
                    if (!isInString && ',' == s[i] && countOfOpeningBraces == countOfClosingBraces + 1) {
                        result->push_back(s.substr(start + 1, i - start - 1));
                        start = i;
                    }
                    ++i;
                }

                // last argument
                if (countOfOpeningBraces == countOfClosingBraces) {
                    result->push_back(s.substr(start + 1, i - start - 2));
                }
                return result;
            }


            Executor() {
            }

            Executor(Executor const &);

            void operator=(Executor const &);

            executor::Variable* Operator_Declare(string name, types::TypesEnum type) {
                if ("" == name) {
                    throw "Variable name is empty";
                }
                if (isVariableWithNameDeclared(name)) {
                    throw "Variable " + name + " is already declared";
                }

                executor::Variable *variable = new executor::Variable;
                variable->setVariableName(name);
                variable->setType(type);

                _variables[name] = variable;

                return variable;
            }

            void assignVariable(string name, values::Variable *value) {
//            if (!isVariableWithNameDeclared(name)) {
//                throw "Variable " + name + " must be declared before usage";
//            }
////            if (variable->getValueTypeName() != newValue->getValueTypeName()) {
////                throw "Variable " + variable->getVariableName() + " type is different than a value assigned: "
////                      + variable->getValueTypeName() + ", " + newValue->getValueTypeName();
////            }
//            executor::Variable* v = Executor::getInstance().getVariables().at(name);
//            evaluateExpression(v, expression);
            }

        public:
            executor::Variable *getVariableByName(string name) {
                if (!isVariableWithNameDeclared(name)) {
                    if (DEBUG) {
                        cout << "Variable " + name + " is not declared" << endl;
                    }
                    throw "Variable " + name + " is not declared";
                }
                return _variables.find(name)->second;
            }

            bool isVariableWithNameDeclared(string name) {
                unordered_map<string, executor::Variable *>::const_iterator got = _variables.find(name);
                return got != _variables.end();
            }

            executor::Variable* Operator_Assign(string name, executor::Variable *variable) {
                if (!isVariableWithNameDeclared(name)) {
                    if (DEBUG) {
                        cout << "Variable " + name + " must be declared before assign" << endl;
                    }
                    throw "Variable " + name + " must be declared before assign";
                }
                executor::Variable *v = getVariableByName(name);
                if (variable->getType() != v->getType()) {
                    throw "Variable type is different than a value assigned. New: "
                          + variable->getVariableName() + ", old: " + v->getVariableName();
                }
                v->setVariableValue(variable->getVariableValue());
                return v;
            }

            void executeFile(string sourcePath) {
                _sourceContents = utils::getFileContents(sourcePath);
                istringstream ss(_sourceContents);
                string line;
                int lineNumber = 0;
                while (std::getline(ss, line, '\n')) {
                    ++lineNumber;
                    executeLine(line, lineNumber, 0);
                }
            }

            executor::Variable* executeOperatorWithArguments(string &s) {
                executor::Variable* v;
                if (isString(s)) {
                    v = new executor::Variable;
                    v->setType(types::TypesEnum::StringType);
                    v->setVariableStringValue(new string(s));
                } else if (isInteger(s)) {
                    v = new executor::Variable;
                    v->setType(types::TypesEnum::IntegerType);
                    v->setVariableIntegerValue(new int(std::stoi( s )));
                } else {
                    string o = getOperatorName(s);
                    string as = s.substr(o.length());
                    vector<string>* oa = getOperatorArguments(as);
                    v = executeOperator(o, oa);
                }
                return v;
            }
            executor::Variable* executeOperator(string &operatorName, vector<string> *arguments) {
                if ("Operator_Print" == operatorName) {
                    string expressionArguments = arguments->at(0);
                    string o = getOperatorName(expressionArguments);
                    string as = expressionArguments.substr(o.length());
                    vector<string>* oa = getOperatorArguments(as);
                    executor::Variable* printValue = executeOperator(o, oa);

                    std::cout << "Type: " << printValue->getType()
                                << ", value: ";
                    if (types::TypesEnum::StringType == printValue->getType()) {
                        std::cout << printValue->getVariableStringValue() << std::endl;
                    } else {
                        std::cout << printValue->getVariableIntegerValue() << std::endl;
                    }


                    return printValue;
                }
                if ("Operator_1" == operatorName || "Value_E" == operatorName) {
                    string expressionArguments = arguments->at(0);
                    string o = getOperatorName(expressionArguments);
                    string as = expressionArguments.substr(o.length());
                    vector<string>* oa = getOperatorArguments(as);

                    return executeOperator(o, oa);
                }
                if ("Value_V" == operatorName) {
                    string variableName = arguments->at(0);
                    return getVariableByName(variableName);
                }
                if ("Value_I" == operatorName) {
                    string variableValue = arguments->at(0);
                    executor::Variable* v = new executor::Variable;
                    v->setVariableValue(new int(std::stoi(variableValue)));
                    v->setType(types::TypesEnum::IntegerType);
                    return v;
                }
                if ("Value_S" == operatorName) {
                    string variableValue = arguments->at(0);
                    executor::Variable* v = new executor::Variable;
                    v->setVariableValue(new string(variableValue.substr(1, variableValue.size() - 2)));
                    v->setType(types::TypesEnum::StringType);
                    return v;
                }
                if ("Operator_Declare" == operatorName) {
                    string variableName = arguments->at(0);
                    string variableTypeString = arguments->at(1);
                    types::TypesEnum type;
                    if ("\"Int\"" == variableTypeString) {
                        type = types::TypesEnum::IntegerType;
                    } else if ("\"String\"" == variableTypeString) {
                        type = types::TypesEnum::StringType;
                    } else {
                        if (DEBUG) {
                            cout << "Error: unknown type declaration: " << type << endl;
                        }
                        throw "Error: unknown type declaration: " + variableTypeString;
                    }
                    return Operator_Declare(variableName, type);
                }
                if ("Operator_Assign" == operatorName) {
                    string argument1String = arguments->at(0);
                    string argument2String = arguments->at(1);
                    string variableOperatorName = getOperatorName(argument1String);
                    if ("Value_V" != variableOperatorName) {
                        if (DEBUG) {
                            cout << "Error: Only variable can be assigned: " << variableOperatorName << endl;
                        }
                        throw "Error: Only variable can be assigned: " + variableOperatorName;
                    }
                    string variableArgumentsString = argument1String.substr(variableOperatorName.length());
                    vector<string>* variableArguments = getOperatorArguments(variableArgumentsString);
                    executor::Variable* variableToAssign = executeOperator(variableOperatorName, variableArguments);

                    string valueOperatorName = getOperatorName(argument2String);
                    string valueArgumentsString = argument2String.substr(valueOperatorName.length());
                    vector<string>* valueOperatorArguments = getOperatorArguments(valueArgumentsString);

                    executor::Variable* variableValue = executeOperator(valueOperatorName, valueOperatorArguments);

                    return Operator_Assign(variableToAssign->getVariableName(), variableValue);
                }
                if ("Operator_Add" == operatorName) {
                    string arg0String = arguments->at(0);
                    string arg1String = arguments->at(1);

                    executor::Variable* arg0 = executeOperatorWithArguments(arg0String);
                    executor::Variable* arg1 = executeOperatorWithArguments(arg1String);

                    if (arg0->getType() != arg0->getType()) {
                        if (DEBUG) {
                            cout << "Error: arguments for math operation must be of same type " << endl;
                        }
                        throw "Error: arguments for math operation must be of same type " ;
                    }

                    executor::Variable* tmpResult = new executor::Variable;

                    if (types::TypesEnum::StringType == arg0->getType()) {
                        std::string* value;
                        value = new string(arg0->getVariableStringValue()
                                    + arg1->getVariableStringValue());
                        tmpResult->setVariableStringValue(value);
                        tmpResult->setType(types::TypesEnum::StringType);
                    }
                    if (types::TypesEnum::IntegerType == arg0->getType()) {
                        int tmp = arg0->getVariableIntegerValue()
                                  + arg1->getVariableIntegerValue();
                        int* value;
                        value = new int(tmp);
                        tmpResult->setVariableIntegerValue(value);
                        tmpResult->setType(types::TypesEnum::IntegerType);
                    }

                    return tmpResult;
                }

                if (DEBUG) {
                    cout << "Error: unsupported operator: " << operatorName << endl;
                }
                throw "unsupported operator: " + operatorName;
//                for (std::vector<string>::const_iterator i = arguments->begin(); i != arguments->end(); ++i) {
//                    string tmpOperatorName = getOperatorName(*i);
//                    if ("" == tmpOperatorName) {
//                        if () {
//
//                        }
//                    }
//                    string tmpArgumentsString = line.substr(tmpOperatorName.length());
//                    vector<string> *tmpArguments = getOperatorArguments(tmpArgumentsString);
//
//
//                }
//                string operatorName = getOperatorName(line);
//
//                string argumentsString = line.substr(operatorName.length());
//                vector<string> *arguments = getOperatorArguments(argumentsString);
//                if (DEBUG) {
//                    cout << "operatorName: " << operatorName << endl
//                         << "arguments: ";
//                    for (std::vector<string>::const_iterator i = arguments->begin(); i != arguments->end(); ++i) {
//                        std::cout << *i << " ";
//                    }
//                    cout << endl;
//                }
//
//                executeOperator(operatorName, arguments);
            }

            void executeLine(string &line, int lineNumber, int sourceLineNumber) {
                if (DEBUG) {
                    cout << "-------" << endl << "Line " << lineNumber << ": " << line << endl;
                }

                string operatorName = getOperatorName(line);

                string argumentsString = line.substr(operatorName.length());
                vector<string> *arguments = getOperatorArguments(argumentsString);
                if (DEBUG) {
                    cout << "operatorName: " << operatorName << endl
                         << "arguments: ";
                    for (std::vector<string>::const_iterator i = arguments->begin(); i != arguments->end(); ++i) {
                        std::cout << *i << " ";
                    }
                    cout << endl;
                }

                executeOperator(operatorName, arguments);
            }

            static Executor &getInstance() {
                static Executor instance;
                // Instantiated on first use.
                return instance;
            }

        };
    }
}