#include "libft.h"

char	*ft_strndup(const char *str, size_t n)
{
	size_t	i;
	char	*dup;

	if (!str)
		return (NULL);
	if (ft_strlen(str) + 1 < n)
		n = ft_strlen(str) + 1;
	dup = malloc (sizeof(char) * n);
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
