#include "../includes/shell.h"

int input_validate(char *input);
char *in_quotes(char *input);
static int check_properly_enclosed(char *input);
static int check_special_character(char *input);

int input_validate(char *input)
{
	if(check_properly_enclosed(input))
		return (syntax_error("Sysntax Error : unclosed quotes !"));
	if(check_special_character(input))
		return (syntax_error("Sysntax Error : unrecognized characters !"));
	return (0);
}

static int check_properly_enclosed(char *input)
{
	int in_single_quotes = 0, in_double_quotes = 0, i = 0;

	while(input && input[i])
	{
		if(input[i] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		if(input[i] == '"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		i++;
	}
	return (in_single_quotes || in_double_quotes);
}

static int check_special_character(char *input)
{
	int i = 0;
	char *special_chars = "\\&;,{()}", *str;

	str = in_quotes(input);
	while(special_chars[i])
	{
		if(ft_strchr(input, special_chars[i]))
		{
			if(str && ft_strchr(str, special_chars[i]))
			{
				free(str);
				return (0);
			}
			free(str);
			return (1);
		}
		i++;
	}
	free(str);
	return (0);
}

char *in_quotes(char *input)
{
	int i = 0, start = 0, end = 0, len = 0;
	char *str = NULL;

	while(input && input[i])
	{
		if(input[i] == '\'' || input[i] == '"')
			str = ft_strchr(input, input[i]);
		i++;
	}
	if(!str)
		return (NULL);
	start = str - input;
	i = ft_strlen(input) - 1;
	while(input && input[i])
	{
		if(input[i] == '\'' || input[i] == '"')
			str = ft_strrchr(input, input[i]);
		i--;
	}
	if(!str)
		return (NULL);
	end = str - input;
	len = end - start + 1;
	str = malloc(sizeof(char) * len);
	if(!str)
		return (NULL);
	ft_strlcpy(str, &input[start], (end - start + 2));
	return (str);
}
