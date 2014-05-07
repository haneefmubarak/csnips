// snips/rendezvous.h

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// snips hashing
#include "hash.h"

typedef struct {
	uint8_t **keys;		// an array of keys to select against
	uint8_t *value;		// the value to use the rendezvous method against
	snips_hash_h_t hash;	// which hash to use - pick one ans stick with it
	uint16_t count;		// too many keys == bad mojo
	struct len {		// and honestly, 1024 bit keys or values are a bit too long - use a hash at that point
		int16_t key;	// key length
		int16_t value;	// rendezvous value length
	};
} snips_rendezvous_in_t;

typedef struct {
	uint8_t **keys;		// sorted output array of keys
	uint8_t **hashes;	// corresponding hashes
	snips_hash_h_t hash;	// which hash was used / hashing error
	int16_t err;		// treat zero as valid, all else is an error
	int8_t len;		// output hash length
} snips_rendezvous_out_t;
