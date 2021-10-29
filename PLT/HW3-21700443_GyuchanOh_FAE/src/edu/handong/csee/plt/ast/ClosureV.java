package edu.handong.csee.plt.ast;


public class ClosureV extends AST{
    String p = "";
	AST b = new AST();
	AST defrdSub = new AST();
	
	public ClosureV(String p, AST b, AST defrdSub){
		this.p = p;
		this.b = b;
		this.defrdSub = defrdSub;
	}
	
	public String getParam() {
		return p;
	}

	public AST getBody() {
		return b;
	}

	public AST getDefrdSub() {
		return defrdSub;
	}
	
	public String getASTCode() {
		return "(closureV '" + p + " " + b.getASTCode() + " " + defrdSub.getASTCode() + ")";
	}
}
