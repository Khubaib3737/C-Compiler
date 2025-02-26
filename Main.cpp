/*
Khubaib Ashraf			L1F21BSCS0805
Mubashir Qadeer			L1F21BSCS0293
Sanan Tahir				L1F21BSCS0368
Aqib Aqeel				L1F21BSCS1154
*/

#pragma once
#include <iostream> // 

// Custom Header files.
#include "Scanner.h"
#include "SyntaxAnalyzer.h"
#include "ParseTree.h"
#include "Grammar.h"

_StackCheck;


int main()
{
	//1: Create Grammar instance to write the productions which are used by source.txt
	Grammar _Grammar;

	// 2: Scan source code(source.txt) and generate tokens in token.txt. Generate tokens and Productions
	LexicalAnalyzer()("parser_files/source.txt", _Grammar);

	// 3:  After scan tokens, Check for syntax errors and write into error.txt file
	SyntaxAnalyzer()("parser_files/source.txt");

	return 0;
}