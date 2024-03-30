#include <stdio.h> 
#include <stdlib.h> 
#include <malloc.h>
#include <locale.h>

int* ToBinary(int decimal, int size)
{
    int* binaryArray = (int*)malloc(size * sizeof(int));
    int isNegative = 0;
    if (decimal < 0)
    {
        isNegative = 1;
        decimal = abs(decimal);
    }

    for (int i = size - 1; i >= 0; i--)
    {
        if (binaryArray)
        {
            binaryArray[i] = decimal % 2;
            decimal /= 2;
        }
    }

    if (isNegative)
    {
        int carry = 1;
        for (int i = size - 1; i >= 0; i--)
        {
            if (binaryArray)
            {
                binaryArray[i] = binaryArray[i] ^ 1; // 
                binaryArray[i] = binaryArray[i] ^ carry;//  
                carry = binaryArray[i] & carry;
            }
        }
    }

    return binaryArray;
}

int SUM(int* binaryArrayResult, int* binaryArray1, int* binaryArray2, int size, int out, int K)
{
    binaryArrayResult[K] = binaryArray1[K] + binaryArray2[K] + out;
    out = 0;
    if (binaryArrayResult[K] == 2)
    {
        binaryArrayResult[K] = 0;
        out = 1;
    }
   
    if (binaryArrayResult[K] == 3)
    {
        binaryArrayResult[K] = 1;
        out = 1;
    }
   
    K = K - 1;
    if (K == -1)
    {
        return 0;
    }
    else
    {
        return  SUM(binaryArrayResult, binaryArray1, binaryArray2, size, out, K);
    }
}

int MINUS(int* binaryArrayResult, int* binaryArray1, int* binaryArray2, int size, int out, int K)
{
    binaryArrayResult[K] = binaryArray1[K] - binaryArray2[K] + out;
    out = 0;

    if (binaryArrayResult[K] < 0)
    {
        binaryArrayResult[K] += 2;
        out = -1;
    }
    K = K - 1;

    if (K == -1)
    {
        return 0;
    }
    else
    {
        return MINUS(binaryArrayResult, binaryArray1, binaryArray2, size, out, K);
    }
}

int MULT(int* binaryArrayResult1, int* binaryArray1, int* binaryArray2, int size)
{
    int* resultArray = (int*)malloc((size * 2 + 1) * sizeof(int));
    for (int i = 0; i < size * 2 + 1; i++)
        resultArray[i] = 0;

    for (int i = 0; i < size; i++) 
    {
        for (int j = 0; j < size; j++)
        {
            if (resultArray)
                resultArray[i + j + 1] += binaryArray1[i] * binaryArray2[j];
        }
    }

    for (int i = size * 2; i > 0; i--)
    {
        resultArray[i - 1] += resultArray[i] / 2;
        resultArray[i] %= 2;
    }

    for (int i = 0; i < size * 2; i++)
    {
            printf("%d", resultArray[i]);
            if ((i + 1) % 4 == 0)
                printf(" ");
    }
    return 0;
}

int SRAWN(int* binaryArray1, int* binaryArray2, int size, int go) 
{
    if (go == size) 
        return 3;
 
    if (binaryArray1[go] == binaryArray2[go])
    {
        go = go + 1;
        return SRAWN(binaryArray1, binaryArray2, size, go);
    }
    if (binaryArray1[go] > binaryArray2[go]) 
        return 1;
   
    if (binaryArray1[go] < binaryArray2[go]) 
        return 2;
    
    return 0;
}

int DIV(int* binaryArrayResult, int* binaryArray1, int* binaryArray2, int size, int funnymonkey)
{
    MINUS(binaryArray1, binaryArray1, binaryArray2, size, 0, size - 1);
    funnymonkey = funnymonkey + 1;
    int true1 = SRAWN(binaryArray1, binaryArray2, size, 0);

    if (true1 == 2)
    {
        binaryArrayResult = ToBinary(funnymonkey, size);
        for (int g = 0; g < size; g++)
        {
            if (binaryArrayResult)
            {
                printf("%d", binaryArrayResult[g]);
                if ((g + 1) % 4 == 0)
                    printf(" ");
            }
        }
        return 0;
    }

    if (true1 == 3)
    {
        binaryArrayResult = ToBinary(funnymonkey + 1, size);
        for (int g = 0; g < size; g++) 
        {
            if (binaryArrayResult)
            {
                printf("%d", binaryArrayResult[g]);
                if ((g + 1) % 4 == 0)
                    printf(" ");
            }
        }
        return 0;
    }
    if (true1 == 1)
        return DIV(binaryArrayResult, binaryArray1, binaryArray2, size, funnymonkey);
 
    return 0;
}

int OSTAT(int* binaryArrayResult, int* binaryArray1, int* binaryArray2, int size)
{
    MINUS(binaryArray1, binaryArray1, binaryArray2, size, 0, size - 1);
    int true1 = SRAWN(binaryArray1, binaryArray2, size, 0);
    if (true1 == 2)
    {
        printf("Результат деления с остатком:\n--> ");
        for (int g = 0; g < size; g++)
        {
            if (binaryArray1)
            {
                printf("%d", binaryArray1[g]);
                if ((g + 1) % 4 == 0)
                    printf(" ");
            }
        }
        return 0;
    }

    if (true1 == 3)
    {
        MINUS(binaryArray1, binaryArray1, binaryArray2, size, 0, size - 1);
        printf("Результат деления с остатком:\n--> ");
        for (int g = 0; g < size; g++)
        {
            if (binaryArray1)
            {
                printf("%d", binaryArray1[g]);
                if ((g + 1) % 4 == 0)
                    printf(" ");
            }
        }
        return 0;
    }

    if (true1 == 1)
        return OSTAT(binaryArrayResult, binaryArray1, binaryArray2, size);

    return 0;
}

//Лог. оп.

int* NOT(int* binaryArrayResult1, int* binaryArray1, int size)
{
    for (int i = 0; i < size; i++)
    {
        binaryArrayResult1[i] = binaryArray1[i] ^ 1;
    }
    return binaryArrayResult1;
}

int* AND(int* binaryArrayResult1, int* binaryArray1, int* binaryArray2, int size)
{
    for (int i = 0; i < size; i++)
    {
        binaryArrayResult1[i] = binaryArray1[i] && binaryArray2[i];
    }
    return binaryArrayResult1;
}

int* OR(int* binaryArrayResult1, int* binaryArray1, int* binaryArray2, int size)
{
    for (int i = 0; i < size; i++)
    {
        binaryArrayResult1[i] = binaryArray1[i] || binaryArray2[i];
    }
    return binaryArrayResult1;
}

int* XOR(int* binaryArrayResult1, int* binaryArray1, int* binaryArray2, int size)
{
    binaryArrayResult1 = OR(binaryArrayResult1, (AND(binaryArrayResult1, NOT(binaryArrayResult1, binaryArray1, size), binaryArray2, size)), (AND(binaryArrayResult1, NOT(binaryArrayResult1, binaryArray2, size), binaryArray1, size)), size);
    return binaryArrayResult1;
}

int* XNOR(int* binaryArrayResult1, int* binaryArray1, int* binaryArray2, int size)
{
    binaryArrayResult1 = NOT(binaryArrayResult1, XOR(binaryArrayResult1, binaryArray1, binaryArray2, size), size);
    return binaryArrayResult1;
}

int* IMPLICATION(int* binaryArrayResult1, int* binaryArray1, int* binaryArray2, int size)
{
    binaryArrayResult1 = OR(binaryArrayResult1, binaryArray2, NOT(binaryArrayResult1, binaryArray1, size), size);
    return binaryArrayResult1;
}

int* SHEFFER(int* binaryArrayResult1, int* binaryArray1, int* binaryArray2, int size)
{
    binaryArrayResult1 = NOT(binaryArrayResult1, AND(binaryArrayResult1, binaryArray1, binaryArray2, size), size);
    return binaryArrayResult1;
}

int* PIRS(int* binaryArrayResult1, int* binaryArray1, int* binaryArray2, int size)
{
    binaryArrayResult1 = NOT(binaryArrayResult1, OR(binaryArrayResult1, binaryArray1, binaryArray2, size), size);
    return binaryArrayResult1;
}

int main()
{
    system("color 2");
    setlocale(LC_ALL, "Rus");
    int sch1 = 0, sch2 = 0;
    int consent1;
    int consent2;
    int decimal1, decimal2, size;
    long long hex1, hex2;


    while (sch1 == 0)
    {
        printf("Использовать для первого числа:\nДесятичную систему счисления(Введите 1)\nШестнадцатеричную систему счисления(Введите 2)\n--> ");
        scanf_s("%d", &consent1);
        if (consent1 == 1 || consent1 == 2)
            sch1++;
        else
            printf("\n!!! НЕКОРРЕКТНЫЙ ВВОД !!!\n>>>>Попробуйте снова>>>>>\n\n");
    }
    printf("Введите первое число:\n--> ");
    if (consent1 != 1)
        scanf_s(" %llx", &hex1);
    else
        scanf_s("%d", &decimal1);


    while (sch2 == 0)
    {
        printf("Использовать для второго числа:\nДесятичную систему счисления(Введите 1)\nШестнадцатеричную систему счисления(Введите 2)\n--> ");
        scanf_s("%d", &consent2);
        if (consent2 == 1 || consent2 == 2)
            sch2++;
        else
            printf("\n!!! НЕКОРРЕКТНЫЙ ВВОД !!!\n>>>>Попробуйте снова>>>>>\n\n");
    }
    printf("Введите первое число:\n--> ");
    if (consent2 != 1)
        scanf_s(" %llx", &hex2);
    else
        scanf_s("%d", &decimal2);


    printf("\nВведите размер двоичного массива:\n--> ");
    scanf_s("%d", &size);
    size = size * 8;

    int* binaryArray1;
    int* binaryArray2;

    if (consent1 == 1)
        binaryArray1 = ToBinary(decimal1, size);
    else
        binaryArray1 = ToBinary(hex1, size);

    if (consent2 == 1)
        binaryArray2 = ToBinary(decimal2, size);
    else
        binaryArray2 = ToBinary(hex2, size);

    if (consent1 == 1)
        printf("Двоичная запись числа %d: ", decimal1);
    if (consent1 == 2)
        printf("Двоичная запись числа %llx: ", hex1);
    for (int i = 0; i < size; i++)
    {
        printf("%d", binaryArray1[i]);
        if ((i + 1) % 4 == 0)
        {
            printf(" ");
        }
    }
    printf("\n");

    if (consent2 == 1)
        printf("Двоичная запись числа %d: ", decimal2);
    if (consent2 == 2)
        printf("Двоичная запись числа %llx: ", hex2);
    for (int i = 0; i < size; i++)
    {
        printf("%d", binaryArray2[i]);
        if ((i + 1) % 4 == 0)
        {
            printf(" ");
        }
    }
    printf("\n");

    int* binaryArrayResult = (int*)malloc(size * 4 * sizeof(int));
    int* binaryArrayResult1 = (int*)malloc(size * 4 * 2 * sizeof(int));
    printf("\nВыберите операцию:\n                                (+ -> 1),(- -> 2),(* -> 3),(/ -> 4),(%% -> 5)\n (NOT -> 6),(AND -> 7),(OR -> 8),(XOR -> 9),(XNOR -> 10),(IMPLICATION -> 11),(SHEFFER -> 12),(PIRS -> 13).\n--> ");
    int* resMULT = (int*)malloc(size * 4 * 2 * sizeof(int));
    int* resDIV = (int*)malloc(size * 4 * 2 * sizeof(int));
    int* resOstat = (int*)malloc(size * 4 * 2 * sizeof(int));
    int menu;
    scanf_s("%d", &menu);
    switch (menu)
    {
    case (1):
        SUM(binaryArrayResult, binaryArray1, binaryArray2, size, 0, size);
        printf("Результат сложения:\n--> ");
        for (int g = 0; g < size; g++)
        {
            if (binaryArrayResult)
            {
                printf("%d", binaryArrayResult[g]);
                if ((g + 1) % 4 == 0)
                    printf(" ");
            }
        }
        printf("\n");
        break;
    case (2):
        MINUS(binaryArrayResult, binaryArray1, binaryArray2, size, 0, size - 1);
        printf("Результат разности:\n--> ");
        for (int g = 0; g < size; g++)
        {
            if (binaryArrayResult)
            {
                printf("%d", binaryArrayResult[g]);
                if ((g + 1) % 4 == 0)
                    printf(" ");
            }
        }
        printf("\n");
        break;
    case (3):
        printf("Результат произведения:\n--> ");
        MULT(binaryArrayResult1, binaryArray1, binaryArray2, size);
        
        printf("\n");
        break;
    case (4):
        
        if (decimal2 == 0 || hex2 == 0)
            printf("!!! ОШИБКА: ДЕЛЕНИЕ НА НОЛЬ !!!");
        else
            printf("Результат деления:\n--> ");
            DIV(binaryArrayResult, binaryArray1, binaryArray2, size, 0);
        
        printf("\n");
        break;
    case (5):
        OSTAT(binaryArrayResult, binaryArray1, binaryArray2, size);
        
        printf("\n");
        break;
    case (6):
        printf("\nРезультат ф-ии NOT над первым числом:\n--> ");
        binaryArrayResult = NOT(binaryArrayResult, binaryArray1, size);
        for (int g = 0; g < size; g++)
        {
            if (binaryArrayResult)
            {
                printf("%d", binaryArrayResult[g]);
                if ((g + 1) % 4 == 0)
                    printf(" ");
            }
        }
        printf("\nРезультат ф-ии NOT над вторым числом:\n--> ");
        binaryArrayResult = NOT(binaryArrayResult, binaryArray2, size);
        for (int g = 0; g < size; g++)
        {
            if (binaryArrayResult)
            {
                printf("%d", binaryArrayResult[g]);
                if ((g + 1) % 4 == 0)
                    printf(" ");
            }
        }
        printf("\n");
        break;
    case (7):
        printf("\nРезультат ф-ии AND:\n--> ");
        binaryArrayResult = AND(binaryArrayResult1, binaryArray1, binaryArray2, size);
        for (int g = 0; g < size; g++)
        {
            if (binaryArrayResult)
            {
                printf("%d", binaryArrayResult[g]);
                if ((g + 1) % 4 == 0)
                    printf(" ");
            }
        }
        printf("\n");
        break;
    case (8):
        printf("\nРезультат ф-ии OR:\n--> ");
        binaryArrayResult = OR(binaryArrayResult1, binaryArray1, binaryArray2, size);
        for (int g = 0; g < size; g++)
        {
            if (binaryArrayResult)
            {
                printf("%d", binaryArrayResult[g]);
                if ((g + 1) % 4 == 0)
                    printf(" ");
            }
        }
        printf("\n");
        break;
    case (9):
        printf("\nРезультат ф-ии XOR:\n--> ");
        binaryArrayResult = XOR(binaryArrayResult1, binaryArray1, binaryArray2, size);
        for (int g = 0; g < size; g++)
        {
            if (binaryArrayResult)
            {
                printf("%d", binaryArrayResult[g]);
                if ((g + 1) % 4 == 0)
                    printf(" ");
            }
        }
        printf("\n");
        break;
    case (10):
        printf("\nРезультат ф-ии XNOR:\n--> ");
        binaryArrayResult = XNOR(binaryArrayResult1, binaryArray1, binaryArray2, size);
        for (int g = 0; g < size; g++)
        {
            if (binaryArrayResult)
            {
                printf("%d", binaryArrayResult[g]);
                if ((g + 1) % 4 == 0)
                    printf(" ");
            }
        }
        printf("\n");
        break;
    case (11):
        printf("\nРезультат ф-ии IMPLICATION:\n--> ");
        binaryArrayResult = IMPLICATION(binaryArrayResult1, binaryArray1, binaryArray2, size);
        for (int g = 0; g < size; g++)
        {
            if (binaryArrayResult)
            {
                printf("%d", binaryArrayResult[g]);
                if ((g + 1) % 4 == 0)
                    printf(" ");
            }
        }
        printf("\n");
        break;
    case (12):
        printf("\nРезультат ф-ии SHEFFER:\n--> ");
        binaryArrayResult = SHEFFER(binaryArrayResult1, binaryArray1, binaryArray2, size);
        for (int g = 0; g < size; g++)
        {
            if (binaryArrayResult)
            {
                printf("%d", binaryArrayResult[g]);
                if ((g + 1) % 4 == 0)
                    printf(" ");
            }
        }
        printf("\n");
        break;
    case (13):
        printf("\nРезультат ф-ии PIRS:\n--> ");
        binaryArrayResult = PIRS(binaryArrayResult1, binaryArray1, binaryArray2, size);
        for (int g = 0; g < size; g++)
        {
            if (binaryArrayResult)
            {
                printf("%d", binaryArrayResult[g]);
                if ((g + 1) % 4 == 0)
                    printf(" ");
            }
        }
        printf("\n");
        break;
    default:
        printf_s("\n!!! НЕКОРРЕКТНЫЙ ВВОД !!!\n");
        break;
    }
    return 0;
}