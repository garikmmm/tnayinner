#include "language/type/interfaceType.hpp"
#include "language/type/string.hpp"
#include "language/type/integer.hpp"

#include "language/value/interfaceValue.hpp"
#include "language/value/integerConstant.hpp"
#include "language/value/stringConstant.hpp"
#include "language/value/variable.hpp"

#include "language/operator/interfaceOperator.hpp"
#include "language/operator/declare.hpp"
#include "language/operator/assign.hpp"
#include "language/operator/add.hpp"
#include "language/operator/del.hpp"
#include "language/operator/mul.hpp"
#include "language/operator/sub.hpp"
#include "language/operator/fake.hpp"

#include "parser/utils.hpp"
#include "parser/parser.hpp"

using namespace interpretator;

int main(int argc, char *argv[]) {

    if (2 != argc) {
        printf("Usage is: interpretator example.code");
        return 0;
    }
    Parser p;
//    p.parse(argv[1]);
    p.parse("/Applications/MAMP/htdocs/tnayinner/interpretator/a.code");
    return 0;
}