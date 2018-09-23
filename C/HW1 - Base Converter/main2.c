#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "SPBufferset.h"

int error2() {
	printf("An error occurred!\n");
	return 0;
}

int main2() {

	int base1, base2;
	char basecheck[1024];
	char input[1024];
	char output[1024];
	int convert;
	long sum = 0;

	unsigned int i = 0;
	int j;

	SP_BUFF_SET()
	;

	printf("Please enter the number's base:\n");
	if (fgets(basecheck, sizeof(basecheck), stdin)) {
		if (1 == sscanf(basecheck, "%d", &j)) {
			for (i = 0; i < strlen(basecheck); i++) {
				if (!isdigit(basecheck[i])) {/* input isn't a number */
					return error2();
				}
			}
		}
		else {
			return error2();
		}
	} else {
		return error2();
	}

	i = 0;
	while (basecheck[i] == '0') /*Cut 0's from the front */
		i++;
	if ((strlen(basecheck) - i > 2) || (strlen(basecheck) - i == 0)) {
		printf("Invalid input base\n");
		return 0;
	}

	if (strlen(basecheck) - i == 1)
		base1 = (int) (basecheck[i + 1] - '0');
	else
		base1 = (int) (basecheck[i + 1] - '0') * 10
				+ (int) (basecheck[i + 2] - '0');

	if (!((base1 >= 2) && (base1 <= 16))) {
		printf("Invalid input base\n");
		return 0;
	}

	printf("Please enter the desired base:\n");
	scanf(" %[^\n]%*c", basecheck);
	for (i = 0; i < strlen(basecheck); i++) {
		if (!isdigit(basecheck[i])) {
			printf("An error occurred!\n");
			return 0;
		}
	}
	i = 0;
	while (basecheck[i] == '0') /*Cut 0's from the front */
		i++;
	if ((strlen(basecheck) - i > 2) || (strlen(basecheck) - i == 0)) {
		printf("Invalid desired base\n");
		return 0;
	}

	if (strlen(basecheck) - i == 1)
		base2 = (int) basecheck[i + 1] - '0';
	else
		base2 = ((int) basecheck[i + 1] - '0') * 10 + (int) basecheck[i + 2]
				- '0';

	if (!((base2 >= 2) && (base2 <= 16))) {
		printf("%d", base2);
		printf("Invalid desired base\n");
		return 0;
	}

	printf("Please enter a number in base %d:\n", base1);
	scanf(" %[^\n]%*c", input);
	for (i = 0; i < strlen(input); i++) {
		if (isdigit(input[i])) /*Check if character is a digit*/
			convert = ((int) input[i]) - '0';
		else if (((int) input[i] >= 65) && ((int) input[i] <= 70))/*Check if character is a A-F*/
			convert = (int) input[i] - 'A' + 10;
		else {
			printf("Invalid number!\n");/*Character isn't compatible*/
			return 0;
		}
		if (convert > (base1 - 1)) {
			printf("Invalid number!\n");
			return 0;
		}
		sum += pow(base1, strlen(input) - i - 1) * convert;/*convert from any basis to Decimal*/
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

