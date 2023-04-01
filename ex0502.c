#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MIN_STUDENT_ 1
#define MAX_STUDENT_ 9
#define MIN_SCORE_ -1
#define MAX_SCORE_ 100
#define PASSED_SCORE_ 60

#define FOR(i, n) for (int i = 0; i < n; i++)
/*
    Structure of a report
*/
struct scoreReportStruct
{
    int numberOfStudents;
    int numberOfPassed;
    int percentOfPassed;
    float averageScore;
    int maxScore;
    int minScore;
};

void scoreReportPrinter(struct scoreReportStruct scoreReport)
{
    printf("======= score info =======\n");
    printf(" #students = %d\n", scoreReport.numberOfStudents);
    printf(" #passed = %d (%d%)\n\n", scoreReport.numberOfPassed, scoreReport.percentOfPassed);
    printf("ave = %.1f\n", scoreReport.averageScore);
    printf("max = %d\n", scoreReport.maxScore);
    printf("min = %d\n", scoreReport.minScore);
    printf("==========================");
}

/*
    PARA:   a string
    RETURN: a boolean

    This function is used to check if a number is integer or not.
    If the number is an integer, it returns true. Otherwise, it returns false.
*/
bool isInteger(char number[])
{
    FOR(i, strlen(number))
    {
        if (number[i] == '.')
            return false;
    }
    if (number[0] == '0')
        return true;
    int nnumber = atoi(number);
    if (nnumber == 0)
        return false;
    return true;
}

/*
    PARA:   an integer
    RETURN: a boolean
    This function is used to check if a number is valid number, which is more than 0 and less than 10.
    It returns true if the number is valid or 0 if the number is not.
*/
bool isValid(int number, bool isScore)
{
    int minValue, maxValue;
    if (isScore)
    {
        maxValue = MAX_SCORE_;
        minValue = MIN_SCORE_;
    }
    else
    {
        maxValue = MAX_STUDENT_;
        minValue = MIN_STUDENT_;
    }
    if (number < minValue || number > maxValue)
    {
        return false;
    }
    return true;
}

/*

*/
int maxValue(int numberArray[], int sizeOfArray)
{
    int currentMaxValue = numberArray[0];
    FOR(i, sizeOfArray)
    {
        if ((numberArray[i] > currentMaxValue) && (numberArray[i] != -1))
            currentMaxValue = numberArray[i];
    }
    if (currentMaxValue == -1)
        currentMaxValue = 0;
    return currentMaxValue;
}

/*

*/
int minValue(int numberArray[], int sizeOfArray)
{
    int currentMinValue = numberArray[0];
    FOR(i, sizeOfArray)
    {
        if ((numberArray[i] < currentMinValue) && (numberArray[i] != -1))
            currentMinValue = numberArray[i];
    }
    if (currentMinValue == -1)
        currentMinValue = 0;
    return currentMinValue;
}

/*

*/
float averageValue(int numberArray[], int sizeOfArray, int numberOfIgnored)
{
    float averageValue = 0.0, sumValue = 0.0;
    FOR(i, sizeOfArray)
    {
        if (numberArray[i] == -1)
            continue;
        else
            sumValue += numberArray[i];
    }
    if ((sizeOfArray - numberOfIgnored) > 0)
        averageValue = sumValue / (sizeOfArray - numberOfIgnored);
    return averageValue;
}

/*

*/
int passedNumbers(int numberArray[], int sizeOfArray, int thresholdValue)
{
    int numberOfPassed = 0;
    FOR(i, sizeOfArray)
    {
        if (numberArray[i] >= thresholdValue)
            numberOfPassed++;
    }
    return numberOfPassed;
}

/*
    PARAM:  number of students
    RETURN: a boolean
    This function is used to input number of students.
    It returns true if the number inputted is valid or false if not.
*/
bool isInputtingNumberOfStudentsSuccess(int *numberOfStudents)
{
    char rawInput[10];
    int rawNumber;
    printf("n = ");
    scanf("%s", rawInput);
    if (!isInteger(rawInput))
    {
        printf("ERROR: invalid number of students (%s)\n", rawInput);
        return false;
    }
    rawNumber = atoi(rawInput);
    if (!isValid(rawNumber, false))
    {
        printf("ERROR: invalid number of students (%d)\n", rawNumber);
        return false;
    }
    *numberOfStudents = rawNumber;
    return true;
}

/*
    PARAM:
*/
bool isInputtingScoresSuccess(struct scoreReportStruct *scoreReport, int numberOfStudents)
{
    //  checking if input is valid or not
    int modifiedInput[numberOfStudents], numberOfIgnored = 0;
    printf("scores = ");
    FOR(i, numberOfStudents)
    {
        char rawInput[10];
        scanf("%s", rawInput);
        if (isInteger(rawInput) && (isValid(atoi(rawInput), true)))
        {
            modifiedInput[i] = atoi(rawInput);
            if (modifiedInput[i] == -1)
            {
                numberOfIgnored++;
            }
        }
        else
        {
            printf("ERROR: invalid score (%s)", rawInput);
            return false;
        }
    }
    scoreReport->minScore = minValue(modifiedInput, numberOfStudents);
    scoreReport->maxScore = maxValue(modifiedInput, numberOfStudents);
    scoreReport->averageScore = averageValue(modifiedInput, numberOfStudents, numberOfIgnored);
    scoreReport->numberOfPassed = passedNumbers(modifiedInput, numberOfStudents, PASSED_SCORE_);
    scoreReport->percentOfPassed = div(scoreReport->numberOfPassed * 100, numberOfStudents).quot;
    return true;
}

/*
    ===================== The main function =====================
*/
int main(void)
{
    struct scoreReportStruct scoreReport;
    if (!isInputtingNumberOfStudentsSuccess(&scoreReport.numberOfStudents))
        return 0;
    if (!isInputtingScoresSuccess(&scoreReport, scoreReport.numberOfStudents))
        return 0;
    scoreReportPrinter(scoreReport);
    return 0;
}