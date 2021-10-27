package edu.handong.csee.plt.ast;

public class With extends AST{
    AST id = new AST();
	AST named = new AST();
	AST body = new AST();
	
	public With(AST id, AST named, AST body) {
		this.id = id;
        this.named = named;
		this.body = body;
	}

	public AST getId() {
		return id;
	}

    public AST getNamed() {
		return named;
	}

    public AST getBody() {
		return body;
	}

	public String getASTCode() {

		return "(with " + id.getASTCode() + " (" + named.getASTCode()  + body.getASTCode() + "))";
	}
}
