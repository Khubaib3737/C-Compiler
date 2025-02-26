#pragma once

// Custom Header files.
#include "CustomDataTypesLibrary.h"
#include "SyntaxAnalyzer.h"
#include "Grammar.h"


#include <iostream>
#include <fstream>
#include <iomanip> // Used for formatting output, such as add whitespace in output terminal/file



using namespace std;

class SyntaxAnalyzer;

// -> Brief: This class is responsible for tokenize C++ code. <-
// 

template <int MAX_SIZE>
class Scanner {
private:
    CustomMap<const char*, const char*, MAX_SIZE> patterns;

    // Function to convert operator symbols to lexemes
    const char* operator_to_name(const char* op) {

        if (strcmp(op, "*") == 0) return "MUL";
        else if (strcmp(op, "+") == 0) return "ADD";
        else if (strcmp(op, ">>") == 0) return "INSERTION";
        else if (strcmp(op, "<<") == 0) return "EXTRACTION";
        else if (strcmp(op, ">") == 0) return "RSHFT OR Greater";
        else if (strcmp(op, "<") == 0) return "LSHFT OR Less";
        else if (strcmp(op, "==") == 0) return "EQUAL";
        else if (strcmp(op, "!=") == 0) return "Not Equal";
        else if (strcmp(op, ">=") == 0) return "Greater or Equal";
        else if (strcmp(op, "<=") == 0) return "Less or Equal";
        else if (strcmp(op, "=") == 0) return "Equal";
        else if (strcmp(op, ":") == 0) return "Colon";
        return "";
    }

    // Function to check if a character is a valid identifier start character
    bool isIdentifierStart(char c)

    {
        return my_isalpha(c) || c == '_';
    }

    // Function to check if a character can be part of an identifier
    bool isIdentifierChar(char c)

    {
        return my_isalnum(c) || c == '_';
    }

    // Function to report syntax errors
    void reportSyntaxError(const char* errorToken)

    {
        cerr << "Syntax Error: Unexpected token '" << errorToken << "'" << endl;
    }

    // Function to match and print tokens from the input string
    void matchAndPrintTokens(const char* str, class Grammar* pGrammar)

    {

        if (!pGrammar) return;

        char buffer[256];
        int tokenNo = 0;

        ofstream fout("TokensAndErrorsOutput/tokensVersion2.txt");
        if (!fout) {
            cerr << "Unable to open tokens.txt for writing." << endl;
            return;
        }

        for (size_t i = 0; str[i] != '\0'; ++i) {
            if (my_isspace(str[i])) {
                continue;
            }

            if (my_ispunct(str[i]) && str[i] != '_') { // Handles special symbols and operators
                buffer[0] = str[i];
                buffer[1] = '\0';

                if (str[i + 1] != '\0' && my_ispunct(str[i + 1]) && str[i + 1] != '_') {
                    // Check for two-character operators
                    char twoCharOp[3] = { str[i], str[i + 1], '\0' };
                    if (strcmp(patterns.get(twoCharOp), "") != 0) {
                        buffer[1] = str[i + 1];
                        buffer[2] = '\0';
                        ++i;
                    }
                }
                ++tokenNo;
                cout << "Token Number: " << setw(10) << tokenNo << " : " << setw(10) << buffer << "   | "
                    << setw(20) << patterns.get(buffer);


                const char* lexeme = operator_to_name(buffer);
                if (lexeme[0] != '\0') {
                    cout << " , " << lexeme;
                }
                cout << endl;

                fout << "Token Number: " << setw(10) << tokenNo << " : " << setw(10) << buffer << "   | "
                    << setw(20) << patterns.get(buffer);




                if (lexeme[0] != '\0') {
                    fout << " , " << lexeme;
                }
                fout << endl;
                pGrammar->checkAndLogRule(buffer);


            }
            else if (isIdentifierStart(str[i])) { // Handles identifiers and keywords
                int j = 0;
                while (str[i] != '\0' && isIdentifierChar(str[i])) {
                    buffer[j++] = str[i++];
                }
                buffer[j] = '\0';
                --i;
                ++tokenNo;
                if (strcmp(patterns.get(buffer), "") != 0) {
                    cout << "Token Number: " << setw(10) << tokenNo << " : " << setw(10) << buffer << "   | "
                        << setw(20) << patterns.get(buffer) << endl;



                    fout << "Token Number: " << setw(10) << tokenNo << " : " << setw(10) << buffer << "   | "
                        << setw(20) << patterns.get(buffer) << endl;

                    pGrammar->checkAndLogRule(buffer);


                }
                else {
                    cout << "Token Number: " << setw(10) << tokenNo << " : " << setw(10) << buffer << "   | Identifier" << endl;

                    fout << "Token Number: " << setw(10) << tokenNo << " : " << setw(10) << buffer << "   | Identifier" << endl;

                    pGrammar->checkAndLogRule(buffer);
                }
            }
            else if (my_isdigit(str[i])) { // Handles integers
                int j = 0;
                while (str[i] != '\0' && my_isdigit(str[i])) {
                    buffer[j++] = str[i++];
                }
                buffer[j] = '\0';
                --i;
                ++tokenNo;
                cout << "Token Number: " << setw(10) << tokenNo << " : " << setw(10) << buffer << "   | Integer" << endl;

                fout << "Token Number: " << setw(10) << tokenNo << " : " << setw(10) << buffer << "   | Integer" << endl;

                ////xSyntaxAnalyzer.CheckAndPrintErrors(buffer);

                pGrammar->checkAndLogRule(buffer);

            }
            else { // Handle unexpected characters
                char errorToken[2] = { str[i], '\0' };
                reportSyntaxError(errorToken);
            }
        }

        fout.close();
    }

public:
    // Constructor to populate the token patterns map
    Scanner()
    {
        Make_Regex_Map(patterns);
    };


    inline CustomMap<const char*, const char*, MAX_SIZE> GetPatternMap() { return patterns; };


    virtual ~Scanner() {}

    // Function to create the regex map for token recognition
    void Make_Regex_Map(CustomMap<const char*, const char*, MAX_SIZE>& patterns)
    {
        // add more tokens here.

        patterns.insert(";", "Special Symbol");
        patterns.insert("{", "Special Symbol");
        patterns.insert("}", "Special Symbol");
        patterns.insert("(", "Special Symbol");
        patterns.insert(")", "Special Symbol");
        patterns.insert(",", "Special Symbol");
        patterns.insert("#", "Special Symbol");
        patterns.insert("int", "Keyword");
        patterns.insert("float", "Keyword");
        patterns.insert("for", "Keyword");
        patterns.insert("while", "Keyword");
        patterns.insert("if", "Keyword");
        patterns.insert("return", "Keyword");
        patterns.insert("else", "Keyword");
        patterns.insert("include", "Pre-Processor Directive");
        patterns.insert("define", "Pre-Processor Directive");
        patterns.insert("iostream", "Library");
        patterns.insert("stdio", "Library");
        patterns.insert("*", "Operator");
        patterns.insert("+", "Operator");
        patterns.insert(">>", "Operator");
        patterns.insert("<<", "Operator");
        patterns.insert("<", "Operator");
        patterns.insert(">", "Operator");
        patterns.insert("==", "Operator");
        patterns.insert("!=", "Operator");
        patterns.insert(">=", "Operator");
        patterns.insert("<=", "Operator");
        patterns.insert("=", "Operator");
        patterns.insert(":", "Special Symbol");

    }





    // Function to scan and tokenize a given C++ code string
    void scan(const char* code)

    {
        matchAndPrintTokens(code);
    }

    // Function to scan and tokenize a C++ code file
    void scanFile(const char* filename, class Grammar* pGrammar) noexcept {
        fstream fin(filename, fstream::in);

        if (fin.is_open()) {
            // Determine the size of the file
            fin.seekg(0, fin.end);
            int fileSize = (int)fin.tellg();
            fin.seekg(0, fin.beg);

            // Allocate memory for the C-style string
            char* str = new char[fileSize + 1]; // +1 for the null terminator
            str[0] = '\0'; // Initialize the string with the null terminator

            char c;
            while (fin >> noskipws >> c) {
                // Concatenate the character to the C-style string
                int len = (int)strlen(str);
                str[len] = c;
                str[len + 1] = '\0';
            }
            fin.close();

            matchAndPrintTokens(str, pGrammar);

            cout << "\n\n\n\nTokens have been written to token.txt.\n";
            cout << "\nErrors have been written to error.txt(if any).\n\n\n\n";

            // Free the allocated memory
            delete[] str;
        }
        else {
            cout << "\nFILE NOT FOUND!\n\n";
        }
    }

};




// High level access to Lexical Class
class LexicalAnalyzer

{

public:

    LexicalAnalyzer() {}

    void operator()(const char* sourceFile, Grammar& GrammarRef) const
    {
        Scanner<ScannerStackSize> Sc;

        // Generate tokens and Productions
        Sc.scanFile(sourceFile, &GrammarRef);
    }
};

#pragma once
