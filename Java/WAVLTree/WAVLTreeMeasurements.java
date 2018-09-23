package WAVLTree;


import java.util.ArrayList;
import java.util.Collections;
import java.util.Random;

public class WAVLTreeMeasurements {

    public static int N = 10;
    public static int NUM_OF_OPERATIONS = 10000 * N;

    public static void main(String[] args) {

        ArrayList<Integer> unsorted = new ArrayList<>(NUM_OF_OPERATIONS);
        for (int i = 0; i < NUM_OF_OPERATIONS; i++) {
            unsorted.add(i);
        }

        ArrayList<Integer> sorted = new ArrayList<Integer>(unsorted);

        Collections.shuffle(unsorted);

        WAVLTree t = new WAVLTree();
        int sumOperationsOfInsertions = 0;
        int maxOperationsOfInsertions = 0;
        for (int i = 0; i < NUM_OF_OPERATIONS; i++) {
            int n = insert(t, unsorted.get(i));
            sumOperationsOfInsertions += n;
            if (n > maxOperationsOfInsertions) {
                maxOperationsOfInsertions = n;
            }
        }
        System.out.println("Max num of operations of insertions: " + maxOperationsOfInsertions);
        System.out.println(
                "Avg num up operations of insertions: " + ((double) sumOperationsOfInsertions / NUM_OF_OPERATIONS));

        int sumOperationsOfDeletions = 0;
        int maxOperationsOfDeletions = 0;

        for (int i = 0; i < NUM_OF_OPERATIONS; i++) {
            int n = delete(t, sorted.get(i));
            sumOperationsOfDeletions += n;
            if (n > maxOperationsOfDeletions) {
                maxOperationsOfDeletions = n;
            }
        }
        System.out.println("Max num of operations of deletions: " + maxOperationsOfDeletions);
        System.out.println(
                "Avg num up operations of deletions: " + ((double) sumOperationsOfDeletions / NUM_OF_OPERATIONS));
    }

    public static int getRandInt(int min, int max) {
        Random rand = new Random();
        return rand.nextInt(max - min) + min;
    }

    public static int insert(WAVLTree t, int k) {
        int res = t.insert(k, Integer.toString(k));
        return res;
    }

    public static int delete(WAVLTree t, int k) {
        int res = t.delete(k);
        return res;
    }
}
