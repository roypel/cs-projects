package il.ac.tau.cs.sw1.hw6;

public class Polynomial {
	
	private double[] polynomialCoefficients;
	
	/*
	 * Creates the zero-polynomial with p(x) = 0 for all x.
	 */
	public Polynomial()
	{
		this.polynomialCoefficients = new double [1];
	} 
	/*
	 * Creates a new polynomial with the given coefficients.
	 */
	public Polynomial(double[] coefficients) 
	{
		double[] newCoefficients;
		if (coefficients[coefficients.length-1] == 0)
			newCoefficients = cutTail(coefficients);
		else{
			newCoefficients = new double[coefficients.length];
			for (int i = 0; i < newCoefficients.length; i++){
				newCoefficients[i] = coefficients[i];
				}
			}
		this.polynomialCoefficients = newCoefficients;
	}
	/*
	 * Checks if the given polynomial is the zero-polynomial
	 */
	private boolean isZeroPolynomial(Polynomial polynomial){
		if ((polynomial.polynomialCoefficients.length == 1) && (polynomial.polynomialCoefficients[0] == 0.0))
				return true;
		return false;
	}
	/*
	 * Adds a tail of polynomial, assume that from start point the polynomial is only zeroes,
	 * and both arrays are same length.
	 */
	private double[] addTail(int start, double[] polynomial, double[] tail){
		for (int i = start; i < polynomial.length; i++){
			polynomial[i] = tail[i];
		}
		return polynomial;
	}
	/*
	 * The function cuts the "tail" of the polynomial
	 * and leaves only the highest degree
	 */
	private double[] cutTail(double[] coefficients){
		if (coefficients[coefficients.length-1] != 0.0)
			return coefficients;
		int i = coefficients.length-1;
		while (i > 0){
			if (coefficients[i] != 0.0)
				break;
			i--;
		}
		double[] newCoefficients = new double[i+1];
		for (i = 0; i < newCoefficients.length; i++){
			newCoefficients[i] = coefficients[i];
		}
		return newCoefficients;
	}
	/*
	 * Adds this polynomial to the given one
	 *  and returns the sum as a new polynomial.
	 */	
	public Polynomial adds(Polynomial polynomial)
	{
		if (isZeroPolynomial(this))
			return polynomial;
		if (isZeroPolynomial(polynomial))
			return this;
		int thisDegree = this.getDegree();
		int otherDegree = polynomial.getDegree();
		double[] newPolynomial = new double[Math.max(thisDegree, otherDegree) + 1];//Polynomial degree is at most the maximum degree between the 2 polynomials
		for (int i = 0; i < Math.min(thisDegree, otherDegree) + 1; i++){//Add only up to the shortest polynomial, or else pointer exception error
			newPolynomial[i] = this.polynomialCoefficients[i] + polynomial.polynomialCoefficients[i];
		}
		if (thisDegree > otherDegree){//add remaining part to the polynomial
			addTail(otherDegree + 1, newPolynomial, this.polynomialCoefficients);
		}
		else if(otherDegree > thisDegree){
			addTail(thisDegree + 1, newPolynomial, polynomial.polynomialCoefficients);
		}
		newPolynomial = cutTail(newPolynomial);
		if (newPolynomial.length == 0)
			return new Polynomial();
		return new Polynomial(newPolynomial);
	}
	/*
	 * Multiplies a to this polynomial and returns 
	 * the result as a new polynomial.
	 */
	public Polynomial multiply(double a)
	{
		if (a == 0.0)
			return new Polynomial();
		double[] newPolynomial = new double[this.getDegree() + 1];
		for (int i = 0; i < newPolynomial.length; i++){
			newPolynomial[i] = a * this.polynomialCoefficients[i];
		}
		return new Polynomial(newPolynomial);
	}
	/*
	 * Returns the degree (the largest exponent) of this polynomial.
	 */
	public int getDegree()
	{
		return this.polynomialCoefficients.length-1;
	}
	/*
	 * Returns the coefficient of the variable x 
	 * with degree n in this polynomial.
	 */
	public double getCoefficient(int n)
	{
		return this.polynomialCoefficients[n];
	}
	
	/*
	 * Returns the first derivation of this polynomial.
	 *  The first derivation of a polynomial a0x0 + ...  + anxn is defined as 1 * a1x0 + ... + n anxn-1.
	 */
	public Polynomial getFirstDerivation()
	{
		double[] newPolynomial = new double[this.getDegree()];
		for (int i = 0; i < newPolynomial.length; i++){
			newPolynomial[i] = (i+1) * this.polynomialCoefficients[i+1];
		}
		return new Polynomial(newPolynomial);
	}
	
	/*
	 * given an assignment for the variable x,
	 * compute the polynomial value
	 */
	public double computePolynomial(int x)
	{
		if (x == 0)
			return 0.0;
		double result = 0;
		for (int i = 0; i < this.polynomialCoefficients.length; i++){
			result += this.polynomialCoefficients[i] * Math.pow(x, i);
		}
		return result;
	}
	
	
	
	

    
    

}
