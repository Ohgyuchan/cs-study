package edu.handong.csee.plt.ast;

public class ExprV extends AST {
    AST e = new AST();
	AST ds = new AST();
	
	public ExprV(AST e, AST ds){
		this.e = e;
		this.ds = ds;
	}
	
	public AST getExpr() {
		return e;
	}

	public AST getDefrdSub() {
		return ds;
	}
	
	public String getASTCode() {
		return "(exprV '" + e.getASTCode() + " " + ds.getASTCode() + ")";
	}
}
