import java.io.*;
import java.math.*;
import java.security.*;
import java.text.*;
import java.util.*;
import java.util.concurrent.*;
import java.util.function.*;
import java.util.regex.*;
import java.util.stream.*;
import static java.util.stream.Collectors.joining;
import static java.util.stream.Collectors.toList;

class Result {

    /*
     * Complete the 'maximumSum' function below.
     *
     * The function is expected to return a LONG_INTEGER.
     * The function accepts following parameters:
     *  1. LONG_INTEGER_ARRAY a
     *  2. LONG_INTEGER m
     */

    public static long maximumSum(List<Long> a, long m) {
        TreeSet<Long> sums = new TreeSet<>();
        long sum = 0;
        long max_modular_sum = 0;

        for (long num : a) {
            sum = (sum + num) % m;
            Long higher = sums.higher(sum);

            if (higher != null) {
                max_modular_sum = Math.max(max_modular_sum, (sum - higher + m) % m);
            }

            sums.add(sum);
            max_modular_sum = Math.max(max_modular_sum, sum);
        }

        return max_modular_sum;
    }
    
    public static long maximumSum2(List<Long> a, long m) {
    // Write your code here
        int n = a.size();
        long[][] sums = new long[n][2];
        sums[0][0] = a.get(0) % m;
        sums[0][1] = 1;

        for (int i = 1; i < n; ++i) {
            sums[i][0] = (sums[i - 1][0] + a.get(i) % m) % m;
            sums[i][1] = i + 1;
        }

        Arrays.sort(sums, (x, y) -> Long.compare(x[0], y[0]));

        long maxModularSum = sums[n - 1][0];
        long minDiff = Long.MAX_VALUE;

        for (int i = 0; i < n - 1; ++i) {
            if (sums[i][1] > sums[i + 1][1]) {
                long diff = sums[i + 1][0] - sums[i][0];
                if (diff < minDiff) {
                    minDiff = diff;
                }
            }
        }

        return Math.max(maxModularSum, m - minDiff);
    }

}

public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

        int q = Integer.parseInt(bufferedReader.readLine().trim());

        IntStream.range(0, q).forEach(qItr -> {
            try {
                String[] firstMultipleInput = bufferedReader.readLine().replaceAll("\\s+$", "").split(" ");

                int n = Integer.parseInt(firstMultipleInput[0]);

                long m = Long.parseLong(firstMultipleInput[1]);

                List<Long> a = Stream.of(bufferedReader.readLine().replaceAll("\\s+$", "").split(" "))
                    .map(Long::parseLong)
                    .collect(toList());

                long result = Result.maximumSum(a, m);

                bufferedWriter.write(String.valueOf(result));
                bufferedWriter.newLine();
            } catch (IOException ex) {
                throw new RuntimeException(ex);
            }
        });

        bufferedReader.close();
        bufferedWriter.close();
    }
}
