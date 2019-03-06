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
	uint16_t		packet_size;
	struct udphdr	hdr;

	packet_size = sizeof(hdr) + DATA_SIZE;
	packet = (uint8_t*)xv(ft_memalloc(packet_size), MALLOC);
	set_udphdr(env, &hdr, packet, packet_size);
	x(sendto(env->sendsock,
			packet,
			packet_size,
			0,
			env->dst_addr,
			sizeof(struct sockaddr_in))
		, SENDTO);
	x(gettimeofday(send_time, NULL), TIMEOFDAY);
	free(packet);
}
