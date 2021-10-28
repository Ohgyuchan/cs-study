package edu.handong.csee.plt.value;

public class NumV extends Value {
	String numV = "0";
	
	public NumV(String numV){
		this.numV = numV;
	}
	
	public String getStrNumV() {
		return numV;
	}
	
	public String getASTCode() {
		return "(numV " + numV +")";
	}
}