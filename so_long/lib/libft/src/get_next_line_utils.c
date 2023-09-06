/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                     :+:    :+:           */
/*                                                     +:+                    */
/*   By: ncornacc <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/01 15:46:12 by ncornacc      #+#    #+#                 */
/*   Updated: 2023/01/17 15:54:56 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char const *s2)
{
	size_t	total_len;
	char	*ptr;
	int		i;
	int		k;

	if (!s1 && !s2)
		return (NULL);
	i = -1;
	k = 0;
	total_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	ptr = malloc(sizeof(char) * (total_len));
	if (!ptr)
		return (free(s1), NULL);
	while (s1[++i])
	{
		ptr[i] = s1[i];
	}
	while (s2[k])
	{
		ptr[i++] = s2[k++];
	}
	ptr[total_len - 1] = '\0';
	free(s1);
	return (ptr);
}