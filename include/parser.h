#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include <iostream>
#include <any>
#include <stack>

#include "scanner.h"

enum class CommandType {
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
};


#pragma region HSML_Command

struct HSML_Command {
	CommandType type;
	virtual void interpret(struct HSML_LabelInfo* info) {};
};

struct HSML_LabelInfo {
	std::wstring name;
	std::vector<HSML_Command*>* commands;
	std::stack<std::any>* globalStack; 
	std::map<int, std::any>* localMap;
	int* localIndexPointer; 
	int lineCount;
	bool* returned;
	bool* errored;
	HSML_LabelInfo(std::vector<HSML_Command*>* cmds, std::stack<std::any>* gs, std::map<int, std::any>* lm, int* lp, int lc, std::wstring n, bool* rtrned, bool* erd)
		: commands(cmds), globalStack(gs), localMap(lm), localIndexPointer(lp), lineCount(lc), name(n), returned(rtrned), errored(erd) {}
};

struct HSML_ADR : HSML_Command {
	std::wstring name;
	int address;
	HSML_ADR(std::wstring n, int a) : name(n), address(a) { this->type = CommandType::ADR; }
	void interpret(HSML_LabelInfo* info);
};

struct HSML_POP : HSML_Command {
	int targetAddress;
	HSML_POP(int ta) : targetAddress(ta) { this->type = CommandType::POP; }
	void interpret(HSML_LabelInfo* info);
};

struct HSML_PSH : HSML_Command {
	std::any value;
	int address;
	bool pushWithLiteral;
	explicit HSML_PSH(std::any v) : pushWithLiteral(true), value(v) { this->type = CommandType::PSH; }
	explicit HSML_PSH(int i) : pushWithLiteral(false), address(i) { this->type = CommandType::PSH; }
	void interpret(HSML_LabelInfo* info);
};

struct HSML_SET : HSML_Command {
	int targetAddress;
	
	std::any value;
	int withAddress;
	bool setWithLiteral;

	explicit HSML_SET(int ta, int w) : targetAddress(ta), setWithLiteral(false), withAddress(w) { this->type = CommandType::SET; }
	explicit HSML_SET(int ta, std::any v) : targetAddress(ta), setWithLiteral(true), value(v) { this->type = CommandType::SET; }
	void interpret(HSML_LabelInfo* info);
};

struct HSML_INC : HSML_Command {
	int targetAddress;

	bool incWithLiteral;
	std::any incValue;
	int incAddress;
	explicit HSML_INC(int ta, int ia) : targetAddress(ta), incWithLiteral(false), incAddress(ia) { this->type = CommandType::INC; }
	explicit HSML_INC(int ta, std::any v) : targetAddress(ta), incWithLiteral(true), incValue(v) { this->type = CommandType::INC; }
	void interpret(HSML_LabelInfo* info);
};

struct HSML_DEC : HSML_Command {
	int targetAddress;
	
	bool decWithLiteral;
	std::any decValue;
	int decAddress;
	explicit HSML_DEC(int ta, int ia) : targetAddress(ta), decWithLiteral(false), decAddress(ia) { this->type = CommandType::DEC; }
	explicit HSML_DEC(int ta, std::any v) : targetAddress(ta), decWithLiteral(true), decValue(v) { this->type = CommandType::DEC; }
	void interpret(HSML_LabelInfo* info);
};


struct HSML_JMP : HSML_Command {
	int targetIndex;
	HSML_JMP(int i) : targetIndex(i) { this->type = CommandType::JMP; }
	void interpret(HSML_LabelInfo* info);
};

struct HSML_RET : HSML_Command {
	HSML_RET() { this->type = CommandType::RET; }
	void interpret(HSML_LabelInfo* info);
};

struct HSML_PRT : HSML_Command {
	bool prtWithLiteral;
	std::any value;
	int valueAddress;
	explicit HSML_PRT(int va) : prtWithLiteral(false), valueAddress(va) { this->type = CommandType::PRT; }
	explicit HSML_PRT(std::any v) : prtWithLiteral(true), value(v) { this->type = CommandType::PRT; }
	void interpret(HSML_LabelInfo* info);
};

struct HSML_PRL : HSML_Command {
	bool prlWithLiteral;
	std::any value;
	int valueAddress;
	explicit HSML_PRL(int va) : prlWithLiteral(false), valueAddress(va) { this->type = CommandType::PRL; }
	explicit HSML_PRL(std::any v) : prlWithLiteral(true), value(v) { this->type = CommandType::PRL; }
	void interpret(HSML_LabelInfo* info);
};

struct HSML_TRY : HSML_Command {
	int targetIndex;
	std::wstring labelName;
	HSML_TRY(int ti, std::wstring n) : targetIndex(ti), labelName(n) { this->type = CommandType::TRY; }
	void interpret(HSML_LabelInfo* info);
};

struct HSML_INT : HSML_Command {
	int toAddress;
	int fromAddress;
	HSML_INT(int t, int f) : toAddress(t), fromAddress(f) { this->type = CommandType::INT; }
	void interpret(HSML_LabelInfo* info);
};

struct HSML_STR : HSML_Command {
	int toAddress;
	int fromAddress;
	HSML_STR(int t, int f) : toAddress(t), fromAddress(f) { this->type = CommandType::STR; }
	void interpret(HSML_LabelInfo* info);
};

struct HSML_FLT : HSML_Command {
	int toAddress;
	int fromAddress;
	HSML_FLT(int t, int f) : toAddress(t), fromAddress(f) { this->type = CommandType::FLT; }
	void interpret(HSML_LabelInfo* info);
};


struct HSML_INP : HSML_Command {
	int targetAddress;
	HSML_INP(int ta) : targetAddress(ta) { this->type = CommandType::INP; }
	void interpret(HSML_LabelInfo* info);
};

struct HSML_CAL : HSML_Command {
	std::wstring labelName;
	HSML_CAL(std::wstring l) : labelName(l) { this->type = CommandType::CAL; }
	void interpret(HSML_LabelInfo* info);
};

struct HSML_EXT : HSML_Command {
	int code;
	HSML_EXT(int c) : code(c) { this->type = CommandType::EXT; }
	void interpret(HSML_LabelInfo* info);
};

enum class ExpType {
	ADR2ADR, ADR2VAL, VAL2ADR, VAL2VAL
};

struct HSML_ADD : HSML_Command {
	ExpType expType;
	int targetAddress;
	int leftAddress;
	std::any left;
	int rightAddress;
	std::any right;
	explicit HSML_ADD(int ta, int la, int ra)         : targetAddress(ta), expType(ExpType::ADR2ADR), leftAddress(la), rightAddress(ra) { this->type = CommandType::ADD; }
	explicit HSML_ADD(int ta, std::any a, int ra)     : targetAddress(ta), expType(ExpType::VAL2ADR), left(a), rightAddress(ra) { this->type = CommandType::ADD; }
	explicit HSML_ADD(int ta, int la, std::any b)     : targetAddress(ta), expType(ExpType::ADR2VAL), leftAddress(la), right(b) { this->type = CommandType::ADD; }
	explicit HSML_ADD(int ta, std::any a, std::any b) : targetAddress(ta), expType(ExpType::VAL2VAL), left(a), right(b) { this->type = CommandType::ADD; }
	void interpret(HSML_LabelInfo* info);
};

struct HSML_SUB : HSML_Command {
	ExpType expType;
	int targetAddress;
	int leftAddress;
	std::any left;
	int rightAddress;
	std::any right;
	explicit HSML_SUB(int ta, int la, int ra) : targetAddress(ta), expType(ExpType::ADR2ADR), leftAddress(la), rightAddress(ra) { this->type = CommandType::SUB; }
	explicit HSML_SUB(int ta, std::any a, int ra) : targetAddress(ta), expType(ExpType::VAL2ADR), left(a), rightAddress(ra) { this->type = CommandType::SUB; }
	explicit HSML_SUB(int ta, int la, std::any b) : targetAddress(ta), expType(ExpType::ADR2VAL), leftAddress(la), right(b) { this->type = CommandType::SUB; }
	explicit HSML_SUB(int ta, std::any a, std::any b) : targetAddress(ta), expType(ExpType::VAL2VAL), left(a), right(b) { this->type = CommandType::SUB; }
	void interpret(HSML_LabelInfo* info);
};

struct HSML_MUL : HSML_Command {
	ExpType expType;
	int targetAddress;
	int leftAddress;
	std::any left;
	int rightAddress;
	std::any right;
	explicit HSML_MUL(int ta, int la, int ra) : targetAddress(ta), expType(ExpType::ADR2ADR), leftAddress(la), rightAddress(ra) { this->type = CommandType::MUL; }
	explicit HSML_MUL(int ta, std::any a, int ra) : targetAddress(ta), expType(ExpType::VAL2ADR), left(a), rightAddress(ra) { this->type = CommandType::MUL; }
	explicit HSML_MUL(int ta, int la, std::any b) : targetAddress(ta), expType(ExpType::ADR2VAL), leftAddress(la), right(b) { this->type = CommandType::MUL; }
	explicit HSML_MUL(int ta, std::any a, std::any b) : targetAddress(ta), expType(ExpType::VAL2VAL), left(a), right(b) { this->type = CommandType::MUL; }
	void interpret(HSML_LabelInfo* info);
};

struct HSML_DIV : HSML_Command {
	ExpType expType;
	int targetAddress;
	int leftAddress;
	std::any left;
	int rightAddress;
	std::any right;
	explicit HSML_DIV(int ta, int la, int ra) : targetAddress(ta), expType(ExpType::ADR2ADR), leftAddress(la), rightAddress(ra) { this->type = CommandType::DIV; }
	explicit HSML_DIV(int ta, std::any a, int ra) : targetAddress(ta), expType(ExpType::VAL2ADR), left(a), rightAddress(ra) { this->type = CommandType::DIV; }
	explicit HSML_DIV(int ta, int la, std::any b) : targetAddress(ta), expType(ExpType::ADR2VAL), leftAddress(la), right(b) { this->type = CommandType::DIV; }
	explicit HSML_DIV(int ta, std::any a, std::any b) : targetAddress(ta), expType(ExpType::VAL2VAL), left(a), right(b) { this->type = CommandType::DIV; }
	void interpret(HSML_LabelInfo* info);
};

struct HSML_MOD : HSML_Command {
	ExpType expType;
	int targetAddress;
	int leftAddress;
	std::any left;
	int rightAddress;
	std::any right;
	explicit HSML_MOD(int ta, int la, int ra) : targetAddress(ta), expType(ExpType::ADR2ADR), leftAddress(la), rightAddress(ra) { this->type = CommandType::MOD; }
	explicit HSML_MOD(int ta, std::any a, int ra) : targetAddress(ta), expType(ExpType::VAL2ADR), left(a), rightAddress(ra) { this->type = CommandType::MOD; }
	explicit HSML_MOD(int ta, int la, std::any b) : targetAddress(ta), expType(ExpType::ADR2VAL), leftAddress(la), right(b) { this->type = CommandType::MOD; }
	explicit HSML_MOD(int ta, std::any a, std::any b) : targetAddress(ta), expType(ExpType::VAL2VAL), left(a), right(b) { this->type = CommandType::MOD; }
	void interpret(HSML_LabelInfo* info);
};

struct HSML_POW : HSML_Command {
	ExpType expType;
	int targetAddress;
	int leftAddress;
	std::any left;
	int rightAddress;
	std::any right;
	explicit HSML_POW(int ta, int la, int ra) : targetAddress(ta), expType(ExpType::ADR2ADR), leftAddress(la), rightAddress(ra) { this->type = CommandType::POW; }
	explicit HSML_POW(int ta, std::any a, int ra) : targetAddress(ta), expType(ExpType::VAL2ADR), left(a), rightAddress(ra) { this->type = CommandType::POW; }
	explicit HSML_POW(int ta, int la, std::any b) : targetAddress(ta), expType(ExpType::ADR2VAL), leftAddress(la), right(b) { this->type = CommandType::POW; }
	explicit HSML_POW(int ta, std::any a, std::any b) : targetAddress(ta), expType(ExpType::VAL2VAL), left(a), right(b) { this->type = CommandType::POW; }
	void interpret(HSML_LabelInfo* info);
};

struct HSML_SIN : HSML_Command {
	int targetAddress;
	bool sinWithLiteral;
	std::any value;
	int valueAddress;
	explicit HSML_SIN(int ta, int va) : targetAddress(ta), sinWithLiteral(false), valueAddress(va) { this->type = CommandType::SIN; }
	explicit HSML_SIN(int ta, std::any v) : targetAddress(ta), sinWithLiteral(true), value(v) { this->type = CommandType::SIN; }
	void interpret(HSML_LabelInfo* info);
};

struct HSML_COS : HSML_Command {
	int targetAddress;
	bool cosWithLiteral;
	std::any value;
	int valueAddress;
	explicit HSML_COS(int ta, int va) : targetAddress(ta), cosWithLiteral(false), valueAddress(va) { this->type = CommandType::COS; }
	explicit HSML_COS(int ta, std::any v) : targetAddress(ta), cosWithLiteral(true), value(v) { this->type = CommandType::COS; }
	void interpret(HSML_LabelInfo* info);
};

struct HSML_TAN : HSML_Command {
	int targetAddress;
	bool tanWithLiteral;
	std::any value;
	int valueAddress;
	explicit HSML_TAN(int ta, int va) : targetAddress(ta), tanWithLiteral(false), valueAddress(va) { this->type = CommandType::TAN; }
	explicit HSML_TAN(int ta, std::any v) : targetAddress(ta), tanWithLiteral(true), value(v) { this->type = CommandType::TAN; }
	void interpret(HSML_LabelInfo* info);
};


struct HSML_GRT : HSML_Command {
	ExpType expType;
	std::any left;
	int leftAddress;
	std::any right;
	int rightAddress;
	int targetIndex;
	HSML_GRT(std::any a, std::any b, int ti) : expType(ExpType::VAL2VAL), left(a), right(b), targetIndex(ti) { this->type = CommandType::GRT; }
	HSML_GRT(int la,     std::any b, int ti) : expType(ExpType::ADR2VAL), leftAddress(la), right(b), targetIndex(ti) { this->type = CommandType::GRT; }
	HSML_GRT(std::any a, int ra,     int ti) : expType(ExpType::VAL2ADR), left(a), rightAddress(ra), targetIndex(ti) { this->type = CommandType::GRT; }
	HSML_GRT(int la,     int ra,     int ti) : expType(ExpType::ADR2ADR), leftAddress(la), rightAddress(ra), targetIndex(ti) { this->type = CommandType::GRT; }
	void interpret(HSML_LabelInfo* info);
};

struct HSML_GOE : HSML_Command {
	ExpType expType;
	std::any left;
	int leftAddress;
	std::any right;
	int rightAddress;
	int targetIndex;
	HSML_GOE(std::any a, std::any b, int ti) : expType(ExpType::VAL2VAL), left(a), right(b), targetIndex(ti) { this->type = CommandType::GOE; }
	HSML_GOE(int la, std::any b, int ti) : expType(ExpType::ADR2VAL), leftAddress(la), right(b), targetIndex(ti) { this->type = CommandType::GOE; }
	HSML_GOE(std::any a, int ra, int ti) : expType(ExpType::VAL2ADR), left(a), rightAddress(ra), targetIndex(ti) { this->type = CommandType::GOE; }
	HSML_GOE(int la, int ra, int ti) : expType(ExpType::ADR2ADR), leftAddress(la), rightAddress(ra), targetIndex(ti) { this->type = CommandType::GOE; }
	void interpret(HSML_LabelInfo* info);
};

struct HSML_LES : HSML_Command {
	ExpType expType;
	std::any left;
	int leftAddress;
	std::any right;
	int rightAddress;
	int targetIndex;
	HSML_LES(std::any a, std::any b, int ti) : expType(ExpType::VAL2VAL), left(a), right(b), targetIndex(ti) { this->type = CommandType::LES; }
	HSML_LES(int la, std::any b, int ti) : expType(ExpType::ADR2VAL), leftAddress(la), right(b), targetIndex(ti) { this->type = CommandType::LES; }
	HSML_LES(std::any a, int ra, int ti) : expType(ExpType::VAL2ADR), left(a), rightAddress(ra), targetIndex(ti) { this->type = CommandType::LES; }
	HSML_LES(int la, int ra, int ti) : expType(ExpType::ADR2ADR), leftAddress(la), rightAddress(ra), targetIndex(ti) { this->type = CommandType::LES; }
	void interpret(HSML_LabelInfo* info);
};

struct HSML_LOE : HSML_Command {
	ExpType expType;
	std::any left;
	int leftAddress;
	std::any right;
	int rightAddress;
	int targetIndex;
	HSML_LOE(std::any a, std::any b, int ti) : expType(ExpType::VAL2VAL), left(a), right(b), targetIndex(ti) { this->type = CommandType::LOE; }
	HSML_LOE(int la, std::any b, int ti) : expType(ExpType::ADR2VAL), leftAddress(la), right(b), targetIndex(ti) { this->type = CommandType::LOE; }
	HSML_LOE(std::any a, int ra, int ti) : expType(ExpType::VAL2ADR), left(a), rightAddress(ra), targetIndex(ti) { this->type = CommandType::LOE; }
	HSML_LOE(int la, int ra, int ti) : expType(ExpType::ADR2ADR), leftAddress(la), rightAddress(ra), targetIndex(ti) { this->type = CommandType::LOE; }
	void interpret(HSML_LabelInfo* info);
};

struct HSML_EQL : HSML_Command {
	ExpType expType;
	std::any left;
	int leftAddress;
	std::any right;
	int rightAddress;
	int targetIndex;
	HSML_EQL(std::any a, std::any b, int ti) : expType(ExpType::VAL2VAL), left(a), right(b), targetIndex(ti) { this->type = CommandType::EQL; }
	HSML_EQL(int la, std::any b, int ti) : expType(ExpType::ADR2VAL), leftAddress(la), right(b), targetIndex(ti) { this->type = CommandType::EQL; }
	HSML_EQL(std::any a, int ra, int ti) : expType(ExpType::VAL2ADR), left(a), rightAddress(ra), targetIndex(ti) { this->type = CommandType::EQL; }
	HSML_EQL(int la, int ra, int ti) : expType(ExpType::ADR2ADR), leftAddress(la), rightAddress(ra), targetIndex(ti) { this->type = CommandType::EQL; }
	void interpret(HSML_LabelInfo* info);
};

struct HSML_NEQ : HSML_Command {
	ExpType expType;
	std::any left;
	int leftAddress;
	std::any right;
	int rightAddress;
	int targetIndex;
	HSML_NEQ(std::any a, std::any b, int ti) : expType(ExpType::VAL2VAL), left(a), right(b), targetIndex(ti) { this->type = CommandType::NEQ; }
	HSML_NEQ(int la, std::any b, int ti) : expType(ExpType::ADR2VAL), leftAddress(la), right(b), targetIndex(ti) { this->type = CommandType::NEQ; }
	HSML_NEQ(std::any a, int ra, int ti) : expType(ExpType::VAL2ADR), left(a), rightAddress(ra), targetIndex(ti) { this->type = CommandType::NEQ; }
	HSML_NEQ(int la, int ra, int ti) : expType(ExpType::ADR2ADR), leftAddress(la), rightAddress(ra), targetIndex(ti) { this->type = CommandType::NEQ; }
	void interpret(HSML_LabelInfo* info);
};

struct HSML_LAD : HSML_Command {
	ExpType expType;
	std::any left;
	int leftAddress;
	std::any right;
	int rightAddress;
	int targetIndex;
	HSML_LAD(std::any a, std::any b, int ti) : expType(ExpType::VAL2VAL), left(a), right(b), targetIndex(ti) { this->type = CommandType::LAD; }
	HSML_LAD(int la, std::any b, int ti) : expType(ExpType::ADR2VAL), leftAddress(la), right(b), targetIndex(ti) { this->type = CommandType::LAD; }
	HSML_LAD(std::any a, int ra, int ti) : expType(ExpType::VAL2ADR), left(a), rightAddress(ra), targetIndex(ti) { this->type = CommandType::LAD; }
	HSML_LAD(int la, int ra, int ti) : expType(ExpType::ADR2ADR), leftAddress(la), rightAddress(ra), targetIndex(ti) { this->type = CommandType::LAD; }
	void interpret(HSML_LabelInfo* info);
};

struct HSML_LOR : HSML_Command {
	ExpType expType;
	std::any left;
	int leftAddress;
	std::any right;
	int rightAddress;
	int targetIndex;
	HSML_LOR(std::any a, std::any b, int ti) : expType(ExpType::VAL2VAL), left(a), right(b), targetIndex(ti) { this->type = CommandType::LOR; }
	HSML_LOR(int la, std::any b, int ti) : expType(ExpType::ADR2VAL), leftAddress(la), right(b), targetIndex(ti) { this->type = CommandType::LOR; }
	HSML_LOR(std::any a, int ra, int ti) : expType(ExpType::VAL2ADR), left(a), rightAddress(ra), targetIndex(ti) { this->type = CommandType::LOR; }
	HSML_LOR(int la, int ra, int ti) : expType(ExpType::ADR2ADR), leftAddress(la), rightAddress(ra), targetIndex(ti) { this->type = CommandType::LOR; }
	void interpret(HSML_LabelInfo* info);
};



#pragma endregion


struct HSML_Label {
	std::wstring name;
	std::vector<HSML_Command*> contents;
};


struct HSML_Program {
	std::vector<HSML_Label> labels;
};

static std::vector<Token>::iterator current;

static void expect(Kind k) {
	if (current->kind != k) {
		std::wcout << L"Error From Parser.h : Expect Token : " << kindToString[k] << " : But " << current->source << " Were Given";
		exit(1);
	}
}

HSML_Command* parseADR(std::map<std::wstring, int>& addrMap);
HSML_Command* parsePOP(std::map<std::wstring, int>& addrMap);
HSML_Command* parsePSH(std::map<std::wstring, int>& addrMap);
HSML_Command* parseSET(std::map<std::wstring, int>& addrMap);
HSML_Command* parseINC(std::map<std::wstring, int>& addrMap);
HSML_Command* parseDEC(std::map<std::wstring, int>& addrMap);
HSML_Command* parseJMP(std::map<std::wstring, int>& addrMap);
HSML_Command* parseRET(std::map<std::wstring, int>& addrMap);
HSML_Command* parsePRT(std::map<std::wstring, int>& addrMap);
HSML_Command* parsePRL(std::map<std::wstring, int>& addrMap);
HSML_Command* parseTRY(std::map<std::wstring, int>& addrMap);
HSML_Command* parseINT(std::map<std::wstring, int>& addrMap);
HSML_Command* parseSTR(std::map<std::wstring, int>& addrMap);
HSML_Command* parseFLT(std::map<std::wstring, int>& addrMap);
HSML_Command* parseINP(std::map<std::wstring, int>& addrMap);
HSML_Command* parseCAL(std::map<std::wstring, int>& addrMap);
HSML_Command* parseEXT(std::map<std::wstring, int>& addrMap);
HSML_Command* parseADD(std::map<std::wstring, int>& addrMap);
HSML_Command* parseSUB(std::map<std::wstring, int>& addrMap);
HSML_Command* parseMUL(std::map<std::wstring, int>& addrMap);
HSML_Command* parseDIV(std::map<std::wstring, int>& addrMap);
HSML_Command* parseMOD(std::map<std::wstring, int>& addrMap);
HSML_Command* parsePOW(std::map<std::wstring, int>& addrMap);
HSML_Command* parseSIN(std::map<std::wstring, int>& addrMap);
HSML_Command* parseCOS(std::map<std::wstring, int>& addrMap);
HSML_Command* parseTAN(std::map<std::wstring, int>& addrMap);
HSML_Command* parseGRT(std::map<std::wstring, int>& addrMap);
HSML_Command* parseGOE(std::map<std::wstring, int>& addrMap);
HSML_Command* parseLES(std::map<std::wstring, int>& addrMap);
HSML_Command* parseLOE(std::map<std::wstring, int>& addrMap);
HSML_Command* parseEQL(std::map<std::wstring, int>& addrMap);
HSML_Command* parseNEQ(std::map<std::wstring, int>& addrMap);
HSML_Command* parseLAD(std::map<std::wstring, int>& addrMap);
HSML_Command* parseLOR(std::map<std::wstring, int>& addrMap);

HSML_Label parseLabel();
HSML_Program parse(std::vector<Token> tokens);


template<typename T>
static HSML_Command* parseExpr(std::map<std::wstring, int>& addrMap) {
	current++; // add
	int targetAddress;
	int leftAddress, rightAddress;
	std::any left, right;
	bool isLeftLiteral, isRightLiteral;

	HSML_Command* result = nullptr;
	if (current->kind == Kind::DefAddress) {
		current++;
		expect(Kind::IntegerLiteral);
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
		isLeftLiteral = false;
		current++;
		expect(Kind::Identifier);
		if (addrMap.find(current->source) == addrMap.end()) {
			std::wcout << L"Unregistered Address Name : " << current->source;
			exit(1);
		}
		leftAddress = addrMap[current->source];
		current++;
	}
	else {
		isLeftLiteral = true;
		if (current->kind == Kind::IntegerLiteral) {
			left = std::any(std::stoi(current->source));
			current++;
		}
		else if (current->kind == Kind::FloatingLiteral) {
			left = std::any(std::stof(current->source));
			current++;
		}
		else if (current->kind == Kind::StringLiteral) {
			left = std::any(current->source);
			current++;
		}
		else {
			std::wcout << L"Unexpected Literal : " << current->source;
			exit(1);
		}
	}
	if (current->kind == Kind::GetAddress) {
		isRightLiteral = false;
		current++;
		expect(Kind::Identifier);
		if (addrMap.find(current->source) == addrMap.end()) {
			std::wcout << L"Unregistered Address Name : " << current->source;
			exit(1);
		}
		rightAddress = addrMap[current->source];
	}
	else {
		isRightLiteral = true;
		if (current->kind == Kind::IntegerLiteral) {
			right = std::any(std::stoi(current->source));
		}
		else if (current->kind == Kind::FloatingLiteral) {
			right = std::any(std::stof(current->source));
		}
		else if (current->kind == Kind::StringLiteral) {
			right = std::any(current->source);
		}
		else {
			std::wcout << L"Unexpected Literal : " << current->source;
			exit(1);
		}
	}
	if (isLeftLiteral == true && isRightLiteral == true)
		result = new T(targetAddress, left, right);
	else if (isLeftLiteral == false && isRightLiteral == true)
		result = new T(targetAddress, leftAddress, right);
	else if (isLeftLiteral == true && isRightLiteral == false)
		result = new T(targetAddress, left, rightAddress);
	else if (isLeftLiteral == false && isRightLiteral == false)
		result = new T(targetAddress, leftAddress, rightAddress);
	return result;
}

template<typename T>
static HSML_Command* parseTri(std::map<std::wstring, int>& addrMap) {
	current++;
	int targetAddress;
	bool triWithLiteral;
	std::any value;
	int valueAddress;

	HSML_Command* result = nullptr;
	if (current->kind == Kind::DefAddress) {
		current++;
		expect(Kind::IntegerLiteral);
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
		triWithLiteral = false;
		current++;
		expect(Kind::Identifier);
		if (addrMap.find(current->source) == addrMap.end()) {
			std::wcout << L"Unregistered Address Name : " << current->source;
			exit(1);
		}
		valueAddress = addrMap[current->source];
	}
	else {
		triWithLiteral = true;
		if (current->kind == Kind::IntegerLiteral) {
			value = std::any(std::stoi(current->source));
		}
		else if (current->kind == Kind::FloatingLiteral) {
			value = std::any(std::stof(current->source));
		}
		else if (current->kind == Kind::StringLiteral) {
			value = std::any(current->source);
		}
		else {
			std::wcout << L"Unexpected Literal : " << current->source;
			exit(1);
		}
	}
	if (triWithLiteral == true) {
		result = new T(targetAddress, value);
	}
	else {
		result = new T(targetAddress, valueAddress);
	}
	return result;
}

template<typename T>
static HSML_Command* parseOp(std::map<std::wstring, int>& addrMap) {
	current++;
	std::any left;
	int leftAddress;
	std::any right;
	int rightAddress;
	bool isLeftLiteral, isRightLiteral;
	int jumpToIndex;

	HSML_Command* result = nullptr;
	if (current->kind == Kind::GetAddress) {
		isLeftLiteral = false;
		current++;
		expect(Kind::Identifier);
		if (addrMap.find(current->source) == addrMap.end()) {
			std::wcout << L"Unregistered Address Name : " << current->source;
			exit(1);
		}
		leftAddress = addrMap[current->source];
		current++;
	}
	else {
		isLeftLiteral = true;
		if (current->kind == Kind::IntegerLiteral) {
			left = std::any(std::stoi(current->source));
			current++;
		}
		else if (current->kind == Kind::FloatingLiteral) {
			left = std::any(std::stof(current->source));
			current++;
		}
		else if (current->kind == Kind::StringLiteral) {
			left = std::any(current->source);
			current++;
		}
		else {
			std::wcout << L"Unexpected Literal : " << current->source;
			exit(1);
		}
	}
	if (current->kind == Kind::GetAddress) {
		isRightLiteral = false;
		current++;
		expect(Kind::Identifier);
		if (addrMap.find(current->source) == addrMap.end()) {
			std::wcout << L"Unregistered Address Name : " << current->source;
			exit(1);
		}
		rightAddress = addrMap[current->source];
		current++;
	}
	else {
		isRightLiteral = true;
		if (current->kind == Kind::IntegerLiteral) {
			right = std::any(std::stoi(current->source));
			current++;
		}
		else if (current->kind == Kind::FloatingLiteral) {
			right = std::any(std::stof(current->source));
			current++;
		}
		else if (current->kind == Kind::StringLiteral) {
			right = std::any(current->source);
			current++;
		}
		else {
			std::wcout << L"Unexpected Literal : " << current->source;
			exit(1);
		}
	}
	expect(Kind::IntegerLiteral);
	jumpToIndex = std::stoi(current->source);
	if (isLeftLiteral == false && isRightLiteral == false)
		result = new T(leftAddress, rightAddress, jumpToIndex);
	else if (isLeftLiteral == true && isRightLiteral == false)
		result = new T(left, rightAddress, jumpToIndex);
	else if (isLeftLiteral == false && isRightLiteral == true)
		result = new T(leftAddress, right, jumpToIndex);
	else if (isLeftLiteral == true && isRightLiteral == true)
		result = new T(left, right, jumpToIndex);
	return result;
}

#endif