package TemaPOO;

public class CheckPrime {
	
	public CheckPrime() {
		
	}
	
	/**
	 * Returns true if the number is prime 
	 * and false if it is composite
	 * @param numar Number given as parameter
	 * @return Returns true or false
	 */
	
	public boolean primeNumber(int numar) {
		if(numar < 2) {
			return false;
		}
		for(int i = 2; i < numar; i++) {
			if(numar % i == 0) {
				return false;
			}
		}
		return true;
	}
}