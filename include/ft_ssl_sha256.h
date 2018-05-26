/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_sha256.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 09:38:20 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/03 09:38:21 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_SHA256_H
# define FT_SSL_SHA256_H
# include "ft_ssl_des.h"
# include <string.h>
# include <stdint.h>

/*
** ****************************************************************************
** ************************* MACROS for transform *****************************
** ****************************************************************************
*/

# define RL(x,n) (((x) << n) | ((x) >> (32 - n)))
# define RR(x,n) (((x) >> n) | ((x) << (32 - n)))
# define S0(x) (RR((x), 2) ^ RR((x),13) ^ RR((x),22))
# define S1(x) (RR((x), 6) ^ RR((x),11) ^ RR((x),25))
# define G0(x) (RR((x), 7) ^ RR((x),18) ^ ((x) >> 3))
# define G1(x) (RR((x),17) ^ RR((x),19) ^ ((x) >> 10))
# define BSWP(x,y) bswapw((uint32_t *)(x), (uint32_t)(y))
# define MEMCP(x,y,z) ft_memcpy((x),(y),(z))
# define B(x, y) b[(x - y) & 7]
# define P(x, y) p[(x + y) & 15]
/*
** ****************************************************************************
** **************************** struct for data *******************************
** ****************************************************************************
*/

typedef struct		s_sha256
{
	uint32_t		buf[16];
	uint32_t		hash[8];
	uint32_t		len[2];
}					t_sha256;

/*
** ****************************************************************************
** **************************** const hash table ******************************
** ****************************************************************************
*/

static const uint32_t K[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};


/*
** ****************************************************************************
** ********************************* files ************************************
** ****************************************************************************
*/


void sha256init(t_sha256 *data);
void sha256hash(t_sha256 *data, uint8_t *dat, uint32_t sz);
void sha256done(t_sha256 *data, uint8_t *buf);

#endif
