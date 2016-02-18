import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;


public class RouteExtractionSpring {

	/**
	 * @param args
	 */
	public static Map<String, ArrayList> Routes = new HashMap<String, ArrayList>();
	public static Map<String, ArrayList> SID_R = new HashMap<String, ArrayList>();
	
	
	//routeids are unique (associated with only one route
	public static void intervalRouteID() throws FileNotFoundException{
		String csvFile = "D:/Fall2015/DataMining/FinalProject/RouteExtraction/RouteID_original_spring.csv";
		BufferedReader br = null;
		String line = "";
		String csvSplitBy = ",";
	//	PrintWriter w = new PrintWriter("D:/Fall2015/DataMining/FinalProject/CodeGeneratedFiles/Stopcode_Geocode/Geocode_"+busIDS.get(i)+".csv");
		PrintWriter w = new PrintWriter("D:/Fall2015/DataMining/FinalProject/RouteExtraction/importRoutes_spring.csv");
		w.println("RouteID,ScheduleID");
		try {
			
			br = new BufferedReader(new FileReader(csvFile));
			line = br.readLine();
			while ((line = br.readLine()) != null) {
				StringBuilder sb = new StringBuilder();
				String[] record = line.split(csvSplitBy);
				String routeID = record[0];
				String routeName = record[1];
				String[] names = routeName.split(" ");
				if(names.length==3){
					//System.out.println(routeName);
					if(names[2].length()>1){
//						System.out.println(names[2]);
						if(names[2].equals("M-R")){
								//System.out.println(names[2]);
								w.println(routeID+","+"M-"+names[0]);
								w.println(routeID+","+"T-"+names[0]);
								w.println(routeID+","+"W-"+names[0]);
								w.println(routeID+","+"R-"+names[0]);
								
							
						}
						else if(names[2].equals("U-S") || names[2].equals("S-U")){
							//System.out.println(names[2]);
							w.println(routeID+","+"S-"+names[0]);
							w.println(routeID+","+"U-"+names[0]);
							
						}
					}
					
					else{
					sb.append(names[2].concat("-"));
					sb.append(names[0]);
					w.println(routeID+","+sb);
					}
					
				}
				else{
					w.println(routeID+","+routeName);
				}
				
				
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (Exception e) {
			
			e.printStackTrace();
		} finally {
			if (br != null) {
				try {
					br.close();
					w.close();
					}
				 catch (IOException e) {
					e.printStackTrace();
				}
			}
		}


		System.out.println("Done writing importRoutes file");

	}
	
	public static void ridershipSpringRouteID() throws FileNotFoundException{
		String csvFile = "D:/Fall2015/DataMining/FinalProject/RouteExtraction/ridershipSpring_original.csv";
		BufferedReader br = null;
		String line = "";
		String csvSplitBy = ",";
		int count = 0;
		PrintWriter w = new PrintWriter("D:/Fall2015/DataMining/FinalProject/RouteExtraction/ridershipSpringRoutes.csv");
		w.println("RouteID,ScheduleID");
		
		try {
			br = new BufferedReader(new FileReader(csvFile));
			line = br.readLine();
			while ((line = br.readLine()) != null) {
				StringBuilder sb = new StringBuilder();
				String[] record = line.split(csvSplitBy);
				String scheduleID = record[0];
				String[] sched = scheduleID.split("-");
			//	System.out.println(scheduleID);
				if(sched.length==2){
					//System.out.println(sched);
					sb.append(sched[0].concat("-"+sched[1].substring(0, 1)));
				}
				else if(sched.length>2){
					sb.append(sched[1].concat("-"));
					sb.append(sched[2].substring(0, 1));
					
				}
				else{
					sb.append(scheduleID);
				}
	//			count+=1;
//				System.out.println(scheduleID+" = "+sb);
				
				/*if(SID_R.containsKey(sb.toString())){
					ArrayList<String> rids = SID_R.get(sb.toString());
					//String sid = sb.toString();
					for(int i=0;i<rids.size();i++){
						w.println(rids.get(i)+","+scheduleID);
					}
				}*/
				
				
				
				if(SID_R.containsKey(sb.toString())){
					ArrayList<String> rids = SID_R.get(sb.toString());
					if(scheduleID.substring(0, 2).equals("EX")){
						rids.add("370");
						rids.add("343");
						
					}	
					
					for(int i=0;i<rids.size();i++){
						w.println(rids.get(i)+","+"SP-"+scheduleID);
					}
				}
				
				else if(sb.toString().equals("Auditorium") && SID_R.containsKey("Aud")){
					ArrayList<String> rids = SID_R.get("Aud");
					for(int i=0;i<rids.size();i++){
						w.println(rids.get(i)+","+"SP-"+scheduleID);
					}
				}
				
				else if(sb.toString().equals("Special") && SID_R.containsKey(" Special")){
					ArrayList<String> rids = SID_R.get(" Special");
					for(int i=0;i<rids.size();i++){
						w.println(rids.get(i)+","+"SP-"+scheduleID);
					}
				}
				else{
					System.out.println(scheduleID+" = "+sb);
					
				}
				
		/*		Iterator iter = SID_R.entrySet().iterator();
				boolean flag = false;
				
			    while (iter.hasNext()) {
			    	
			    	
			        Map.Entry pair = (Map.Entry)iter.next();
			        String key = (String) pair.getKey();
			        if(key.equalsIgnoreCase(sb.toString()) || (key.regionMatches(true, 0, sb.toString(), 0, 3)) && (key.contains("Aud"))){
			        
			        ArrayList<String> rids = (ArrayList<String>) pair.getValue();
			        for(int i=0;i<rids.size();i++){
						w.println(rids.get(i)+","+scheduleID);
					}
			        flag = true;
			        break;
			        
			        }
			        
			        
			        //System.out.println(pair.getKey()+" = "+value.size() + " = " + pair.getValue());
			       // it.remove(); // avoids a ConcurrentModificationException
			    }
			    
			    if(!flag){
			    	
			    	System.out.println(scheduleID+" = "+sb);
			    }
		*/		
				
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (Exception e) {
			
			e.printStackTrace();
		} finally {
			w.close();
			if (br != null) {
				try {
					br.close();
					
					}
				 catch (IOException e) {
					e.printStackTrace();
				}
			}
		}


		System.out.println("Done");
		//System.out.println(count);
	}
	
	public static void intervalRouteGenerateHashmap(){
		String csvFile = "D:/Fall2015/DataMining/FinalProject/RouteExtraction/importRoutes_spring.csv";
		BufferedReader br = null;
		String line = "";
		String csvSplitBy = ",";
		try {
			br = new BufferedReader(new FileReader(csvFile));
			line = br.readLine();
			while ((line = br.readLine()) != null) {
				String[] record = line.split(csvSplitBy);
				String sid = record[1];
				String rid = record[0];
				if(SID_R.get(sid) == null){
	        		ArrayList<String> routeids = new ArrayList<String>();
	        		routeids.add(rid);
	        		SID_R.put(sid, routeids);
	        	}
	        	else{
	        		ArrayList<String> routeids = SID_R.get(sid);
	        		routeids.add(rid);
	        		SID_R.put(sid, routeids);
	        	}
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (Exception e) {
			
			e.printStackTrace();
		} finally {
			if (br != null) {
				try {
					br.close();
					
					}
				 catch (IOException e) {
					e.printStackTrace();
				}
			}
		}


		System.out.println("Done generating interval route hashmap");
		
	}
	public static void main(String[] args) throws FileNotFoundException {
		// TODO Auto-generated method stub

		//intervalRouteID();
		intervalRouteGenerateHashmap();
		ridershipSpringRouteID();
		
		
		Iterator iter = SID_R.entrySet().iterator();
		
		
	    while (iter.hasNext()) {
	        Map.Entry pair = (Map.Entry)iter.next();
	        String key = (String) pair.getKey();
	        ArrayList<String> value = (ArrayList<String>) pair.getValue();
	        
	        
	     //   System.out.println(pair.getKey()+" = "+value.size() + " = " + pair.getValue());
	       // it.remove(); // avoids a ConcurrentModificationException
	    }
		
	}

}
