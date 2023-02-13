#include <stdio.h>
#include <stdbool.h>
void printBinary(char* bits)
{
  for(int x=31;x >= 0; --x)
  {
    printf("%c",bits[x]);
  }
  printf("\n");
}

void clearBinaryBits(char* bits)
{
  decimalToBinary(0,&bits[0]);
}

void convertPrintBinary(int number, char* bits)
{
  clearBinaryBits(&bits[0]);
  decimalToBinary(number,&bits[0]);
  printBinary(&bits[0]);
}

void decimalToBinary(int number,char* bits)
{
  int index = 0;
  int result = number;
  while(result != 0)
  {
    int remainder = result % 2;

    if(remainder > 0);
    bits[index] = '1';

    result = result/2;
    ++index;
  }
}

int main()
{
  int flag=0;
  char bits[32] = { '0','0','0','0','0','0','0','0',
                    '0','0','0','0','0','0','0','0',
                    '0','0','0','0','0','0','0','0',
                    '0','0','0','0','0','0','0','0',
  };
  while(flag<10)
  {
    printf("Enter the value:\n");
    int pageSize;

    while(true)
    {
      printf("Input the page size it can only be 4095 or 8191:\n ");
      scanf("%d", &pageSize);
      if(pageSize==4095 || pageSize==8191) break;
      printf("Wrong value entered, retry:\n ");
    }
    if(pageSize==4095)
    {
      printf("The number in binary is : ");
      convertPrintBinary(pageSize,&bits[0]);
      printf("The number in hexidecimal is : 0x%08X\n",pageSize);

    }
    else if(pageSize==8191)
    {
      printf("The number in binary is : ");
      convertPrintBinary(pageSize,&bits[0]);
      printf("The number in hexidecimal is : 0x%08X\n",pageSize);


    }
    long int pageTable[5];

    int cntr = 0;
    while(cntr != 5)
    {
      printf("Enter the 5 values of the hexadecimal virtual memory address (between 0x00000000 and 0x000FFFFF)\n");
      scanf("%d", &pageTable[cntr]);
      printf("The number in hexidecimal is : 0x%08X\n",&pageTable[cntr]);
      cntr++;
    }

    flag++;
  }

  return 0;
}
