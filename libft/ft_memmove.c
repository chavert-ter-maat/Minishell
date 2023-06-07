/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 10:50:18 by fhuisman      #+#    #+#                 */
/*   Updated: 2022/10/16 16:50:17 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*cdst;
	const char	*csrc;
	char		*endcdst;
	const char	*endcsrc;

	cdst = (char *) dst;
	csrc = (char *) src;
	if (!dst && !src)
		return (0);
	if (dst > src && dst - src < (int) len)
	{
		endcdst = cdst + len - 1;
		endcsrc = csrc + len - 1;
		while (len--)
			*endcdst-- = *endcsrc--;
		return (dst);
	}
	else
	{
		while (len--)
			*cdst++ = *csrc++;
		return (dst);
	}
}
/*
#include <string.h>
#include <stdio.h>
int main(void)
{
	char str1[50] = "Test this thing!";
	char str2[50] = "Test this thing!";
	int arr1[50] = {10, 20, 30, 40, 50, 60, 70};
	int arr2[50] = {10, 20, 30, 40, 50, 60, 70};
	int i;

	memmove(str1 + 6, str1, 9);
	ft_memmove(str2 + 6, str2, 9);
	printf("%s\n", str1);
	printf("%s\n", str2);
	memmove(arr1 + 2, arr1, 7*sizeof(arr1[0]));
	ft_memmove(arr2 + 2, arr2, 7*sizeof(arr2[0]));
	i = 0;
	while (i < 9)
	{
		printf("%d, %d\n", arr1[i], arr2[i]);
		i++;
	}
	return (0);
}
*/