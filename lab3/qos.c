#include "rte_common.h"
#include "rte_mbuf.h"
#include "rte_meter.h"
#include "rte_red.h"

#include "qos.h"


struct rte_meter_srtcm app_flows[APP_FLOWS_MAX];
struct rte_meter_srtcm_params app_srtcm_params[APP_FLOWS_MAX] = {
    {.cir = 10000000000,  .cbs = 10000, .ebs = 10000},
};

struct rte_red_config  red_params[e_RTE_METER_COLORS];                      
struct rte_red         red_datas[APP_FLOWS_MAX][e_RTE_METER_COLORS];        
unsigned               red_queues[APP_FLOWS_MAX][e_RTE_METER_COLORS] = {};  

int
qos_meter_init(void)
{
    /* to do */
    uint32_t i, j;
	int ret;
    for(int k =0; k<4; k++){
        app_srtcm_params[k].cir = (1<<(4-k))*10000000000;
        app_srtcm_params[k].cbs = (1<<(3-k))*10000;
        app_srtcm_params[k].ebs = (1<<(3-k))*10000;
    }
	for (i = 0, j = 0; i < APP_FLOWS_MAX;
			i ++, j = (j + 1) % RTE_DIM(app_srtcm_params)) {
		ret = rte_meter_srtcm_config(&app_flows[i], &app_srtcm_params[i]);
		if (ret)
			return ret;
	}

	return 0; 
}

/* use color blind mode, so no need input color */
enum qos_color
qos_meter_run(uint32_t flow_id, uint32_t pkt_len, uint64_t time)
{
    /* to do */
    uint8_t output_color;
    output_color = (uint8_t) rte_meter_srtcm_color_blind_check(&app_flows[flow_id], time, pkt_len);
    return output_color;
}


/**
 * WRED
 */

int
qos_dropper_init(void)
{
    /* to do */
    int ret;
    enum qos_color color;
    for(color = GREEN; color < RED; color++){
        ret = rte_red_config_init(&red_params[(color)], 9, 1022, 1023, 10);
        if (ret) 
            return ret;
        int i; 
        for (i = 0; i < APP_FLOWS_MAX; ++i) 
            if (rte_red_rt_data_init(&red_datas[i][(color)]) != 0) 
                rte_panic("Cannot init RED data\n"); 
    }
    // color == RED
    ret = rte_red_config_init(&red_params[(color)], 9, 0, 1, 10);
        if (ret) 
            return ret;
    int i; 
    for (i = 0; i < APP_FLOWS_MAX; ++i) 
        if (rte_red_rt_data_init(&red_datas[i][(color)]) != 0) 
            rte_panic("Cannot init RED data\n"); 
    return 0;
}

int
qos_dropper_run(uint32_t flow_id, enum qos_color color, uint64_t time)
{
    /* to do */
    static uint64_t last_time = 0; 
    // time change
    if (time != last_time) { 
        memset(red_queues, 0, sizeof(red_queues));
        for (int i = 0; i < APP_FLOWS_MAX; i++)
            for (int j = 0; j < e_RTE_METER_COLORS; j++)
                rte_red_mark_queue_empty(&red_datas[i][j], time); 
    }

    last_time = time;

    // Decides
    int result = rte_red_enqueue(&red_params[color], &red_datas[flow_id][color], 
                                 red_queues[flow_id][color], time);

    // drop it
    if (!result)
        red_queues[flow_id][color]++;

    return result;
}