#include "interpreter.h"


void HSML_ADR::interpret(HSML_LabelInfo* info) {
	(*info->localMap)[this->address] = std::any(nullptr);
	(*(info->localIndexPointer))++;
}

void HSML_POP::interpret(HSML_LabelInfo* info) {
	std::any top = info->globalStack->top();
	info->globalStack->pop();
	(*info->localMap)[this->targetAddress] = top;
	(*(info->localIndexPointer))++;
}

void HSML_PSH::interpret(HSML_LabelInfo* info) {
	if (this->pushWithLiteral == true) {
		info->globalStack->push(this->value);
	}
	else {
		if (info->localMap->find(this->address) != info->localMap->end()) {
			info->globalStack->push(info->localMap->at(this->address));
		}
		else {
			std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << L": Cannot Push Value Of Given Address";
		}
	}
	(*(info->localIndexPointer))++;
}

void HSML_SET::interpret(HSML_LabelInfo* info) {
	if (this->setWithLiteral) {
		(*info->localMap)[this->targetAddress] = this->value;
	}
	else {
		(*info->localMap)[this->targetAddress] = (*info->localMap)[this->withAddress];
	}
	(*(info->localIndexPointer))++;
}

void HSML_INC::interpret(HSML_LabelInfo* info) {
	if (this->incWithLiteral) {
		if (isInt(this->incValue)) {
			if (isInt((*info->localMap)[this->targetAddress])) {
				(*info->localMap)[this->targetAddress] = std::any(toInt((*info->localMap)[this->targetAddress]) + toInt(this->incValue));
			}
			else if (isFloat((*info->localMap)[this->targetAddress])) {
				(*info->localMap)[this->targetAddress] = std::any(toFloat((*info->localMap)[this->targetAddress]) + toInt(this->incValue));
			}
			else {
				std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << L": Cannot Increase Pointer With Given Value";
				exit(1);
			}
		}
		else if (isFloat(this->incValue)) {
			if (isInt((*info->localMap)[this->targetAddress])) {
				(*info->localMap)[this->targetAddress] = std::any(toInt((*info->localMap)[this->targetAddress]) + toFloat(this->incValue));
			}
			else if (isFloat((*info->localMap)[this->targetAddress])) {
				(*info->localMap)[this->targetAddress] = std::any(toFloat((*info->localMap)[this->targetAddress]) + toFloat(this->incValue));
			}
			else {
				std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << L": Cannot Increase Pointer With Given Value";
				exit(1);
			}
		}
		else if (isStr(this->incValue)) {
			if (isStr((*info->localMap)[this->targetAddress])) {
				(*info->localMap)[this->targetAddress] = std::any(toStr((*info->localMap)[this->targetAddress]) + toStr(this->incValue));
			}
			else {
				std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << L": Cannot Increase Pointer With Given Value";
				exit(1);
			}
		}
		else {
			std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << L": Cannot Increase Pointer With Given Value";
			exit(1);
		}
	}
	else {
		if (isInt((*info->localMap)[this->incAddress])) {
			if (isInt((*info->localMap)[this->targetAddress])) {
				(*info->localMap)[this->targetAddress] = std::any(toInt((*info->localMap)[this->targetAddress]) + toInt((*info->localMap)[this->incAddress]));
			}
			else if (isFloat((*info->localMap)[this->targetAddress])) {
				(*info->localMap)[this->targetAddress] = std::any(toFloat((*info->localMap)[this->targetAddress]) + toInt((*info->localMap)[this->incAddress]));
			}
			else {
				std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << L": Cannot Increase Pointer With Given Value";
				exit(1);
			}
		}
		else if (isFloat((*info->localMap)[this->incAddress])) {
			if (isInt((*info->localMap)[this->targetAddress])) {
				(*info->localMap)[this->targetAddress] = std::any(toInt((*info->localMap)[this->targetAddress]) + toFloat((*info->localMap)[this->incAddress]));
			}
			else if (isFloat((*info->localMap)[this->targetAddress])) {
				(*info->localMap)[this->targetAddress] = std::any(toFloat((*info->localMap)[this->targetAddress]) + toFloat((*info->localMap)[this->incAddress]));
			}
			else {
				std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << L": Cannot Increase Pointer With Given Value";
				exit(1);
			}
		}
		else if (isStr((*info->localMap)[this->incAddress])) {
			if (isStr((*info->localMap)[this->targetAddress])) {
				(*info->localMap)[this->targetAddress] = std::any(toStr((*info->localMap)[this->targetAddress]) + toStr((*info->localMap)[this->incAddress]));
			}
			else {
				std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << L": Cannot Increase Pointer With Given Value";
				exit(1);
			}
		}
		else {
			std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << L": Cannot Increase Pointer With Given Value";
			exit(1);
		}
	}
	(*(info->localIndexPointer))++;
}

void HSML_DEC::interpret(HSML_LabelInfo* info) {
	if (this->decWithLiteral) {
		if (isInt(this->decValue)) {
			if (isInt((*info->localMap)[this->targetAddress])) {
				(*info->localMap)[this->targetAddress] = std::any(toInt((*info->localMap)[this->targetAddress]) - toInt(this->decValue));
			}
			else if (isFloat((*info->localMap)[this->targetAddress])) {
				(*info->localMap)[this->targetAddress] = std::any(toFloat((*info->localMap)[this->targetAddress]) - toInt(this->decValue));
			}
			else {
				std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << L": Cannot Decrease Pointer With Given Value";
				exit(1);
			}
		}
		else if (isFloat(this->decValue)) {
			if (isInt((*info->localMap)[this->targetAddress])) {
				(*info->localMap)[this->targetAddress] = std::any(toInt((*info->localMap)[this->targetAddress]) - toFloat(this->decValue));
			}
			else if (isFloat((*info->localMap)[this->targetAddress])) {
				(*info->localMap)[this->targetAddress] = std::any(toFloat((*info->localMap)[this->targetAddress]) - toFloat(this->decValue));
			}
			else {
				std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << L": Cannot Decrease Pointer With Given Value";
				exit(1);
			}
		}
		else {
			std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << L": Cannot Decrease Pointer With Given Value";
			exit(1);
		}
	}
	else {
		if (isInt((*info->localMap)[this->decAddress])) {
			if (isInt((*info->localMap)[this->targetAddress])) {
				(*info->localMap)[this->targetAddress] = std::any(toInt((*info->localMap)[this->targetAddress]) + toInt((*info->localMap)[this->decAddress]));
			}
			else if (isFloat((*info->localMap)[this->targetAddress])) {
				(*info->localMap)[this->targetAddress] = std::any(toFloat((*info->localMap)[this->targetAddress]) + toInt((*info->localMap)[this->decAddress]));
			}
			else {
				std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << L": Cannot Increase Pointer With Given Value";
				exit(1);
			}
		}
		else if (isFloat((*info->localMap)[this->decAddress])) {
			if (isInt((*info->localMap)[this->targetAddress])) {
				(*info->localMap)[this->targetAddress] = std::any(toInt((*info->localMap)[this->targetAddress]) - toFloat((*info->localMap)[this->decAddress]));
			}
			else if (isFloat((*info->localMap)[this->targetAddress])) {
				(*info->localMap)[this->targetAddress] = std::any(toFloat((*info->localMap)[this->targetAddress]) - toFloat((*info->localMap)[this->decAddress]));
			}
			else {
				std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << L": Cannot Increase Pointer With Given Value";
				exit(1);
			}
		}
		else {
			std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << L": Cannot Increase Pointer With Given Value";
			exit(1);
		}
	}
	(*(info->localIndexPointer))++;
}

void HSML_JMP::interpret(HSML_LabelInfo* info) {
	(*info->localIndexPointer) += this->targetIndex;
}

void HSML_RET::interpret(HSML_LabelInfo* info) {
	(*info->returned) = true;
}

void HSML_PRT::interpret(HSML_LabelInfo* info) {
	if (this->prtWithLiteral == true) {
		if (isInt(this->value)) {
			std::wcout << toInt(this->value);
		}
		else if (isFloat(this->value)) {
			std::wcout << toFloat(this->value);
		}
		else if (isStr(this->value)) {
			std::wcout << toStr(this->value);
		}
		else {
			std::wcout << L"Error In Label" << info->name << L" At Line" << *(info->localIndexPointer) << L": Cannot Print Given Value";
			exit(1);
		}
	}
	else {
		if (info->localMap->find(this->valueAddress) != info->localMap->end()){
			std::any val = info->localMap->at(this->valueAddress);
			if (isInt(val)) {
				std::wcout << toInt(val);
			}
			else if (isFloat(val)) {
				std::wcout << toFloat(val);
			}
			else if (isStr(val)) {
				std::wcout << toStr(val);
			}
			else {
				std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << L": Cannot Print Given Value : Type = " << val.type().name();
				exit(1);
			}
		}
		else {
			std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << L": Cannot Print Value Of Given Address";
			exit(1);
		}
	}
	(*(info->localIndexPointer))++;
}

void HSML_PRL::interpret(HSML_LabelInfo* info) {
	if (this->prlWithLiteral == true) {
		if (isInt(this->value)) {
			std::wcout << toInt(this->value) << L"\n";
		}
		else if (isFloat(this->value)) {
			std::wcout << toFloat(this->value) << L"\n";
		}
		else if (isStr(this->value)) {
			std::wcout << toStr(this->value) << L"\n";
		}
		else {
			std::wcout << L"Error In Label" << info->name << L" At Line" << *(info->localIndexPointer) << L": Cannot Print Given Value";
			exit(1);
		}
	}
	else {
		if (info->localMap->find(this->valueAddress) != info->localMap->end()) {
			std::any val = info->localMap->at(this->valueAddress);
			if (isInt(val)) {
				std::wcout << toInt(val) << L"\n";
			}
			else if (isFloat(val)) {
				std::wcout << toFloat(val) << L"\n";
			}
			else if (isStr(val)) {
				std::wcout << toStr(val) << L"\n";
			}
			else {
				std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << L": Cannot Print Given Value : Type = " << val.type().name();
				exit(1);
			}
		}
		else {
			std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << L": Cannot Print Value Of Given Address";
			exit(1);
		}
	}
	(*(info->localIndexPointer))++;
}

void HSML_TRY::interpret(HSML_LabelInfo* info) {
	int testIndex = this->targetIndex + (*info->localIndexPointer);
	if (testIndex < info->lineCount) {
		int translateBackIndex = *info->localIndexPointer;
		(*info->commands)[testIndex]->interpret(info);
		(*info->localIndexPointer) = translateBackIndex;
		if (*info->errored == true) {
			if (m_GlobalLabels.find(this->labelName) != m_GlobalLabels.end()) {
				interpretLabel(m_GlobalLabels[this->labelName]);
				(*info->returned) = true;
			}
			else {
				std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << L": Cannot Find Label";
				exit(1);
			}
		}
		else {
			(*info->localIndexPointer)++;
		}
	}
	else {
		std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << L": Index Out Of Range";
		exit(1);
	}
}

void HSML_INT::interpret(HSML_LabelInfo* info) {
	int turnedValue;
	if ((*info->localMap).find(this->fromAddress) != (*info->localMap).end()) {
		std::any fromValue = (*info->localMap)[this->fromAddress];
		if (isInt(fromValue)) { turnedValue = toInt(fromValue); }
		else if (isFloat(fromValue)) { turnedValue = int(toFloat(fromValue)); }
		else if (isStr(fromValue)) {
			try {
				turnedValue = std::stoi(toStr(fromValue)); 
			} catch(std::invalid_argument& e) {
				(*info->errored) = true;
				return;
			}
		}
		else {
			(*info->errored) = true;
			return;
		}
	}
	else {
		std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << L": Cannot Get Address Value";
		exit(1);
	}
	if ((*info->localMap).find(this->toAddress) != (*info->localMap).end()) {
		(*info->localMap)[this->toAddress] = std::any(turnedValue);
	}
	else {
		std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << L": Cannot Get Address Value";
		exit(1);
	}
	(*(info->localIndexPointer))++;
}

void HSML_STR::interpret(HSML_LabelInfo* info) {
	std::wstring turnedValue;
	if ((*info->localMap).find(this->fromAddress) != (*info->localMap).end()) {
		std::any fromValue = (*info->localMap)[this->fromAddress];
		if (isInt(fromValue)) { turnedValue = std::to_wstring(toInt(fromValue)); }
		else if (isFloat(fromValue)) { turnedValue = std::to_wstring(toFloat(fromValue)); }
		else if (isStr(fromValue)) { turnedValue = toStr(fromValue); }
		else {
			(*info->errored) = true;
			return;
		}
	}
	else {
		std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << L": Cannot Get Address Value";
		exit(1);
	}
	if ((*info->localMap).find(this->toAddress) != (*info->localMap).end()) {
		(*info->localMap)[this->toAddress] = std::any(turnedValue);
	}
	else {
		std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << L": Cannot Get Address Value";
		exit(1);
	}
	(*(info->localIndexPointer))++;
}

void HSML_FLT::interpret(HSML_LabelInfo* info) {
	float turnedValue;
	if ((*info->localMap).find(this->fromAddress) != (*info->localMap).end()) {
		std::any fromValue = (*info->localMap)[this->fromAddress];
		if (isInt(fromValue)) { turnedValue = float(toInt(fromValue)); }
		else if (isFloat(fromValue)) { turnedValue = toFloat(fromValue); }
		else if (isStr(fromValue)) { 
			try {
				turnedValue = std::stof(toStr(fromValue)); 
			}
			catch (std::invalid_argument& e) {
				(*info->errored) = true;
				return;
			}
		}
		else {
			std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << L": Unexpected Value";
			exit(1);
		}
	}
	else {
		std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << L": Cannot Get Address Value";
		exit(1);
	}
	if ((*info->localMap).find(this->toAddress) != (*info->localMap).end()) {
		(*info->localMap)[this->toAddress] = std::any(turnedValue);
	}
	else {
		std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << L": Cannot Get Address Value";
		exit(1);
	}
	(*(info->localIndexPointer))++;
}

void HSML_INP::interpret(HSML_LabelInfo* info) {
	std::wstring nn; std::wcin >> nn;
	
	if ((*info->localMap).find(this->targetAddress) != (*info->localMap).end()) {
		(*info->localMap)[this->targetAddress] = nn;
	}
	else {
		std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address : " << targetAddress;
		exit(1);
	}
	(*(info->localIndexPointer))++;
}

void HSML_CAL::interpret(HSML_LabelInfo* info) {
	if (m_GlobalLabels.find(this->labelName) != m_GlobalLabels.end()) {
		interpretLabel(m_GlobalLabels[this->labelName]);
	}
	else {
		std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Label Name";
		exit(1);
	}
	(*(info->localIndexPointer))++;
}

void HSML_EXT::interpret(HSML_LabelInfo* info) {
	exit(this->code);
	(*(info->localIndexPointer))++;
}

void HSML_ADD::interpret(HSML_LabelInfo* info) {
	std::any leftVal, rightVal;
	switch (this->expType) {
	case (ExpType::ADR2ADR): {
		if ((*info->localMap).find(this->leftAddress) != (*info->localMap).end()) { leftVal = (*info->localMap)[this->leftAddress];}
		else { std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address";exit(1);}
		if ((*info->localMap).find(this->rightAddress) != (*info->localMap).end()) { rightVal = (*info->localMap)[this->rightAddress]; }
		else { std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address"; exit(1); }
		break;
	}
	case (ExpType::ADR2VAL): {
		if ((*info->localMap).find(this->leftAddress) != (*info->localMap).end()) { leftVal = (*info->localMap)[this->leftAddress]; }
		else { std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address"; exit(1); }
		rightVal = this->right;
		break;
	}
	case (ExpType::VAL2ADR): {
		leftVal = this->left;
		if ((*info->localMap).find(this->rightAddress) != (*info->localMap).end()) { rightVal = (*info->localMap)[this->rightAddress]; }
		else { std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address"; exit(1); }
		break;
	}
	case (ExpType::VAL2VAL): {
		leftVal = this->left; rightVal = this->right;
		break;
	}
	}
	if ((*info->localMap).find(this->targetAddress) != (*info->localMap).end()) {
		if (isInt(leftVal) && isInt(rightVal)) { (*info->localMap)[this->targetAddress] = toInt(leftVal) + toInt(rightVal); }
		else if (isInt(leftVal) && isFloat(rightVal)) { (*info->localMap)[this->targetAddress] = toInt(leftVal) + toFloat(rightVal); }
		else if (isFloat(leftVal) && isInt(rightVal)) { (*info->localMap)[this->targetAddress] = toFloat(leftVal) + toInt(rightVal); }
		else if (isFloat(leftVal) && isFloat(rightVal)) { (*info->localMap)[this->targetAddress] = toFloat(leftVal) + toFloat(rightVal); }
		else if (isStr(leftVal) && isStr(rightVal)) { (*info->localMap)[this->targetAddress] = toStr(leftVal) + toStr(rightVal); }
		else {
			std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Undefined Operation Of Given Two Values";
			exit(1);
		}
	}
	else {
		std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address";
		exit(1);
	}
	(*(info->localIndexPointer))++;
}

void HSML_SUB::interpret(HSML_LabelInfo* info) {
	std::any leftVal, rightVal;
	switch (this->expType) {
	case (ExpType::ADR2ADR): {
		if ((*info->localMap).find(this->leftAddress) != (*info->localMap).end()) { leftVal = (*info->localMap)[this->leftAddress]; }
		else { std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address"; exit(1); }
		if ((*info->localMap).find(this->rightAddress) != (*info->localMap).end()) { rightVal = (*info->localMap)[this->rightAddress]; }
		else { std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address"; exit(1); }
		break;
	}
	case (ExpType::ADR2VAL): {
		if ((*info->localMap).find(this->leftAddress) != (*info->localMap).end()) { leftVal = (*info->localMap)[this->leftAddress]; }
		else { std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address"; exit(1); }
		rightVal = this->right;
		break;
	}
	case (ExpType::VAL2ADR): {
		leftVal = this->left;
		if ((*info->localMap).find(this->rightAddress) != (*info->localMap).end()) { rightVal = (*info->localMap)[this->rightAddress]; }
		else { std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address"; exit(1); }
		break;
	}
	case (ExpType::VAL2VAL): {
		leftVal = this->left; rightVal = this->right;
		break;
	}
	}
	if ((*info->localMap).find(this->targetAddress) != (*info->localMap).end()) {
		if (isInt(leftVal) && isInt(rightVal)) { (*info->localMap)[this->targetAddress] = toInt(leftVal) - toInt(rightVal); }
		else if (isInt(leftVal) && isFloat(rightVal)) { (*info->localMap)[this->targetAddress] = toInt(leftVal) - toFloat(rightVal); }
		else if (isFloat(leftVal) && isInt(rightVal)) { (*info->localMap)[this->targetAddress] = toFloat(leftVal) - toInt(rightVal); }
		else if (isFloat(leftVal) && isFloat(rightVal)) { (*info->localMap)[this->targetAddress] = toFloat(leftVal) - toFloat(rightVal); }		
		else {
			std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Undefined Operation Of Given Two Values";
			exit(1);
		}
	}
	else {
		std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address";
		exit(1);
	}
	(*(info->localIndexPointer))++;
}

void HSML_MUL::interpret(HSML_LabelInfo* info) {
	std::any leftVal, rightVal;
	switch (this->expType) {
	case (ExpType::ADR2ADR): {
		if ((*info->localMap).find(this->leftAddress) != (*info->localMap).end()) { leftVal = (*info->localMap)[this->leftAddress]; }
		else { std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address"; exit(1); }
		if ((*info->localMap).find(this->rightAddress) != (*info->localMap).end()) { rightVal = (*info->localMap)[this->rightAddress]; }
		else { std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address"; exit(1); }
		break;
	}
	case (ExpType::ADR2VAL): {
		if ((*info->localMap).find(this->leftAddress) != (*info->localMap).end()) { leftVal = (*info->localMap)[this->leftAddress]; }
		else { std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address"; exit(1); }
		rightVal = this->right;
		break;
	}
	case (ExpType::VAL2ADR): {
		leftVal = this->left;
		if ((*info->localMap).find(this->rightAddress) != (*info->localMap).end()) { rightVal = (*info->localMap)[this->rightAddress]; }
		else { std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address"; exit(1); }
		break;
	}
	case (ExpType::VAL2VAL): {
		leftVal = this->left; rightVal = this->right;
		break;
	}
	}
	if ((*info->localMap).find(this->targetAddress) != (*info->localMap).end()) {
		if (isInt(leftVal) && isInt(rightVal)) { (*info->localMap)[this->targetAddress] = toInt(leftVal) * toInt(rightVal); }
		else if (isInt(leftVal) && isFloat(rightVal)) { (*info->localMap)[this->targetAddress] = toInt(leftVal) * toFloat(rightVal); }
		else if (isFloat(leftVal) && isInt(rightVal)) { (*info->localMap)[this->targetAddress] = toFloat(leftVal) * toInt(rightVal); }
		else if (isFloat(leftVal) && isFloat(rightVal)) { (*info->localMap)[this->targetAddress] = toFloat(leftVal) * toFloat(rightVal); }
		else {
			std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Undefined Operation Of Given Two Values";
			exit(1);
		}
	}
	else {
		std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address";
		exit(1);
	}
	(*(info->localIndexPointer))++;
}

void HSML_DIV::interpret(HSML_LabelInfo* info) {
	std::any leftVal, rightVal;
	switch (this->expType) {
	case (ExpType::ADR2ADR): {
		if ((*info->localMap).find(this->leftAddress) != (*info->localMap).end()) { leftVal = (*info->localMap)[this->leftAddress]; }
		else { std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address"; exit(1); }
		if ((*info->localMap).find(this->rightAddress) != (*info->localMap).end()) { rightVal = (*info->localMap)[this->rightAddress]; }
		else { std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address"; exit(1); }
		break;
	}
	case (ExpType::ADR2VAL): {
		if ((*info->localMap).find(this->leftAddress) != (*info->localMap).end()) { leftVal = (*info->localMap)[this->leftAddress]; }
		else { std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address"; exit(1); }
		rightVal = this->right;
		break;
	}
	case (ExpType::VAL2ADR): {
		leftVal = this->left;
		if ((*info->localMap).find(this->rightAddress) != (*info->localMap).end()) { rightVal = (*info->localMap)[this->rightAddress]; }
		else { std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address"; exit(1); }
		break;
	}
	case (ExpType::VAL2VAL): {
		leftVal = this->left; rightVal = this->right;
		break;
	}
	}
	if ((*info->localMap).find(this->targetAddress) != (*info->localMap).end()) {
		if ((isInt(rightVal) && toInt(rightVal) == 0) || (isFloat(rightVal) && toFloat(rightVal) == 0.0f)) {
			std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Divided By Zero";
			exit(1);
		}
		if (isInt(leftVal) && isInt(rightVal)) { (*info->localMap)[this->targetAddress] = toInt(leftVal) / toInt(rightVal); }
		else if (isInt(leftVal) && isFloat(rightVal)) { (*info->localMap)[this->targetAddress] = toInt(leftVal) / toFloat(rightVal); }
		else if (isFloat(leftVal) && isInt(rightVal)) { (*info->localMap)[this->targetAddress] = toFloat(leftVal) / toInt(rightVal); }
		else if (isFloat(leftVal) && isFloat(rightVal)) { (*info->localMap)[this->targetAddress] = toFloat(leftVal) / toFloat(rightVal); }
		else {
			std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Undefined Operation Of Given Two Values";
			exit(1);
		}
	}
	else {
		std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address";
		exit(1);
	}
	(*(info->localIndexPointer))++;
}

void HSML_MOD::interpret(HSML_LabelInfo* info) {
	std::any leftVal, rightVal;
	switch (this->expType) {
	case (ExpType::ADR2ADR): {
		if ((*info->localMap).find(this->leftAddress) != (*info->localMap).end()) { leftVal = (*info->localMap)[this->leftAddress]; }
		else { std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address"; exit(1); }
		if ((*info->localMap).find(this->rightAddress) != (*info->localMap).end()) { rightVal = (*info->localMap)[this->rightAddress]; }
		else { std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address"; exit(1); }
		break;
	}
	case (ExpType::ADR2VAL): {
		if ((*info->localMap).find(this->leftAddress) != (*info->localMap).end()) { leftVal = (*info->localMap)[this->leftAddress]; }
		else { std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address"; exit(1); }
		rightVal = this->right;
		break;
	}
	case (ExpType::VAL2ADR): {
		leftVal = this->left;
		if ((*info->localMap).find(this->rightAddress) != (*info->localMap).end()) { rightVal = (*info->localMap)[this->rightAddress]; }
		else { std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address"; exit(1); }
		break;
	}
	case (ExpType::VAL2VAL): {
		leftVal = this->left; rightVal = this->right;
		break;
	}
	}
	if ((*info->localMap).find(this->targetAddress) != (*info->localMap).end()) {
		if (isInt(leftVal) && isInt(rightVal)) { (*info->localMap)[this->targetAddress] = toInt(leftVal) % toInt(rightVal); }
		else if (isInt(leftVal) && isFloat(rightVal)) { (*info->localMap)[this->targetAddress] = toInt(leftVal) % int(toFloat(rightVal)); }
		else if (isFloat(leftVal) && isInt(rightVal)) { (*info->localMap)[this->targetAddress] = int(toFloat(leftVal)) % toInt(rightVal); }
		else if (isFloat(leftVal) && isFloat(rightVal)) { (*info->localMap)[this->targetAddress] = int(toFloat(leftVal)) % int(toFloat(rightVal)); }
		else {
			std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Undefined Operation Of Given Two Values";
			exit(1);
		}
	}
	else {
		std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address";
		exit(1);
	}
	(*(info->localIndexPointer))++;
}

void HSML_POW::interpret(HSML_LabelInfo* info) {
	std::any leftVal, rightVal;
	switch (this->expType) {
	case (ExpType::ADR2ADR): {
		if ((*info->localMap).find(this->leftAddress) != (*info->localMap).end()) { leftVal = (*info->localMap)[this->leftAddress]; }
		else { std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address"; exit(1); }
		if ((*info->localMap).find(this->rightAddress) != (*info->localMap).end()) { rightVal = (*info->localMap)[this->rightAddress]; }
		else { std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address"; exit(1); }
		break;
	}
	case (ExpType::ADR2VAL): {
		if ((*info->localMap).find(this->leftAddress) != (*info->localMap).end()) { leftVal = (*info->localMap)[this->leftAddress]; }
		else { std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address"; exit(1); }
		rightVal = this->right;
		break;
	}
	case (ExpType::VAL2ADR): {
		leftVal = this->left;
		if ((*info->localMap).find(this->rightAddress) != (*info->localMap).end()) { rightVal = (*info->localMap)[this->rightAddress]; }
		else { std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address"; exit(1); }
		break;
	}
	case (ExpType::VAL2VAL): {
		leftVal = this->left; rightVal = this->right;
		break;
	}
	}
	if ((*info->localMap).find(this->targetAddress) != (*info->localMap).end()) {
		if (isInt(leftVal) && isInt(rightVal)) { (*info->localMap)[this->targetAddress] = int(std::pow(toInt(leftVal), toInt(rightVal))); }
		else if (isInt(leftVal) && isFloat(rightVal)) { (*info->localMap)[this->targetAddress] = float(std::pow(toInt(leftVal), toFloat(rightVal))); }
		else if (isFloat(leftVal) && isInt(rightVal)) { (*info->localMap)[this->targetAddress] = float(std::pow(toFloat(leftVal), toInt(rightVal))); }
		else if (isFloat(leftVal) && isFloat(rightVal)) { (*info->localMap)[this->targetAddress] = float(std::pow(toFloat(leftVal), toFloat(rightVal))); }
		else {
			std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Undefined Operation Of Given Two Values";
			exit(1);
		}
	}
	else {
		std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address";
		exit(1);
	}
	(*(info->localIndexPointer))++;
}

void HSML_SIN::interpret(HSML_LabelInfo* info) {
	std::any funcedValue;
	if (this->sinWithLiteral){
		std::any temp = this->value;
		if (isInt(temp)) { funcedValue = std::sin(toInt(temp)); }
		if (isFloat(temp)) { funcedValue = std::sin(toFloat(temp)); }
		else {
			std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unsupported Type";
			exit(1);
		}
	}
	else {
		if ((*info->localMap).find(this->valueAddress) != (*info->localMap).end()) {
			std::any temp = (*info->localMap)[this->valueAddress];
			if (isInt(temp)) { funcedValue = std::sin(toInt(temp));}
			if (isFloat(temp)) { funcedValue = std::sin(toFloat(temp));}
			else {
				std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unsupported Type";
				exit(1);
			}
		}
		else {
			std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address";
			exit(1);
		}
	}
	if ((*info->localMap).find(this->targetAddress) != (*info->localMap).end()) {
		(*info->localMap)[this->targetAddress] = funcedValue;
	}
	else {
		std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address";
		exit(1);
	}
	(*(info->localIndexPointer))++;
}

void HSML_COS::interpret(HSML_LabelInfo* info) {
	std::any funcedValue;
	if (this->cosWithLiteral) {
		std::any temp = this->value;
		if (isInt(temp)) { funcedValue = std::sin(toInt(temp)); }
		if (isFloat(temp)) { funcedValue = std::sin(toFloat(temp)); }
		else {
			std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unsupported Type";
			exit(1);
		}
	}
	else {
		if ((*info->localMap).find(this->valueAddress) != (*info->localMap).end()) {
			std::any temp = (*info->localMap)[this->valueAddress];
			if (isInt(temp)) { funcedValue = std::cos(toInt(temp)); }
			if (isFloat(temp)) { funcedValue = std::cos(toFloat(temp)); }
			else {
				std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unsupported Type";
				exit(1);
			}
		}
		else {
			std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address";
			exit(1);
		}
	}
	if ((*info->localMap).find(this->targetAddress) != (*info->localMap).end()) {
		(*info->localMap)[this->targetAddress] = funcedValue;
	}
	else {
		std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address";
		exit(1);
	}
	(*(info->localIndexPointer))++;
}

void HSML_TAN::interpret(HSML_LabelInfo* info) {
	std::any funcedValue;
	if (this->tanWithLiteral) {
		std::any temp = this->value;
		if (isInt(temp)) { funcedValue = std::sin(toInt(temp)); }
		if (isFloat(temp)) { funcedValue = std::sin(toFloat(temp)); }
		else {
			std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unsupported Type";
			exit(1);
		}
	}
	else {
		if ((*info->localMap).find(this->valueAddress) != (*info->localMap).end()) {
			std::any temp = (*info->localMap)[this->valueAddress];
			if (isInt(temp)) { funcedValue = std::tan(toInt(temp)); }
			if (isFloat(temp)) { funcedValue = std::tan(toFloat(temp)); }
			else {
				std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unsupported Type";
				exit(1);
			}
		}
		else {
			std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address";
			exit(1);
		}
	}
	if ((*info->localMap).find(this->targetAddress) != (*info->localMap).end()) {
		(*info->localMap)[this->targetAddress] = funcedValue;
	}
	else {
		std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address";
		exit(1);
	}
	(*(info->localIndexPointer))++;
}

void HSML_GRT::interpret(HSML_LabelInfo* info) {
	float leftVal, rightVal;
	if ((*info->localMap).find(this->leftAddress) != (*info->localMap).end()) {
		std::any temp = (*info->localMap)[this->leftAddress];
		if (isInt(temp)) { leftVal = float(toInt(temp)); }
		else if (isFloat(temp)) { leftVal = toFloat(temp);}
		else {
			std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unsupported Type";
			exit(1);
		}
	} else {
		std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address";
		exit(1);
	}
	if ((*info->localMap).find(this->rightAddress) != (*info->localMap).end()) {
		std::any temp = (*info->localMap)[this->rightAddress];
		if (isInt(temp)) { rightVal = float(toInt(temp)); }
		else if (isFloat(temp)) { rightVal = toFloat(temp); }
		else {
			std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unsupported Type";
			exit(1);
		}
	}
	else {
		std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address";
		exit(1);
	}
	if (leftVal > rightVal) {
		(*info->localIndexPointer) += this->targetIndex;
	}
	else {
		(*(info->localIndexPointer))++;
	}
}

void HSML_GOE::interpret(HSML_LabelInfo* info) {
	float leftVal, rightVal;
	if ((*info->localMap).find(this->leftAddress) != (*info->localMap).end()) {
		std::any temp = (*info->localMap)[this->leftAddress];
		if (isInt(temp)) { leftVal = float(toInt(temp)); }
		else if (isFloat(temp)) { leftVal = toFloat(temp); }
		else {
			std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unsupported Type";
			exit(1);
		}
	}
	else {
		std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address";
		exit(1);
	}
	if ((*info->localMap).find(this->rightAddress) != (*info->localMap).end()) {
		std::any temp = (*info->localMap)[this->rightAddress];
		if (isInt(temp)) { rightVal = float(toInt(temp)); }
		else if (isFloat(temp)) { rightVal = toFloat(temp); }
		else {
			std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unsupported Type";
			exit(1);
		}
	}
	else {
		std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address";
		exit(1);
	}
	if (leftVal >= rightVal) {
		(*info->localIndexPointer) += this->targetIndex;
	}
	else {
		(*(info->localIndexPointer))++;
	}
}

void HSML_LES::interpret(HSML_LabelInfo* info) {
	float leftVal, rightVal;
	if ((*info->localMap).find(this->leftAddress) != (*info->localMap).end()) {
		std::any temp = (*info->localMap)[this->leftAddress];
		if (isInt(temp)) { leftVal = float(toInt(temp)); }
		else if (isFloat(temp)) { leftVal = toFloat(temp); }
		else {
			std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unsupported Type";
			exit(1);
		}
	}
	else {
		std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address";
		exit(1);
	}
	if ((*info->localMap).find(this->rightAddress) != (*info->localMap).end()) {
		std::any temp = (*info->localMap)[this->rightAddress];
		if (isInt(temp)) { rightVal = float(toInt(temp)); }
		else if (isFloat(temp)) { rightVal = toFloat(temp); }
		else {
			std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unsupported Type";
			exit(1);
		}
	}
	else {
		std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address";
		exit(1);
	}
	if (leftVal < rightVal) {
		(*info->localIndexPointer) += this->targetIndex;
	}
	else {
		(*(info->localIndexPointer))++;
	}
}

void HSML_LOE::interpret(HSML_LabelInfo* info) {
	float leftVal, rightVal;
	if ((*info->localMap).find(this->leftAddress) != (*info->localMap).end()) {
		std::any temp = (*info->localMap)[this->leftAddress];
		if (isInt(temp)) { leftVal = float(toInt(temp)); }
		else if (isFloat(temp)) { leftVal = toFloat(temp); }
		else {
			std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unsupported Type";
			exit(1);
		}
	}
	else {
		std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address";
		exit(1);
	}
	if ((*info->localMap).find(this->rightAddress) != (*info->localMap).end()) {
		std::any temp = (*info->localMap)[this->rightAddress];
		if (isInt(temp)) { rightVal = float(toInt(temp)); }
		else if (isFloat(temp)) { rightVal = toFloat(temp); }
		else {
			std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unsupported Type";
			exit(1);
		}
	}
	else {
		std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address";
		exit(1);
	}
	if (leftVal <= rightVal) {
		(*info->localIndexPointer) += this->targetIndex;
	}
	else {
		(*(info->localIndexPointer))++;
	}
}

void HSML_EQL::interpret(HSML_LabelInfo* info) {
	float leftVal, rightVal;
	if ((*info->localMap).find(this->leftAddress) != (*info->localMap).end()) {
		std::any temp = (*info->localMap)[this->leftAddress];
		if (isInt(temp)) { leftVal = float(toInt(temp)); }
		else if (isFloat(temp)) { leftVal = toFloat(temp); }
		else {
			std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unsupported Type";
			exit(1);
		}
	}
	else {
		std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address";
		exit(1);
	}
	if ((*info->localMap).find(this->rightAddress) != (*info->localMap).end()) {
		std::any temp = (*info->localMap)[this->rightAddress];
		if (isInt(temp)) { rightVal = float(toInt(temp)); }
		else if (isFloat(temp)) { rightVal = toFloat(temp); }
		else {
			std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unsupported Type";
			exit(1);
		}
	}
	else {
		std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address";
		exit(1);
	}
	if (leftVal == rightVal) {
		(*info->localIndexPointer) += this->targetIndex;
	}
	else {
		(*(info->localIndexPointer))++;
	}
}

void HSML_NEQ::interpret(HSML_LabelInfo* info) {
	float leftVal, rightVal;
	if ((*info->localMap).find(this->leftAddress) != (*info->localMap).end()) {
		std::any temp = (*info->localMap)[this->leftAddress];
		if (isInt(temp)) { leftVal = float(toInt(temp)); }
		else if (isFloat(temp)) { leftVal = toFloat(temp); }
		else {
			std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unsupported Type";
			exit(1);
		}
	}
	else {
		std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address";
		exit(1);
	}
	if ((*info->localMap).find(this->rightAddress) != (*info->localMap).end()) {
		std::any temp = (*info->localMap)[this->rightAddress];
		if (isInt(temp)) { rightVal = float(toInt(temp)); }
		else if (isFloat(temp)) { rightVal = toFloat(temp); }
		else {
			std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unsupported Type";
			exit(1);
		}
	}
	else {
		std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address";
		exit(1);
	}
	if (leftVal != rightVal) {
		(*info->localIndexPointer) += this->targetIndex;
	}
	else {
		(*(info->localIndexPointer))++;
	}
}

void HSML_LAD::interpret(HSML_LabelInfo* info) {
	int leftVal, rightVal;
	if ((*info->localMap).find(this->leftAddress) != (*info->localMap).end()) {
		std::any temp = (*info->localMap)[this->leftAddress];
		if (isInt(temp)) { leftVal = toInt(temp); }
		else if (isFloat(temp)) { leftVal = int(toFloat(temp)); }
		else {
			std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unsupported Type";
			exit(1);
		}
	}
	else {
		std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address";
		exit(1);
	}
	if ((*info->localMap).find(this->rightAddress) != (*info->localMap).end()) {
		std::any temp = (*info->localMap)[this->rightAddress];
		if (isInt(temp)) { rightVal = toInt(temp); }
		else if (isFloat(temp)) { rightVal = int(toFloat(temp)); }
		else {
			std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unsupported Type";
			exit(1);
		}
	}
	else {
		std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address";
		exit(1);
	}
	if (leftVal && rightVal) {
		(*info->localIndexPointer) += this->targetIndex;
	}
	else {
		(*(info->localIndexPointer))++;
	}
}

void HSML_LOR::interpret(HSML_LabelInfo* info) {
	int leftVal, rightVal;
	if ((*info->localMap).find(this->leftAddress) != (*info->localMap).end()) {
		std::any temp = (*info->localMap)[this->leftAddress];
		if (isInt(temp)) { leftVal = toInt(temp); }
		else if (isFloat(temp)) { leftVal = int(toFloat(temp)); }
		else {
			std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unsupported Type";
			exit(1);
		}
	}
	else {
		std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address";
		exit(1);
	}
	if ((*info->localMap).find(this->rightAddress) != (*info->localMap).end()) {
		std::any temp = (*info->localMap)[this->rightAddress];
		if (isInt(temp)) { rightVal = toInt(temp); }
		else if (isFloat(temp)) { rightVal = int(toFloat(temp)); }
		else {
			std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unsupported Type";
			exit(1);
		}
	}
	else {
		std::wcout << L"Error In Label " << info->name << L" At Line" << *(info->localIndexPointer) << " : Unregistered Address";
		exit(1);
	}
	if (leftVal || rightVal) {
		(*info->localIndexPointer) += this->targetIndex;
	}
	else {
		(*(info->localIndexPointer))++;
	}
}


void interpretLabel(HSML_Label label) {
	std::map<int, std::any> m_LocalMap{};
	int m_LocalIndexPointer = 0;
	bool m_Returned = false;
	bool m_Errored = false;
	int lineCount = label.contents.size();
	HSML_LabelInfo info = HSML_LabelInfo(&label.contents, &m_GlobalStack, &m_LocalMap, &m_LocalIndexPointer, lineCount, label.name, &m_Returned, &m_Errored);
	while (m_LocalIndexPointer < label.contents.size()) {
		label.contents[m_LocalIndexPointer]->interpret(&info);
		if (m_Returned) {
			break;
		}
		info = HSML_LabelInfo(&label.contents, &m_GlobalStack, &m_LocalMap, &m_LocalIndexPointer, lineCount, info.name, &m_Returned, &m_Errored);
	}
}


void interpret(HSML_Program program) {
	for (HSML_Label& lb : program.labels) {
		m_GlobalLabels[lb.name] = lb;
	}
	for (HSML_Label& lb : program.labels) {
		if (lb.name == L"main") {
			interpretLabel(lb);
			return;
		}
	}
	std::wcout << "Main Label Not Found. Abort.";
	exit(1);
}