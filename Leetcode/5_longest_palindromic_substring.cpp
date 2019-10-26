class Subseq {
    int start, end, len;

    Subseq(int start, int end) {
        this.start = start;
        this.end = end;
        this.len = end - start + 1;
    }

    boolean isLonger(Subseq s) {
        return len >= s.len;
    }
}

class Solution {
    Subseq expand(String s, int start, int end) {
        if (s.charAt(start) != s.charAt(end)) {
            return new Subseq(start, end - 1);
        }

        while (start >= 0 && end < s.length() && s.charAt(start) == s.charAt(end)) {
            start--;
            end++;
        }
        return new Subseq(start + 1, end - 1);
    }

    public String longestPalindrome(String s) {
        if (s.isEmpty()) {
            return "";
        }
        Subseq maxSeq = new Subseq(0, 0);
        for (int i = 0; i < s.length() - 1; i++) {
            Subseq seq1 = expand(s, i, i);
            Subseq seq2 = expand(s, i, i + 1);

            if (seq1.isLonger(maxSeq)) {
                maxSeq = seq1;
            }
            if (seq2.isLonger(maxSeq)) {
                maxSeq = seq2;
            }
            System.out.println(seq1.start + " " + seq1.end);
            System.out.println(seq2.start + " " + seq2.end);
            System.out.println();
        }
        System.out.println(maxSeq.start + " " + maxSeq.end);
        return s.substring(maxSeq.start, maxSeq.end + 1);
    }

    public static void main(String args[]) {
        String s = new String("cbbd");
        System.out.println(new Solution().longestPalindrome(s));
    }
}
