#pragma once
#include <iostream>
#include <memory>
#include "Lexer.h"

namespace Json
{

class Parser
{

    Lexer lexer;
    
    Tokens tokens;

    Parser();

};

}