/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 11:59:58 by dengstra          #+#    #+#             */
/*   Updated: 2019/02/11 11:59:59 by dengstra         ###   ########.fr       */
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

char		*get_ipstr(char *ipstr, void *addr)
{
	ft_bzero(ipstr, INET_ADDRSTRLEN + 1);
	inet_ntop(AF_INET,
			addr,
			ipstr,
			INET_ADDRSTRLEN);
	return (ipstr);
}

int			main(int argc, char *argv[])
{
	t_env		env;
	char		ipstr[INET_ADDRSTRLEN + 1];

	ft_bzero(&env, sizeof(env));
	if (argc < 2)
		x(-1, USAGE);
	if ((*++argv)[0] == '-')
		env.options = get_options(*argv++);
	if (env.options & H_OP && argc < 3)
		x(-1, USAGE);
	env.maxhops = 64;
	if (env.options & H_OP)
		env.maxhops = ft_atoi(*argv++);
	create_env(&env, *argv);
	printf("traceroute to %s (%s), %d hops max, 52 byte packets\n",
		*argv, get_ipstr(ipstr, env.dst_addr), env.maxhops);
	main_loop(&env);
	return (0);
}
