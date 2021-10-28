package edu.handong.csee.plt;

import edu.handong.csee.plt.defrdSub.Asub;
import edu.handong.csee.plt.defrdSub.DefrdSub;
import edu.handong.csee.plt.defrdSub.MtSub;

public class Lookup {
    public String lookup(String name, DefrdSub ds) {
		if(ds instanceof MtSub) {
            return "" + "free identifier";
        }
        
        if(ds instanceof Asub) {
            Asub aSub = (Asub)ds;
            
            if(aSub.getStrName() instanceof String && name instanceof String) {
                return "" + aSub.getV();
            } else {
                return "" + (lookup(name, aSub.getDefrdSub()));    
            }
        }
        

		return null;
        
	}
}

