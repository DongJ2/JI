/*
 * FILE: rdt_sender.cc
 * DESCRIPTION: Reliable data transfer sender.
 * NOTE: This implementation assumes there is no packet loss, corruption, or 
 *       reordering.  You will need to enhance it to deal with all these 
 *       situations.  In this implementation, the packet format is laid out as 
 *       the following:
 *       
 *       |<-  1 byte  ->|<-             the rest            ->|
 *       | payload size |<-             payload             ->|
 *
 *       The first byte of each packet indicates the size of the payload
 *       (excluding this single-byte header)
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rdt_struct.h"
#include "rdt_sender.h"

#define TIMEOUT 0.3
#define WINDOW_SIZE 10
#define BUFFER_SIZE 10000

#define HEADER_SIZE 7
#define MAX_PAYLOAD_SIZE (RDT_PKTSIZE - HEADER_SIZE)



/* packet sequence number */
static int pkt_seq;
/* packet window */
static packet* window;
/* the num of pkts in window */
static int wpkt_num;
/* the seq of pkt which is to be sended */
static int current_pkt;



/* the ack which is expected to receive */
static int expected_ack;
/* the newest also biggest ack gotted */
static int ack;



/* massage sequence number */
static int msg_seq;
/* massage buffer */
static message* buffer;
/* the num of msgs in buffer */
static int bmsg_num;



/*  the 16 bit checksum algorithm
 *  if no static, will cause the redefined error 
 */
static short checksum(struct packet* pkt) {
    unsigned long sum = 0;
    for(int i = 2; i < RDT_PKTSIZE; i += 2) sum += *(short *)(&(pkt->data[i]));
    while(sum >> 16) sum = (sum >> 16) + (sum & 0xffff);
    return ~sum;
}



static void Sender_SendPacket() {
    /* the cursor always points to the first unsent byte in the message */
    static int cursor;

    /* the seq of msg which is sending */
    static int current_msg = 0;
    message msg = buffer[current_msg % BUFFER_SIZE];

    /* reuse the same packet data structure */
    packet pkt;

    /* add packet to window */
    while (wpkt_num < WINDOW_SIZE && current_msg < msg_seq) {
        short sum;
        if(msg.size - cursor > MAX_PAYLOAD_SIZE){
            /* fill in the packet */
            memcpy(pkt.data + sizeof(short), &pkt_seq, sizeof(int));
            pkt.data[HEADER_SIZE - 1] = MAX_PAYLOAD_SIZE;
            memcpy(pkt.data + HEADER_SIZE, msg.data + cursor, MAX_PAYLOAD_SIZE);
            sum = checksum(&pkt);
            memcpy(pkt.data, &sum, sizeof(short));

            /* save the packet to window buffer */
            memcpy(&(window[pkt_seq % WINDOW_SIZE]), &pkt, sizeof(packet));

            /* move the cursor */
            cursor += MAX_PAYLOAD_SIZE;
            pkt_seq++;
            wpkt_num++;
        } 
        /* send out the last packet */
        else if (msg.size > cursor) {
            /* fill in the packet */
            memcpy(pkt.data + sizeof(short), &pkt_seq, sizeof(int));
            pkt.data[HEADER_SIZE - 1] = msg.size - cursor;
            memcpy(pkt.data + HEADER_SIZE, msg.data + cursor, msg.size - cursor);
            sum = checksum(&pkt);
            memcpy(pkt.data, &sum, sizeof(short));

            /* save the packet to window buffer */
            memcpy(&(window[pkt_seq % WINDOW_SIZE]), &pkt, sizeof(packet));

            /* finish the msg */
            bmsg_num--;
            current_msg++;
            if(current_msg < msg_seq){
                msg = buffer[current_msg % BUFFER_SIZE];
            }

            /* move the cursor */
            cursor = 0;
            pkt_seq++;
            wpkt_num++;
        }
    }

    /* send pkt(in window) out through the lower layer */
    while(current_pkt < pkt_seq) {
        /* some optimition */
        if(current_pkt < ack) {
            current_pkt = ack+1;
            continue;
        }
        else{
            memcpy(&pkt, &(window[current_pkt % WINDOW_SIZE]), sizeof(packet));
            Sender_ToLowerLayer(&pkt);
            current_pkt++;
        }
    }
}



/* sender initialization, called once at the very beginning */
void Sender_Init()
{
    pkt_seq = 0;
    window = (packet*) malloc((WINDOW_SIZE) * sizeof(packet));
    wpkt_num = 0;
    current_pkt = 0;

    expected_ack = 0;

    ack = -1;
    
    msg_seq = 0;
    buffer = (message*) malloc((BUFFER_SIZE) * sizeof(message));
    memset(buffer, 0, (BUFFER_SIZE) * sizeof(message));
    bmsg_num = 0;

    fprintf(stdout, "At %.2fs: sender initializing ...\n", GetSimulationTime());
}

/* sender finalization, called once at the very end.
   you may find that you don't need it, in which case you can leave it blank.
   in certain cases, you might want to take this opportunity to release some
   memory you allocated in Sender_init(). */
void Sender_Final()
{
    /* don't forget to free the space */
    for(int i = 0; i < BUFFER_SIZE; i++) {
        if(buffer[i].size != 0) free(buffer[i].data);
    }
    free(buffer);
    free(window);
    fprintf(stdout, "At %.2fs: sender finalizing ...\n", GetSimulationTime());
}

/* event handler, called when a message is passed from the upper layer at the sender 
 * use go-back-n method
 */
void Sender_FromUpperLayer(struct message *msg)
{
    /* 11-byte header for first packet of msg
     * |<-  2 byte  ->|<-  4 byte  ->|<-  1 byte  ->|<- 4 byts ->|  the rest            ->|
     * |<- checksum ->|<-seq number->| payload size |<-msg size->|  payload             ->| 
     */ 
    /* 7-byte header for rest packets of msg
     * |<-  2 byte  ->|<-  4 byte  ->|<-  1 byte  ->|<-             the rest            ->|
     * |<- checksum ->|<-seq number->| payload size |<-             payload             ->| 
     */
    /* if message is too many */
    if(bmsg_num > BUFFER_SIZE){
        ASSERT(0);
        fprintf(stdout, "too many msg in buffer");
    }

    /* save massage in buffer, also save msg->size to its data*/
    if(buffer[msg_seq % BUFFER_SIZE].size != 0) 
        free(buffer[msg_seq % BUFFER_SIZE].data);
    buffer[msg_seq % BUFFER_SIZE].size = msg->size + sizeof(int);
    buffer[msg_seq % BUFFER_SIZE].data = (char *) malloc(msg->size + sizeof(int));
    memcpy(buffer[msg_seq % BUFFER_SIZE].data, &msg->size, sizeof(int));
    memcpy(buffer[msg_seq % BUFFER_SIZE].data + sizeof(int), msg->data, msg->size);
    msg_seq++;
    bmsg_num++;

    /* not timeout yet */
    if(Sender_isTimerSet()) return;

    Sender_StartTimer(TIMEOUT);

    Sender_SendPacket();
}

/* event handler, called when a packet is passed from the lower layer at the
   sender */
void Sender_FromLowerLayer(struct packet *pkt)
{
    /* checksum */
    short sum;
    memcpy(&sum, pkt->data, sizeof(short));
    if(sum != checksum(pkt)) return;

    memcpy(&ack, pkt->data + sizeof(short), sizeof(int));
    if(ack > pkt_seq) pkt_seq = ack+1;
    /* receiver send ack in order, so it's doesn't matter if ack < expected */
    if(expected_ack <= ack && ack < pkt_seq){
        /* receive an ack and move the wimdow */
        Sender_StartTimer(TIMEOUT);
        wpkt_num -= (ack - expected_ack + 1);
        expected_ack = ack + 1;
        Sender_SendPacket();
    }

    if(ack == pkt_seq - 1) Sender_StopTimer();
}

/* event handler, called when the timer expires */
void Sender_Timeout()
{
    Sender_StartTimer(TIMEOUT);
    current_pkt = expected_ack;
    Sender_SendPacket();
}