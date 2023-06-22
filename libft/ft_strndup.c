#include "libft.h"

char	*ft_strndup(const char *str, size_t n)
{
	size_t	i;
	char	*dup;

	if (!str)
		return (NULL);
	if (ft_strlen(str) < n)
		n = ft_strlen(str);
	dup = malloc (sizeof(char) * n + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dup[i] = str[i];
		i++;
	}
		dup[n] = '\0';
	return (dup);
}
