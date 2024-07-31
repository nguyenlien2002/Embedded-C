#include<stdio.h>
#include<stdint.h>
#define REG_BIT_SET32(add,n) (*((uint32_t*)add) |= (1 << n))
#define REG_BIT_CLEAR32(add,n) ((*(uint32_t*)add) &= ~(1 << n))
#define SWAP_BYTE32(add) (*(uint32_t *)(add) = \
    (((*(uint32_t *)(add) & 0x000000FFU) << 24) | \
    ((*(uint32_t *)(add) & 0x0000FF00U) << 8) | \
    ((*(uint32_t *)(add) & 0x00FF0000U) >> 8) | \
    ((*(uint32_t *)(add) & 0xFF000000U) >> 24)))
#define SWAP_BYTE16(add) (*(uint16_t *)(add) = \
    (((*(uint16_t *)(add) & 0x00FFU) << 8) | \
    ((*(uint16_t *)(add) & 0xFF00U) >> 8)))

int main()
{
    uint32_t a = 0x00000000;
    printf("a ban dau 0x%08x\n",a);
    REG_BIT_SET32(&a,7);
    printf("a sau khi set bit so 7 la 0x%08x\n", a);
    REG_BIT_SET32(&a,9);
    printf("a sau khi set bit so 9 la 0x%08x\n", a);
    REG_BIT_CLEAR32(&a,9);
    REG_BIT_CLEAR32(&a,7);
    printf("a sau khi clear la 0x%08x\n", a);
    a = 0x12345678;
    printf("a truoc khi swap la 0x%08x\n", a);
    SWAP_BYTE32(&a);
    printf("a sau khi swap la 0x%08x\n", a);
    uint16_t b = 0x1234;
    printf("b truoc khi swap la 0x%04x\n", b);
    SWAP_BYTE16(&b);
    printf("b truoc khi swap la 0x%04x\n", b); 
}
