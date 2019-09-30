package sjtu.sdic.mapreduce.core;

import com.alibaba.fastjson.JSONArray;
import com.alibaba.fastjson.JSONObject;
import sjtu.sdic.mapreduce.common.KeyValue;
import sjtu.sdic.mapreduce.common.Utils;

import java.io.*;
import java.lang.reflect.Array;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.util.*;

import static sjtu.sdic.mapreduce.common.Utils.reduceName;

/**
 * Created by Cachhe on 2019/4/19.
 */
public class Reducer {

    /**
     * 
     * 	doReduce manages one reduce task: it should read the intermediate
     * 	files for the task, sort the intermediate key/value pairs by key,
     * 	call the user-defined reduce function {@code reduceFunc} for each key,
     * 	and write reduceFunc's output to disk.
     * 	
     * 	You'll need to read one intermediate file from each map task;
     * 	{@code reduceName(jobName, m, reduceTask)} yields the file
     * 	name from map task m.
     *
     * 	Your {@code doMap()} encoded the key/value pairs in the intermediate
     * 	files, so you will need to decode them. If you used JSON, you can refer
     * 	to related docs to know how to decode.
     * 	
     *  In the original paper, sorting is optional but helpful. Here you are
     *  also required to do sorting. Lib is allowed.
     * 	
     * 	{@code reduceFunc()} is the application's reduce function. You should
     * 	call it once per distinct key, with a slice of all the values
     * 	for that key. {@code reduceFunc()} returns the reduced value for that
     * 	key.
     * 	
     * 	You should write the reduce output as JSON encoded KeyValue
     * 	objects to the file named outFile. We require you to use JSON
     * 	because that is what the merger than combines the output
     * 	from all the reduce tasks expects. There is nothing special about
     * 	JSON -- it is just the marshalling format we chose to use.
     * 	
     * 	Your code here (Part I).
     * 	
     * 	
     * @param jobName the name of the whole MapReduce job
     * @param reduceTask which reduce task this is
     * @param outFile write the output here
     * @param nMap the number of map tasks that were run ("M" in the paper)
     * @param reduceFunc user-defined reduce function
     */
    public static void doReduce(String jobName, int reduceTask, String outFile, int nMap, ReduceFunc reduceFunc) {
        // read the intermediate files for the task,
        List<KeyValue> list = new ArrayList<>();
        for(int i = 0; i<nMap; i++){
            String inFile = reduceName(jobName, i, reduceTask);
            String value = "";
            try{
                BufferedReader in = new BufferedReader(new FileReader(inFile));
                String s;
                while((s = in.readLine()) != null)
                    value += s;
            } catch (IOException e) {
                System.out.println(e);
            }
            List l = JSONArray.parseArray(value, KeyValue.class);
            list.addAll(l);
        }
        // sort the intermediate key/value pairs by key
        Collections.sort(list, new Comparator<KeyValue>() {
            @Override
            public int compare(KeyValue kv1, KeyValue kv2) {return kv1.key.compareTo(kv2.key);
            }
        });
        // call the user-defined reduce function {@code reduceFunc} for each key,
        JSONObject jsonObject = new JSONObject();
        List<String> last = new ArrayList<>();
        if(list.size() == 0) return;
        last.add(list.get(0).value);
        for(int i=1; i<list.size(); i++){
            // String比较要用equal
            if(list.get(i).key.equals(list.get(i-1).key) != true){
                String result = reduceFunc.reduce(list.get(i-1).key, last.toArray(new String[last.size()]));
                jsonObject.put(list.get(i-1).key, result);
                last.clear();
            }
            //else{
                last.add(list.get(i).value);
            //}
        }
        String result = reduceFunc.reduce(list.get(list.size()-1).key, last.toArray(new String[last.size()]));
        jsonObject.put(list.get(list.size()-1).key, result);
        last.clear();
        // write reduceFunc's output to disk.
        FileOutputStream fos = null;
        File output = new File(outFile);
        try {
            fos = new FileOutputStream(output);
            String s = jsonObject.toJSONString();
            fos.write(s.getBytes());
            fos.close();
        } catch (Exception e){
            e.printStackTrace();
        }
    }
}
