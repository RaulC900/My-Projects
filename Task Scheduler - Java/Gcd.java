package TemaPOO;

public class Gcd {
	
	/**
	 * Returns the gcd of two numbers
	 * @param nr1 first parameter
	 * @param nr2 second parameter
	 * @return greatest common divisor of the two
	 */
	
	public int cmmdc(int nr1, int nr2)
	{
		if(nr2 == 0) {
			return nr1;
		}
		if(nr1 == 0) {
			return nr2;
		}
	    while (nr2 > 0) // Algoritumul lui Euclid
	    {
	        int temporar = nr1 % nr2;
	        nr1 = nr2;
	        nr2 = temporar;
	    }
	    return nr1;
	}
	
	/**
	 * Returns the gcd of an array of numbers
	 * @param currWeight The current weight from the array
	 * @return Greatest common divisor of the numbers from the array
	 */
	
	public int cmmdcMultipleValues(int[] currWeight)
	{
	    int result = currWeight[0];
	    for(int i = 1; i < currWeight.length; i++) {
	    	result = cmmdc(result, currWeight[i]);
	    }
	    return result;
	}
}
