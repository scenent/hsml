#ifndef SCANNER_H
#define SCANNER_H

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <any>

static std::wstring replaceAll(std::wstring str, const std::wstring from, const std::wstring to) {
	if (from.empty())
		return L"";
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::wstring::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
	return str;
}


enum class Kind {
	ADR, // define address
	POP, // pop
	PSH, // push
	SET, // set
	INC, // increase
	DEC, // decrease
	JMP, // jump
	RET, // return
	PRT, // print
	PRL, // printLn
	TRY, // try
	INT, // int()
	STR, // str()
	FLT, // float()
	INP, // input
	CAL, // call
	EXT, // exit
	ADD, // add
	SUB, // subtract
	MUL, // multiply
	DIV, // divide
	MOD, // modulo
	POW, // power
	SIN, // sine
	COS, // cosine
	TAN, // tangent
	GRT, // Greater
	GOE, // Greater Or Equal
	LES, // Less
	LOE, // Less Or Equal
	EQL, // Equal
	NEQ, // Not Equal
	LAD, // Logical And
	LOR, // Logical Or
	Unknown, EndOfToken,

	Label,

	LinedCommentStart, MultiLinedCommentStart, MultiLinedCommentEnd,

	IntegerLiteral, FloatingLiteral, StringLiteral,
	Identifier,


	Block,
	Dot, 
	EscapeSeq,
	DefAddress,
	GetAddress,
	QuestionMark,
	Colon,
};


enum class CharType {
	Unknown,
	SubUnary,
	EscapeSeq,
	WhiteSpace,
	NumberLiteral,
	StringLiteral,
	IdentifierAndKeyword,
	OperatorAndPunctuator,
};

struct Token {
	Kind kind = Kind::Unknown;
	std::wstring source;
	Token(Kind k, std::wstring s) : kind(k), source(s) {
	}
};

static std::map<std::wstring, Kind> stringToKind = {
  {L"#Unknown",    Kind::Unknown},
  {L"#EndOfToken", Kind::EndOfToken},
  {L"#LinedCommentStart", Kind::LinedCommentStart},
  {L"#MultiLinedCommentStart", Kind::MultiLinedCommentStart},
  {L"#MultiLinedCommentEnd", Kind::MultiLinedCommentEnd},

  {L"adr", Kind::ADR},
  {L"pop", Kind::POP},
  {L"psh", Kind::PSH},
  {L"set", Kind::SET},
  {L"inc", Kind::INC},
  {L"dec", Kind::DEC},
  {L"jmp", Kind::JMP},
  {L"ret", Kind::RET},
  {L"prt", Kind::PRT},
  {L"prl", Kind::PRL},
  {L"try", Kind::TRY},
  {L"int", Kind::INT},
  {L"flt", Kind::FLT},
  {L"str", Kind::STR},
  {L"inp", Kind::INP},
  {L"cal", Kind::CAL},
  {L"ext", Kind::EXT},
  {L"add", Kind::ADD},
  {L"sub", Kind::SUB},
  {L"mul", Kind::MUL},
  {L"div", Kind::DIV},
  {L"mod", Kind::MOD},
  {L"pow", Kind::POW},
  {L"sin", Kind::SIN},
  {L"cos", Kind::COS},
  {L"tan", Kind::TAN},
  {L"grt", Kind::GRT},
  {L"goe", Kind::GOE},
  {L"les", Kind::LES},
  {L"loe", Kind::LOE},
  {L"eql", Kind::EQL},
  {L"neq", Kind::NEQ},
  {L"lad", Kind::LAD},
  {L"lor", Kind::LOR},

  {L"Integer",     Kind::IntegerLiteral},
  {L"Float",     Kind::FloatingLiteral},
  {L"String",     Kind::StringLiteral},
  {L"identifier", Kind::Identifier},

  {L".",           Kind::Dot},

  {L"lab", Kind::Label},
  {L"    ", Kind::Block},
  {L"\n", Kind::EscapeSeq},
  {L".", Kind::Dot},
  {L"&", Kind::DefAddress},
  {L"*", Kind::GetAddress},
  {L"?", Kind::QuestionMark},
  {L":", Kind::Colon},
};

static std::map<Kind, std::wstring> kindToString = {
  {Kind::Unknown, L"#Unknown"},
  {Kind::EndOfToken, L"#EndOfToken"},
  {Kind::LinedCommentStart, L"#LinedCommentStart"},
  {Kind::MultiLinedCommentStart, L"#MultiLinedCommentStart"},
  {Kind::MultiLinedCommentEnd, L"#MultiLinedCommentEnd"},

  {Kind::ADR, L"ADR"},
  {Kind::POP, L"POP"},
  {Kind::PSH, L"PSH"},
  {Kind::SET, L"SET"},
  {Kind::INC, L"INC"},
  {Kind::DEC, L"DEC"},
  {Kind::JMP, L"JMP"},
  {Kind::RET, L"RET"},
  {Kind::PRT, L"PRT"},
  {Kind::PRL, L"PRL"},
  {Kind::TRY, L"TRY"},
  {Kind::INT, L"INT"},
  {Kind::FLT, L"FLT"},
  {Kind::STR, L"STR"},
  {Kind::INP, L"INP"},
  {Kind::CAL, L"CAL"},
  {Kind::EXT, L"EXT"},
  {Kind::ADD, L"ADD"},
  {Kind::SUB, L"SUB"},
  {Kind::MUL, L"MUL"},
  {Kind::DIV, L"DIV"},
  {Kind::MOD, L"MOD"},
  {Kind::POW, L"POW"},
  {Kind::SIN, L"SIN"},
  {Kind::COS, L"COS"},
  {Kind::TAN, L"TAN"},
  {Kind::GRT, L"GRT"},
  {Kind::GOE, L"GOE"},
  {Kind::LES, L"LES"},
  {Kind::LOE, L"LOE"},
  {Kind::EQL, L"EQL"},
  {Kind::NEQ, L"NEQ"},
  {Kind::LAD, L"LAD"},
  {Kind::LOR, L"LOR"},


  {Kind::IntegerLiteral, L"Integer"},
  {Kind::FloatingLiteral, L"Floating"},
  {Kind::StringLiteral, L"String"},
  {Kind::Identifier, L"Identifier"},

  {Kind::Dot, L"Dot"},

  {Kind::Label, L"Label"},
  {Kind::Block, L"Block"},
  {Kind::EscapeSeq, L"EscapeSeq"},
  {Kind::Dot, L"Dot"},
  {Kind::DefAddress, L"DefAddress"},
  {Kind::GetAddress, L"GetAddress"},
  {Kind::QuestionMark, L"QuestionMark"},
  {Kind::Colon, L"Colon"},
};

static std::wostream& operator<<(std::wostream& o, Token& t) {
	o << kindToString[t.kind] << "    " << t.source;
	return o;
}

static Kind toKind(std::wstring s) {
	auto result = stringToKind.find(s);
	if (result == stringToKind.end()) {
		return Kind::Unknown;
	}
	return stringToKind[s];
}

std::vector<Token> scan(std::wstring sourceCode);
void scanLinedCommentLiteral(std::wstring::iterator& iter);
void scanMultiLinedCommentLiteral(std::wstring& source, std::wstring::iterator& iter);
Token scanNumberLiteral(std::wstring::iterator& iter);
Token scanStringLiteral(std::wstring&, std::wstring::iterator&);
Token scanIdentifierAndKeyword(std::wstring::iterator&);
Token scanOperatorAndPunctuator(std::wstring::iterator&);
CharType getCharType(wchar_t);
bool isCharType(wchar_t, CharType);






#endif