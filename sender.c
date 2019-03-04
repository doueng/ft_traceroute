/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sender.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 12:00:09 by dengstra          #+#    #+#             */
/*   Updated: 2019/02/11 12:00:10 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void			set_udphdr(t_env *env,
						struct udphdr *hdr,
						uint8_t *packet,
						size_t packet_size)
{
	hdr->source = htons(100);
	hdr->dest = htons(env->port++);
	hdr->len = htons(packet_size);
	hdr->check = 0;
	ft_memcpy(packet, hdr, sizeof(*hdr));
	hdr->check = checksum(packet, packet_size);
}

void			sender(t_env *env, struct timeval *send_time)
{
	uint8_t			*packet;
	struct udphdr	hdr;

	packet = (uint8_t*)xv(ft_memalloc(env->packetsize), MALLOC);
	set_udphdr(env, &hdr, packet, env->packetsize);
	x(sendto(env->sendsock,
			packet,
			env->packetsize,
			0,
			env->dst_addr,
			sizeof(struct sockaddr_in))
		, SENDTO);
	x(gettimeofday(send_time, NULL), TIMEOFDAY);
	free(packet);
}
