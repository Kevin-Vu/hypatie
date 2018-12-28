/* -----------------------------------------------------------------------------------------------------  */
/* Adapted from :                                                                                         */
/* Sources : kulkarniamit https://github.com/kulkarniamit/openssl-evp-demo/blob/master/openssl_evp_demo.c */
/*           Yoann Sculo http://www.yoannsculo.fr/faire-un-hash-md5-dun-string-en-c/                      */
/* ------------------------------------------------------------------------------------------------------ */
#include "openssl.h"

/* ----------------------------------------------------- */
void cleanup(cipher_params_t *params, FILE *ifp, FILE *ofp)
/* ----------------------------------------------------- */
{
    free(params);
    fclose(ifp);
    fclose(ofp);
}
/* ----------------------------------------------------------------- */
int file_encrypt_decrypt(cipher_params_t *params, FILE *ifp, FILE *ofp)
/* ----------------------------------------------------------------- */
{
    /* Allow enough space in output buffer for additional block */
    int cipher_block_size = EVP_CIPHER_block_size(params->cipher_type);
    unsigned char in_buf[BUFSIZE], out_buf[BUFSIZE + cipher_block_size];

    int num_bytes_read, out_len;
    EVP_CIPHER_CTX *ctx;

    ctx = EVP_CIPHER_CTX_new();
    if(ctx == NULL){
        fprintf(stderr, "ERROR: EVP_CIPHER_CTX_new failed. OpenSSL error: %s\n", ERR_error_string(ERR_get_error(), NULL));
        cleanup(params, ifp, ofp);
        return ERROR;
    }

    /* Don't set key or IV right away; we want to check lengths */
    if(!EVP_CipherInit_ex(ctx, params->cipher_type, NULL, NULL, NULL, params->encrypt)){
        fprintf(stderr, "ERROR: EVP_CipherInit_ex failed. OpenSSL error: %s\n", ERR_error_string(ERR_get_error(), NULL));
        cleanup(params, ifp, ofp);
        return ERROR;
    }

    OPENSSL_assert(EVP_CIPHER_CTX_key_length(ctx) == AES_256_KEY_SIZE);
    OPENSSL_assert(EVP_CIPHER_CTX_iv_length(ctx) == AES_BLOCK_SIZE);

    /* Now we can set key and IV */
    if(!EVP_CipherInit_ex(ctx, NULL, NULL, params->key, params->iv, params->encrypt)){
        fprintf(stderr, "ERROR: EVP_CipherInit_ex failed. OpenSSL error: %s\n", ERR_error_string(ERR_get_error(), NULL));
        EVP_CIPHER_CTX_free(ctx);
        cleanup(params, ifp, ofp);
        return ERROR;
    }

    while(1){
        // Read in data in blocks until EOF. Update the ciphering with each read.
        num_bytes_read = fread(in_buf, sizeof(unsigned char), BUFSIZE, ifp);
        if (ferror(ifp)){
            fprintf(stderr, "ERROR: fread error: %s\n", strerror(errno));
            EVP_CIPHER_CTX_free(ctx);
            cleanup(params, ifp, ofp);
            return ERROR;
        }
        if(!EVP_CipherUpdate(ctx, out_buf, &out_len, in_buf, num_bytes_read)){
            fprintf(stderr, "ERROR: EVP_CipherUpdate failed. OpenSSL error: %s\n", ERR_error_string(ERR_get_error(), NULL));
            EVP_CIPHER_CTX_free(ctx);
            cleanup(params, ifp, ofp);
            return ERROR;
        }
        fwrite(out_buf, sizeof(unsigned char), out_len, ofp);
        if (ferror(ofp)) {
            fprintf(stderr, "ERROR: fwrite error: %s\n", strerror(errno));
            EVP_CIPHER_CTX_free(ctx);
            cleanup(params, ifp, ofp);
            return ERROR;
        }
        if (num_bytes_read < BUFSIZE) {
            /* Reached End of file */
            break;
        }
    }

    /* Now cipher the final block and write it out to file */
    if(!EVP_CipherFinal_ex(ctx, out_buf, &out_len)){
        fprintf(stderr, "ERROR: Password might be invalid\n");
        EVP_CIPHER_CTX_free(ctx);
        cleanup(params, ifp, ofp);
        return ERROR;
    }
    fwrite(out_buf, sizeof(unsigned char), out_len, ofp);
    if (ferror(ofp)) {
        fprintf(stderr, "ERROR: fwrite error: %s\n", strerror(errno));
        EVP_CIPHER_CTX_free(ctx);
        cleanup(params, ifp, ofp);
        return ERROR;
    }
    EVP_CIPHER_CTX_free(ctx);
    return SUCCESS;
}
/* ------------------------------------------------------------------------------------------------------------------------------------ */
int call_encrypt_decrypt(const char * ifname, const char * ofname, char key[AES_256_KEY_SIZE], unsigned char iv[AES_BLOCK_SIZE], int mode)
/* ------------------------------------------------------------------------------------------------------------------------------------ */
{
    FILE *f_input, *f_out;

    cipher_params_t *params = (cipher_params_t *)malloc(sizeof(cipher_params_t));
    if (!params) {
        /* Unable to allocate memory on heap*/
        fprintf(stderr, "ERROR: malloc error: %s\n", strerror(errno));
        return ERROR;
    }

    params->key = (unsigned char *) key;
    params->iv = iv;

    /* Indicate that we want to encrypt or decrypt */
    params->encrypt = mode;

    /* Set the cipher type you want for encryption-decryption */
    params->cipher_type = EVP_aes_256_cbc();

    /* Open the input file for reading in binary ("rb" mode) */
    f_input = fopen(ifname, "rb");
    if (!f_input) {
        /* Unable to open file for reading */
        fprintf(stderr, "ERROR: fopen error: %s : %s\n", ifname, strerror(errno));
        free(params);
        return ERROR;
    }

    /* Open and truncate file to zero length or create ciphertext file for writing */
    f_out = fopen(ofname, "wb");
    if (!f_out) {
        /* Unable to open file for writing */
        fprintf(stderr, "ERROR: fopen error: %s : %s\n", ofname, strerror(errno));
        fclose(f_input);
        free(params);
        return ERROR;
    }

    /* Encrypt / Decrypt the given file */
    if(file_encrypt_decrypt(params, f_input, f_out) == ERROR)
        return ERROR;
    /* Done, close the file descriptors */
    fclose(f_input);
    fclose(f_out);

    /* Free the memory allocated to our structure */
    free(params);
    return SUCCESS;
}
/* ----------------------------------------------------------------------------------------------------------------------------- */
int verify_encryption(const char * file, const char * encrypted_file, char key[AES_256_KEY_SIZE], unsigned char iv[AES_BLOCK_SIZE])
/* ----------------------------------------------------------------------------------------------------------------------------- */
{
    /* Decrypt enc.csv to a temp file */
    if(call_encrypt_decrypt(encrypted_file,TEMP_FILE, key, iv, DECRYPT_MODE) == ERROR)
        return ERROR;

    /* Compute the md5 of the two files */
    char * md5_file = NULL;
    char * md5_decrypted_file = NULL;

    md5_file = md5_hash_from_file(file);
    md5_decrypted_file = md5_hash_from_file(TEMP_FILE);

    /* Check if the md5 are equal */
    if(strcmp(md5_file, md5_decrypted_file) != 0){
        fprintf(stderr, "ERROR: invalid: md5sum of the two files is different\n");
        free(md5_file);
        free(md5_decrypted_file);
        remove(TEMP_FILE);
        return ERROR;
    }

    /* Clean free */
    remove((const char *)TEMP_FILE);
    free(md5_file);
    free(md5_decrypted_file);
    
    return SUCCESS;
}
/* ------------------------------------------ */
char * md5_hash_from_file(const char * filename)
/* ------------------------------------------ */
{
    MD5_CTX c;
    MD5_Init(&c);

    char buf[BUFSIZE];
    ssize_t bytes;

    char * md5_hash = (char *) malloc( (2*MD5_DIGEST_LENGTH+1) * sizeof(char));
    unsigned char md5[MD5_DIGEST_LENGTH] = {0};

    FILE * fp = fopen(filename, "r");
    if(fp == NULL)
    {
        free(md5_hash);
        return NULL;
    }
    int filedes = fileno(fp);

    bytes=read(filedes, buf, BUFSIZE);
    while(bytes > 0)
    {
        MD5_Update(&c, buf, bytes);
        bytes=read(filedes, buf, BUFSIZE);
    }

    MD5_Final(md5, &c);
    int i = 0;
    for (i = 0; i < MD5_DIGEST_LENGTH; i++)
        sprintf(md5_hash + 2*i, "%02x", md5[i]);
    fclose(fp);
    return md5_hash;
}
/* -------------------------------- */
char * md5_hash_from_string(char *str)
/* -------------------------------- */
{
    int i = 0;
    char unsigned md5[MD5_DIGEST_LENGTH] = {0};
    char * md5_hash = (char *) malloc( (2*MD5_DIGEST_LENGTH+1) * sizeof(char));
    MD5((const unsigned char *)str, strlen(str), md5);
    for (i = 0; i < MD5_DIGEST_LENGTH; i++)
        sprintf(md5_hash + 2*i, "%02x", md5[i]);
    return md5_hash;
}
/* ------------------------------------ */
char * sha256_hash_from_string(char * str)
/* ------------------------------------ */
{
    int i = 0;
    unsigned char *sha = SHA256((const unsigned char *)str, strlen(str), 0);
    char * sha256_hash = (char *) malloc( (2*SHA256_DIGEST_LENGTH+1) * sizeof(char));
    for (i = 0; i < SHA256_DIGEST_LENGTH; i++)
        sprintf(sha256_hash + 2*i, "%02x", sha[i]);
    return sha256_hash;
}
