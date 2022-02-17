#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char  encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
static char* decoding_table   = NULL;
static int   mod_table[]      = {0, 2, 1};

void
build_decoding_table()
{
    decoding_table = malloc(256);

    for (int i = 0; i < 64; i++)
        decoding_table[(unsigned char)encoding_table[i]] = i;
}

void
base64_cleanup()
{
    free(decoding_table);
}

char*
base64_encode(const unsigned char* data, size_t input_length, size_t* output_length)
{
    *output_length = 4 * ((input_length + 2) / 3);

    char* encoded_data = malloc(*output_length);
    if (encoded_data == NULL)
        return NULL;

    for (int i = 0, j = 0; i < input_length;) {
        uint32_t octet_a = i < input_length ? (unsigned char)data[i++] : 0;
        uint32_t octet_b = i < input_length ? (unsigned char)data[i++] : 0;
        uint32_t octet_c = i < input_length ? (unsigned char)data[i++] : 0;

        uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
    }

    for (int i = 0; i < mod_table[input_length % 3]; i++)
        encoded_data[*output_length - 1 - i] = '=';

    return encoded_data;
}

unsigned char*
base64_decode(const char* data, size_t input_length, size_t* output_length)
{
    if (decoding_table == NULL)
        build_decoding_table();

    if (input_length % 4 != 0)
        return NULL;

    *output_length = input_length / 4 * 3;
    if (data[input_length - 1] == '=')
        (*output_length)--;
    if (data[input_length - 2] == '=')
        (*output_length)--;

    unsigned char* decoded_data = malloc(*output_length);
    if (decoded_data == NULL)
        return NULL;

    for (int i = 0, j = 0; i < input_length;) {
        uint32_t sextet_a = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        uint32_t sextet_b = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        uint32_t sextet_c = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        uint32_t sextet_d = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];

        uint32_t triple = (sextet_a << 3 * 6) + (sextet_b << 2 * 6) + (sextet_c << 1 * 6) + (sextet_d << 0 * 6);

        if (j < *output_length)
            decoded_data[j++] = (triple >> 2 * 8) & 0xFF;
        if (j < *output_length)
            decoded_data[j++] = (triple >> 1 * 8) & 0xFF;
        if (j < *output_length)
            decoded_data[j++] = (triple >> 0 * 8) & 0xFF;
    }

    return decoded_data;
}


uint8_t data[] = {0x01, 0x80, 0xc2, 0x00, 0x00, 0x00, 0xd0, 0x07, 0xca, 0x20, 0x4b, 0x03, 0x81, 0x00, 0x00, 0x01, 0x00, 0x69, 0x42, 0x42, 0x03, 0x00, 0x00, 0x03, 0x02, 0x4e, 0x00, 0x00, 0x08, 0xb2, 0x58, 0x48, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0xb2, 0x58, 0x48, 0x28, 0x00, 0x84, 0x00, 0x00, 0x00, 0x14, 0x00, 0x02, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x40, 0x00, 0x44, 0x45, 0x41, 0x43, 0x49, 0x50, 0x5f, 0x30, 0x30, 0x30, 0x30, 0x5f, 0x52, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xac, 0x36, 0x17, 0x7f, 0x50, 0x28, 0x3c, 0xd4, 0xb8, 0x38, 0x21, 0xd8, 0xab, 0x26, 0xde, 0x62, 0x00, 0x00, 0x01, 0xf4, 0x30, 0x00, 0xd0, 0x07, 0xca, 0x20, 0x4b, 0x03, 0x12};

int
main()
{
    long  input_size   = sizeof(data);
    char* encoded_data = base64_encode(data, input_size, &input_size);
    printf("Encoded Data is: %s \n", encoded_data);

    /*
    long  decode_size  = strlen(encoded_data);
    char* decoded_data = base64_decode(encoded_data, decode_size, &decode_size);
    printf("Decoded Data is: %s \n", decoded_data);
    */
}
