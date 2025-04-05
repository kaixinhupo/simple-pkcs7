/*
 * pkcs.c
 *
 *  Created on: 2025年4月4日
 *      Author: kaixinhupo
 */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pkcs.h"

pkcs7_t* create_pkcs7(const void *data, uint32_t data_len, uint8_t block_size) {
	if (block_size == 0) {
		perror("create_pkcs7:unexpected block size,it must great than 0");
		return NULL;
	}
	if (data == NULL || data_len == 0) {
		return NULL;
	}

	pkcs7_t *result = (pkcs7_t*) malloc(sizeof(pkcs7_t));
	if (NULL == result) {
		perror("create_pkcs7:fail to allocate memory");
		return NULL;
	}
	result->ori_len = data_len;

	uint8_t padding = block_size - (data_len % block_size); /* number of bytes to be appended,as well,the byte for padding */
	result->padding = padding; /* according to the PKCS7 */
	result->data_len = data_len + padding;

	uint8_t *result_data = (uint8_t*) malloc(result->data_len);
	if (NULL == result_data) {
		perror("create_pkcs7:fail to allocate memory");
		return NULL;
	}

	memcpy(result_data, data, data_len); /* copying the original data for further adding padding */
	for (uint8_t i = 0; i < padding; i++) {
		result_data[data_len + i] = padding; /* adding padding bytes */
	}
	result->data = result_data;

	return result;
}


void* copy_pkcs_data(const pkcs7_t *pkcs) {
	if (pkcs == NULL) {
		return NULL;
	}
	if (pkcs->data ==NULL|| pkcs->data_len == 0) {
		return NULL;
	}
	void *data = malloc(pkcs->data_len);
	if (data == NULL) {
		perror("copy_pkcs_data:fail to allocate memory");
		return NULL;
	}
	memcpy(data, pkcs->data, pkcs->data_len);
	return data;
}

void* copy_pkcs_origin(const pkcs7_t *pkcs) {
	if (pkcs == NULL) {
		return NULL;
	}
	if (pkcs->data ==NULL || pkcs->ori_len == 0) {
		return NULL;
	}
	void *data = malloc(pkcs->ori_len);
	if (data == NULL) {
		perror("copy_pkcs_origin:fail to allocate memory");
		return NULL;
	}
	memcpy(data, pkcs->data, pkcs->ori_len);
	return data;
}

void free_pkcs(pkcs7_t *pkcs) {
	if (pkcs->data) {
		free(pkcs->data);
		pkcs->data = NULL;
	}
	free(pkcs);
	pkcs = NULL;
}

void print_data(const uint8_t *data, uint32_t data_len) {
	for (uint32_t i = 0; i < data_len; i++) {
		printf("%x", *data);
		((i + 1) % 4 == 0) ? printf("\n") : printf("\t");
		data++;
	}
}

void print_pkcs_data(const pkcs7_t* pkcs) {
	if(pkcs==NULL || pkcs->data==NULL){
		return;
	}
	print_data(pkcs->data,pkcs->data_len);
}

void print_pkcs_origin(const pkcs7_t* pkcs) {
	if(pkcs==NULL || pkcs->data==NULL){
		return;
	}
	print_data(pkcs->data,pkcs->ori_len);
	printf("\n");
}


