package sjtu.sdic.mapreduce.core;

import com.alibaba.fastjson.JSONArray;
import sjtu.sdic.mapreduce.common.KeyValue;
import sjtu.sdic.mapreduce.common.Utils;

import java.io.*;
import java.nio.file.Files;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import static sjtu.sdic.mapreduce.common.Utils.reduceName;

/**
 * Created by Cachhe on 2019/4/19.
 */
public class Mapper {

    /**
     * doMap manages one map task: it should read one of the input files
     * {@code inFile}, call the user-defined map function {@code mapFunc} for
     * that file's contents, and partition mapFunc's output into {@code nReduce}
     * intermediate files.
     *
     * There is one intermediate file per reduce task. The file name
     * includes both the map task number and the reduce task number. Use
     * the filename generated by {@link Utils#reduceName(String, int, int)}
     * as the intermediate file for reduce task r. Call
     * {@link Mapper#hashCode(String)} on each key, mod nReduce,
     * to pick r for a key/value pair.
     *
     * {@code mapFunc} is the map function provided by the application. The first
     * argument should be the input file name, though the map function
     * typically ignores it. The second argument should be the entire
     * input file contents. {@code mapFunc} returns a list containing the
     * key/value pairs for reduce; see {@link KeyValue} for the definition of
     * KeyValue.
     *
     * Look at Java's File and Files API for functions to read
     * and write files.
     *
     * Coming up with a scheme for how to format the key/value pairs on
     * disk can be tricky, especially when taking into account that both
     * keys and values could contain newlines, quotes, and any other
     * character you can think of.
     *
     * One format often used for serializing data to a byte stream that the
     * other end can correctly reconstruct is JSON. You are not required to
     * use JSON, but as the output of the reduce tasks *must* be JSON,
     * familiarizing yourself with it here may prove useful. There're many
     * JSON-lib for Java, and we recommend and supply with FastJSON powered by
     * Alibaba. You can refer to official docs or other resources to figure
     * how to use it.
     *
     * The corresponding decoding functions can be found in {@link Reducer}.
     *
     * Remember to close the file after you have written all the values!
     *
     * Your code here (Part I).
     *
     * @param jobName the name of the MapReduce job
     * @param mapTask which map task this is
     * @param inFile file name (if in same dir, it's also the file path)
     * @param nReduce the number of reduce task that will be run ("R" in the paper)
     * @param mapFunc the user-defined map function
     */
    public static void doMap(String jobName, int mapTask, String inFile, int nReduce, MapFunc mapFunc) {
        // read file
        String value = "";
        try{
            // Files.readAllBytes(Path)方法把整个文件读入内存，此方法返回一个字节数组，
            // 还可以把结果传递给String的构造器，以便创建字符串输出。
            // 在针对大文件的读取的时候，可能会出现内存不足，导致堆溢出
            value = new String(Files.readAllBytes(new File(inFile).toPath()));
        } catch (IOException e) {
            System.out.println(e);
        }
        // call the user-defined map function and partition
        List<KeyValue> list = mapFunc.map(inFile, value);
        List<KeyValue>[] partition_lists = new List[nReduce];
        for (int i = 0; i < nReduce; i++)
            partition_lists[i] = new ArrayList<>();
        for(int i=0; i<list.size(); i++){
            int r = hashCode(list.get(i).key);
            r = r%nReduce;
            partition_lists[r].add(list.get(i));
        }
        //generate intermediate files.
        FileOutputStream fos = null;
        for(int i = 0; i < nReduce; i++){
            String ifname = reduceName(jobName, mapTask, i);
            File output = new File(ifname);
            try {
                fos = new FileOutputStream(output);
                String s = JSONArray.toJSONString(partition_lists[i]);
                fos.write(s.getBytes());
            } catch (Exception e){
                e.printStackTrace();
            } finally {
                if (fos != null) {
                    try {
                        fos.close();
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            }
        }
    }

    /**
     * a simple method limiting hash code to be positive
     *
     * @param src string
     * @return a positive hash code
     */
    private static int hashCode(String src) {
        return src.hashCode() & Integer.MAX_VALUE;
    }
}
