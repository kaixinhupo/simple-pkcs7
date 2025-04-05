/*
 * pkcs.h
 *
 *  Created on: 2025年4月4日
 *      Author: kaixinhupo
 */

#ifndef INCLUDE_PKCS_H_
#define INCLUDE_PKCS_H_
#include <stdint.h>

typedef struct {
	void *data; /* padded data */
	int32_t ori_len; /* length of origin data */
	int32_t data_len; /* length of the data */
	uint8_t padding; /* used for padding byte value */
} pkcs7_t;

// create pkcs7 with data
// @data to add padding
// @data_len length of @data
// @block_size block size of data,range (0,256]
pkcs7_t* create_pkcs7(const void *data, uint32_t data_len, uint8_t block_size);

// get a copy of padded data
void* copy_pkcs_data(const pkcs7_t* pkcs);
// get a copy of original data
void* copy_pkcs_origin(const pkcs7_t* pkcs);

// deallocate pkcs7 instance
void free_pkcs(pkcs7_t* pkcs);

// print pkcs7 padded data
void print_pkcs_data(const pkcs7_t* pkcs);

// print pkcs7 original data
void print_pkcs_origin(const pkcs7_t* pkcs);

#endif /* INCLUDE_PKCS_H_ */
