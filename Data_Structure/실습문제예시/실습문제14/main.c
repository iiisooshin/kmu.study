#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "LinearList.h"

// ���ڿ��� �Ľ��Ͽ� ���׽� ����Ʈ ����
listType* parsePolynomial(const char* input) {
	listType* poly = createList(100);  // ����� ū ����Ʈ

	int i = 0, coef = 0, expo = 0, sign = 1;
	while (input[i] != '\0') {
		if (isspace(input[i])) { i++; continue; }

		// ��ȣ ó��
		sign = 1;
		if (input[i] == '+') { sign = 1; i++; }
		else if (input[i] == '-') { sign = -1; i++; }

		// ��� �б�
		coef = 0;
		int coef_set = 0;
		while (isdigit(input[i])) {
			coef = coef * 10 + (input[i] - '0');
			i++;
			coef_set = 1;
		}
		if (!coef_set) coef = 1;

		// x �� ���� ó��
		if (input[i] == 'x' || input[i] == 'X') {
			i++;
			if (input[i] == '^') {
				i++;
				expo = 0;
				while (isdigit(input[i])) {
					expo = expo * 10 + (input[i] - '0');
					i++;
				}
			}
			else {
				expo = 1;
			}
		}
		else {
			expo = 0;
		}

		ordered_insertItem(poly, (elementType) { coef* sign, expo });
	}

	return poly;
}

// ���׽� ����
listType* addPoly(listType* f_poly, listType* s_poly) {
	listType* result = createList(f_poly->last + s_poly->last + 1);
	int i = 0, j = 0;
	elementType f_item, s_item;

	while (i <= f_poly->last && j <= s_poly->last) {
		f_item = readItem(f_poly, i);
		s_item = readItem(s_poly, j);
		if (f_item.expo < s_item.expo) {
			ordered_insertItem(result, f_item);
			i++;
		}
		else if (f_item.expo == s_item.expo) {
			int sum = f_item.coef + s_item.coef;
			if (sum != 0)
				ordered_insertItem(result, (elementType) { sum, f_item.expo });
			i++; j++;
		}
		else {
			ordered_insertItem(result, s_item);
			j++;
		}
	}
	while (i <= f_poly->last) ordered_insertItem(result, readItem(f_poly, i++));
	while (j <= s_poly->last) ordered_insertItem(result, readItem(s_poly, j++));

	return result;
}

// ���׽� ����
listType* mulPoly(listType* f_poly, listType* s_poly) {
	listType* result = createList((f_poly->last + 1) * (s_poly->last + 1));
	elementType f_item, s_item;

	for (int i = 0; i <= f_poly->last; i++) {
		f_item = readItem(f_poly, i);
		for (int j = 0; j <= s_poly->last; j++) {
			s_item = readItem(s_poly, j);
			elementType temp = { f_item.coef * s_item.coef, f_item.expo + s_item.expo };

			// ����
			int found = 0;
			for (int k = 0; k <= result->last; k++) {
				if (result->array[k].expo == temp.expo) {
					result->array[k].coef += temp.coef;
					found = 1;
					break;
				}
			}
			if (!found && temp.coef != 0) {
				ordered_insertItem(result, temp);
			}
		}
	}
	return result;
}

int main() {
	char buffer[256];

	printf("ù ��° ���׽��� �Է��ϼ��� (��: 3x^2+4x+1):\n");
	fgets(buffer, sizeof(buffer), stdin);
	buffer[strcspn(buffer, "\n")] = '\0';  // ���� ����
	listType* poly1 = parsePolynomial(buffer);

	printf("�� ��° ���׽��� �Է��ϼ��� (��: 2x^2+5x+3):\n");
	fgets(buffer, sizeof(buffer), stdin);
	buffer[strcspn(buffer, "\n")] = '\0';  // ���� ����
	listType* poly2 = parsePolynomial(buffer);

	printf("\n[ù ��° ���׽�]\n");
	printList(poly1);

	printf("\n[�� ��° ���׽�]\n");
	printList(poly2);

	listType* sum = addPoly(poly1, poly2);
	printf("\n[���� ���]\n");
	printList(sum);

	listType* product = mulPoly(poly1, poly2);
	printf("\n[���� ���]\n");
	printList(product);

	return 0;
}
