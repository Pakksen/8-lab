#pragma once

#include <string>
#include <vector>

std::vector<std::string> split(std::string s);

bool isNumber(std::string s);

bool isSign(std::string s);

bool checkExpression(std::string expression);

float calculate(std::string expression);
