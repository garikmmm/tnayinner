#include <iostream>

#include "language/type/interfaceType.hpp"
#include "language/type/string.hpp"
#include "language/type/integer.hpp"

#include "language/value/interfaceValue.hpp"
#include "language/value/integerConstant.hpp"
#include "language/value/stringConstant.hpp"
#include "language/value/variable.hpp"

#include "interpreter/variable.hpp"

#include "language/operator/interfaceOperator.hpp"
#include "language/operator/declare.hpp"
#include "language/operator/assign.hpp"
#include "language/operator/add.hpp"
#include "language/operator/div.hpp"
#include "language/operator/mul.hpp"
#include "language/operator/sub.hpp"
#include "language/operator/one.hpp"
#include "language/operator/print.hpp"

#include "language/value/expression.hpp"

#include "compiler/utils.hpp"
#include "compiler/parser.hpp"

#include "interpreter/executor.hpp"

using namespace interpreter;
using namespace executor;

int main(int argc, char *argv[]) {

    if (2 != argc) {
        printf("Usage is: interpreter example.code");
        return 0;
    }
    string fileBaseNameWithPath = "/Applications/MAMP/htdocs/tnayinner/interpreter/a";
    ofstream intermediateFile(fileBaseNameWithPath + ".intermediate");
    Parser p;
    Executor e;

//    p.parse(argv[1]);
    vector<operators::InterfaceOperator *> commands;
    commands = p.parse(fileBaseNameWithPath + ".code");
    std::cout << "==============================" << std::endl
              << "Starting execution:" << std::endl;
    for (int i = 0; i < commands.size(); ++i) {
        operators::InterfaceOperator *command = commands.at(i);
        //Executor::getInstance().executeIntermediateCode(command);
        string line = command->getOperatorIntermediateCode();
        std::cout << i + 1 << ":" << line << std::endl;
        intermediateFile << line << std::endl;
        e.executeLine(line, i + 1, command->getSourceLineNumber());
    }
    intermediateFile.close();

//    Executor::getInstance().parse(fileBaseNameWithPath + ".intermediate");
    return 0;
}