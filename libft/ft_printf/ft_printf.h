/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 07:41:28 by hbelleuv          #+#    #+#             */
/*   Updated: 2025/11/25 15:48:01 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stdarg.h>

int	ft_printf(const char *format, ...);
int	ft_print_char(char c);
int	ft_print_nbhex(unsigned int n, char format);
int	ft_print_nbr(int nb);
int	ft_print_percent(void);
int	ft_print_ptr(void *ptr);
int	ft_print_str(char *str);
int	ft_print_unsigned(unsigned int nb);
int	ft_print_type(char c, va_list args);

#endif
