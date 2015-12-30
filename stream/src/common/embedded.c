/* embedded.c
 * author: pangyemeng
 */

#include "embedded.h"

unsigned int Emb32(void *addr)
{
    unsigned int u32;

    u32 = *(((unsigned short*)&(addr))+1);
    u32 = (u32<<16) | *(((unsigned short*)&(addr)));
    
    return u32;
}

void embedded_link(void)
{

}
