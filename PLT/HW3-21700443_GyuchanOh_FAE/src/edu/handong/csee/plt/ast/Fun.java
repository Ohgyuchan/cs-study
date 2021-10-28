package edu.handong.csee.plt.ast;

public class Fun extends AST{
	AST p;
	AST b = new AST();
	
	public Fun(AST p, AST b){
		this.p = p;
        this.b = b;
	}
	
	public AST getParam() {
		return p;
	}
	
    public AST getBody() {
		return b;
	}
	
	public String getASTCode() {
		return "(fun '" + p.getASTCode() + b.getASTCode() + ")";
	}
}
