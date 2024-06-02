/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msawada <msawada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:25:08 by msawada           #+#    #+#             */
/*   Updated: 2024/06/02 20:25:14 by msawada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*add_char(char *line, char c, int line_size)
{
	int		i;
	char	*new_line;

	new_line = (char *)malloc(sizeof(char) * line_size);
	if (new_line == NULL)
		return (NULL);
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

// ここの関数がTIMEOUTの原因
char	get_char(int fd)
{
	static char	buf[BUFFER_SIZE];
	static char	*bufcpy;
	static int	buf_count;
	char		c;

	c = '\0';
	if (buf_count  == 0)
	{
		buf_count = read(fd, buf, BUFFER_SIZE);
		bufcpy = buf;
	}
	buf_count -= 1;
	if(buf_count >= 0)
	{
		c = *bufcpy;
		bufcpy ++;
	}
	else if (buf_count == -1)
		c = EOF;
	return (c);
}
// この関数にすると解決する
static char	ft_getchar(int fd)
{
	static char	buf[BUFFER_SIZE];
	static char	*ptr;
	static int	read_byte;

	if (read_byte == 0)
	{
		read_byte = read(fd, buf, BUFFER_SIZE);
		if (read_byte < 0)
			return (FALSE);
		ptr = buf;
	}
	if (--read_byte >= 0)
		return ((char)*(ptr++));
	else
		return (EOF);
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
			break;
		line = add_char(line, c, ++line_size);
		if (c == '\n')
			break;
	}
	return (line);
}

// int	main(void)
// {
// 	int	fd = open("alternate_line_nl_no_nl", O_RDONLY);
// 	char	*str;

// 	str = NULL;
// 	str = get_next_line(fd);
// 	printf("\n-----------------------------------------\n(1)=%s$\n--------------------------------\n", str);
// 	str = get_next_line(fd);
// 	printf("\n-----------------------------------------\n(2)=%s$\n--------------------------------\n", str);
// 	str = get_next_line(fd);
// 	printf("\n-----------------------------------------\n(3)=%s$\n--------------------------------\n", str);
// 	str = get_next_line(fd);
// 	printf("\n-----------------------------------------\n(4)=%s$\n--------------------------------\n", str);
// 	str = get_next_line(fd);
// 	printf("\n-----------------------------------------\n(5)=%s$\n--------------------------------\n", str);
// 	free(str);
// 	// system("leaks a.out");
// 	close(fd);
// }