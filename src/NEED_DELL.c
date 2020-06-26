#include "fractol.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len += 1;
	return (len);
}

char	*ft_strcat(char *dst, const char *src)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(dst);
	i = 0;
	while (src[i] != '\0')
	{
		dst[len + i] = src[i];
		i += 1;
	}
	dst[len + i] = '\0';
	return (dst);
}


void	ft_bzero(void *dest, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		((unsigned char *)dest)[i] = '\0';
		i += 1;
	}
}

char	*ft_strnew(size_t size)
{
	char	*memory;

	if (size > size + 1)
		return (NULL);
	if (!(memory = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	ft_bzero(memory, size + 1);
	return (memory);
}

int		ft_atoi(const char *str)
{
	unsigned long int	num;
	int					sign;

	while ((9 <= *str && *str <= 13) || *str == ' ')
		str += 1;
	sign = *str == '-' ? -1 : 1;
	if (*str == '-' || *str == '+')
		str += 1;
	num = 0;
	while (*str != '\0')
	{
		if ('0' <= *str && *str <= '9')
		{
			num = 10 * num + (*str - '0');
			if (num > 9223372036854775807UL && sign == 1)
				return (-1);
			if (num > 9223372036854775808UL)
				return (0);
			str += 1;
			continue ;
		}
		return (sign * (int)num);
	}
	return (sign * (int)num);
}