// This code here comes from http://www.xnoiz.co.cc/fast-exp-x/

/*
    Copyright (c) 2011, Philipp Krähenbühl
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
        * Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.
        * Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.
        * Neither the name of the Stanford University nor the
        names of its contributors may be used to endorse or promote products
        derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY Philipp Krähenbühl ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL Philipp Krähenbühl BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once

inline float fast_log2 (float val) {
   int * const  exp_ptr = reinterpret_cast <int *> (&val);
   int          x = *exp_ptr;
   const int    log_2 = ((x >> 23) & 255) - 128;
   x &= ~(255 << 23);
   x += 127 << 23;
   *exp_ptr = x;

   return (val + log_2);
}
inline float fast_log (const float &val) {
   return (fast_log2 (val) * 0.69314718f);
}
inline float very_fast_exp(float x) {
	// err <= 3e-3
// 	return 1
// 		   -x*(0.9664
// 		   -x*(0.3536));

	return 1
	-x*(0.9999999995f
	-x*(0.4999999206f

	-x*(0.1666653019f
	-x*(0.0416573475f
	-x*(0.0083013598f

	-x*(0.0013298820f
	-x*(0.0001413161f)))))));
}
inline float fast_exp(float x) {
	bool lessZero = true;
	if (x < 0) {

		lessZero = false;
		x = -x;

	}
	// This diry little trick only works because of the normalization and the fact that one element in the normalization is 1
	if (x > 20)
		return 0;
	int mult = 0;

	while (x > 0.69*2*2*2) {

		mult+=3;
		x /= 8.0f;
	}

	while (x > 0.69*2*2) {
		mult+=2;

		x /= 4.0f;
	}
	while (x > 0.69) {

		mult++;
		x /= 2.0f;
	}

	x = very_fast_exp(x);
	while (mult) {

		mult--;
		x = x*x;
	}

	if (lessZero) {
		return 1 / x;

	} else {
		return x;
	}
}


