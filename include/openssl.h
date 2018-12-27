/* ------------------- */
/* ---- openssl.h ---- */
/* ------------------- */

/* -----------------------------------------------------------------------------------------------------  */
/* Adapted from :																						  */
/* Sources : kulkarniamit https://github.com/kulkarniamit/openssl-evp-demo/blob/master/openssl_evp_demo.c */
/* -----------------------------------------------------------------------------------------------------  */

#ifndef OPENSSSL_
#define OPENSSSL_

#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <openssl/md5.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "util_file.h"

#define ERR_EVP_CIPHER_INIT -1
#define ERR_EVP_CIPHER_UPDATE -2
#define ERR_EVP_CIPHER_FINAL -3
#define ERR_EVP_CTX_NEW -4

#define AES_256_KEY_SIZE 32
#define AES_BLOCK_SIZE 16
#define BUFSIZE 1024

#define STORE_FILE      ((const char *)"doc/doc.csv")
#define ENC_FILE        ((const char *)"doc/enc.csv")

#define DECRYPT_MODE 0
#define ENCRYPT_MODE 1

#define SUCCESS 0
#define ERROR 1
#define INFO 2

typedef struct _cipher_params_t{
    unsigned char *key;
    unsigned char *iv;
    unsigned int encrypt;
    const EVP_CIPHER *cipher_type;
}cipher_params_t;

/* ---------------------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------- encryp and decrypt text with aes 256 ---------------------------------------- */
void cleanup(cipher_params_t *params, FILE *ifp, FILE *ofp);
int file_encrypt_decrypt(cipher_params_t *params, FILE *ifp, FILE *ofp);
int call_encrypt_decrypt(const char * ifname, const char * ofname, char key[AES_256_KEY_SIZE], unsigned char iv[AES_BLOCK_SIZE], int mode);
int verify_encryption(const char * file, const char * encrypted_file, char key[AES_256_KEY_SIZE], unsigned char iv[AES_BLOCK_SIZE]);
/* --------------------------------- */
/* ----------- hash algo ----------- */
char * md5_hash_from_string(char *str);
char * sha256_hash_from_string(char * str);
char * md5_hash_from_file(const char * filename);

#endif