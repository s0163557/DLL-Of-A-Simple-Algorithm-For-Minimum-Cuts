using System.Runtime.InteropServices;
using System;

internal class Program
{
    private static void Main(string[] args)
    {
        [DllImport("MCDLL.dll", CallingConvention = CallingConvention.Cdecl)]
        // Where n - amount of vertices, m - amount of edges.
        // The edges are represented as v1 - v2 - w, where v1 and v2 are vertices, and w is the weight of the edge. 
        // The variable d is the exponent in the probability of success 1 − 1/(n)^d for Algorithm 2. 
        static extern double MinCutStart(int n, int m, int[,] edges, double d);
        int[,] test = new int[,] 
        { 
            {0, 1, 1}, 
            {1, 2, 1}, 
            {2, 3, 1}, 
            {1, 3, 1}, 
            {0, 2, 1}, 
            {0, 3, 1}, 
            {4, 1, 1}, 
            {4, 0, 1}
        };
        Console.WriteLine(MinCutStart(5, 8, test, 1));
    }
}