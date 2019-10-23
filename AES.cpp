#include<bitset>
#include<vector>
#include<algorithm>
#include <iostream>
#include"TYPES.h"
#include"DEVICES.h"
using namespace std;

void addRoundKey(vc& state, vc& key) {
	_ASSERT(state.size() == key.size());
	for (int i = 0; i < state.size(); i++) {
		state[i] = state[i] ^ key[i];
	}
}
void subBytes(vc& state, const uc sbox[] = SBOX) {//default is encryption
	for (int i = 0; i < state.size(); i++)
			state[i] = sbox[state[i]];
}
void shiftRows(vc& state, const vi& shifter = SHIFTROWPERM) {
	vc tmp(state.size());
	for (int i = 0; i < state.size(); i++)
		tmp[i] = state[shifter[i]];
	state = tmp;
}
uc mod(ll n) {
	while (n & (~255ll)) {//as long as n is not 8 bit
		int shift = 64-9;  ll p = 1ll << 63;
		while ((n & p) == 0ll)
		{ 
			shift--, p >>= 1; 
		}
		n = n ^ (MOD << (shift));
	}
	return uc(n);
}
uc multiply(uc a, uc b) {
	ll mx = max(a, b), mn = min(a,b);
	ll mul = 1;
	ll ans = 0;
	int shift = 0;
	while (mul <= mn) {
		if (mul & mn) {//if a bit in mn is 1
			ans ^= mx << shift;//xor the mx shifted by the order of this bit in mn
		}
		shift++;
		mul <<= 1;
	}
	return mod(ans);
}
void mixColumns(vc& state, const uc mat [][4]= MIXCOL) {
	uc tmp[4][4];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			tmp[j][i] = state[4 * i + j];
	uc ans[4][4];

	for (int i = 0; i < 4; i++) {
		ans[0][i] = multiply(tmp[0][i], mat[0][0]) ^ multiply(tmp[1][i], mat[0][1]) ^ multiply(tmp[2][i], mat[0][2]) ^ multiply(tmp[3][i], mat[0][3]);
		ans[1][i] = multiply(tmp[0][i], mat[1][0]) ^ multiply(tmp[1][i], mat[1][1]) ^ multiply(tmp[2][i], mat[1][2]) ^ multiply(tmp[3][i], mat[1][3]);
		ans[2][i] = multiply(tmp[0][i], mat[2][0]) ^ multiply(tmp[1][i], mat[2][1]) ^ multiply(tmp[2][i], mat[2][2]) ^ multiply(tmp[3][i], mat[2][3]);
		ans[3][i] = multiply(tmp[0][i], mat[3][0]) ^ multiply(tmp[1][i], mat[3][1]) ^ multiply(tmp[2][i], mat[3][2]) ^ multiply(tmp[3][i], mat[3][3]);
	}
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			state[4 * i + j] = ans[j][i];
}
/*
Cut the plain text and keys into 2 parts to fit into 64 bit integers
*/
void AES(ll pMSB, ll pLSB , ll kMSB, ll kLSB, bool encrypt = 1) {
	vc state(16);
	for (int i = 0; i < 8; i++) {
		state[i] = pMSB >> (64 - 8);
		pMSB <<= 8;
	}
	for (int i = 0; i < 8; i++) {
		state[i + 8] = pLSB >> (64 - 8);
		pLSB <<= 8;
	}
	mixColumns(state);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
			cout << hex << int(state[4*j + i]) << " ";
		cout << endl;
	}
	//state now is correct

	/*
	addRoundKey();

	for (int i = 1; i < 10; i++) {
		subBytes();
		shiftRows();
		mixColumns();
		addRoundKey();
	}

	subBytes();
	shiftRows();
	addRoundKey();*/
}
int main()
{
    std::cout << "Start\n";
	ll msb = 0x876E46A6F24CE78C; //msb
	ll lsb = 0x4D904AD897ECC395; //msb
	AES(msb, lsb, 0, 0);
}
