/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 12:46:12 by fhuisman      #+#    #+#                 */
/*   Updated: 2022/10/16 16:45:56 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*csrc;
	char	*cdst;

	csrc = (char *) src;
	cdst = dst;
	if (!dst && !src)
		return (0);
	while (n-- > 0)
		*cdst++ = *csrc++;
	return (dst);
}
/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	// const char src1[14] = "Hello world!";
	// char dst1[14];
	// const char src2[14] = "Hello world!";
	// char dst2[14];
	int arr1[7] = {10, 20, 30, 40, 50, 60, 70};
	int arr2[7];
	int arr3[7] = {10, 20, 30, 40, 50, 60, 70};
	int arr4[7];
	int i;
	int n;

	//memcpy(dst1, src1, 0);
	printf("%s\n", memcpy(((void *)0), ((void *)0), 3));
	//ft_memcpy(dst2, src2, 0);
	printf("%s\n", ft_memcpy(((void *)0), ((void *)0), 3));
	n = sizeof(arr1)/sizeof(arr1[0]);
	memcpy(arr2, arr1, sizeof(arr1));
	ft_memcpy(arr4, arr3, sizeof(arr3));
	i = 0;
	while(i < n)
	{
		printf("%d, %d\n", arr2[i], arr4[i]);
		i++;
	}
	return (0);
}
*/