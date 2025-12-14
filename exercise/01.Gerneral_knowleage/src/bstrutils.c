#include <stdio.h>
#include "../inc/strutils.h"
#include <stdlib.h>
#include <string.h>

static enum Check_string str_or_int_check(char *str)
{
    int i=0; 
    while( str[i] != '\0' )
    {
        if(str[i] != ' ' )
        { 
            break;
        }    
        i++;
    }

    if(str[i] == '-' || str[i] == '+')
    {
        i++;
    }

    while( str[i] != '\0' )
    {
    
        if((str[i] < '0'  || str[i] >'9') )
        {
            return text;
        }

        i++;
    }

    return number;
}


void str_reverse(char *str)
{
    printf("-------Reverse string:--------\n");

    if(str_or_int_check(str) == number)
    {
        printf("not string\n");
        return ;
    }
    int left = 0;
    int right = strlen(str) - 1;
    char temp;
    char *string_reverse = malloc(sizeof(char)* strlen(str)) ;
    strcpy(string_reverse, str);

    while (left < right)
    {
        temp = string_reverse[left];
        string_reverse[left] = string_reverse[right];
        string_reverse[right] = temp;
        left++;
        right--;
    }

    printf("string: %s \n",str);
    printf("string reverse: %s \n",string_reverse);

    if(string_reverse != NULL)
    {
        free(string_reverse);
        printf("free successful\n");
    }
        
}

void str_trim(char *str)
{
    printf("-------Trim string:--------\n");
    
    if(str_or_int_check(str) == number)
    {
        printf("not string\n");
        return ;
    }

    char *string_trim = malloc(sizeof(char)* strlen(str)) ;
    int i = 0;
    int j = 0;

    while( str[i] != '\0' )
    {
        if(str[i] != ' ')
        {
            string_trim[j] = str[i];
            j++;
        }
        i++;
        
    } 

    printf("string: %s \n",str);
    printf("string trim: %s \n",string_trim);

     if(string_trim != NULL)
    {
        free(string_trim);
        printf("free successful\n");
    }
        
}

int str_to_int(char *str, int *integer_convert)
{
    printf("-------Covert to interger the end--------\n");

    int result = 0;
    int sign = 1;
    
    if(str_or_int_check(str) == text)
    {
        printf("not number\n");
        return -1;
    }

   while (*str == ' ' || *str == '\t' || *str == '\n')  str++;

    if (*str == '+') {
        str++;
    } else if (*str == '-') {
        sign = -1;
        str++;
    }


    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }

    *integer_convert = result * sign;
    return 0;
}

