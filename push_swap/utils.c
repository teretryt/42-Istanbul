#include "push_swap.h"

int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9'))
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

int    digitc(char *str)
{
    int i;
    int dc;

    i = 0;
    dc = 0;
    while (str[i])
    {
        if (ft_isdigit(str[i]))
            dc++;
        else
        {
            if (ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != ' ')
                return (-1);
            if (str[i] == ' ')
                i++;
        }
		i++;
    }
    
    if (dc == 0)
        return (-1);
    return (1);
}

static int	word_counter(char const *s, char c)
{
	size_t	i;
	int		words;
	int		important;

	i = 0;
	words = 0;
	important = 0;
	while (s[i])
	{
		if (s[i] != c && important == 0)
		{
			important = 1;
			words++;
		}
		else if (s[i] == c)
			important = 0;
		i++;
	}
	return (words);
}

static char	*word_create(char *s, char c)
{
	char	*str;
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	str = (char *)malloc(i + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split(char const *s)
{
	char	**split;
    char    c;
	size_t	i;
	size_t	j;

    c = ' ';
	if (!s)
		return (NULL);
	i = word_counter(s, c);
	j = 0;
	split = (char **)malloc((i + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else if (s[i] != c)
		{
			split[j++] = word_create((char *)&s[i], c);
			while (s[i] != c && s[i])
				i++;
		}
	}
	split[j] = 0;
	return (split);
}