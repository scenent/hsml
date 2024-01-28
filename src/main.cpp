#include "main.h"

int main(const int argc, const char* argv[]) {
	if (argc > 1) {
		std::wstring content = readFileW(s2ws(argv[1]));
		std::vector<Token> tokens = scan(content);
		HSML_Program program = parse(tokens);
		interpret(program);
		system("pause");
		exit(0);
	}
}