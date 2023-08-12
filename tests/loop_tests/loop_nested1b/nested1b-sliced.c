// This file is part of the SV-Benchmarks collection of verification tasks:
// https://github.com/sosy-lab/sv-benchmarks
//
// This file was part of CPAchecker,
// a tool for configurable software verification:
// https://cpachecker.sosy-lab.org
//
// SPDX-FileCopyrightText: 2007-2020 Dirk Beyer <https://www.sosy-lab.org>
//
// SPDX-License-Identifier: Apache-2.0

void reach_error() { assert(0); }

void reach_error_slice_1(void){
  ERROR: {reach_error();}
  return;
}


int main() {
	int a = 6;


	for(a = 0; a < 6; ++a) {

	}
	if(a == 6 ) {
		reach_error_slice_1();
	}
	return 1;
}
