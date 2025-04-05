/*
 * test.c
 *
 *  Created on: 2025年4月4日
 *      Author: kaixinhupo
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <CUnit/Basic.h>
#include <CUnit/Console.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <CUnit/Automated.h>

#include "../pkcs.h"

void test_pkcs(void) {
	char *data = "hello";
	pkcs7_t *pkcs = create_pkcs7(data, strlen(data) + 1, 16);
	CU_ASSERT(pkcs!=NULL);

	printf("origin data ==============\n\n");
	print_pkcs_origin(pkcs);

	printf("\npadded data ============== \r\n");
	print_pkcs_data(pkcs);
	uint8_t *ori2 = (uint8_t*) copy_pkcs_data(pkcs);
	CU_ASSERT(ori2!=NULL);
	CU_ASSERT(pkcs->data_len % 16 == 0);
	free(ori2);

	printf("\norigin data ============== \r\n");
	char *ori = (char*) copy_pkcs_origin(pkcs);
	CU_ASSERT(strcmp(ori, data) == 0);
	free(ori);
	free_pkcs(pkcs);
}

static int init_suite(void){
    return 0;
}

static int clean_suite(void) {
    return 0;
}

int run_tests(void) {
    CU_ErrorCode ret;
    CU_pSuite pSuite = NULL;

    ret = CU_initialize_registry();
    if (ret != CUE_SUCCESS) {
        printf("CUnit  initialize failed\n");
        return -1;
    }

    printf("CUnit initialize success\n");

    pSuite = CU_add_suite("Suite_1", init_suite, clean_suite);
    if (pSuite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (CU_add_test(pSuite, "test of pkcs", test_pkcs) == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_automated_run_tests();

    CU_cleanup_registry();
    printf("clean up all the test case\n");
    return 0;
}

int main(int argc, char * argv[])
{
	run_tests();
    return 0;
}

