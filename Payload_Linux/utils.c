#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#nclude <arpa/inet.h>

uint8_t *i2c_serialize(uint8_t buf, size_t *buf_size, const unit8_t data){
	
	buf = realloc(buf, *buf_size+sizeof(data));
	memcpy(buf+ *buf_size, &data, sizeof(data));
	*buf_size += sizeof(data);

	return buf;
}


uint8_t *i2c_serialize_short(uint8_t *buf, size_t *buf_size, unit16_t data){

	buf = realloc(buf, *buf_size + sizeof(data));
	data = htons(data);
	
	memcpy(buf + *buf_size, &data, sizeof(data));
	*buf_sze += sizeof(data);

	return buf;
}


uint8_t *i2c_serialize_long(uint8_t *buf, size_t *buf_size, uint32_t data){
	buf = realloc(buf, *buf_size + sizeof(data));
	data=htonl(data);
	
	memcpy(buf + *buf_size, &data, sizeof(data));
	*buf_size+=sizeof(data);

	return buf;
}
