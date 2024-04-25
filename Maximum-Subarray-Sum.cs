using System.CodeDom.Compiler;
using System.Collections.Generic;
using System.Collections;
using System.ComponentModel;
using System.Diagnostics.CodeAnalysis;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.Serialization;
using System.Text.RegularExpressions;
using System.Text;
using System;

class Result
{

    /*
     * Complete the 'maximumSum' function below.
     *
     * The function is expected to return a LONG_INTEGER.
     * The function accepts following parameters:
     *  1. LONG_INTEGER_ARRAY a
     *  2. LONG_INTEGER m
     */

    public static long maximumSum(List<long> a, long m)
    {
        List<Tuple<long, long>> sums = new List<Tuple<long, long>>(a.Count);
        sums.Add(new Tuple<long, long>(a[0] % m, 1));

        for (int i = 1; i < a.Count; ++i)
        {
            long currentSum = (sums[i - 1].Item1 + a[i] % m) % m;
            sums.Add(new Tuple<long, long>(currentSum, i + 1));
        }

        sums = sums.OrderBy(x => x.Item1).ToList();
        long maxModularSum = sums[sums.Count - 1].Item1;
        long minDiff = long.MaxValue;

        for (int i = 0; i < a.Count - 1; ++i)
        {
            if (sums[i].Item2 > sums[i + 1].Item2)
            {
                long diff = sums[i + 1].Item1 - sums[i].Item1;
                if (diff < minDiff)
                {
                    minDiff = diff;
                }
            }
        }

        return Math.Max(maxModularSum, m - minDiff);
    }

}

class Solution
{
    public static void Main(string[] args)
    {
        TextWriter textWriter = new StreamWriter(@System.Environment.GetEnvironmentVariable("OUTPUT_PATH"), true);

        int q = Convert.ToInt32(Console.ReadLine().Trim());

        for (int qItr = 0; qItr < q; qItr++)
        {
            string[] firstMultipleInput = Console.ReadLine().TrimEnd().Split(' ');

            int n = Convert.ToInt32(firstMultipleInput[0]);

            long m = Convert.ToInt64(firstMultipleInput[1]);

            List<long> a = Console.ReadLine().TrimEnd().Split(' ').ToList().Select(aTemp => Convert.ToInt64(aTemp)).ToList();

            long result = Result.maximumSum(a, m);

            textWriter.WriteLine(result);
        }

        textWriter.Flush();
        textWriter.Close();
    }
}
