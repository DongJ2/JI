/*
 * FILE: rdt_receiver.cc
 * DESCRIPTION: Reliable data transfer receiver.
 * NOTE: This implementation assumes there is no packet loss, corruption, or
 *       reordering.  You will need to enhance it to deal with all these
 *       situations.  In this implementation, the ack packet format is laid out as
 *       the following:
 *
 *       |<-  2 byte -->|<-  4 byte  ->|
 *       |   check sum  |     ack      |
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rdt_struct.h"
#include "rdt_receiver.h"

#define HEADER_SIZE 7
#define MAX_PAYLOAD_SIZE (RDT_PKTSIZE - HEADER_SIZE)
#define WINDOW_SIZE 10




/* packet window */
static packet* window;
/* correspond to packet window, 1 represents valid */
static char* pkt_valids;
/* the massage sequence number is receiving now */
static message* msg;



/* same as sender */
static short checksum(struct packet* pkt) {
    unsigned long sum = 0;
    for(int i = 2; i < RDT_PKTSIZE; i += 2) sum += *(short *)(&(pkt->data[i]));
    while(sum >> 16) sum = (sum >> 16) + (sum & 0xffff);
    return ~sum;
}



static void Receiver_SendACK(int ack) {
    /* fill in the packet */
    packet ack_packet;
    memcpy(ack_packet.data + sizeof(short), &ack, sizeof(int));
    short sum = checksum(&ack_packet);
    memcpy(ack_packet.data, &sum, sizeof(short));

    Receiver_ToLowerLayer(&ack_packet);
    //fprintf(stdout, "At %.2fs: receiver send ack %d ...\n", GetSimulationTime(), ack);
}



/* receiver initialization, called once at the very beginning */
void Receiver_Init()
{
    window = (packet *)malloc(WINDOW_SIZE * sizeof(packet));
    pkt_valids = (char *)malloc(WINDOW_SIZE);
    memset(pkt_valids, 0, WINDOW_SIZE);

    /* construct a message */
    msg = (message *)malloc(sizeof(message));
    memset(msg, 0, sizeof(message));

    fprintf(stdout, "At %.2fs: receiver initializing ...\n", GetSimulationTime());
}

/* receiver finalization, called once at the very end.
   you may find that you don't need it, in which case you can leave it blank.
   in certain cases, you might want to use this opportunity to release some
   memory you allocated in Receiver_init(). */
void Receiver_Final()
{
    /* don't forget to free the space */
    free(window);
    free(pkt_valids);
    free(msg);
    fprintf(stdout, "At %.2fs: receiver finalizing ...\n", GetSimulationTime());
}

/* event handler, called when a packet is passed from the lower layer at the
   receiver */
void Receiver_FromLowerLayer(struct packet *pkt)
{
    /* the cursor always points to the first unreceive byte in the message */
    static int cursor = 0;
    /* the pkt_seq expected to receive */
    static int expected_pkt = 0;

    /* checksum */
    short sum;
    memcpy(&sum, pkt->data, sizeof(short));
    if(sum != checksum(pkt)) return;


    int pkt_seq = 0;
    memcpy(&pkt_seq, pkt->data + sizeof(short), sizeof(int));
    //fprintf(stdout, "At %.2fs: receiver get seq %d ...\n", GetSimulationTime(), pkt_seq);
    if(pkt_seq > expected_pkt && pkt_seq < expected_pkt + WINDOW_SIZE) {
        /* window is not full */
        /* save it to packet window */
        /* because timeout resend protocal, if valid, no need to update */
        if(!pkt_valids[pkt_seq % WINDOW_SIZE]) {
            memcpy(&(window[pkt_seq % WINDOW_SIZE].data), pkt->data, RDT_PKTSIZE);
            pkt_valids[pkt_seq % WINDOW_SIZE] = 1;
        }
        //Receiver_SendACK(expected_pkt - 1);
        return;
    }
    /* pkt_seq < expected_pkt */
    else if(pkt_seq != expected_pkt) {
        Receiver_SendACK(expected_pkt - 1);
        //fprintf(stdout, "At %.2fs: receiver get small seq ...\n", GetSimulationTime());
        return;
    }
    /* impossible to get  pkt_seq >= expected_pkt+WINDOW_SIZE */
    /* pkt_seq == expected_pkt */
    else{
        while(true){
            expected_pkt++;
            int payload_size = pkt->data[HEADER_SIZE - 1];

            /* get the first pkt of a msg */
            if(cursor == 0){
                if(msg->size != 0) free(msg->data);
                memcpy(&msg->size, pkt->data + HEADER_SIZE, sizeof(int));
                msg->data = (char*) malloc(msg->size);
                memcpy(msg->data, pkt->data + HEADER_SIZE + sizeof(int), payload_size - sizeof(int));
                cursor += payload_size - sizeof(int);
            } 
            else {
                memcpy(msg->data + cursor, pkt->data + HEADER_SIZE, payload_size);
                cursor += payload_size;
            }

            /* a massage is finish */
            if(msg->size == cursor) {
                Receiver_ToUpperLayer(msg);
                cursor = 0;
            }

            /* check pkt in window which is expected */
            if(pkt_valids[expected_pkt % WINDOW_SIZE]){
                pkt = &window[expected_pkt % WINDOW_SIZE];
                memcpy(&pkt_seq, pkt->data + sizeof(short), sizeof(int));
                pkt_valids[expected_pkt % WINDOW_SIZE] = 0;
            } 
            else 
                break;

            /* to avoid some wrong timeout */
            //if((pkt_seq%3)==0)Receiver_SendACK(pkt_seq);
        }

        Receiver_SendACK(pkt_seq);
    }
}