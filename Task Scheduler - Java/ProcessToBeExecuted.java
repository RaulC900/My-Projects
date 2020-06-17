package TemaPOO;

public class ProcessToBeExecuted {
	int rezultat;
	
	public ProcessToBeExecuted() {
		this.rezultat = rezultat;
	}
	
	/**
	 * Returns the result of the process that is executed
	 * @param struct Object of the type ProcessStructure[]
	 * @param i Counter in the for in MainClass
	 * @param nextNo Number on which the process is executed
	 * @return Result of the process
	 */
	
	public int processSelection( ProcessStructure[] struct, int i, int nextNo) {
		
		
		int rezultat = 0;
	    if(struct[i].getType().equals("CheckPrime")) {
	    	CheckPrime prime = new CheckPrime();
	    	rezultat = prime.primeNumber(nextNo)?1:0; // ? op ternar
	    }
	    if(struct[i].getType().equals("NextPrime")) {
	    	NextPrime next = new NextPrime();
	    	rezultat = next.nextPrime(nextNo);
	    }
	    if(struct[i].getType().equals("Fibonacci")) {
	    	FibonacciNr fibo = new FibonacciNr();
	    	rezultat = fibo.findFibo(nextNo);
	    }
	    if(struct[i].getType().equals("Sqrt")) {
	    	Sqrt rad = new Sqrt();
	    	rezultat = rad.floorSqrt(nextNo);
	    }
	    if(struct[i].getType().equals("Square")) {
	    	Square sq = new Square();
	    	rezultat = sq.squareOfNumber(nextNo);
	    }
	    if(struct[i].getType().equals("Cube")) {
	    	Cube cube = new Cube();
	    	rezultat = cube.cubeOfNumber(nextNo);
	    }
	    if(struct[i].getType().equals("Factorial")) {
	    	Factorial fact = new Factorial();
	    	rezultat = fact.factorialNr(nextNo);
	    }
	   return rezultat;
	}
}
