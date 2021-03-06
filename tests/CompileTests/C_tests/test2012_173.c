#include <linux/types.h>
#include <stdio.h>

#define test_strcmp(s1, s2)  strcmp((const char *) s1, (const char *) s2)

static inline void test_cpuid(uint32_t i, uint32_t *buf);
static inline void test_cpuid_new(uint32_t i, uint32_t *buf);


static inline void
test_cpuid_new(uint32_t i, uint32_t *buf)
{
    uint32_t  eax, ebx, ecx, edx, trash;

    printf("Probe: %s\n", "NEW ALGORITHM");    
    /*
     * we could not use %ebx as output parameter if gcc builds PIC,
     * and we could not save %ebx on stack, because %esp is used,
     * when the -fomit-frame-pointer optimization is specified.
     */

    __asm__ (

    "    mov    %%ebx, %%esi;  "

    "    cpuid;                "
    "    mov    %%ebx, %%edi;  "

    "    mov    %%esi, %%ebx;  "

    : "=a" (eax), "=D" (ebx), "=c" (ecx), "=d" (edx), "=S" (trash) : "a" (i) );

    buf[0] = eax;
    buf[1] = ebx;
    buf[2] = edx;
    buf[3] = ecx;
}



static inline void
test_cpuid(uint32_t i, uint32_t *buf)
{
    printf("Probe: %s\n", "ORIGINAL ALGORITHM");

    /*
     * we could not use %ebx as output parameter if gcc builds PIC,
     * and we could not save %ebx on stack, because %esp is used,
     * when the -fomit-frame-pointer optimization is specified.
     */

    __asm__ (

    "    mov    %%ebx, %%esi;  "

    "    cpuid;                "
    "    mov    %%eax, (%1);   "
    "    mov    %%ebx, 4(%1);  "
    "    mov    %%edx, 8(%1);  "
    "    mov    %%ecx, 12(%1); "

    "    mov    %%esi, %%ebx;  "

    : : "a" (i), "D" (buf) : "ecx", "edx", "esi", "memory" );
}




/* auto detect the L2 cache line size of modern and widespread CPUs */

void
test_cpuinfo(void)
{
    u_char    *vendor;
    uint32_t   vbuf[5], cpu[4], model, ngx_cacheline_size;

    ngx_cacheline_size = 0;

    vbuf[0] = 0;
    vbuf[1] = 0;
    vbuf[2] = 0;
    vbuf[3] = 0;
    vbuf[4] = 0;

    test_cpuid(0, vbuf);

    vendor = (u_char *) &vbuf[1];

    if (vbuf[0] == 0) {
        return;
    }

    test_cpuid(1, cpu);

    if (test_strcmp(vendor, "GenuineIntel") == 0) {
        printf("Processor Type: %s\n", "GenuineIntel");
        switch ((cpu[0] & 0xf00) >> 8) {

        /* Pentium */
        case 5:
            printf("Processor Model: %s\n", "Pentium");
            ngx_cacheline_size = 32;
            break;

        /* Pentium Pro, II, III */
        case 6:
            ngx_cacheline_size = 32;

            model = ((cpu[0] & 0xf0000) >> 8) | (cpu[0] & 0xf0);

            if (model >= 0xd0) {
                /* Intel Core, Core 2, Atom */
                printf("Processor Model: %s\n", "Core, Core 2, Atom");
                ngx_cacheline_size = 64;
            } else {
                printf("Processor Model: %s\n", "Pentium Pro, II, III");
            }

            break;

        /*
         * Pentium 4, although its cache line size is 64 bytes,
         * it prefetches up to two cache lines during memory read
         */
        case 15:
            printf("Processor Model: %s\n", "Pentium 4");
            ngx_cacheline_size = 128;
            break;
        }

    } else if (test_strcmp(vendor, "AuthenticAMD") == 0) {
        ngx_cacheline_size = 64;
    }
}

int main(int argc, char** argv) {
    test_cpuinfo();
}
