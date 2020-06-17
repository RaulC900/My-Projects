package TemaPOO;

import java.util.Random;

public class MainClass {

	public static void main(String[] args) {
		Random rand = new Random();
		HomeworkReader reader = new HomeworkReader(args[0]);
		HomeworkWriter writer = new HomeworkWriter(args[1]);
		ProblemData data = reader.readData();
		ProcessToBeExecuted proc = new ProcessToBeExecuted();
		int nrProcese = data.getProcesses().length;
		ProcessStructure[] struct = data.getProcesses();
		
		
		if (data.getSchedulerType().equals("RandomScheduler"))
		{
			
			for(int i =0; i < data.getNumbersToBeProcessed().length; i++)
			{
			    int answer = rand.nextInt(nrProcese);
			    int nextNo = data.getNumbersToBeProcessed()[i];
			    int rezultat = proc.processSelection(struct, answer, nextNo);
			    String linie = ""+nextNo+" "+ " " + struct[answer].getType() + " "+rezultat+" Computed";
			    writer.println(linie);
				 
			}
		}else
		if (data.getSchedulerType().equals("RoundRobinScheduler")) // la string folosim equals, pornind cu stringul cu care compar
		{	
			for(int i =0; i < data.getNumbersToBeProcessed().length; i++)
			{
			    int answer = i % nrProcese;
			    int nextNo = data.getNumbersToBeProcessed()[i];
			    int rezultat = proc.processSelection(struct, answer, nextNo);
			    String linie = ""+nextNo+" "+ " " + struct[answer].getType() + " "+rezultat+" Computed";
			    writer.println(linie);
			}
		}else
		if (data.getSchedulerType().equals("WeightedScheduler"))
		{
			int totalWeight = 0;
			Gcd gcd = new Gcd();
			
			for(int j = 0; j < nrProcese; j++) {
				int weight = struct[j].getWeight();
				totalWeight = totalWeight + weight;
			}
			
			int arrayOfWeights[] = new int[nrProcese];
			for(int j = 0; j < nrProcese; j++) {
				arrayOfWeights[j] = struct[j].getWeight();
			}	
			
			int cmmdc = gcd.cmmdcMultipleValues(arrayOfWeights);
			
			int t = totalWeight/cmmdc;
			int index = 0;
			
			
			for(int i = 0; i < nrProcese; i++) {
				for(int j = 0; j < ((struct[i].getWeight()/cmmdc) * data.getNumbersToBeProcessed().length)/t; j++) {
					int nextNo = data.getNumbersToBeProcessed()[index];
					int rezultat = proc.processSelection(struct, i, nextNo);
					String linie = ""+nextNo+" "+ " " + struct[i].getType() + " "+ rezultat +" Computed";
					writer.println(linie);
					index++;
				}
			}
		}
	writer.close();
	}
}