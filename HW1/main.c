#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "SPBufferset.h"

#define INPUT_SIZE 1024

int error() {
	printf("An error occurred!\n");
	return 0;
}

int checkBase() {
	char c;
	char input[INPUT_SIZE] = { 0 };
	int i;
	int numOfDigits = 0;
	int flag = 0;
	int num;
	for (i = 0; (c = getchar()) != '\n'; i++) {
		if ((c != (' ')) && (c != EOF)) {
			if (!isdigit(c)) {
				return -1;
			}
			if (flag) {
				input[numOfDigits] = c;
				numOfDigits++;
			} else {
				if (c != '0') {
					flag = 1;
					input[numOfDigits] = c;
					numOfDigits++;
				}
			}
		} else
			break;
	}
	if ((numOfDigits > 2) || (numOfDigits == 0))
		return -2;

	if (numOfDigits == 1) {
		num = (int) input[0] - '0';
		if (num < 2)
			return -2;
	} else {
		num = ((int) input[0] - '0') * 10 + ((int) input[1] - '0');
		if (num > 16)
			return -2;
	}
	return num;
}

long checkNumber(int base) {
	long num = 0;
	char c;
	char input[INPUT_SIZE] = { 0 };
	int i;
	int numOfDigits = 0;
	int flag = 0;
	int multiplier = 1;

	for (i = 0; (c = getchar()) != '\n'; i++) {
		if ((c != (' ')) && (c != EOF)) {
			if (!isdigit(c)) {
				if ((c >= 'a') && (c <= 'f'))
					c = c - 32;
				if ((c < 'A') || (c > 'F'))
					return -1;
				else {
					flag = 1;
					input[numOfDigits] = (int) c - 'A' + 10;
					numOfDigits++;
				}
			} else {
				if (flag) {
					input[numOfDigits] = (int) c - '0';
					numOfDigits++;
				} else {
					if (c != '0') {
						flag = 1;
						input[numOfDigits] = (int) c - '0';
						numOfDigits++;
					}
				}
			}
		} else
			break;
	}

	if (numOfDigits == 0)
		return 0;
	for (i = numOfDigits - 1; i >= 0; i--) {
		if (input[i] > base - 1)
			return -2;
		num += input[i] * multiplier;
		multiplier *= base;
	}
	if (num == -1)
		return 0;
	return num;
}

int main() {

	int base1, base2;
	long sum = 0;
	int convert;
	char output[INPUT_SIZE] = { 0 };

	int i = 0;

	SP_BUFF_SET()
	;

	printf("Please enter the number's base:\n");
	base1 = checkBase();
	if (base1 == -1)
		return error();
	if (base1 == -2) {
		printf("Invalid input base\n");
		return 0;
	}

	printf("Please enter the desired base:\n");
	base2 = checkBase();
	if (base2 == -1)
		return error();
	if (base2 == -2) {
		printf("Invalid desired base\n");
		return 0;
	}

	printf("Please enter a number in base %d:\n", base1);
	sum = checkNumber(base1);

	if (sum == -1)
		return error();
	if (sum == -2) {
		printf("Invalid number!\n");
		return 0;
	}

	i = 0;
	if (sum == 0) {
		printf("The result is: 0");
		return 0;
	}
	while (sum != 0) {
		convert = sum % base2;
		if (convert < 10)
			output[i] = convert + '0';
		else {
			output[i] = 'A' + convert - 10;
		}
		sum = sum / base2;
		i++;
	}

	printf("The result is: ");
	for (i = strlen(output); i > 0; i--) {
		printf("%c", output[i - 1]);
	}
	printf("\n");

	return 0;
}
