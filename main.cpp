
#include <iostream>
#include "src/container/arrayList.h"
#include "src/object/pyString.h"
#include "src/container/bufferedInputStream.h"
#include "src/code/binaryFileParser.hpp"
#include "src/runtime/interpreter.h"
#include "src/runtime/universal.h"
int main() {
    Universal::genesis();
    const char * filename = "../demo/function.pyc";
    BufferedInputStream buffer(filename);
    BinaryFileParser parser(&buffer);
    CodeObject * codeObject = parser.parse();
    Interpreter i;
    i.run(codeObject);
    Universal::destroy();
    return 0;
}