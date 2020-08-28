/*
 * scrambler.h
 *
 *  Created on: Aug 27, 2020
 *      Author: joebe
 */

#ifndef __CORE_SCRAMBLER_H_
#define __CORE_SCRAMBLER_H_

#include <stdlib.h>
#include "lfsr.h"

typedef struct
{
  lfsr_handle_t lfsr;
  uint8_t prev_bit;
} scrambler_handle_t;

int32_t
scrambler_init (scrambler_handle_t *h, uint32_t pol, uint32_t seed,
		uint32_t order);

int32_t
scrambler_reset (scrambler_handle_t *h);

int32_t
descrambler_init (scrambler_handle_t *h, uint32_t pol, uint32_t seed,
		uint32_t order);

int32_t
descrambler_reset (scrambler_handle_t *h);

int32_t
scramble_data (scrambler_handle_t *h, uint8_t *out, const uint8_t *in,
	       size_t len);

int32_t
scramble_data_nrzi (scrambler_handle_t *h, uint8_t *out, const uint8_t *in,
		    size_t len);

int32_t
descramble_data (scrambler_handle_t *h, uint8_t *out, const uint8_t *in,
		 size_t len);

int32_t
descramble_data_nrzi (scrambler_handle_t *h, uint8_t *out, const uint8_t *in,
		      size_t len);

int32_t
scramble_one_bit_per_byte (scrambler_handle_t *h, uint8_t *out,
			   const uint8_t *in, size_t bit_cnt);

int32_t
descramble_one_bit_per_byte (scrambler_handle_t *h, uint8_t *out,
			     const uint8_t *in, size_t bit_cnt);


#endif /* APPLICATION_USER_CORE_SCRAMBLER_H_ */
