#include <stdlib.h>

char	*ft_strnew(size_t size);
void	ft_bzero(void *dest, size_t count);
static int	f_len(int abs);
char	*ft_strdup(const char *str);
char		*ft_itoa(int n);

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

static int	f_len(int abs)
{
	int		len;

	len = 1;
	while (abs >= 10)
	{
		abs /= 10;
		len += 1;
	}
	return (len);
}

char	*ft_strdup(const char *str)
{
	char	*nstr;
	int		len;
	int		i;

	len = 0;
	while (str[len] != '\0')
		len += 1;
	nstr = (char *)malloc(sizeof(char) * (len + 1));
	if (nstr == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		nstr[i] = str[i];
		i += 1;
	}
	nstr[i] = '\0';
	return (nstr);
}

char		*ft_itoa(int n)
{
	int		abs;
	int		sign;
	int		len;
	char	*number;
	int		i;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	sign = n < 0 ? 1 : 0;
	abs = sign == 1 ? (-1) * n : n;
	len = f_len(abs);
	number = ft_strnew(len + sign);
	if (!number)
		return (NULL);
	if (sign == 1)
		number[0] = '-';
	abs = sign == 1 ? (-1) * n : n;
	i = 0;
	while (i < len)
	{
		number[len + sign - 1 - i] = ((abs % 10) + 48);
		abs /= 10;
		i += 1;
	}
	return (number);
}