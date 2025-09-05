#include "main.h"

/**
 * _atoi - convert a string to an integer
 * @s: input string
 *
 * Rules:
 * - اجمع كل إشارات '+' و '-' الموجودة قبل أول رقم (بدون إعادة ضبط).
 * - عند الوصول لأول رقم، اقرأ الأرقام المتتالية فقط.
 * - ابنِ الناتج كسالب دومًا: result = result * 10 - digit
 *   لتجنّب overflow مع -fsanitize.
 * - إن لم توجد أرقام، أعِد 0.
 * Return: converted integer
 */
int _atoi(char *s)
{
	int i = 0, sign = 1;
	int result = 0; /* نحفظه دائمًا بسالب */
	int has_digit = 0;

	if (!s)
		return (0);

	/* عدّ علامات + و - قبل أول رقم */
	while (s[i] != '\0' && (s[i] < '0' || s[i] > '9'))
	{
		if (s[i] == '-')
			sign = -sign;
		/* '+' نتجاهله */
		i++;
	}

	/* لا يوجد أرقام */
	if (s[i] == '\0')
		return (0);

	/* اقرأ الأرقام وابنِ الناتج كسالب لتفادي overflow */
	while (s[i] >= '0' && s[i] <= '9')
	{
		int d = s[i] - '0';

		result = result * 10 - d;
		i++;
		has_digit = 1;
	}

	if (!has_digit)
		return (0);

	/* إن كانت الإشارة موجبة أعِد الموجب، وإلا أعِد السالب كما هو */
	return (sign > 0) ? -result : result;
}
