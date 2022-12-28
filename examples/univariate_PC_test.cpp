#include "VPD/linearPC.h"
#include "linear_code/linear_code_encode.h"
#include <chrono>
#include <cstdio>
#define timer_mark(x) auto x = std::chrono::high_resolution_clock::now()
#define time_diff(start, end)                                                  \
  (std::chrono::duration_cast<std::chrono::duration<double>>(end - start)      \
       .count())
int main(int argc, char *argv[]) {
  printf("111\n");
  int N, lg_N;
  sscanf(argv[1], "%d", &lg_N);
  N = 1 << lg_N;

  printf("222\n");

  expander_init(N / column_size);

  printf("333\n");

  prime_field::field_element *coefs = new prime_field::field_element[N];
  for (int i = 0; i < N; ++i)
    coefs[i] = prime_field::random();

  printf("444\n");

  timer_mark(commit_t0);
  auto h = commit(coefs, N);
  timer_mark(commit_t1);

  printf("555\n");

  timer_mark(open_t0);
  auto result = open_and_verify(prime_field::random(), N, h);
  timer_mark(open_t1);
  printf("Commit time %lf\n", time_diff(commit_t0, commit_t1));
  printf("Open time %lf\n", time_diff(open_t0, open_t1));
  printf("%s\n", result.second ? "succ" : "fail");
  return 0;
}
