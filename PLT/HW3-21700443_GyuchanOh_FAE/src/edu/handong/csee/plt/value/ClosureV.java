package edu.handong.csee.plt.value;

import edu.handong.csee.plt.ast.AST;
import edu.handong.csee.plt.defrdSub.DefrdSub;


public class ClosureV extends Value{
    String p = "0";
	AST b = new AST();
	DefrdSub defrdSub = new DefrdSub();
	
	public ClosureV(String p, AST b, DefrdSub defrdSub){
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

	public DefrdSub getDefrdSub() {
		return defrdSub;
	}
	
	public String getASTCode() {
		return "(closureV '" + p + " " + b.getASTCode() + " " + defrdSub.getASTCode() + ")";
	}
}
