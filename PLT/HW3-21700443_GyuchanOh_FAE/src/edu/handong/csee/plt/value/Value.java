package edu.handong.csee.plt.value;

public class Value {
	
	public String getASTCode() {
		String astCode="";
		if(this instanceof NumV)
			astCode = ((NumV)this).getASTCode();
		
		if(this instanceof ClosureV)
			astCode = ((ClosureV)this).getASTCode();
		

		return astCode;
	}
}


