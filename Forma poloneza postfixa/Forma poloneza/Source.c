//Se introduce o expresie analitica (tipa a+b-c/d), se introduc valorile lui a b c d si programul calculeaza raspunsul
//E pur copiat de pe internet si e dificil (asa ceva sigur nu o sa avem, nu te speria)
//Doar pentru dezvoltare personala ;)

#include <stdio.h>

char expression[100];
int variableCount;
float variableValue[26];

struct Operator {
	char sign;
	int priority;
};
struct Operator operatorStack[100];
int operatorStackSize = 0;

float operandStack[100];
int operandStackSize = 0;

int operatorPriority(char operator) {
	if (operator == '*' || operator == '/') {
		return 1;
	}
	return 0;
}

float valueOf(char variable) {
	return variableValue[variable - 'a'];
}

int isOperator(char c) { return c == '+' || c == '-' || c == '*' || c == '/'; }
int isOperand(char c) { return c >= 'a' && c <= 'z'; }
int isOpeningBracket(char c) { return c == '('; }
int isClosingBracket(char c) { return c == ')'; }

float resultOf(char sign, float a, float b) {
	switch (sign) {
	case '+':
		return a + b;
	case '-':
		return a - b;
	case '*':
		return a * b;
	case '/':
		return a / b;
	default: // Only needed for code inspection
		return 0;
	}
}

void popStacksAndPushResult() {
	float b = operandStack[--operandStackSize];
	float a = operandStack[--operandStackSize];
	char sign = operatorStack[--operatorStackSize].sign;
	float result = resultOf(sign, a, b);
	operandStack[operandStackSize++] = result;
}

int main() {
	scanf("%d", &variableCount);
	scanf("%s", expression);
	for (int i = 0; i < variableCount; ++i) {
		scanf("%f", &variableValue[i]);
	}

	int priorityModifier = 0;
	for (int i = 0; expression[i] != '\0'; ++i) {
		char c = expression[i];
		if (isOpeningBracket(c)) {
			priorityModifier += 10;
		}
		else if (isClosingBracket(c)) {
			priorityModifier -= 10;
		}
		else if (isOperand(c)) {
			operandStack[operandStackSize++] = valueOf(c);
		}
		else if (isOperator(c)) {
			struct Operator operator;
			operator.sign = c;
			operator.priority = operatorPriority(c) + priorityModifier;
			while (operatorStackSize > 0 && operatorStack[operatorStackSize - 1].priority >= operator.priority) {
				popStacksAndPushResult();
			}
			operatorStack[operatorStackSize++] = operator;
		}
	}
	while (operatorStackSize > 0) {
		popStacksAndPushResult();
	}
	float result = operandStack[0];
	printf("Result: %f", result);
	return 0;
}