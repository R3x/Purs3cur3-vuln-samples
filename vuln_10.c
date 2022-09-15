/*
 * This is from OPENSSL
 */

if (sslv2format) {
    size_t numciphers = PACKET_remaining(cipher_suites) / n;
    PACKET sslv2ciphers = *cipher_suites;
    unsigned int leadbyte;
    unsigned char *raw;

    /*
    * We store the raw ciphers list in SSLv3+ format so we need to do some
    * preprocessing to convert the list first. If there are any SSLv2 only
    * ciphersuites with a non-zero leading byte then we are going to
    * slightly over allocate because we won't store those. But that isn't a
    * problem.
    */

    raw = OPENSSL_malloc(numciphers * TLS_CIPHER_LEN);
    s->s3->tmp.ciphers_raw = raw;
    if (raw == NULL) {
        *al = SSL_AD_INTERNAL_ERROR;
        goto err;
    }
    for (s->s3->tmp.ciphers_rawlen = 0;
            PACKET_remaining(&sslv2ciphers) > 0;
            raw += TLS_CIPHER_LEN) {
        if (!PACKET_get_1(&sslv2ciphers, &leadbyte)
                || (leadbyte == 0
                    && !PACKET_copy_bytes(&sslv2ciphers, raw,
                                            TLS_CIPHER_LEN))
                || (leadbyte != 0
                    && !PACKET_forward(&sslv2ciphers, TLS_CIPHER_LEN))) {
            *al = SSL_AD_INTERNAL_ERROR;
            OPENSSL_free(raw);
            s->s3->tmp.ciphers_raw = NULL;
            s->s3->tmp.ciphers_rawlen = 0;
            goto err;
        }
        if (leadbyte == 0)
            s->s3->tmp.ciphers_rawlen += TLS_CIPHER_LEN;
    }
} else if (!PACKET_memdup(cipher_suites, &s->s3->tmp.ciphers_raw,
                        &s->s3->tmp.ciphers_rawlen)) {
    *al = SSL_AD_INTERNAL_ERROR;
    goto err;
}
