#include <stdio.h>
int main() 
{
	char name[10];
	int age;
	printf("Enter your first name and age: \n");
	scanf("%s %d", name, &age); 
	printf("You entered: %s %d",name,age);
}
