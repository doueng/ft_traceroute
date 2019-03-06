/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 12:00:49 by dengstra          #+#    #+#             */
/*   Updated: 2019/02/11 12:00:50 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H

# include "./libft/libft.h"
# include <sys/socket.h>
# include <arpa/inet.h>
# include <sys/types.h>
# include <netdb.h>
# include <sys/time.h>
# include <signal.h>
# include <netinet/ip.h>
# include <netinet/ip_icmp.h>
# include <stdio.h>
# include <sys/time.h>
# include <netinet/udp.h>
# include <errno.h>

# define H_OP 0b1

# define DATA_SIZE 54
# define ICMP_SIZE 8

enum
{
	READ,
	RECV,
	GETPID,
	MALLOC,
	SENDTO,
	SETSOCK,
	SOCKET,
	USAGE,
	BIND,
	TIMEOFDAY,
	ROOT,
	INVALID_OPTION
};

typedef struct		s_env
{
	struct sockaddr	*dst_addr;
	struct addrinfo	*addrinfo;
	int				sendsock;
	int				recvsock;
	int				options;
	int				maxhops;
	int				packetsize;
	uint16_t		seq;
	uint16_t		port;
}					t_env;

void				sender(t_env *env, struct timeval *send_time);
void				main_loop(t_env *env);
void				ft_freeaddr(struct addrinfo *curr);
void				create_env(t_env *env, char *address);
char				*get_ipstr(char *ipstr, void *addr);
int					x(int res, int error);
void				*xv(void *res, int error);
uint16_t			checksum(void *b, int len);
void				receiver(t_env *env, struct ip *ip_recv,
							struct icmp *icmp_recv,
							struct timeval *recv_time);
#endif
