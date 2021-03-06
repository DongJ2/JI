package sjtu.sdic.mapreduce.core;

import sjtu.sdic.mapreduce.common.Channel;
import sjtu.sdic.mapreduce.common.DoTaskArgs;
import sjtu.sdic.mapreduce.common.JobPhase;
import sjtu.sdic.mapreduce.common.Utils;
import sjtu.sdic.mapreduce.rpc.Call;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;

/**
 * Created by Cachhe on 2019/4/22.
 */
public class Scheduler {

    /**
     * schedule() starts and waits for all tasks in the given phase (mapPhase
     * or reducePhase). the mapFiles argument holds the names of the files that
     * are the inputs to the map phase, one per map task. nReduce is the
     * number of reduce tasks. the registerChan argument yields a stream
     * of registered workers; each item is the worker's RPC address,
     * suitable for passing to {@link Call}. registerChan will yield all
     * existing registered workers (if any) and new ones as they register.
     *
     * @param jobName job name
     * @param mapFiles files' name (if in same dir, it's also the files' path)
     * @param nReduce the number of reduce task that will be run ("R" in the paper)
     * @param phase MAP or REDUCE
     * @param registerChan register info channel
     */
    public static void schedule(String jobName, String[] mapFiles, int nReduce, JobPhase phase, Channel<String> registerChan) {
        int nTasks = -1; // number of map or reduce tasks
        int nOther = -1; // number of inputs (for reduce) or outputs (for map)
        switch (phase) {
            case MAP_PHASE:
                nTasks = mapFiles.length;
                nOther = nReduce;
                break;
            case REDUCE_PHASE:
                nTasks = nReduce;
                nOther = mapFiles.length;
                break;
        }

        System.out.println(String.format("Schedule: %d %s tasks (%d I/Os)", nTasks, phase, nOther));

        //TODO:
        // All ntasks tasks have to be scheduled on workers. Once all tasks
        // have completed successfully, schedule() should return.
        // Your code here (Part III, Part IV).

        //List<boolean> states = new ArrayList<boolean>(nTasks);
        boolean[] taskStatus = new boolean[nTasks];
        for (int i = 0; i < nTasks; i++) {
            taskStatus[i] = false;
        }

        try{
            CountDownLatch latch = new CountDownLatch(nTasks);
            boolean allDone = false;
            while(!allDone) {
                int count = 0;
                allDone = true;
                while (count < nTasks) {
                    if (taskStatus[count]) {
                        count++;
                        continue;
                    }
                    allDone = false;
                    // learn about the set of workers by reading registerChan
                    String worker = registerChan.read();
                    DoTaskArgs doTaskArgs = new DoTaskArgs(jobName, mapFiles[count], phase, count, nOther);

                    new Thread() {
                        public void run() {
                            try {
                                // System.out.println("子线程"+Thread.currentThread().getName()+"正在执行");
                                Call.getWorkerRpcService(worker).doTask(doTaskArgs);
                                taskStatus[doTaskArgs.taskNum] = true;
                                latch.countDown();
                                // am i need to add?
                                registerChan.write(worker);
                                // System.out.println("子线程"+Thread.currentThread().getName()+"执行完毕")
                            } catch (InterruptedException e) {
                                e.printStackTrace();
                            }
                        }
                    }.start();

                    count++;
                }
            }
            latch.await(10000, TimeUnit.MILLISECONDS);
        } catch (InterruptedException e){
            e.printStackTrace();
        }

        System.out.println(String.format("Schedule: %s done", phase));
    }
}
