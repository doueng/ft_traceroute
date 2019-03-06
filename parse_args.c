/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 16:35:07 by dengstra          #+#    #+#             */
/*   Updated: 2019/03/06 16:35:08 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

static int	get_options(char *op_str)
{
	int options;

	options = 0;
	if (op_str[0] != '-')
		return (options);
	x(ft_strequ(op_str, "-") ? -1 : 0, USAGE);
	while (*++op_str)
	{
		*op_str == 'h' ? options |= H_OP : 0;
		if (ft_strchr("h", *op_str) == NULL)
			x(-1, USAGE);
	}
	return (options);
}

char		*parse_args(t_env *env, int argc, char *argv[])
{
	if (argc < 2)
		x(-1, USAGE);
	if ((*++argv)[0] == '-')
		env->options = get_options(*argv++);
	if (env->options & H_OP)
		x(-1, USAGE);
	return (*argv);
}
