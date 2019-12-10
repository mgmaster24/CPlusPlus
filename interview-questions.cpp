#include <stdio.h>
#include <stdlib.h>

inline void swap(char* x, char* y)
{
    char temp = *x;
    *x = *y;
    *y = temp;
}

char* itoa(int value, int base);

int main (int argc, char** argv)
{
    char * result = itoa(10, 10);
    delete [] result;
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
     
    if(value == 0)
    {
        buffer[0] = '0';
        buffer[1] = '\0';
        return buffer; 
    }

    int valuecopy = value, i = 0; 
    const char* available = "0123456789abcdef";
    
    while(valuecopy != 0)
    {
        buffer[i] = available[valuecopy % base];
        valuecopy /= base;
    }

    for(; valuecopy && i; --i)
    {
        buffer[i++] = available[valuecopy % base];
        valuecopy /= base;
    }

    if(value < 0)
    {
        buffer[i++] = '-';
    }

    buffer[i] = '\0';

    int start = 0, end = i - 1;
    while(start < end)
    {
        swap((buffer+start), (buffer+end));
        start++;
        end--;
    }

    return buffer; 
}