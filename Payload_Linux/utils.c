#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>

uint8_t *i2c_serialize(uint8_t buf, size_t *buf_size, const uint8_t data){
	
	buf = realloc(buf, *buf_size+sizeof(data));
	memcpy(buf+ *buf_size, &data, sizeof(data));
	*buf_size += sizeof(data);

	return buf;
}


uint8_t *i2c_serialize_short(uint8_t *buf, size_t *buf_size, uint16_t data){

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


//Function that adds a padding to the memory buffer in case we need more buffer space

uint8_t *i2c_serialize_pad(uint8_t *buf, size_t buf_size, const uint8_t data, const size_t size){
	buf = realloc(buf, *buf_size+size));
	memcpy(buf+*buf_size, data,size);

	*buf_size +=size;
	
	return buf;
}


uint8_t i2c_serialize_data(uint8_t *buf, size_t *buf_size, const uint8_t data, const size_t){

	buf = realloc(buf, *buf_size + size);
	memcpy(buf+*buf_size , data, size0;

	*buf_size += size;

	return buf;

}

uint8_t i2c_lrc(const uint8_t *buf, const size_t size){
	uint8_t lrc =0;
	size_t i;

	for (i=0; i< size; i++){
		lrc ^=buf[i];
	}

	return lrc;
}
