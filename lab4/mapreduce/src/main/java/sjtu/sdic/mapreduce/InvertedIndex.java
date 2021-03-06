package sjtu.sdic.mapreduce;

import org.apache.commons.io.filefilter.WildcardFileFilter;
import sjtu.sdic.mapreduce.common.KeyValue;
import sjtu.sdic.mapreduce.core.Master;
import sjtu.sdic.mapreduce.core.Worker;

import java.io.File;
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * Created by Cachhe on 2019/4/24.
 */
public class InvertedIndex {

    public static List<KeyValue> mapFunc(String file, String value) {
        Pattern pattern = Pattern.compile("[a-zA-Z0-9]+");
        Matcher matcher = pattern.matcher(value);
        List<KeyValue> list = new ArrayList<>();
        while (matcher.find()){
            String word = matcher.group();
            list.add(new KeyValue(word, file));
        }
        return list;
    }

    public static String reduceFunc(String key, String[] values) {
        TreeSet<String> treeSet = new TreeSet<>();
        int l = values.length;
        for(int i=0; i<l; i++){
            treeSet.add(values[i]);
        }

        StringBuilder res = new StringBuilder();
        int tl = treeSet.size();
        res.append(tl);
        res.append(" ");
        for (String value:treeSet){
            res.append(value);
            res.append(',');
        }
        res.deleteCharAt(res.lastIndexOf(","));
        return res.toString();

    }

    public static void main(String[] args) {
        if (args.length < 3) {
            System.out.println("error: see usage comments in file");
        } else if (args[0].equals("master")) {
            Master mr;

            String src = args[2];
            File file = new File(".");
            String[] files = file.list(new WildcardFileFilter(src));
            if (args[1].equals("sequential")) {
                mr = Master.sequential("iiseq", files, 3, InvertedIndex::mapFunc, InvertedIndex::reduceFunc);
            } else {
                mr = Master.distributed("wcdis", files, 3, args[1]);
            }
            mr.mWait();
        } else {
            Worker.runWorker(args[1], args[2], InvertedIndex::mapFunc, InvertedIndex::reduceFunc, 100, null);
        }
    }
}
