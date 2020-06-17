package TemaPOO;

public class FibonacciNr {
	
	public FibonacciNr() {
		
	}
	
	/**
	 * Returns the nth fibonacci number modulo 9973
	 * @param n Number given as parameter
	 * @return Nth fibbonaci number modulo 9973
	 */
	
	public int findFibo(int n) {
		int num1 = 0;
		int num2 = 1;
		int fib = 0;
		
		if(n < 0) {
			return -1;
		}
		if(n == 0) {
			return num1;
		}
		else {
			for(int i = 0; i < n-1; i++) {
				fib = num2;
				num2 = (num2 + num1) % 9973;
				num1 = fib;
			}
			return num2;
		}
	}	
}
