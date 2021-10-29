public class Lookup {
    public AST lookup(String name, AST ds) {
		if(ds instanceof MtSub) {
            System.out.println("free identifier");
            System.exit(0);
        }
        
        if(ds instanceof Asub) {
            Asub aSub = (Asub)ds;

            if(aSub.getI() == name) {
                return aSub.getV();
            } else {
                return (lookup(name, aSub.getDefrdSub()));    
            }
        }
        

		return null;
        
	}
}
