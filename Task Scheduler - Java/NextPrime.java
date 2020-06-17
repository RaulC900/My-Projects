package TemaPOO;

public class NextPrime {
	

	public NextPrime() {
		
	}
	
	/**
	 * Returns the next prime number
	 * @param numar Number given as parameter
	 * @return Next prime number after "numar"
	 */
	
	public int nextPrime(int numar) {
		CheckPrime prime = new CheckPrime();
		if(numar <= 0) {
			return 2;
		}
		numar ++;
		while (prime.primeNumber(numar) == false) {
		    numar++;
		}      
		return numar;
	}
	
}
