/* This class write all productions which are being used by the input source.txt file and write
 into ProductionsUsed.txt file */


#pragma once
#include <fstream> // for write output text file
#include <cstring> // for strcmp
#include <iostream> //
#include "Scanner.h"



class Grammar
{

private:

    bool isIdentifier(const char* token)


    {
        if (!my_isalpha(token[0]) && token[0] != '_')

        {
            return false;

        }
        for (int i = 1; token[i] != '\0'; ++i)

        {
            if (!my_isalnum(token[i]) && token[i] != '_') {
                return false;
            }
        }
        return true;
    }

    /// 
    ofstream fout;

public:
    Grammar()

    {
        fout.open("TokensAndErrorsOutput/ProductionsUsed.txt");
        if (!fout) {
            cerr << "Unable to open grammarused.txt for writing." << endl;
        }
    }

    ~Grammar() {
        if (fout.is_open())

        {
            fout.close();
        }
    }

    void logRule(const char* rule)

    {
        if (fout.is_open()) {
            fout << rule << endl;
        }
    }

    void checkAndLogRule(const char* token)


    {
        if (strcmp(token, "int") == 0 || strcmp(token, "float") == 0)


        {
            logRule("Type -> int | float");
        }
        else if (isIdentifier(token)) {
            logRule("IdentList -> identifier IdentList'");
            logRule("IdentList' -> , identifier IdentList' | null");
        }
        else if (strcmp(token, "for") == 0) {
            logRule("Stmt -> ForStmt");
            logRule("ForStmt -> for < Expr ; OptExpr ; OptExpr > Stmt");
        }
        else if (strcmp(token, "while") == 0) {
            logRule("Stmt -> WhileStmt");
            logRule("WhileStmt -> while < Expr > Stmt");
        }
        else if (strcmp(token, "if") == 0)

        {
            logRule("Stmt -> IfStmt");


            logRule("IfStmt -> if < Expr > Stmt ElsePart");
            logRule("ElsePart -> else Stmt | null");
        }
        else if (strcmp(token, "{") == 0) {
            logRule("Stmt -> CompoundStmt");
            logRule("CompoundStmt -> { StmtList }");
        }
        else if (strcmp(token, "=") == 0) {
            logRule("Compare -> ==");
        }
        else if (strcmp(token, "==") == 0 || strcmp(token, "!=") == 0 ||
            strcmp(token, "<") == 0 || strcmp(token, ">") == 0 ||
            strcmp(token, "<=") == 0 || strcmp(token, ">=") == 0) {
            logRule("Compare -> == | < | > | <= | >= | != | <>");
        }
        else if (strcmp(token, "+") == 0 || strcmp(token, "-") == 0) {
            logRule("Mag -> Mag + Term | Mag - Term | Term");
        }
        else if (strcmp(token, "*") == 0 || strcmp(token, "/") == 0) {
            logRule("Term -> Term * Factor | Term / Factor | Factor");
        }
        else if (strcmp(token, ";") == 0) {
            logRule("Stmt -> Expr ; | ;");
        }
    }
};