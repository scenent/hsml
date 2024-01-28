#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "parser.h"

static std::map<std::wstring, HSML_Label> m_GlobalLabels;
static std::stack<std::any> m_GlobalStack;
void interpretLabel(HSML_Label label);
void interpret(HSML_Program program);

static bool isInt(const std::any& value) {
	return value.type() == typeid(int);
}

static bool isStr(const std::any& value) {
	return value.type() == typeid(std::wstring);
}

static bool isFloat(const std::any& value) {
	return value.type() == typeid(float);
}

static int toInt(const std::any& value) {
	return std::any_cast<int>(value);
}

static std::wstring toStr(const std::any& value) {
	return std::any_cast<std::wstring>(value);
}

static float toFloat(const std::any& value) {
	return std::any_cast<float>(value);
}

#endif