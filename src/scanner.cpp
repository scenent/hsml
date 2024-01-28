#include "scanner.h"




std::vector<Token> scan(std::wstring sourceCode) {
	std::vector<Token> result;
	sourceCode += L'\0';
	std::wstring::iterator current = sourceCode.begin();
	while (*current != L'\0') {
		switch (getCharType(*current)) {
		case CharType::SubUnary: {
			current++;
			std::wstring string;
			while (isCharType(*current, CharType::NumberLiteral))
				string += *current++;
			if (*current == '.') {
				string += *current++;
				while (isCharType(*current, CharType::NumberLiteral))
					string += *current++;
				result.push_back(Token{ Kind::FloatingLiteral, L"-" + string});
				break;
			}
			result.push_back(Token{ Kind::IntegerLiteral, L"-" + string});
			break;
		}
		case CharType::EscapeSeq: {
			result.push_back({ Kind::EscapeSeq, L"\n" });
			current++;
			break;
		}
		case CharType::WhiteSpace: {
			int isBlockCount = 0;
			while (getCharType(*current) == CharType::WhiteSpace) {
				current++;
				isBlockCount++;
			}
			if (isBlockCount == 4) {
				result.push_back(Token(Kind::Block, L"    "));
			}
			break;
		}
		case CharType::NumberLiteral: {
			result.push_back(scanNumberLiteral(current));
			break;
		}
		case CharType::StringLiteral: {
			result.push_back(scanStringLiteral(sourceCode, current));
			break;
		}
		case CharType::IdentifierAndKeyword: {
			result.push_back(scanIdentifierAndKeyword(current));
			break;
		}
		case CharType::OperatorAndPunctuator: {
			if (*current == L'/' && current + 1 != sourceCode.end() && *(current + 1) == L'/') {
				scanLinedCommentLiteral(current);
				result.push_back({ Kind::EscapeSeq, L"\n" });
				break;
			}
			if (*current == L'/' && current + 1 != sourceCode.end() && *(current + 1) == L'*') {
				scanMultiLinedCommentLiteral(sourceCode, current);
				result.push_back({ Kind::EscapeSeq, L"\n" });
				break;
			}
			result.push_back(scanOperatorAndPunctuator(current));
			break;
		}
		default: {
			std::wcout << L"Error From Scanner.h : " + std::wstring(1, *current) + L" : This Character Is Illegal.";
		}
		}
	}
	result.push_back({ Kind::EndOfToken, L"#EndOfToken" });
	return result;
}

Token scanNumberLiteral(std::wstring::iterator& current) {
	std::wstring string;
	while (isCharType(*current, CharType::NumberLiteral))
		string += *current++;
	if (*current == '.') {
		string += *current++;
		while (isCharType(*current, CharType::NumberLiteral))
			string += *current++;
		return Token{ Kind::FloatingLiteral, string };
	}
	return Token{ Kind::IntegerLiteral, string };
}

void scanLinedCommentLiteral(std::wstring::iterator& iter) {
	while (*iter != L'\n') {
		iter++;
	}
	iter++;
}

void scanMultiLinedCommentLiteral(std::wstring& source, std::wstring::iterator& iter) {
	while (source.end() != iter && !(*iter == L'*' && *(iter + 1) == L'/')) {
		iter++;
	}
	if (iter + 1 != source.end()) {
		iter += 1;
		if (iter + 1 != source.end()) {
			iter += 1;
		}
	}
}

auto scanStringLiteral(std::wstring& currentString, std::wstring::iterator& current) -> Token {
	std::wstring string;
	current++;
	while (!(*current == L'\"' && *(current - 1) != L'\\')) {
		string += *current++;
	}
	if (*current != '\"') {
		std::cout << "Required : '\"'";
		exit(1);
	}
	current++;
	string = replaceAll(string, L"\\n", L"\n");
	string = replaceAll(string, L"\\\"", L"\"");
	return Token{ Kind::StringLiteral, string };
}

Token scanIdentifierAndKeyword(std::wstring::iterator& current) {
	std::wstring string;
	while (isCharType(*current, CharType::IdentifierAndKeyword))
		string += *current++;
	auto kind = toKind(string);
	if (kind == Kind::Unknown)
		kind = Kind::Identifier;
	return Token{ kind, string };
}

auto scanOperatorAndPunctuator(std::wstring::iterator& current) -> Token {
	std::wstring string;
	while (isCharType(*current, CharType::OperatorAndPunctuator))
		string += *current++;
	while (string.empty() == false && toKind(string) == Kind::Unknown) {
		string.pop_back();
		current--;
	}
	if (string.empty()) {
		std::cout << char(*current) << " Invalid Character";
		exit(1);
	}
	return Token{ stringToKind[string], string };
}

CharType getCharType(wchar_t c) {
	if (L'-' == c) {
		return CharType::SubUnary;
	}
	if (L'\n' == c) {
		return CharType::EscapeSeq;
	}
	if (L' ' == c) {
		return CharType::WhiteSpace;
	}
	if (L'0' <= c && c <= L'9') {
		return CharType::NumberLiteral;
	}
	if (c == L'\"') {
		return CharType::StringLiteral;
	}
	if (L'_' == c || (L'a' <= c && c <= L'z') || (L'A' <= c && c <= L'Z')) {
		return CharType::IdentifierAndKeyword;
	}
	if (33 <= c && c <= 47 ||
		58 <= c && c <= 64 ||
		91 <= c && c <= 96 ||
		123 <= c && c <= 126) {
		return CharType::OperatorAndPunctuator;
	}
	return CharType::Unknown;
}

bool isCharType(wchar_t c, CharType type) {
	switch (type) {
	case CharType::NumberLiteral: {
		return L'0' <= c && c <= L'9';
	}
	case CharType::StringLiteral: {
		return 32 <= c && c <= 126 && c != L'\"';
	}
	case CharType::IdentifierAndKeyword: {
		return L'0' <= c && c <= L'9' ||
			L'a' <= c && c <= L'z' ||
			L'A' <= c && c <= L'Z' ||
			c == L'_';
	}

	case CharType::OperatorAndPunctuator: {
		return 33 <= c && c <= 47 ||
			58 <= c && c <= 64 ||
			91 <= c && c <= 96 ||
			123 <= c && c <= 126;
	}
	default: {
		return false;
	}
	}
}