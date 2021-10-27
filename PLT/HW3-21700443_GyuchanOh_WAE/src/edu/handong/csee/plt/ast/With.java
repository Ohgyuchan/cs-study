package edu.handong.csee.plt.ast;

public class With extends AST{
    AST i = new AST();
	AST v = new AST();
	AST e = new AST();
	
	public With(AST i, AST v, AST e) {
		this.i = i;
        this.v = v;
		this.e = e;
	}

	public AST getI() {
		return i;
	}

    public AST getV() {
		return v;
	}

    public AST getE() {
		return e;
	}

	public String getASTCode() {

		return "(with " + i.getASTCode() + " (" + v.getASTCode()  + e.getASTCode() + "))";
	}
}
