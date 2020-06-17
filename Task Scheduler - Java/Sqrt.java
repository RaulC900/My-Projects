package TemaPOO;

public class Sqrt {
	
	public Sqrt() {
		
	}
	
	/**
	 * Returns the floor of a sqrt
	 *  of the absoulte of a number
	 * @param nrprimit Number given as parameter
	 * @return Floor(sqrt(abs(nrprimit)))
	 */
	
	public int floorSqrt(int nrprimit) {
		if(nrprimit < 0) {
			nrprimit = -nrprimit;
		}
		return (int) Math.floor(Math.sqrt(nrprimit));
	}
}