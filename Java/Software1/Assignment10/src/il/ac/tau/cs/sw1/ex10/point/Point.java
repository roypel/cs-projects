package il.ac.tau.cs.sw1.ex10.point;

import java.util.List;
import java.util.*;

public class Point {
	Integer x;
	Integer y;
	Point(int x,int y)
	{
		this.x=x;
		this.y=y;
	}
	
	public static void main(String[] args) {
		
		List<Point> points = new ArrayList<Point>();
		points.add(new Point(10,2));
		points.add(new Point(5,3));
		points.add(new Point(7,6));
		
		Collections.sort(points,(a,b)->a.x.compareTo(b.x));

    }
}
