// snips/hash.h
#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// hash library headers
#include <blake2.h>
#include <openssl/sha.h>
#include <openssl/md5.h>

typedef enum {
	SNIPS_HASH_INVALID_H	= -1,
	SNIPS_HASH_DEFAULT_H	= 0,
	SNIPS_HASH_BLAKE2_H	= 1,
	SNIPS_HASH_SHA1_H	= 2,
	SNIPS_HASH_MD5_H	= 3
} snips_hash_h_t;

typedef enum {
	SNIPS_HASH_INVALID_M	= -1,
	SNIPS_HASH_DEFAULT_M	= 0,
	SNIPS_HASH_FORCE_M	= 1,
	SNIPS_HASH_LEN_M	= 2
} snips_hash_m_t;

typedef struct {
	uint8_t *in;	// input byte array
	uint64_t len;	// length of ^^^^^^
	snips_hash_h_t hash;	// which hash to use
	struct {
		snips_hash_m_t mode;	// which hash selection heuristic to use
		uint8_t len;	// preferred output length
	} prefer;
} snips_hash_in_t;

typedef struct {
	uint8_t *out;	// output byte array
	snips_hash_h_t hash;	// which hash was used
	snips_hash_m_t mode;	// which hash selection heuristic was used
	int16_t len;	// length of ^^^^^^^
	int16_t err;	// treat zero as valid, all else is an error
} snips_hash_out_t;

snips_hash_out_t snips_hash_f (snips_hash_in_t);
