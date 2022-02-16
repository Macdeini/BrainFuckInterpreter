#include <iostream>
#include <array>
#include <vector>
#include <fstream>
#include <string>
#include <stack>

int main()
{
    const std::string commands = "><+-.,[]";
    std::vector<char> instructions;
    std::string file = "mandelbrot.txt";
    std::array<char, 30000> data;
    data.fill(0);
    std::stack<char> matching_brackets;

    int dataptr = 0;
    int instructionptr = 0; 

    char byte = 0;
    std::ifstream program(file);
    if(!program.is_open()){
        return 1;
    }
    while (program.get(byte))
    {
        if (commands.find(byte) != std::string::npos)
            instructions.push_back(byte);
    }
    for (auto &i : instructions)
        std::cout << i;
    std::cout << std::endl;

    while (instructionptr < instructions.size())
    {
        switch(instructions[instructionptr])
        {
            case '>':
                dataptr++;
                instructionptr++;
                break;
            case '<':
                dataptr--;
                instructionptr++;
                break;
            case '+':
                data[dataptr]++;
                instructionptr++;
                break;
            case '-':
                data[dataptr]--;
                instructionptr++;
                break;
            case '.':
                std::cout << data[dataptr];
                instructionptr++;
                break;
            case ',':
                std::cout << "Input Char: " << std::endl;
                std::cin >> data[dataptr];
                instructionptr++;
                break;
            case '[':
                if (data[dataptr] == 0) {
                    matching_brackets.push('x');
                    int tempptr = instructionptr;
                    while (instructions[tempptr] != ']' || !matching_brackets.empty())
                    {
                        tempptr++;
                        if (instructions[tempptr] == '[')
                            matching_brackets.push('x');
                        if (instructions[tempptr] == ']')
                            matching_brackets.pop();
                    }
                    instructionptr = tempptr + 1;
                } else {
                    instructionptr++;
                }
                break;
            case ']':
                if (data[dataptr] != 0) {
                    matching_brackets.push('y');
                    int tempptr = instructionptr;
                    while (instructions[tempptr] != '[' || !matching_brackets.empty())
                    {
                        tempptr--;
                        if (instructions[tempptr] == ']')
                            matching_brackets.push('y');
                        if (instructions[tempptr] == '[')
                            matching_brackets.pop();
                    }
                    instructionptr = tempptr + 1;
                } else {
                    instructionptr++;
                }
                break;
        }
    }
    return 0;
}