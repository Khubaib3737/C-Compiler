/*
    This class check for syntax errors in the given source code and write in error.txt file
*/


#pragma once
#include <iostream>
#include <fstream>
#include <memory>
#include "CustomDataTypesLibrary.h"

using namespace std;
#pragma warning(disable:4996) 


constexpr int Error = 5;
constexpr int maxRows = 100;
constexpr int maxCols = 50;



CustomMap<const char*, int, ScannerStackSize> reserveKeywords;

class SyntaxAnalyzer_Internal
{
protected:
    const int bufferSize = 16384 * 4; // (16*4)k

public:

    int LL1Table1[maxRows][maxCols];
    int LL1Table2[maxRows][maxCols];
    int isFinalIndex = -1;

    bool __isAlphabet(char x)
    {
        return x >= 'a' && x <= 'z' || x >= 'A' && x <= 'Z';
    }

    bool __isUnderscore(char x)
    {
        return x == '_';
    }

    bool __isNumber(char x)
    {
        return x >= '0' && x <= '9';
    }

    bool __isExclamation(char x)
    {
        return x == '!';
    }

    bool __isEqual(char x)
    {
        return x == '=';
    }

    bool __isLess(char x)
    {
        return x == '<';
    }

    bool __isGreater(char x)
    {
        return x == '>';
    }

    bool __isMinus(char x)
    {
        return x == '-';
    }

    bool __isColon(char x)
    {
        return x == ':';
    }

    bool __isPlus(char x)
    {
        return x == '+';
    }

    bool __isAmpersand(char x)
    {
        return x == '&';
    }

    bool __isPersentage(char x)
    {
        return x == '%';
    }

    bool __isAsterisk(char x)
    {
        return x == '*';
    }

    bool __isDot(char x)
    {
        return x == '.';
    }

    bool __isDivided(char x)
    {
        return x == '/';
    }

    bool __isExponent(char x)
    {
        return x == 'E';
    }

    bool __isOr(char x)
    {
        return x == '|';
    }

    bool __isSquareStart(char x)
    {
        return x == '[';
    }

    bool __isSquareEnd(char x)
    {
        return x == ']';
    }

    bool __isMiddleStart(char x)
    {
        return x == '{';
    }

    bool __isMiddleEnd(char x)
    {
        return x == '}';

    }

    void ParseLL1Table(const char* filename, int table[maxRows][maxCols], int& rows, int& cols) noexcept
    {
        ifstream fin(filename);
        char dummy{};
        int x;
        rows = 0;

        if (fin.is_open())
        {
            while (!fin.eof() && rows < maxRows)
            {
                cols = 0;
                dummy = {};
                while (dummy != '\n' && !fin.eof() && cols < maxCols)
                {
                    fin >> x;
                    table[rows][cols] = x;


                    fin.get(dummy);
                    cols++;
                }
                rows++;
            }
            fin.close();
        }
        else
        {
            cout << "Transition Table File Not Found" << endl;
        }
    }

    int int_GetRelation_by_char(char character, int state)
    {
        if (!(state == 10 || state == 12 || state == 6 || state == 16 || state == 46) && __isAlphabet(character))
        {
            return 0;
        }
        else if ((state == 1 || state == 2 || state == 3 || state == 0) && __isUnderscore(character))
        {
            return 1;
        }
        else if ((state == 0 || state == 1 || state == 12 || state == 10 || state == 11 || state == 12 || state == 15 || state == 14 || state == 16 || state == 9 || state == 18) && __isNumber(character))
        {
            return 2;
        }
        else if (__isExclamation(character))
        {
            return 3;
        }
        else if ((state == 0 || state == 7 || state == 4 || state == 8) && __isEqual(character))
        {
            return 4;
        }
        else if (__isLess(character))
        {
            return 5;
        }
        else if ((state == 0 || state == 49 || state == 6 || state == 7) && __isGreater(character))
        {
            return 6;
        }
        else if ((state == 0 || state == 18 || state == 7 || state == 14) && __isPlus(character))
        {
            return 7;
        }
        else if ((state == 46 || state == 0 || state == 7) && __isColon(character))
        {
            return 8;
        }
        else if ((state == 0 || state == 9 || state == 14) && __isMinus(character))
        {
            return 9;
        }
        else if (__isAmpersand(character))
        {
            return 10;
        }
        else if (__isPersentage(character))
        {
            return 11;
        }
        else if (__isAsterisk(character))
        {
            return 12;
        }
        else if ((state == 0) && __isDivided(character))
        {
            return 13;
        }
        else if (state == 10 && __isDot(character))
        {
            return 14;
        }
        else if ((state == 10 || state == 12) && __isExponent(character))
        {
            return 15;
        }
        else if (state == 0 && __isMiddleStart(character))
        {
            return 16;
        }
        else if (state == 0 && __isMiddleEnd(character))
        {
            return 17;
        }
        else if (state == 0 && __isSquareStart(character))
        {
            return 18;
        }
        else if (state == 0 && __isSquareEnd(character))
        {
            return 19;
        }
        else if ((state == 0 || state == 17) && __isOr(character))
        {
            return 20;
        }
        else if (state == 1 && !__isAlphabet(character) && !__isNumber(character) && !__isUnderscore(character))
        {
            return 21;
        }
        else if (state == 2 && !__isAlphabet(character) && !__isNumber(character) && !__isUnderscore(character))
        {
            return 22;
        }
        else if (state == 4 && !__isEqual(character))
        {
            return 23;
        }
        else if (state == 6 && !__isLess(character) && !__isGreater(character))
        {
            return 24;
        }
        else if (state == 7 && !__isLess(character) && !__isGreater(character) && !__isPlus(character) && !__isEqual(character) && !__isColon(character))
        {
            return 25;
        }
        else if (state == 8 && !__isEqual(character))
        {
            return 26;
        }
        else if (state == 46 && !__isColon(character))
        {
            return 27;
        }
        else if (state == 9 && !__isMinus(character))
        {
            return 28;
        }
        else if (state == 18 && !__isPlus(character))
        {
            return 29;
        }
        else if (state == 11 && !__isAmpersand(character))
        {
            return 30;
        }
        else if (state == 49 && !__isGreater(character))
        {
            return 31;
        }
        else if (state == 16 && !__isNumber(character))
        {
            return 32;
        }
        else if (state == 17 && !__isOr(character))
        {
            return 33;
        }
        else if (state == 10 && !__isExponent(character) && !__isNumber(character) && !__isDot(character))
        {
            return 34;
        }
        else if (state == 12 && !__isNumber(character))
        {
        return 35;
        }
        else
        {
            return -1;
        }

    }

    void generateTokens(char* inputBuffer, const char* errorfile, const char* tokenfile)
    {


        if (inputBuffer == NULL) return;



        ofstream _errorFileToWrite(errorfile);


        ofstream _tokenFileToWrite(tokenfile);



        int temp_Index = 0;

        while (inputBuffer[temp_Index] != '\0')
        {
            char lexeme[256] = {}; // Adjust the size if necessary



            if (inputBuffer[temp_Index] == ' ' || inputBuffer[temp_Index] == '\t')
            {
                temp_Index++;
                continue;
            }
            int state = 0; // Start State
            char character = inputBuffer[temp_Index];
            int map = int_GetRelation_by_char(character, state);

            strncat(lexeme, &character, 1);



            while (!LL1Table1[state][isFinalIndex])
            {
                if (map == -1)
                {
                    temp_Index++;


                    break;
                }
                if (LL1Table2[state][map])
                {
                    temp_Index += 1;
                }

                state = LL1Table1[state][map]; // Update the new state

                if (state == Error)
                {
                    break;

                }

                if (!LL1Table1[state][isFinalIndex])
                {
                    character = inputBuffer[temp_Index];
                    map = int_GetRelation_by_char(character, state);
                    if (map == -1)
                    {
                        break;
                    }
                    if (character != ' ' && LL1Table2[state][map])
                    {


                        strncat(lexeme, &character, 1);
                    }
                }
            }
            if (state == 19 && reserveKeywords.count(lexeme))
            {
                _tokenFileToWrite << "< " << lexeme << ", " << " keyword" << " >" << endl;
            }
            else if (state == 19 && reserveKeywords.count(lexeme) == 0)
            {
                _errorFileToWrite << "< " << lexeme << ", " << "error" << " >" << endl;
            }
            else if (state == 5 || map == -1)
            {
                _errorFileToWrite << "< " << lexeme << ", " << "error" << " >" << endl;
            }
            else
            {
                if (state == 36)
                {
                    _tokenFileToWrite << "< " << lexeme << ", " << "constant" << " >" << endl;
                }
                else if (state == 38 || state == 39 || state == 40 || state == 41 || state == 35 || state == 24)
                {
                    _tokenFileToWrite << "< " << lexeme << ", " << "punctuation" << " >" << endl;
                }
                else if (state == 20)
                {
                    _tokenFileToWrite << "< " << lexeme << ", " << "identifier" << " >" << endl;
                }
                else
                {
                    _tokenFileToWrite << "< " << lexeme << ", " << "operator" << " >" << endl;
                }
            }
        }
    }

    char* readSourceCode(const char* filename)
    {

        ifstream fin(filename);
        char* inputBuffer = nullptr;
        if (fin.is_open())
        {
            inputBuffer = new char[bufferSize] { '\0' };


            char x = {};
            int i = 0;
            while (x = fin.get())
            {
                if (x == EOF) {
                    break;
                }
                if (x != '\n')
                {
                    inputBuffer[i] = x;
                    i++;
                }
                if (x != EOF && i == bufferSize)
                {
                    delete[]inputBuffer;
                    inputBuffer = nullptr;
                    cout << "Error: Buffer Overflowed" << endl;


                    return inputBuffer;
                }
            }
            return inputBuffer;
        }
        else
        {
            cout << "Source Code File Not Found" << endl;


        }
        return inputBuffer;
    }

    void lexicalAnalyzer(const char* filename, const char* errorfile, const char* tokenfile) noexcept
    {
        char* inputBuffer = readSourceCode(filename);
        generateTokens(inputBuffer, errorfile, tokenfile);


    }

    void InsertReservedKeywords(const char* filename)
    {
        ifstream fin(filename);

        if (fin.is_open())
        {
            char word[256];
            while (fin >> word) {
                reserveKeywords.insert(strdup(word), 1);

            }
        }
        else
        {
            cout << "Keywords file not found" << endl;
        }
    }

};



// High level access to Syntax Analyzer Class.
class SyntaxAnalyzer

{
public:

    SyntaxAnalyzer() {}


    void operator()(const char* sourceFile) const

    {

        const char* transitionTableFileName = "parser_files/transition_table1.csv";
        const char* advanceTableFileName = "parser_files/transition_table2.csv";
        const char* reserveKeywordsFileName = "parser_files/keywords.txt";
        const char* errorFileName = "TokensAndErrorsOutput/error.txt";
        const char* tokenFileName = "TokensAndErrorsOutput/token.txt";

        // allocate on heap,  This will also ensure auto delete of that object!!
        unique_ptr<SyntaxAnalyzer_Internal> Sa = make_unique<SyntaxAnalyzer_Internal>();

        // SyntaxAnalyzer Sa; 


        Sa->InsertReservedKeywords(reserveKeywordsFileName);

        int rows1 = 0, Columns_ = 0;
        Sa->ParseLL1Table(transitionTableFileName, Sa->LL1Table1, rows1, Columns_);
        Sa->isFinalIndex = Columns_ - 1;

        int rows2 = 0, advCols = 0;
        Sa->ParseLL1Table(advanceTableFileName, Sa->LL1Table2, rows2, advCols);

        Sa->lexicalAnalyzer(sourceFile, errorFileName, tokenFileName);
    }
};