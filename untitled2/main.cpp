#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <sstream>

constexpr unsigned int hash(const char *s, int off = 0)
{
    //hashes the string so i can use a string in a switch
    return !s[off] ? 5381 : (hash(s, off+1)*33)^s[off];
}

std::vector<std::string> splitstr(std::string str, char delimiter) {
    std::vector<std::string> internal;
    std::stringstream ss(str); // Turn the string into a stream.
    std::string tok;

    while(getline(ss, tok, delimiter)) {
        internal.push_back(tok);
    }

    return internal;
}

int main(int argc, char *argv[]) {
    std::ifstream fileHandler;
    fileHandler.open(argv[1]);
    std::string line;

    std::stack<int> stack;
    int a1 = 0;
    int a2 = 0;
    int loopline = 0;

    if(fileHandler.is_open())
    {
        std::vector<std::string> fileVector = splitstr(std::string((std::istreambuf_iterator<char>(fileHandler)), std::istreambuf_iterator<char>()), '\n');
        for(int i = 0; i < fileVector.size(); i++){

            std::string currline = fileVector[i];
            //std::cout << currline << std::endl;
            switch(hash(currline.c_str())) //the switch statement doesn't work with std::string so i'm using the above hash function to convert the value to an int to then use in the switch statement
            {
                case hash("INC1"):
                a1++;
                break;

                case hash("PUSH"):
                stack.push(a1);
                break;

                case hash("POP"):
                stack.pop();
                break;

                case hash("PRINTCHAR"):
                std::cout << (char)stack.top();
                stack.pop();
                break;

                case hash("PRINTNUM"):
                std::cout << stack.top();
                stack.pop();
                break;

                case hash("DEC1"):
                a1--;
                break;

                case hash("MOVPOP"):
                a1 = stack.top();
                stack.pop();
                break;

                case hash("NUL1"):
                    a1 = 0;
                break;

                case hash("INC10"):
                a1+=10;
                break;

                case hash("INC20"):
                a2+=10;
                break;

                case hash("DEC2"):
                a2--;
                break;

                case hash("NUL2"):
                a2 = 0;
                break;
                case hash("START?"):
                    loopline = i;
                    break;

                case hash("LOOP?"):
                    if(stack.top() != a2)
                    {
                        i = loopline;
                    }
                    break;
            }
        }
        fileHandler.close();
    }
    return 0;
}