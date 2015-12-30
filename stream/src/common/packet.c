/* packet.c
 * Function to manipulate packet structure
 * author: pangyemeng
 */

#include <stdlib.h>
#include <string.h>

#include "packet.h"
#include "log.h"
#include "dmemory.h"
#include "proto.h"


void PktFree(packet *pkt)
{
    packet *next;

    do {
        if (pkt == NULL)
            return ;
        
        ProtDelFrame(pkt->stk);
        
        if (pkt->dat_base != NULL) {
            if (pkt->raw != pkt->dat_base) {
                DMemFree(pkt->dat_base);
            }
        }
        else if (pkt->data != NULL) {
            DMemFree(pkt->data);
        }
        if (pkt->raw != NULL) {
            DMemFree(pkt->raw);
        }
        /* list */
        PktFree(pkt->list);

        next = pkt->next;
        DMemFree(pkt);
        pkt = next;
    } while (pkt != NULL);
}


packet* PktNew(void)
{
    packet *pkt;

    pkt = DMemMalloc(sizeof(packet));
    if (pkt != NULL)
        memset(pkt, 0, sizeof(packet));
    
    return pkt;
}


packet* PktCp(const packet *pkt)
{
    packet *new;

    new = PktNew();
    if (new != NULL) {
        new->stk = ProtCopyFrame(pkt->stk, TRUE);
        new->cap_sec = pkt->cap_sec;
        new->cap_usec = pkt->cap_usec;
        new->raw = NULL;
        new->raw_len = 0;
        new->list = NULL;
        new->dat_base = NULL;
        if (pkt->len != 0 && pkt->data != NULL) { /* for protocol with hole (ex:tcp) */
            new->data = DMemMalloc(pkt->len+1);
            memcpy(new->data, pkt->data, pkt->len);
            new->data[pkt->len] = '\0';
        }
        new->len = pkt->len;
        new->next = NULL;
    }

    return new;
}
