#include "parser.h"

static std::vector<std::wstring> cmdList = {
	L"adr", L"pop", L"psh", L"set", L"inc", L"dec", L"jmp", L"ret", 
	L"prt", L"prl", L"try", L"int", L"str", L"flt", L"inp", L"cal", L"ext",
	L"add", L"sub", L"mul", L"div", L"mod", L"pow", L"sin", L"cos", L"tan",
	L"grt", L"goe", L"les", L"loe", L"eql", L"neq", L"lad", L"lor"
};

HSML_Command* parseADR(std::map<std::wstring, int>& addrMap) {
	current++; // adr
	expect(Kind::Identifier);
	std::wstring adrName = current->source;
	current++;
	expect(Kind::DefAddress);
	current++;
	int adr;
	if (current->kind == Kind::IntegerLiteral) {
		adr = std::stoi(current->source);
	}
	else {
		std::wcout << "Invalid Character : " << current->source;
		exit(1);
	}
	addrMap[adrName] = adr;
	HSML_Command* result = new HSML_ADR(adrName, adr);
	return result;
}
HSML_Command* parsePOP(std::map<std::wstring, int>& addrMap) {
	current++; // pop
	int adr;
	if (current->kind == Kind::DefAddress) {
		current++;
		if (current->kind == Kind::IntegerLiteral) {
			adr = std::stoi(current->source);
		}
	}
	else {
		expect(Kind::Identifier);
		if (addrMap.find(current->source) == addrMap.end()) {
			std::wcout << "Unregistered Address Name : " << current->source;
			exit(1);
		}
		adr = addrMap[current->source];
	}
	HSML_Command* result = new HSML_POP(adr);
	return result;
}

HSML_Command* parsePSH(std::map<std::wstring, int>& addrMap) {
	current++; // psh
	HSML_Command* result = nullptr;
	if (current->kind == Kind::GetAddress) {
		current++;
		expect(Kind::Identifier);
		if (addrMap.find(current->source) == addrMap.end()) {
			std::wcout << "Unregistered Address Name : " << current->source;
			exit(1);
		}
		int address = addrMap[current->source];
		result = new HSML_PSH(address);
	}
	else {
		if (current->kind == Kind::IntegerLiteral) {
			int value = std::stoi(current->source);
			result = new HSML_PSH(std::any(value));
		}
		else if (current->kind == Kind::FloatingLiteral) {
			float value = std::stof(current->source);
			result = new HSML_PSH(std::any(value));
		}
		else if (current->kind == Kind::StringLiteral) {
			std::wstring value = current->source;
			result = new HSML_PSH(std::any(value));
		}
		else {
			std::wcout << L"Unexpected Literal : " << current->source;
			exit(1);
		}
	}
	return result;
}
HSML_Command* parseSET(std::map<std::wstring, int>& addrMap) {
	current++; // set
	int targetAddress;
	HSML_Command* result = nullptr;
	if (current->kind == Kind::IntegerLiteral) {
		targetAddress = std::stoi(current->source);
		current++;
	}
	else {
		expect(Kind::Identifier);
		if (addrMap.find(current->source) == addrMap.end()) {
			std::wcout << L"Unregistered Address Name : " << current->source;
			exit(1);
		}
		targetAddress = addrMap[current->source];
		current++;
	}
	if (current->kind == Kind::GetAddress) {
		current++;
		expect(Kind::Identifier);
		if (addrMap.find(current->source) == addrMap.end()) {
			std::wcout << L"Unregistered Address Name : " << current->source;
			exit(1);
		}
		int withAddress = addrMap[current->source];
		result = new HSML_SET(targetAddress, withAddress);
	}
	else {
		if (current->kind == Kind::IntegerLiteral) {
			int value = std::stoi(current->source);
			result = new HSML_SET(targetAddress, std::any(value));
		}
		else if (current->kind == Kind::FloatingLiteral) {
			float value = std::stof(current->source);
			result = new HSML_SET(targetAddress, std::any(value));
		}
		else if (current->kind == Kind::StringLiteral) {
			std::wstring value = current->source;
			result = new HSML_SET(targetAddress, std::any(value));
		}
		else {
			std::wcout << L"Unexpected Literal : " << current->source;
			exit(1);
		}
	}
	return result;
}

HSML_Command* parseINC(std::map<std::wstring, int>& addrMap) {
	current++; // inc
	int targetAddress;
	HSML_Command* result = nullptr;
	if (current->kind == Kind::Identifier) {
		if (addrMap.find(current->source) == addrMap.end()) {
			std::wcout << L"Unregistered Address Name : " << current->source;
			exit(1);
		}
		targetAddress = addrMap[current->source];
		current++;
	}
	else {
		expect(Kind::DefAddress);
		current++;
		expect(Kind::IntegerLiteral);
		targetAddress = std::stoi(current->source);
		current++;
	}
	if (current->kind == Kind::GetAddress) {
		current++;
		expect(Kind::Identifier);
		if (addrMap.find(current->source) == addrMap.end()) {
			std::wcout << L"Unregistered Address Name : " << current->source;
			exit(1);
		}
		result = new HSML_INC(targetAddress, addrMap[current->source]);
	}
	else {
		if (current->kind == Kind::IntegerLiteral) {
			int value = std::stoi(current->source);
			result = new HSML_INC(targetAddress, std::any(value));
		}
		else if (current->kind == Kind::FloatingLiteral) {
			float value = std::stof(current->source);
			result = new HSML_INC(targetAddress, std::any(value));
		}
		else if (current->kind == Kind::StringLiteral) {
			std::wstring value = current->source;
			result = new HSML_INC(targetAddress, std::any(value));
		}
		else {
			std::wcout << L"Unexpected Literal : " << current->source;
			exit(1);
		}
	}
	return result;
}
HSML_Command* parseDEC(std::map<std::wstring, int>& addrMap) {
	current++; // inc
	int targetAddress;
	HSML_Command* result = nullptr;
	if (current->kind == Kind::Identifier) {
		if (addrMap.find(current->source) == addrMap.end()) {
			std::wcout << L"Unregistered Address Name : " << current->source;
			exit(1);
		}
		targetAddress = addrMap[current->source];
		current++;
	}
	else {
		expect(Kind::DefAddress);
		current++;
		expect(Kind::IntegerLiteral);
		targetAddress = std::stoi(current->source);
		current++;
	}
	if (current->kind == Kind::GetAddress) {
		current++;
		expect(Kind::Identifier);
		if (addrMap.find(current->source) == addrMap.end()) {
			std::wcout << L"Unregistered Address Name : " << current->source;
			exit(1);
		}
		result = new HSML_DEC(targetAddress, addrMap[current->source]);
	}
	else {
		if (current->kind == Kind::IntegerLiteral) {
			int value = std::stoi(current->source);
			result = new HSML_DEC(targetAddress, std::any(value));
		}
		else if (current->kind == Kind::FloatingLiteral) {
			float value = std::stof(current->source);
			result = new HSML_DEC(targetAddress, std::any(value));
		}
		else if (current->kind == Kind::StringLiteral) {
			std::wstring value = current->source;
			result = new HSML_DEC(targetAddress, std::any(value));
		}
		else {
			std::wcout << L"Unexpected Literal : " << current->source;
			exit(1);
		}
	}
	return result;
}

HSML_Command* parseJMP(std::map<std::wstring, int>& addrMap) {
	current++;
	expect(Kind::IntegerLiteral);
	int targetIndex = std::stoi(current->source);
	HSML_Command* result = new HSML_JMP(targetIndex);
	return result;
}

HSML_Command* parseRET(std::map<std::wstring, int>& addrMap) {
	current++; // ret
	HSML_Command* result = new HSML_RET();
	return result;
}

HSML_Command* parsePRT(std::map<std::wstring, int>& addrMap) {
	current++;
	HSML_Command* result = nullptr;
	if (current->kind == Kind::GetAddress) {
		current++;
		expect(Kind::Identifier);
		if (addrMap.find(current->source) == addrMap.end()) {
			std::wcout << L"Unregistered Address Name : " << current->source;
			exit(1);
		}
		result = new HSML_PRT(addrMap[current->source]);
	}
	else {
		if (current->kind == Kind::IntegerLiteral) {
			int value = std::stoi(current->source);
			result = new HSML_PRT(std::any(value));
		}
		else if (current->kind == Kind::FloatingLiteral) {
			float value = std::stof(current->source);
			result = new HSML_PRT(std::any(value));
		}
		else if (current->kind == Kind::StringLiteral) {
			std::wstring value = current->source;
			result = new HSML_PRT(std::any(value));
		}
		else {
			std::wcout << L"Unexpected Literal : " << current->source;
			exit(1);
		}
	}
	return result;
}

HSML_Command* parsePRL(std::map<std::wstring, int>& addrMap) {
	current++;
	HSML_Command* result = nullptr;
	if (current->kind == Kind::GetAddress) {
		current++;
		expect(Kind::Identifier);
		if (addrMap.find(current->source) == addrMap.end()) {
			std::wcout << L"Unregistered Address Name : " << current->source;
			exit(1);
		}
		result = new HSML_PRL(addrMap[current->source]);
	}
	else {
		if (current->kind == Kind::IntegerLiteral) {
			int value = std::stoi(current->source);
			result = new HSML_PRL(std::any(value));
		}
		else if (current->kind == Kind::FloatingLiteral) {
			float value = std::stof(current->source);
			result = new HSML_PRL(std::any(value));
		}
		else if (current->kind == Kind::StringLiteral) {
			std::wstring value = current->source;
			result = new HSML_PRL(std::any(value));
		}
		else {
			std::wcout << L"Unexpected Literal : " << current->source;
			exit(1);
		}
	}
	return result;
}

HSML_Command* parseTRY(std::map<std::wstring, int>& addrMap) {
	current++;
	expect(Kind::IntegerLiteral);
	int targetIndex = std::stoi(current->source);
	current++;
	expect(Kind::Identifier);
	std::wstring labelName = current->source;
	HSML_Command* result = new HSML_TRY(targetIndex, labelName);
	return result;
}

HSML_Command* parseINT(std::map<std::wstring, int>& addrMap) {
	current++;
	int toAddress;
	int fromAddress;
	if (current->kind == Kind::DefAddress) {
		current++;
		expect(Kind::IntegerLiteral);
		toAddress = std::stoi(current->source);
		current++;
	}
	else {
		expect(Kind::Identifier);
		if (addrMap.find(current->source) == addrMap.end()) {
			std::wcout << L"Unregistered Address Name : " << current->source;
			exit(1);
		}
		toAddress = addrMap[current->source];
		current++;
	}
	expect(Kind::GetAddress);
	current++;
	expect(Kind::Identifier);
	if (addrMap.find(current->source) == addrMap.end()) {
		std::wcout << L"Unregistered Address Name : " << current->source;
		exit(1);
	}
	fromAddress = addrMap[current->source];
	HSML_Command* result = new HSML_INT(toAddress, fromAddress);
	return result;
}

HSML_Command* parseSTR(std::map<std::wstring, int>& addrMap) {
	current++;
	int toAddress;
	int fromAddress;
	if (current->kind == Kind::DefAddress) {
		current++;
		expect(Kind::IntegerLiteral);
		toAddress = std::stoi(current->source);
		current++;
	}
	else {
		expect(Kind::Identifier);
		if (addrMap.find(current->source) == addrMap.end()) {
			std::wcout << L"Unregistered Address Name : " << current->source;
			exit(1);
		}
		toAddress = addrMap[current->source];
		current++;
	}
	expect(Kind::GetAddress);
	current++;
	expect(Kind::Identifier);
	if (addrMap.find(current->source) == addrMap.end()) {
		std::wcout << L"Unregistered Address Name : " << current->source;
		exit(1);
	}
	fromAddress = addrMap[current->source];
	HSML_Command* result = new HSML_STR(toAddress, fromAddress);
	return result;
}

HSML_Command* parseFLT(std::map<std::wstring, int>& addrMap) {
	current++;
	int toAddress;
	int fromAddress;
	if (current->kind == Kind::DefAddress) {
		current++;
		expect(Kind::IntegerLiteral);
		toAddress = std::stoi(current->source);
		current++;
	}
	else {
		expect(Kind::Identifier);
		if (addrMap.find(current->source) == addrMap.end()) {
			std::wcout << L"Unregistered Address Name : " << current->source;
			exit(1);
		}
		toAddress = addrMap[current->source];
		current++;
	}
	expect(Kind::GetAddress);
	current++;
	expect(Kind::Identifier);
	if (addrMap.find(current->source) == addrMap.end()) {
		std::wcout << L"Unregistered Address Name : " << current->source;
		exit(1);
	}
	fromAddress = addrMap[current->source];
	HSML_Command* result = new HSML_FLT(toAddress, fromAddress);
	return result;
}

HSML_Command* parseINP(std::map<std::wstring, int>& addrMap) {
	current++; // inp
	int targetAddress;
	if (current->kind == Kind::Identifier) {
		if (addrMap.find(current->source) == addrMap.end()) {
			std::wcout << L"Unregistered Address Name : " << current->source;
			exit(1);
		}
		targetAddress = addrMap[current->source];
	}
	else {
		expect(Kind::IntegerLiteral);
		targetAddress = std::stoi(current->source);
	}
	HSML_Command* result = nullptr;
	result = new HSML_INP(targetAddress);
	return result;
}

HSML_Command* parseCAL(std::map<std::wstring, int>& addrMap) {
	current++; // cal
	std::wstring labelName;
	expect(Kind::Identifier);
	labelName = current->source;
	HSML_Command* result = nullptr;
	result = new HSML_CAL(labelName);
	return result;
}

HSML_Command* parseEXT(std::map<std::wstring, int>& addrMap) {
	current++; // ext
	int code;
	expect(Kind::IntegerLiteral);
	code = std::stoi(current->source);
	HSML_Command* result = nullptr;
	result = new HSML_EXT(code);
	return result;
}


HSML_Command* parseADD(std::map<std::wstring, int>& addrMap) {
	return parseExpr<HSML_ADD>(addrMap);
}
HSML_Command* parseSUB(std::map<std::wstring, int>& addrMap) {
	return parseExpr<HSML_SUB>(addrMap);
}
HSML_Command* parseMUL(std::map<std::wstring, int>& addrMap) {
	return parseExpr<HSML_MUL>(addrMap);
}
HSML_Command* parseDIV(std::map<std::wstring, int>& addrMap) {
	return parseExpr<HSML_DIV>(addrMap);
}
HSML_Command* parseMOD(std::map<std::wstring, int>& addrMap) {
	return parseExpr<HSML_MOD>(addrMap);
}
HSML_Command* parsePOW(std::map<std::wstring, int>& addrMap) {
	return parseExpr<HSML_POW>(addrMap);
}

HSML_Command* parseSIN(std::map<std::wstring, int>& addrMap) {
	return parseTri<HSML_SIN>(addrMap);
}
HSML_Command* parseCOS(std::map<std::wstring, int>& addrMap){
	return parseTri<HSML_COS>(addrMap);
}
HSML_Command* parseTAN(std::map<std::wstring, int>& addrMap) {
	return parseTri<HSML_TAN>(addrMap);
}

HSML_Command* parseGRT(std::map<std::wstring, int>& addrMap) {
	return parseOp<HSML_GRT>(addrMap);
}
HSML_Command* parseGOE(std::map<std::wstring, int>& addrMap) {
	return parseOp<HSML_GOE>(addrMap);
}
HSML_Command* parseLES(std::map<std::wstring, int>& addrMap) {
	return parseOp<HSML_LES>(addrMap);
}
HSML_Command* parseLOE(std::map<std::wstring, int>& addrMap) {
	return parseOp<HSML_LOE>(addrMap);
}
HSML_Command* parseEQL(std::map<std::wstring, int>& addrMap) {
	return parseOp<HSML_EQL>(addrMap);
}
HSML_Command* parseNEQ(std::map<std::wstring, int>& addrMap) {
	return parseOp<HSML_NEQ>(addrMap);
}
HSML_Command* parseLAD(std::map<std::wstring, int>& addrMap) {
	return parseOp<HSML_LAD>(addrMap);
}
HSML_Command* parseLOR(std::map<std::wstring, int>& addrMap) {
	return parseOp<HSML_LOR>(addrMap);
}

HSML_Program parse(std::vector<Token> tokens) {
	HSML_Program result;
	current = tokens.begin();

	while (current->kind != Kind::EndOfToken) {
		if (current->kind == Kind::EscapeSeq || current->kind == Kind::Block) {
			current++;
			continue;
		}
		else if (current->kind == Kind::Label) {
			result.labels.push_back(parseLabel());
			continue;
		}
	}
	return result;
}

bool isCmd(const std::wstring& k) {
	for (std::wstring& s : cmdList) {
		if (s == k) return true;
	}
	return false;
}


HSML_Label parseLabel() {
	HSML_Label result;
	expect(Kind::Label); current++;
	expect(Kind::Dot); current++;
	expect(Kind::Identifier); {
		result.name = current->source;
		current++;
	}
	expect(Kind::EscapeSeq); current++;
	std::map<std::wstring, int> addrMap{};
	while (current->kind == Kind::Block) {
		current++;
		if (current->kind == Kind::EscapeSeq) {
			while (current->kind == Kind::EscapeSeq) {
				current++;
			}
			continue;
		}
		if (isCmd(current->source) == false) break;
		switch (current->kind) {
		case (Kind::ADD): result.contents.push_back(parseADD(addrMap)); break;
		case (Kind::ADR): result.contents.push_back(parseADR(addrMap)); break;
		case (Kind::CAL): result.contents.push_back(parseCAL(addrMap)); break;
		case (Kind::COS): result.contents.push_back(parseCOS(addrMap)); break;
		case (Kind::DEC): result.contents.push_back(parseDEC(addrMap)); break;
		case (Kind::DIV): result.contents.push_back(parseDIV(addrMap)); break;
		case (Kind::EQL): result.contents.push_back(parseEQL(addrMap)); break;
		case (Kind::EXT): result.contents.push_back(parseEXT(addrMap)); break;
		case (Kind::FLT): result.contents.push_back(parseFLT(addrMap)); break;
		case (Kind::GOE): result.contents.push_back(parseGOE(addrMap)); break;
		case (Kind::GRT): result.contents.push_back(parseGRT(addrMap)); break;
		case (Kind::INC): result.contents.push_back(parseINC(addrMap)); break;
		case (Kind::INP): result.contents.push_back(parseINP(addrMap)); break;
		case (Kind::INT): result.contents.push_back(parseINT(addrMap)); break;
		case (Kind::JMP): result.contents.push_back(parseJMP(addrMap)); break;
		case (Kind::LAD): result.contents.push_back(parseLAD(addrMap)); break;
		case (Kind::LES): result.contents.push_back(parseLES(addrMap)); break;
		case (Kind::LOE): result.contents.push_back(parseLOE(addrMap)); break;
		case (Kind::LOR): result.contents.push_back(parseLOR(addrMap)); break;
		case (Kind::MOD): result.contents.push_back(parseMOD(addrMap)); break;
		case (Kind::MUL): result.contents.push_back(parseMUL(addrMap)); break;
		case (Kind::NEQ): result.contents.push_back(parseNEQ(addrMap)); break;
		case (Kind::POP): result.contents.push_back(parsePOP(addrMap)); break;
		case (Kind::POW): result.contents.push_back(parsePOW(addrMap)); break;
		case (Kind::PRL): result.contents.push_back(parsePRL(addrMap)); break;
		case (Kind::PRT): result.contents.push_back(parsePRT(addrMap)); break;
		case (Kind::PSH): result.contents.push_back(parsePSH(addrMap)); break;
		case (Kind::RET): result.contents.push_back(parseRET(addrMap)); break;
		case (Kind::SET): result.contents.push_back(parseSET(addrMap)); break;
		case (Kind::SIN): result.contents.push_back(parseSIN(addrMap)); break;
		case (Kind::STR): result.contents.push_back(parseSTR(addrMap)); break;
		case (Kind::SUB): result.contents.push_back(parseSUB(addrMap)); break;
		case (Kind::TAN): result.contents.push_back(parseTAN(addrMap)); break;
		case (Kind::TRY): result.contents.push_back(parseTRY(addrMap)); break;
		}
		if (current->kind != Kind::EndOfToken) {
			current++;
			if (current->kind == Kind::EscapeSeq) {
				current++;
			}
		}
	}
	return result;
}