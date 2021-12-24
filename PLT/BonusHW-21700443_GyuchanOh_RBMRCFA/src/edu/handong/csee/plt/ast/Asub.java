package edu.handong.csee.plt.ast;

public class Asub extends AST{
    String i = "";
    AST v = new AST();
    AST saved = new AST();

	public Asub(String i, AST v, AST saved) {
		this.i = i;
        this.v = v;
        this.saved = saved;
	}
	
	public String getI() {
		return i;
	}

	public AST getV() {
		return v;
	}
    
	public AST getDefrdSub() {
		return saved;
	}
	
    public String getASTCode() {
		return "(Asub " + i + " " + this.getV() +  " " + this.getDefrdSub() + ")";
	}
}
