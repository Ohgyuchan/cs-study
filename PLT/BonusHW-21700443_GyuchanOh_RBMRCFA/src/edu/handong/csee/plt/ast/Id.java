package edu.handong.csee.plt.ast;

public class Id extends AST{
    String name = "";
	
	public Id(String name){
		this.name = name;
	}
	
	public String getStrName() {
		return name;
	}
	
	public String getASTCode() {
		return "(id '" + name +")";
	}
}
