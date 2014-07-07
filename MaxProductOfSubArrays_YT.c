#include <stdio.h>
#include <stdlib.h>
long maxMultiplicationSequence(const long* numArray, const unsigned int arraySize)
{
    unsigned int firstNegNumIndex, lastNegNumIndex;
    unsigned int i, currentArrayIndex = 0;
    unsigned int totalNegNums, startArrayIndex, endArrayIndex;
    long maxResult = 0, tmp1, tmp2;
    while ( currentArrayIndex < arraySize )
    {
        /*  1. filter out leading white spaces (0)  */
        while ( (numArray[currentArrayIndex] == 0) && (currentArrayIndex < arraySize) )
        {
            ++currentArrayIndex;
            continue;
        }
        if ( currentArrayIndex >= arraySize )
            break;

        /*  2. collect a sequence of nonzero numbers    */
        startArrayIndex = currentArrayIndex;
        totalNegNums = 0;
        while ( (currentArrayIndex < arraySize) && numArray[currentArrayIndex] )
        {
            if ( numArray[currentArrayIndex] < 0 )
            {
                if ( totalNegNums++ )
                    lastNegNumIndex = currentArrayIndex;
                else
                    firstNegNumIndex = lastNegNumIndex = currentArrayIndex;
            }
            ++currentArrayIndex;
        }
        endArrayIndex = currentArrayIndex - 1;

        /*  3. get max multiplcation value by count of negative numbers */
        tmp1 = tmp2 = 1;
        if ( totalNegNums & 1 )
        {
            if ( totalNegNums == 1 )
            {
                if ( startArrayIndex == firstNegNumIndex )
                    tmp1 = numArray[firstNegNumIndex];
                if ( endArrayIndex == firstNegNumIndex )
                    tmp2 = numArray[firstNegNumIndex];
            }
            for ( i = startArrayIndex; i < lastNegNumIndex; i++ )
                tmp1 *= numArray[i];
            for ( i = firstNegNumIndex+1; i <= endArrayIndex; i++ )
                tmp2 *= numArray[i];
        } else
            for ( i = startArrayIndex; i <= endArrayIndex; i++ )
                tmp1 *= numArray[i];
            if ( tmp1 > maxResult )
                maxResult = tmp1;
            if ( tmp2 > maxResult )
                maxResult = tmp2;
    }
    return maxResult;
}

int main(int argc, char **argv)
{
    int i, n = argc-1;
    long data[100];
    if (!n) return 0;
    for (i=1;i<argc;i++) data[i-1]=atol(argv[i]);
    printf("max=%ld\n", maxMultiplicationSequence(data, n));   
    return 0;
}
