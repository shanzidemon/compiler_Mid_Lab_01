
#include <iostream>
#include <fstream>
#include <string>
#include <set>
using namespace std;

int main() {

    ifstream file("/Users/shanzidemon/Desktop/Compiler _WEal 3/main.txt");
    ofstream output("/Users/shanzidemon/Desktop/Compiler _WEal 3/output.txt");

    if (!file) {
        cout << "Error opening input file!" << endl;
        return 1;
    }

    if (!output) {
        cout << "Error opening output file!" << endl;
        return 1;
    }

    set<string> keywords = {
        "int", "float", "double", "char", "void",
        "if", "else", "while", "for", "return",
        "using", "namespace", "include", "const",
        "bool", "true", "false"
    };

    char ch;
    string token;

    while (file.get(ch)) {

        
        if (ch == ' ' || ch == '\n' || ch == '\t' ||
            ch == '\r') {
            continue;
        }

        
        if ((ch >= 'A' && ch <= 'Z') ||
            (ch >= 'a' && ch <= 'z') || ch == '_') {

            token = ch;

            while (file.peek() != EOF) {
                char next = file.peek();

                if ((next >= 'A' && next <= 'Z') ||
                    (next >= 'a' && next <= 'z') ||
                    (next >= '0' && next <= '9') ||
                    next == '_') {

                    file.get(ch);
                    token += ch;
                }
                else {
                    break;
                }
            }

            if (keywords.count(token))
                output << token << " : Keyword" << endl;
            else
                output << token << " : Identifier" << endl;
        }


        else if (ch >= '0' && ch <= '9') {

            token = ch;

            while (file.peek() != EOF) {
                char next = file.peek();

                if ((next >= '0' && next <= '9') ||
                    next == '.') {

                    file.get(ch);
                    token += ch;
                }
                else {
                    break;
                }
            }

            output << token << " : Constant" << endl;
        }

       
        else if (ch == '"') {

            token = "\"";

            while (file.get(ch)) {
                token += ch;

                if (ch == '\\') {
                    if (file.get(ch))
                        token += ch;
                }
                else if (ch == '"') {
                    break;
                }
            }

            output << token << " : Constant (String)" << endl;
        }

   
        else {

            if (ch == '<' && file.peek() == '<') {
                file.get(ch);
                output << "<< : Operator" << endl;
            }

            else if (ch == '+' || ch == '-' ||
                     ch == '*' || ch == '/' ||
                     ch == '=' || ch == '<' ||
                     ch == '>' || ch == '%') {

                output << ch << " : Operator" << endl;
            }

            else {
                output << ch << " : Punctuation" << endl;
            }
        }
    }

    file.close();
    output.close();

    cout << "Lexical Analysis Completed!" << endl;
    cout << "Check output.txt file." << endl;

    return 0;
}
