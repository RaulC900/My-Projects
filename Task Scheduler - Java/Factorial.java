package TemaPOO;

public class Factorial {
	
	public Factorial() {

	}
	
	/**
	 * Returns the factorial of a number
	 * @param nrprimit Number given as parameter
	 * @return Factorial of the number
	 */
	
	public int factorialNr(int nrprimit) {
		int prod = 1;
		if(nrprimit < 0) {
			return 0;
		}
		else if(nrprimit == 0) {
			return 1;
		}
		else if(nrprimit >= 9973){
			return 0;
		}
		else {
			for(int i = 1; i <= nrprimit; i++) {
				prod = prod * i;
				prod = prod % 9973;
			}
		return prod;
		}
	}
}
