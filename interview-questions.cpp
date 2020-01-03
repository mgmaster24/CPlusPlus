#include <stdio.h>
#include <stdlib.h>
#include <string.h>

inline void reverse(char* str, int length)
{
    int start = 0, end = length - 1;
    while(start < end)
    {
        char temp = *(str+start);
        *(str+start) = *(str+end);
        *(str+end) = temp;
        start++;
        end--;
    }
}

char* itoa(int value, int base);
void BuildStringFromMatrix(int* Matrix, int NumRows, int NumColumns, char* OutBuffer);

int main (int argc, char** argv)
{
    char* result = itoa(atoi(argv[1]), atoi(argv[2]));
    printf("%s%s\n", "Result: ", result);
    delete [] result;

    int matrix[4][4] = 
    {
        { 2, 3, 4, 8 },
        { 5, 7, 9, 12 },
        { 1, 0, 6, 10 }
    };
    char* output = new char[128];
    BuildStringFromMatrix(*matrix, 3, 4, output);
    printf("%s%s\n", "Matrix Clockwise Spiral: ", output);
    delete [] output;
}

char* itoa(int value, int base)
{
    const int BUFFSIZE = 36;
    // Caller will be in charge of freeing allocated memory.  This could also be done by  
    // statically allocating a char array or using a resource managed pointer (i.e. shared_prt)
    char* buffer = new char[BUFFSIZE];
    if (base != 8 && base != 10 && base != 16)
    {
        buffer[0] = '\0';
        return buffer;
    }
     
    if (value == 0)
    {
        buffer[0] = '0';
        buffer[1] = '\0';
        return buffer; 
    }

    int valuecopy = value, i = 0; 
    const char* availableCharacters = "0123456789abcdef";

    if (valuecopy < 0)
    {
        valuecopy = -valuecopy;
    }

    while (valuecopy != 0)
    {
        buffer[i++] = availableCharacters[valuecopy % base];
        valuecopy /= base;
    }

    if (value < 0)
    {
        buffer[i++] = '-';
    }

    reverse(buffer, i);

    buffer[i] = '\0';

    return buffer; 
}

void BuildStringFromMatrix(int* Matrix, int NumRows, int NumColumns, char* OutBuffer)
{
    enum { left, right, up, down } traverse = right;
    int upperLim = 0, lowerLim = NumRows -1, leftLim = 0, rightLim = NumColumns - 1, 
        elemsToProcess = NumRows * NumColumns, row = 0, col = 0;
    while (elemsToProcess > 0)
    {
        int element = Matrix[row * NumColumns + col];
        char cElem[32];

        if (elemsToProcess-- > 1) 
        {
            sprintf(cElem, "%d, ", element);
        }
        else
        {
            sprintf(cElem, "%d", element);
        }

        sprintf(OutBuffer + strlen(OutBuffer), "%s", cElem);

        if (right == traverse)
        {
            if (++col > rightLim)
            {
                traverse = down;
                upperLim++;
                row++;
	            col--;
            }
        }
        else if (down == traverse)
        {
            if (++row > lowerLim)
            {
                traverse = left;
                rightLim--;
	            row--;
                col--;
            }
        }
        else if (left == traverse)
        {
            if (--col < leftLim)
            {
                traverse = up;
                lowerLim--;
                row--;
	            col++;
            }
        }
        else // up
        {
            if (--row < upperLim)
            {
                traverse = right;
                leftLim++;
                row++;
                col++;
            }
        }
    }
}