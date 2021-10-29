package edu.handong.csee.plt.value;

import edu.handong.csee.plt.ast.AST;

public class Value extends AST{
	
	public String getASTCode() {
		String astCode="";
		
		if(this instanceof NumV)
			astCode = ((NumV)this).getASTCode();
		
		if(this instanceof ClosureV)
			astCode = ((ClosureV)this).getASTCode();
		

		return astCode;
	}
}


