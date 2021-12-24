package edu.handong.csee.plt.ast;

public class NumV extends AST {
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