#include "../hash.h"
#include <assert.h>

snips_hash_out_t snips_hash_f (snips_hash_in_t input) {
	snips_hash_out_t output = { 0 };

	// hash
	if ((input.hash < 0) || (input.hash > 3))
		output.hash = SNIPS_HASH_INVALID_H;
	else
		output.hash = input.hash;

	// mode
	if ((input.prefer.mode < 0) || (input.prefer.mode > 2))
		output.mode = SNIPS_HASH_INVALID_M;
	else
		output.mode = input.prefer.mode;

	// validate input
	if (
		(input.in == NULL)	||
		(input.len <= 0)	||
		(output.hash == -1)	||
		(output.mode == -1)	||
		(input.prefer.len <= 0)
	) {
		output.err = -1;	// invalid parameters

		return output;
	}

	// hash selection heuristic
	switch (input.prefer.mode) {
		case SNIPS_HASH_DEFAULT_M:
		case SNIPS_HASH_FORCE_M:
			output.hash = input.hash;
			break;
		case SNIPS_HASH_LEN_M:
			if (output.len <= 16)		// SHA1 length in bytes
				output.hash = SNIPS_HASH_MD5_H;
			else if (output.len <= 20)	// MD5 length in bytes
				output.hash = SNIPS_HASH_SHA1_H;
			else if (output.len <= 64)	// BLAKE2b max length in bytes
				output.hash = SNIPS_HASH_BLAKE2_H;
			else {
				output.hash = SNIPS_HASH_INVALID_H;
				output.err = 1;		// cannot satisfy length requirement
				return output;
			}

			break;
		default:	// unreachable
			break;
	}


	// actual hashing
	output.len = input.prefer.len;
	output.out = malloc (output.len);
	assert (output.out);
	uint8_t *temp = alloca (20);
	switch (output.hash) {
		case SNIPS_HASH_DEFAULT_H:
		case SNIPS_HASH_BLAKE2_H:
			blake2 (output.out, input.in, NULL, output.len, input.len, 0);
			break;
		case SNIPS_HASH_SHA1_H:
			SHA1 (input.in, input.len, temp);

			memcpy (output.out, temp, output.len);
			break;
		case SNIPS_HASH_MD5_H:
			MD5 (input.in, input.len, temp);

			memcpy (output.out, temp, output.len);
			break;
		default:	// unreachable
			break;
	}

	return output;
}
