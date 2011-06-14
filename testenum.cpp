#include <stdio.h>
#include "days.h"
#include "numbers.h"
#include "fruits.h"

int main(int argc, char* argv[], char* envp[])
{
	int i;
	const char *name;

	printf("Enum Days elements:\n");
	for (i = 0; i < 7; i++)
	{
		name = ENUM_NAME_AT(Days, i);
		if (name)
			printf("\t%d) %-10s\n", i, name);
	}

	printf("\nEnum Number elements:\n");
	for (i = 0; i < 11; i++)
	{
		int pos = ENUM_POS(Numbers, Numbers(i));
		if (pos >= 0) {
			name = ENUM_NAME(Numbers, Numbers(i));
			printf("\t%-10s:\t%d\n", name, i);
		} else {
			printf("    %d is not a valid item of Enum Numbers\n", i);
		}
	}

	printf("\nEnum Fruits elements:\n");
	Fruits value;
	for (i = 0; i < NUMBER_OF(Fruits); i++)
	{
		value = ENUM_VALUE_AT(Fruits, i);
		name = ENUM_NAME_AT(Fruits, i);
//		printf("\t%d) %-10s:\t%d\n", i, name, value);

		name = ENUM_NAME(Fruits, value);
		if (name)
		{
			value = ENUM_VALUE(Fruits, name);
			if (value != INVALID_ENUM_ITEM(Fruits))
				printf("\t%-10s:\t%d\n", name, value);
		}
	}

	return 0;
}
