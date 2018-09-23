package il.ac.tau.cs.sw1.ex10.point;

import java.util.List;
import java.util.*;

public class Point2 {
	Integer x;
	Integer y;
	Point2(int x,int y)
	{
		this.x=x;
		this.y=y;
	}
	static int compare(Point2 p1, Point2 p2)
	{
		return p1.x-p2.x;
		
	}
	
	public static void main(String[] args) {
		
		List<Point2> points = new ArrayList<Point2>();
		points.add(new Point2(10,2));
		points.add(new Point2(5,3));
		points.add(new Point2(7,6));
		
		Collections.sort(points,(a,b)->compare(a,b));		

    }
}
