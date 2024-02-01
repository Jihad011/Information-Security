//playfair cipher
#include <stdio.h>
#include <string.h>

#define SIZE 5

void prepareKeyTable(char key[], char keyTable[][SIZE]) {
    int k, i, j;
    int keySet[26] = {0};
    j = 0;

    for (i = 0; i < strlen(key); i++) {
        if (key[i] != 'J') {
            if (keySet[key[i] - 'A'] == 0) {
                keyTable[j / SIZE][j % SIZE] = key[i];
                keySet[key[i] - 'A'] = 1;
                j++;
            }
        }
    }

    for (k = 0; k < 26; k++) {
        if (k != ('J' - 'A')) {
            if (keySet[k] == 0) {
                keyTable[j / SIZE][j % SIZE] = (char)('A' + k);
                j++;
            }
        }
    }
}

void generateDigraphs(char *input, char digraphs[][2]) {
    int i, j = 0;
    for (i = 0; i < strlen(input); i += 2) {
        digraphs[j][0] = input[i];
        digraphs[j][1] = (input[i + 1] == '\0') ? 'X' : input[i + 1];
        j++;
    }
}

void getDigraphPositions(char keyTable[][SIZE], char ch, int *row, int *col) {
    int i, j;
    if (ch == 'J')
        ch = 'I';

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (keyTable[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void encryptPlayfair(char keyTable[][SIZE], char *input, char *output) {
    char digraphs[strlen(input) / 2][2];
    generateDigraphs(input, digraphs);

    int i, r1, c1, r2, c2;

    for (i = 0; i < strlen(input) / 2; i++) {
        getDigraphPositions(keyTable, digraphs[i][0], &r1, &c1);
        getDigraphPositions(keyTable, digraphs[i][1], &r2, &c2);

        if (r1 == r2) {
            output[2 * i] = keyTable[r1][(c1 + 1) % SIZE];
            output[2 * i + 1] = keyTable[r2][(c2 + 1) % SIZE];
        } else if (c1 == c2) {
            output[2 * i] = keyTable[(r1 + 1) % SIZE][c1];
            output[2 * i + 1] = keyTable[(r2 + 1) % SIZE][c2];
        } else {
            output[2 * i] = keyTable[r1][c2];
            output[2 * i + 1] = keyTable[r2][c1];
        }
    }
    output[strlen(input)] = '\0';
}

int main() {
    char key[] = "KEYWORD";
    char input[] = "HELLO";
    char keyTable[SIZE][SIZE];
    char output[strlen(input) + 1];

    prepareKeyTable(key, keyTable);
    encryptPlayfair(keyTable, input, output);

    printf("Original Message: %s\n", input);
    printf("Encrypted Message: %s\n", output);

    return 0;
}

