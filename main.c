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

t_env g_env;

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
		*op_str == 'v' ? options |= V_OP : 0;
		if (ft_strchr("hv", *op_str) == NULL)
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
	char	c;
	char	ipstr[INET_ADDRSTRLEN];

	ft_bzero(&g_env, sizeof(g_env));
	if (argc < 2)
		x(-1, USAGE);
	if ((*++argv)[0] == '-')
		g_env.options = get_options(*argv++);
	if (g_env.options & H_OP && argc < 4)
		x(-1, USAGE);
	if (g_env.options & H_OP)
		g_env.sweepinc = ft_atoi(*argv++);
	signal(SIGALRM, sig_alarm);
	signal(SIGINT, sig_term);
	create_env(*argv);
	main_loop();
	x(read(2, &c, 1), READ);
	return (0);
}
