/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msawada <msawada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:02:10 by msawada           #+#    #+#             */
/*   Updated: 2024/06/08 16:15:36 by msawada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (str);
}

char	*add_char(char *line, char c, int line_size)
{
	int		i;
	char	*new_line;

	new_line = (char *)malloc(sizeof(char) * line_size);
	if (new_line == NULL)
	{
		free (line);
		return (NULL);
	}
	i = 0;
	while (i < line_size - 2)
	{
		new_line[i] = line[i];
		i ++;
	}
	new_line[i] = c;
	i ++;
	new_line[i] = '\0';
	free (line);
	return (new_line);
}

char	get_char(int fd)
{
	static char	buf[BUFFER_SIZE];
	static char	*bufcpy;
	static int	buf_count;

	if (buf_count == 0)
	{
		buf_count = read(fd, buf, BUFFER_SIZE);
		bufcpy = buf;
	}
	buf_count -= 1;
	if (buf_count >= 0)
	{
		return (*(bufcpy++));
	}
	else
	{
		ft_memset(buf, 0, BUFFER_SIZE);
		bufcpy = NULL;
		buf_count = 0;
		return (EOF);
	}
}

char	*get_next_line(int fd)
{
	char	*line;
	char	c;
	int		line_size;

	line = NULL;
	line_size = 1;
	while (1)
	{
		c = get_char(fd);
		if (c == EOF)
			break ;
		line = add_char(line, c, ++line_size);
		if (line == NULL)
			return (NULL);
		if (c == '\n')
			break ;
	}
	return (line);
}

// int	main(void)
// {
// 	int	fd = open("test", O_RDONLY);
// 	char	*str;

// 	str = NULL;
// 	str = get_next_line(fd);
// 	printf("\n(1)=%s$\n", str);
// 	free(str);
// 	str = get_next_line(fd);
// 	printf("\n(2)=%s$\n", str);
// 	free(str);
// 	str = get_next_line(fd);
// 	printf("\n(3)=%s$\n", str);
// 	free(str);
// 	str = get_next_line(fd);
// 	printf("\n(4)=%s$\n", str);
// 	free(str);
// 	str = get_next_line(fd);
// 	printf("\n(5)=%s$\n", str);
// 	free(str);
// 	system("leaks a.out");
// 	close(fd);
// }