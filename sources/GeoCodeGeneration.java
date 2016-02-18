import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;


public class GeoCodeGeneration {

	/**
	 * @param args
	 */
	//StopCode_Timestamps
	public static Map<String, ArrayList> SC_T = new HashMap<String, ArrayList>();
	//StopCode_Geocode
	public static Map<String, ArrayList> SC_G = new HashMap<String, ArrayList>();
	
	public static Map<String,PrintWriter> writers = new HashMap<String,PrintWriter>();
	
	
	
	public static void extractIntervalData(String busid){
		String csvFile = "D:/Fall2015/DataMining/FinalProject/CodeGeneratedFiles/Interval_busID_Files/intervalData_"+busid+".csv";
		BufferedReader br = null;
		String line = "";
		String csvSplitBy = ",";
		SC_T = new HashMap<String, ArrayList>();
		int skipyear = 0;
		try {
			br = new BufferedReader(new FileReader(csvFile));
			line = br.readLine();
			while ((line = br.readLine()) != null) {
				StringBuilder sb = new StringBuilder();
				// use tab as separator
				String[] record = line.split(csvSplitBy);
				String from = record[1];
				String to = record[2];
				String timestamp = record[6];
				if(timestamp.substring(0, 4).equals("2015-")){
					skipyear+=1;
					if(skipyear>=5)
						break;
				}
				
				
				if(from.equals(to)){
					if(SC_T.get(to) == null){
						ArrayList<String> value = new ArrayList<String>();
						value.add(timestamp);
						SC_T.put(to, value);
					}
					else{
						ArrayList<String> value = SC_T.get(to);
						if(value.size()<200){
							value.add(timestamp);
						
							SC_T.put(to, value);
						}
					}
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


		System.out.println("Done");

	}
	
	
	public static void extractGeocodeData(String busid){
		String csvFile = "D:/Fall2015/DataMining/FinalProject/CodeGeneratedFiles/Geocode_busID_Files/GeocodeData_"+busid+".csv";
		BufferedReader br = null;
		String line = "";
		String csvSplitBy = ",";
		int skipyear = 0;
		SC_G = new HashMap<String, ArrayList>();
		try {
			br = new BufferedReader(new FileReader(csvFile));
			line = br.readLine();
			while ((line = br.readLine()) != null) {
				//StringBuilder sb = new StringBuilder();
				// use tab as separator
				String[] record = line.split(csvSplitBy);
				String timestamp = record[5];
//				String subts = timestamp.substring(0, 4);
				if(timestamp.substring(0, 4).equals("2015-")){
					skipyear+=1;
					if(skipyear>=5)
						break;
				}
				//System.out.println(timestamp);
				timestamp = timestamp.substring(0, 19);
				Iterator it = SC_T.entrySet().iterator();
			    while (it.hasNext()) {
			        Map.Entry pair = (Map.Entry)it.next();
			        String stopcode = (String) pair.getKey();
			        ArrayList<String> value = (ArrayList<String>) pair.getValue();
			      //  System.out.println("timestamp:"+timestamp);
			        if(value.contains(timestamp)){
			        //	System.out.println(timestamp);
			        	if(SC_G.get(stopcode) == null){
			        		ArrayList<String> geocode = new ArrayList<String>();
			        		geocode.add(record[1].concat(","+record[2]));
			        		SC_G.put(stopcode, geocode);
			        	}
			        	else{
			        		ArrayList<String> geocode = SC_G.get(stopcode);
			        		geocode.add(record[1].concat(","+record[2]));
			        		SC_G.put(stopcode, geocode);
			        	}
			        	break;
			        }
			        
			        
//			        System.out.println(pair.getKey()+" = "+value.size() /*+ " = " + pair.getValue()*/);
			        
			       // it.remove(); // avoids a ConcurrentModificationException
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


		System.out.println("Done geocode extraction");
		
	}
	
	
	
	public static void createFileWriters(ArrayList<String> busIDS) throws FileNotFoundException{
		for(int i=0;i<busIDS.size();i++){
			PrintWriter w = new PrintWriter("D:/Fall2015/DataMining/FinalProject/CodeGeneratedFiles/Stopcode_Geocode/Geocode_"+busIDS.get(i)+".csv");
			writers.put(busIDS.get(i), w);
			writers.get(busIDS.get(i)).println("StopCode,Latitude,Longitude");
			
		
		}
		
	}

	public static void closeWriters(ArrayList<String> busIDS) throws FileNotFoundException{
		for(int i=0;i<busIDS.size();i++){
			writers.get(busIDS.get(i)).close();
		
		}
	}
	public static void main(String[] args) throws FileNotFoundException {
		// TODO Auto-generated method stub
		ArrayList<String> busIDS = new ArrayList<String>();
		for(int i=636;i<663;i++){
			busIDS.add(Integer.toString(i));
		}
		createFileWriters(busIDS);
		
		for(int i=0;i<busIDS.size();i++){
			
		String busid = busIDS.get(i);
		extractIntervalData(busid);
		//System.out.println("HELLO THERE!!");
		//System.out.println("Total stops:"+SC_T.size());
		int count = 0;
		Iterator it = SC_T.entrySet().iterator();
	    while (it.hasNext()) {
	        Map.Entry pair = (Map.Entry)it.next();
	        ArrayList<String> value = (ArrayList<String>) pair.getValue();
	       // System.out.println(pair.getKey()+" = "+value.size() /*+ " = " + pair.getValue()*/);
	        count+=value.size();
	       // it.remove(); // avoids a ConcurrentModificationException
	    }
		
		
		extractGeocodeData(busid);
		
		int g_count=0;
		Iterator iter = SC_G.entrySet().iterator();
		PrintWriter w = writers.get(busid);
		//w.println(sb);
		
	    while (iter.hasNext()) {
	        Map.Entry pair = (Map.Entry)iter.next();
	        String key = (String) pair.getKey();
	        ArrayList<String> value = (ArrayList<String>) pair.getValue();
	        for(int j=0;j<10 && j<value.size();j++){
	        	w.println(key+","+value.get(j));
	        }
	        
	      //  System.out.println(pair.getKey()+" = "+value.size() + " = " + pair.getValue());
	        g_count+=value.size();
	       // it.remove(); // avoids a ConcurrentModificationException
	    }
	    
	    w.close();
	    System.out.println(busid+" Interval Total stops:"+SC_T.size());
		System.out.println(busid+" Interval Total Timestamps(2014):"+count);
		
	    System.out.println(busid+" Geocode Total stops:"+SC_G.size());
		System.out.println(busid+" Geocode Total geocode(2014):"+g_count);
		
	    
		}
		closeWriters(busIDS);
		
	}

}
