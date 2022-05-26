#include <iostream>
#include <algorithm>
#include <vector>
#include <complex>
#include <valarray>
#include <cmath>

using namespace std;

const double PI = acos(-1);

typedef complex<double> Complex;
typedef valarray<Complex> CArray;

void fft(CArray& x) {
  const size_t N = x.size();
  if (N <= 1) return;

  CArray even = x[std::slice(0, N/2, 2)];
  CArray  odd = x[std::slice(1, N/2, 2)];

  fft(even);
  fft(odd);

  for (size_t k = 0; k < N/2; ++k) {
    Complex t = std::polar(1.0, -2 * PI * k / N) * odd[k];
    x[k] = even[k] + t;
    x[k+N/2] = even[k] - t;
  }
}

void ifft(CArray& x) {
  x = x.apply(conj);
  fft(x);
  x = x.apply(conj);
  x /= x.size();
}

int main(void) {
	int N, M, Q;
	cin >> N >> M >> Q;

	vector<int> A(N), B(M);
	int max = -1;

	for(int i = 0; i < N; i++) {
		cin >> A[i];
		if (A[i] > max) max = A[i];
	}

	for(int i = 0; i < M; i++) {
		cin >> B[i];
		if (B[i] > max) max = B[i];
	}
	
	int NN = max + 1;
	vector<Complex> PA(NN, 0), PB(NN, 0);

	for(int i = 0; i < A.size(); i++) PA[A[i]] = 1;
	for(int i = 0; i <  B.size(); i++) PB[B[i]] = 1;

    int padded_size = 2 * (1 << int(ceil(log2(NN))));
    vector<Complex> num1_vec(padded_size - NN, 0.0), num2_vec(padded_size - NN, 0.0);

    for(int i = 0; i < NN; i++) {
      num1_vec.push_back(PA[i]);
    }
	
    for(int i = 0; i < NN; i++) {
      num2_vec.push_back(PB[i]);
    }

    CArray data1(padded_size);
    for(int i = 0; i < padded_size; i++) data1[i] = num1_vec[i];
    CArray data2(padded_size);
    for(int i = 0; i < padded_size; i++) data2[i] = num2_vec[i];

    fft(data1);
    fft(data2);

    CArray data3(padded_size);
    data3 = data1 * data2;

    ifft(data3);

    vector<long long> ans;
    for (int i = 0; i < padded_size - 1; i++) {
      ans.push_back((long long)(round(data3[i].real())));
    }


	vector<long long> queries;
    for(int i = padded_size - 1 - (2*NN - 1); i < padded_size - 1; i++) {
      queries.push_back(ans[i]);
    }

	for(int i = 0; i < Q; i++) {
		int q; cin >> q;
		cout << queries[q] << endl;
	}
}