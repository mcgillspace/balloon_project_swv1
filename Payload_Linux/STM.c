#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include "utils.h"


i2c_stm_packet_t i2c_stm_packet(const i2c_stm_block_t *block){
	i2c_stm_packet_t packet;
	packet.buf=NULL;
	packet.size =0;
	packet.buf = i2c_serialize(packet.buff, &packet.size, block->tile);
	packet.buf = i2c_serialize_short(packet.buf, &packet.size, block->index);
	packet.buf = i2c__serialize_data(packet.buf, &packet.size, block->data, block->data_size);
	
	
	if (block->data_size < 155){
		packet.buf = i2c_serialize_pad(packet.buf, &packet.size, 0, 155 - block->data_size);
	}
	packet.buf = i2c_serialize(packet.buf, &packet.size, i2c_lrc(packet.buf, packet.size));

	return packet;

}
