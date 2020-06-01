#pragma once
#ifndef __zk_verifier
#define __zk_verifier

#include "linear_gkr/circuit_fast_track.h"
#include "linear_gkr/zk_prover.h"
#include "linear_gkr/polynomial.h"
#include <utility>

class ldt_commitment
{
public:
	__hhash_digest* commitment_hhash;
	prime_field::field_element *randomness;
	prime_field::field_element *final_rs_code;
	int mx_depth;
	int repeat_no;
};

class zk_verifier
{
public:
	/** @name Randomness&Const 
	* Storing randomness or constant for simplifying computation/
	*/
	///@{
	prime_field::field_element *beta_g_r0_first_half, *beta_g_r0_second_half;
	prime_field::field_element *beta_g_r1_first_half, *beta_g_r1_second_half;
	prime_field::field_element *beta_u_first_half, *beta_u_second_half;
	prime_field::field_element *beta_v_first_half, *beta_v_second_half;

	prime_field::field_element *beta_g_r0_block_first_half, *beta_g_r0_block_second_half;
	prime_field::field_element *beta_g_r1_block_first_half, *beta_g_r1_block_second_half;
	prime_field::field_element *beta_u_block_first_half, *beta_u_block_second_half;
	prime_field::field_element *beta_v_block_first_half, *beta_v_block_second_half;
	///@}
	layered_circuit C; //!< The circuit
	zk_prover *p; //!< The prover
	void beta_init(int depth, prime_field::field_element alpha, prime_field::field_element beta,
	const prime_field::field_element* r_0, const prime_field::field_element* r_1, 
	const prime_field::field_element* r_u, const prime_field::field_element* r_v, 
	const prime_field::field_element* one_minus_r_0, const prime_field::field_element* one_minus_r_1, 
	const prime_field::field_element* one_minus_r_u, const prime_field::field_element* one_minus_r_v);
	void read_circuit(const char *, const char*);
	bool verify(const char*);
	void get_prover(zk_prover*);
	void delete_self();
	std::vector<prime_field::field_element> predicates(int depth, prime_field::field_element *r_0, prime_field::field_element *r_1, prime_field::field_element *r_u, prime_field::field_element *r_v, prime_field::field_element alpha, prime_field::field_element beta);
	prime_field::field_element direct_relay(int depth, prime_field::field_element *r_g, prime_field::field_element *r_u);
	prime_field::field_element V_in(const prime_field::field_element*, const prime_field::field_element*, prime_field::field_element*, int, int);
	std::vector<prime_field::field_element> all_pub_mask;
	prime_field::field_element all_mask_sum; ///<all_mask_sum = all_pub_mask * all_pri_mask;
	prime_field::field_element *VPD_randomness, *one_minus_VPD_randomness;
	void self_inner_product_test(prime_field::field_element alpha_beta_sum, prime_field::field_element v_in);
	/**Test the evaluation of all mask polys after doing random linear combination for them. */
	bool vpd_verify(prime_field::field_element* all_sum, double &v_time, int &proof_size, double &p_time, __hhash_digest merkle_tree_l, __hhash_digest merkle_tree_h);
	ldt_commitment commit_phase();
};

#endif