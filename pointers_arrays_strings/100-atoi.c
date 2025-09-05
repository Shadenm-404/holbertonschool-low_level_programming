#include "main.h"

/**
 * _atoi - convert a string to an integer
 * @s: input string
 *
 * Rules:
 * - نجمع كل علامات '+' و '-' الموجودة قبل أول رقم (في كامل المقدّمة).
 *   كل '-' يقلب الإشارة، و'+' يُتجاهل.
 * - عند الوصول لأول رقم، نقرأ الأرقام المتتالية فقط.
 * - نبني الناتج كسالب دائمًا: result = result * 10 - digit
 *   لتجنّب overflow مع -fsanitize.
 * - إن لم توجد أرقام، نُعيد 0.
 * Return: converted integer
 */
int _atoi(char *s)
{
	int i = 0, sign = 1;
	int result = 0;   /* نحافظ عليه سالب طوال البناء */
	int started = 0;

	if (!s)
		return (0);

	/* اجمع الإشارة من كل ما يسبق أول رقم */
	while (s[i] != '\0')
	{
		if (s[i] == '-')
			sign = -sign;
		else if (s[i] >= '0' && s[i] <= '9')
		{
			started = 1;
			break;
		}
		/* '+' أو أي رمز آخر نتجاهله */
		i++;
	}

	if (!started)
		return (0);

	/* اقرأ الأرقام؛ ابنِ الناتج كسالب لتفادي overflow */
	while (s[i] >= '0' && s[i] <= '9')
	{
		int d = s[i] - '0';

		result = result * 10 - d;
		i++;
	}

	/* إن كانت الإشارة موجبة، أرجِع موجب؛ وإلا أبقه سالب */
	return (sign > 0) ? -result : result;
}
