package WAVLTree;

import java.util.Random;

import WAVLTree.WAVLTree.IWAVLNode;
import WAVLTree.WAVLTree.WAVLNode;



public class WAVLTester {

    public static int NUM_OF_OPERATIONS = 1000;

    public static void main(String[] args) {
        WAVLTree t = new WAVLTree();
        for (int i = 0; i < NUM_OF_OPERATIONS; i++) {
            insert(t, getRandInt(0, NUM_OF_OPERATIONS));
            check(t);
            checkMinMax(t);
        }
        for (int i = 0; i < NUM_OF_OPERATIONS; i++) {
            delete(t, getRandInt(0, NUM_OF_OPERATIONS));
            check(t);
        }
        check(t);
        checkMinMax(t);
    }

    public static void check(WAVLTree t) {
        if (!isBST(t) || !isWAVL(t) || !isSizeConsistent(t)) {
            System.out.println("isBST: \t\t\t" + isBST(t));
            System.out.println("isAVL: \t\t\t" + isAVL(t));
            System.out.println("isWAVL: \t\t" + isWAVL(t));
            System.out.println("isSizeConsistent: \t" + isSizeConsistent(t));
        }
    }

    public static void checkMinMax(WAVLTree t) {
        if (!checkMin(t) || !checkMax(t)) {
            System.out.println("checkMin: \t\t\t" + checkMin(t));
            System.out.println("checkMax: \t\t\t" + checkMax(t));
        }
    }

    private static boolean checkMin(WAVLTree t) {
        String res1 = min(t.getRoot()).getValue();
        String res2 = t.min();
        return (res1 == null && res2 == null) || (res1.equals(res2));
    }

    private static boolean checkMax(WAVLTree t) {
        String res1 = max(t.getRoot()).getValue();
        String res2 = t.max();
        return (res1 == null && res2 == null) || (res1.equals(res2));
    }

    public static void insert(WAVLTree t, int k) {
        int res = t.insert(k, Integer.toString(k));
        System.out.println("Insert: " + k + ", Count: " + res);
    }

    public static void delete(WAVLTree t, int k) {
        int res = t.delete(k);
        System.out.println("Delete: " + k + ", Count: " + res);
    }

    public static int getRandInt(int min, int max) {
        Random rand = new Random();
        return rand.nextInt(max - min) + min;
    }

    /**
     * Returns the number of nodes in the subtree.
     * 
     * @param x
     *            the subtree
     * 
     * @return the number of nodes in the subtree
     */
    private static int size(IWAVLNode x) {
        return x == null ? 0 : x.getSubtreeSize();
    }

    /**
     * Checks if AVL property is consistent.
     * 
     * @return true if AVL property is consistent.
     */
    private static boolean isAVL(WAVLTree t) {
        return isAVL(t.getRoot());
    }

    /**
     * Checks if AVL property is consistent in the subtree.
     * 
     * @param x
     *            the subtree
     * @return true if AVL property is consistent in the subtree
     */
    private static boolean isAVL(IWAVLNode x) {
        if (x == null || !x.isRealNode())
            return true;
        if (!isAVLNode(x)) {
            return false;
        }
        return isAVL(x.getLeft()) && isAVL(x.getRight());
    }

    private static boolean isAVLNode(IWAVLNode x) {
        if (x == null || !x.isRealNode()) {
            return true;
        }
        int leftRank = x.getLeft() == null ? -1 : ((WAVLNode)x.getLeft()).getRank();
        int leftDiff = ((WAVLNode)x).getRank() - leftRank;
        int rightRank = x.getRight() == null ? -1 : ((WAVLNode)x.getRight()).getRank();
        int rightDiff = ((WAVLNode)x).getRank() - rightRank;
        boolean is11Node = leftDiff == 1 && rightDiff == 1;
        boolean is12Node = leftDiff == 1 && rightDiff == 2;
        boolean is21Node = leftDiff == 2 && rightDiff == 1;
        return is11Node || is12Node || is21Node;
    }

    /**
     * Checks if WAVL property is consistent.
     * 
     * @return true if WAVL property is consistent.
     */
    private static boolean isWAVL(WAVLTree t) {
        return isWAVL(t.getRoot());
    }

    /**
     * Checks if WAVL property is consistent in the subtree.
     * 
     * @param x
     *            the subtree
     * @return true if WAVL property is consistent in the subtree
     */
    private static boolean isWAVL(IWAVLNode x) {
        if (x == null || !x.isRealNode())
            return true;
        if (!isWAVLNode(x)) {
            return false;
        }
        return isWAVL(x.getLeft()) && isWAVL(x.getRight());
    }

    private static boolean isWAVLNode(IWAVLNode x) {
        if (x == null || !x.isRealNode()) {
            return true;
        }
        int leftRank = x.getLeft() == null ? -1 : ((WAVLNode)x.getLeft()).getRank();
        int leftDiff = ((WAVLNode)x).getRank() - leftRank;
        int rightRank = x.getRight() == null ? -1 : ((WAVLNode)x.getRight()).getRank();
        int rightDiff = ((WAVLNode)x).getRank() - rightRank;
        boolean is11Node = leftDiff == 1 && rightDiff == 1;
        boolean is12Node = leftDiff == 1 && rightDiff == 2;
        boolean is21Node = leftDiff == 2 && rightDiff == 1;
        boolean is22Node = leftDiff == 2 && rightDiff == 2;
        return is11Node || is12Node || is21Node || is22Node;
        // return (leftDiff >= 1 && leftDiff <= 2 && rightDiff >= 1 && rightDiff
        // <= 2);
    }

    /**
     * Checks if the symmetric order is consistent.
     * 
     * @return true if the symmetric order is consistent
     */
    private static boolean isBST(WAVLTree t) {
        return isBST(t.getRoot(), Integer.MIN_VALUE, Integer.MAX_VALUE);
    }

    /**
     * Checks if the tree rooted at x is a BST with all keys strictly between
     * min and max
     * 
     * @param x
     *            the subtree
     * @param min
     *            the minimum key in subtree
     * @param max
     *            the maximum key in subtree
     * @return true if the symmetric order is consistent
     */
    private static boolean isBST(IWAVLNode x, int min, int max) {
        if (x == null || !x.isRealNode())
            return true;
        if (x.getKey() < min || x.getKey() > max)
            return false;
        return isBST(x.getLeft(), min, x.getKey()) && isBST(x.getRight(), x.getKey(), max);
    }

    /**
     * Checks if size is consistent.
     * 
     * @return true if size is consistent
     */
    private static boolean isSizeConsistent(WAVLTree t) {
        return isSizeConsistent(t.getRoot());
    }

    /**
     * Checks if the size of the subtree is consistent.
     * 
     * @return true if the size of the subtree is consistent
     */
    private static boolean isSizeConsistent(IWAVLNode x) {
        if (x == null || !x.isRealNode())
            return true;
        if (size(x) != size(x.getLeft()) + size(x.getRight()) + 1)
            return false;
        return isSizeConsistent(x.getLeft()) && isSizeConsistent(x.getRight());
    }

    private static IWAVLNode min(IWAVLNode x) {
        while (x.getLeft() != null && x.isRealNode()) {
            x = x.getLeft();
        }
        return x;
    }

    private static IWAVLNode max(IWAVLNode x) {
        while (x.getRight() != null && x.isRealNode()) {
            x = x.getRight();
        }
        return x;
    }
}