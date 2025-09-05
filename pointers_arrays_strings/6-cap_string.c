#include "main.h"

/**
 * cap_string - capitalizes all words of a string
 * @s: pointer to the string to modify
 *
 * Separators: space, tab, newline, ',', ';', '.', '!', '?',
 * '"' , '(', ')', '{', '}'.
 * Return: pointer to the modified string
 */
char *cap_string(char *s)
{
	int i = 0;

	if (!s)
		return (s);

	while (s[i] != '\0')
	{
		if (s[i] >= 'a' && s[i] <= 'z')
		{
			if (i == 0 ||
			    s[i - 1] == ' '  || s[i - 1] == '\t' ||
			    s[i - 1] == '\n' || s[i - 1] == ','  ||
			    s[i - 1] == ';'  || s[i - 1] == '.'  ||
			    s[i - 1] == '!'  || s[i - 1] == '?'  ||
			    s[i - 1] == '"'  || s[i - 1] == '('  ||
			    s[i - 1] == ')'  || s[i - 1] == '{'  ||
			    s[i - 1] == '}')
			{
				s[i] -= ('a' - 'A');
			}
		}
		i++;
	}
	return (s);
}
