
#ifndef HIERARCHICALDETERMINISTICWALLETS_HDWALLET_H
#define HIERARCHICALDETERMINISTICWALLETS_HDWALLET_H

#define SERIALIZED_KEY_BUFFER_LEN 112

#include <stddef.h>
#include <stdint.h>

typedef struct {
    uint8_t version[4];
    uint8_t depth;
    uint8_t parent_fingerprint[4];
    uint8_t child_number[4];
    uint8_t chain_code[32];
    uint8_t key_data[33];
} __attribute__ ((packed)) HDW_key_t;

enum KEY_VERSIONS {
    KEY_VERSION_MAINNET_PUBLIC = 0,
    KEY_VERSION_MAINNET_PRIVATE = 1,
    KEY_VERSION_TESTNET_PUBLIC = 2,
    KEY_VERSION_TESTNET_PRIVATE = 3,
};

/*
 * Contains the values of version prefixes
 */
extern const uint8_t KEY_VERSIONS_VALUES[4][4];

/*
 * Generates the Master Node from a `seed` and puts it into `key`
 */
int HDW_generate_master_node(uint8_t *seed,
                             size_t seed_len,
                             HDW_key_t *key);

/*
 * Takes the `key` and turns it into a BIP32 compliant Base58 representation.
 * Outputs the string in a buffer of size `SERIALIZED_KEY_BUFFER_LEN`
 */
int HDW_serialize_key(HDW_key_t *key,
                      uint8_t *destination,
                      size_t *destination_len);

int HDW_derivate_private_child(HDW_key_t parent_key, HDW_key_t child_key);
int HDW_derivate_public_child(HDW_key_t parent_key, HDW_key_t child_key);

#endif //HIERARCHICALDETERMINISTICWALLETS_HDWALLET_H