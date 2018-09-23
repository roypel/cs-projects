package il.ac.tau.cs.sw1.hw6;

public class SectionA {
	
			/*
			* @pre a != null
			* @post $ret == true if and only if
			* for all i : a.charAt(i) == a.charAt(a.length() - i - 1)
			*/
			public static boolean isPalindrome(String a) {
				if (a == null)
					return false;
				for (int i = 0; i < a.length()/2; i++){
					if (a.charAt(i) != a.charAt(a.length() - i - 1))
						return false;
				}
				return false;
			}
			
			/*
			* @pre data != null
			* @pre for all i in 0 .. data.length: data[i] != NaN
			* @pre for all i in 0 .. data.length: data[i] != Double.POSITIVE_INFINITY
			* @pre for all i in 0 .. data.length: data[i] != Double.NEGATIVE_INFINITY
			* @post (data.length > 0) $implies $ret = data[0] + data[1] + ... +
			* data[data.length-1]
			* @post (data.length == 0) $implies $ret = 0.0
			*/
			public static double sum(double[] data) {
				double sum = 0.0;
				for (double item : data)
					sum += item;
				return sum;
			}
			
			/*
			* @pre for all i in 0 .. data.length: data[i] != NaN
			* @pre for all i in 0 .. data.length: data[i] != Double.POSITIVE_INFINITY
			* @pre for all i in 0 .. data.length: data[i] != Double.NEGATIVE_INFINITY
			* @post $ret = (data[0] + data[1] + ... + data[data.length-1])/data.length
			*/
			public static double average(double[] data) {
				return sum(data) / data.length;
			}
			
			/*
			* @pre a != 0
			* @post (b^2 - 4ac >= 0) ==> for all x in $ret: a*x*x + b*x + c == 0
			*/
			public static double[] roots(double a, double b, double c) {
				if (a == 0)
					return null;
				double dis = Math.sqrt(b * b - 4 * a * c);
				if (dis < 0)
					return null;
				return new double[] { (-b + dis) / (2 * a), (-b - dis) / (2 * a) };
			}



}
