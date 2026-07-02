#include <assert.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define JOLTAGE_DIGITS 12

typedef struct {
    char joltage;
    size_t bankIndex;
} Battery;

Battery getLargestBattery(char *batteryBank, size_t searchStartIndex, size_t searchEndIndex) {
    assert(searchStartIndex <= searchEndIndex);

    Battery largest;
    largest.joltage = batteryBank[searchStartIndex];
    largest.bankIndex = searchStartIndex;

    for (size_t bankIndex = searchStartIndex; bankIndex <= searchEndIndex; bankIndex++) {
        if (batteryBank[bankIndex] - largest.joltage > 0) {
            largest.joltage = batteryBank[bankIndex];
            largest.bankIndex = bankIndex;
        }
    }

    return largest;
}

uint64_t getLargestJoltage(char *batteryBank) {
    size_t bankLength = strlen(batteryBank);
    assert(bankLength >= JOLTAGE_DIGITS);

    char bankJoltage[JOLTAGE_DIGITS + 1] = "";
    int remainingJoltageDigits = JOLTAGE_DIGITS;
    size_t searchStartIndex = 0;
    size_t searchEndIndex;

    while (remainingJoltageDigits > 0) {
        remainingJoltageDigits -= 1;
        searchEndIndex = bankLength - 1 - (size_t)remainingJoltageDigits;

        Battery largestBattery = getLargestBattery(batteryBank, searchStartIndex, searchEndIndex);

        char largestBatteryJoltage[2] = {largestBattery.joltage, '\0'};
        strcat(bankJoltage, largestBatteryJoltage);
        searchStartIndex = largestBattery.bankIndex + 1;
    }

    return atoll(bankJoltage);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input-file>\n", argv[0]);
        return 1;
    }

    FILE *input;
    input = fopen(argv[1], "r");
    if (input == NULL) {
        fprintf(stderr, "File '%s' could not be opened\n", argv[1]);
        return 1;
    }

    char bank[102];
    uint64_t totalOutputJoltage = 0;

    while (fgets(bank, sizeof(bank), input)) {
        bank[strcspn(bank, "\n")] = 0;
        totalOutputJoltage += getLargestJoltage(bank);
    }

    fclose(input);

    printf("Total Joltage: %" PRId64 "\n", totalOutputJoltage);
}
