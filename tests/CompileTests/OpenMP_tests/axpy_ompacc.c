// Experimental test input for Accelerator directives
// Liao 1/15/2013

#define REAL float
void axpy_ompacc(REAL* x, int n, REAL a) {
  int i, gpu0;
  REAL y[100];
/* this one defines both the target device name and data environment to map to,
   I think here we need mechanism to tell the compiler the device type (could be multiple) so that compiler can generate the codes of different versions; 
   we also need to let the runtime know what the target device is so the runtime will chose the right function to call if the code are generated 
*/
/* #pragma omp parallel for shared(x, y, n, a) private(i) */
#pragma omp target device (gpu0) map(y[0:n]) map(in:x[0:n],a,n)
#pragma omp parallel for
  for (i = 0; i < n; ++i)
    y[i] += a * x[i];
}
