#include "polish.h"
#include <iostream>
#include <stack>
#include <string>
#include <vector>

std::vector<std::string> split(std::string s) {
    // Разделяет строку на подстроки по пробелам
    // Например "ab cd    ef" превращает в {"ab", "cd", "ef"}
    s += " ";  // Добавляем пробел, чтобы не обрабатывать случай пустой строки и другие случаи
    std::vector<std::string> res;
    int begin = 0;  // Индекс первого символа подстроки
    int end = 0;
    while (end < s.size()) {
        if (s[end] == ' ') {  // Дошли до пробела
            if (end != begin) {  // Если здесь False, то идут 2 пробела подряд, иначе между begin и end есть подстрока
                res.push_back(s.substr(begin, end - begin));  // Добавляем подстроку к результату
            }
            begin = end + 1;
        }
        end++;
    }
    return res;
}

bool isNumber(std::string s) {
    // Возвращает True, если строка является числом. Например: "25", "23.25", "-1"
    try {
        std::stof(s);
    }
    catch (const std::invalid_argument &e) {
        return false;
    }
    return true;
}

bool isSign(std::string s) {
    // Возвращает True, если строка является +, -, * или /
    return (s == "+" || s == "-" || s == "*" || s == "/");
}

bool checkExpression(std::string expression) {
    // Возвращает True, если выражение верное
    // Проверяет только правильность написания
    // Не проверяет правильность порядка и количество операций и операндов
    auto split_str = split(expression);
    for (std::string val: split_str) {
        if (!isNumber(val) && !isSign(val))
            return false;
    }
    return true;
}

float calculate(std::string expression) {
    if (!checkExpression(expression))  // Сначала проверяем выражение на правильность написания
        throw std::runtime_error("Error: expression is incorrect!");

    std::stack<std::string> stack;  // Стек. Сюда запихиваем операнды, которые будут использоваться в последующих операциях
    std::vector<std::string> split_expr = split(expression);  // Разбиваем выражение по пробелам
    for (std::string val: split_expr) {  // Считываем каждый элемент выражения по порядку
        if (isNumber(val)) {  // Если элемент - число
            stack.push(val);  // Засовываем его в стек
        } else {  // Если элемент - знак операции, т. е. +, -, * или /

            // Достаём из стека два последних элемента
            float v2 = std::stof(stack.top());
            stack.pop();
            float v1 = std::stof(stack.top());
            stack.pop();

            float v3;
            switch (val[0]) {  // Применяем соответствующую элементу операцию
                case '+':
                    v3 = v1 + v2;
                    break;
                case '-':
                    v3 = v1 - v2;
                    break;
                case '*':
                    v3 = v1 * v2;
                    break;
                case '/':
                    v3 = v1 / v2;
                    break;
            }
            stack.push(std::to_string(v3));  // Запихиваем в стек результат операции
        }
    }
    // В итоге в стеке остаётся один элемент, являющийся результатом
    float result = std::stof(stack.top());
    return result;
}