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



int main(int argc, char const *argv[]) {
  int number = 0;
  bool ok = false;
  char bits[32] = { '0','0','0','0','0','0','0','0',
                    '0','0','0','0','0','0','0','0',
                    '0','0','0','0','0','0','0','0',
                    '0','0','0','0','0','0','0','0',
  };

  while(!ok)
  {
    printf("\nDisplay a number between 0 and 1000: ");
    scanf("%d",&number);
    if(number < 0 || number > 1000)
    {
      printf("This number needs to be between 0 and 1000\n");
    }
    else
    {
      ok = true;
    }
  }

  printf("The number in binary is : ");
  convertPrintBinary(number,&bits[0]);

  printf("The number in hexidecimal is : 0x%08X\n",number);
  int result = ((number << 10) & 0xFFFFFC00) | 0x03FF;

  printf("The result in decimal is: %d\n",result);
  printf("The Result in hexidecimal is: 0x%08X\n",result);
  printf("The result in binary is: " );
  convertPrintBinary(result,&bits[0]);
  return 0;
}
