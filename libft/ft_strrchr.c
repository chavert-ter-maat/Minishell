/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/08 15:13:59 by fhuisman      #+#    #+#                 */
/*   Updated: 2022/10/12 10:06:07 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	ch;

	ch = c;
	i = ft_strlen(s);
	while (i >= 0 && s[i] != ch)
		i--;
	if (i < 0)
		return (0);
	s += i;
	return ((char *) s);
}
/*
#include <string.h>
#include <stdio.h>
int	main(void)
{
	char str1[14] = "Hello, world!";
	char str2[14] = "Hello, world!";
	
	printf("%s\n", strrchr(str1, 'o'));
	printf("%s\n", ft_strrchr(str2, 'o'));
	return (0);
}
*/
/*
#include <stdio.h>
#include <stdio.h>
int	main(void)
{ 
	char    str3[] = "";
	
    if (!(str = ft_strrchr(str3, '\0')))
        printf("NULL");
    else
    {
        printf("%s\n", str);
        if (str != str3)
            printf("Return value is false\n");
    }
	return (0);
}
*/
