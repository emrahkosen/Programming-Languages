import java.util.ArrayList;

public class Session {

  private Track track;
  private ArrayList<Team> teamList;
  private int totalLaps;

  public Session() {
    // Fill this method
  }

  public Session(Track track, ArrayList<Team> teamList, int totalLaps) {
    // Fill this method
	  this.track = track;
	  this.teamList = new ArrayList<Team>(teamList.size());
	  for(Team t: teamList)
		  this.teamList.add(t);
	  this.totalLaps = totalLaps;
  }

  public Track getTrack() {
    return track;
  }

  public void setTrack(Track track) {
    this.track = track;
  }

  public ArrayList<Team> getTeamList() {
    return teamList;
  }

  public void setTeamList(ArrayList<Team> teamList) {
    this.teamList = teamList;
  }

  public int getTotalLaps() {
    return totalLaps;
  }

  public void setTotalLaps(int totalLaps) {
    this.totalLaps = totalLaps;
  }

  
  
  
  public void simulate() {
    // Fill this method
	  if(!track.isValidTrack())
	  {
		  System.out.println("Track is invalid.Simulation aborted!");
		  return;
	  }
     System.out.println("Track is valid.Strating simulation on " + track.getTrackName()+  " for " + totalLaps + " laps.");
	  for(int lap= 0; lap < totalLaps; lap++)
	  {
		  int trackSize = track.getFeatureList().size();
		  for(int i = 0; i< trackSize ; i++)
		  {
			  TrackFeature currentfeature = track.getFeatureList().get(i);
			  for(int team = 0; team < teamList.size(); team++)
			  {
				
				  for(int car = 0  ; car < teamList.get(team).getCarList().size(); car ++ )
				  {
					  teamList.get(team).getCarList().get(car).tick(currentfeature);
					  teamList.get(team).getCarList().get(car).getTire().tick(currentfeature);
					 /**********************/ 
					  if(teamList.get(team).getCarList().get(car).getTire().getDegradation() > 70)
					  {
						  teamList.get(team).getCarList().get(car).newTire();
					  }
					 /**********************/ 
				  }
			  }
			  
		  }
	  }
	  
	  String winTeam = printWinnerTeam();
	 System.out.println(winTeam);
	 String team = printTimingTable();
  }

  
  
  public String printWinnerTeam() {
	  
	  int winner = findwinner();
	  String ret = "Team " + teamList.get(winner).getName() + " wins.";
	 // ret.concat(teamList.get(winner).getName());
	 // ret.concat("wins.");
	  int len = teamList.get(winner).getTeamColors().length;//winner team length
	  
	  
	  
	  ret += teamList.get(winner).getTeamColors()[0];
	  for(int i = 1; i < len-1;i++)
	  {
		  ret +=  ", " + teamList.get(winner).getTeamColors()[i] ;
	  }
	  if(teamList.get(winner).getTeamColors().length > 1)
	  {  
		  ret += " and ";
		  ret += teamList.get(winner).getTeamColors()[len-1];
	  }
	  
	  
	  ret += " flags are waving everywhere.";
	  
	  
	  
	  
	  
	  
	  return ret;
	
	
  }

  
  
  
  
  
  private String printTimingTable() {
	 
	  /*
	  int winnerTeam = findwinner();
	  String ret = teamList.get(winnerTeam).getName();
	 //ret.concat(teamList.get(winner).getName());
	  //teamList.get(team).getCarList().get(car).getTotalTime();
	  int sort = 0;
	  for(int car = 0; car < teamList.get(winnerTeam).getCarList().size(); car++)
	  {
		  if(teamList.get(winnerTeam).getCarList().get(car).getTotalTime() < teamList.get(winnerTeam).getCarList().get(sort).getTotalTime())
		  {
			  sort = car;
		  }
	  }
	  
	 // System.out.println(teamList.get(winnerTeam).getCarList().size());
	  
	  
	  int tm = (int)teamList.get(winnerTeam).getCarList().get(sort).getTotalTime();
	  int ms = tm%1000;
	  int sec = (tm%(1000*60))/(1000);;
	  int minute = (tm%(1000*60*60))/(1000*60);;
	  int hours = (tm)/(1000*60*60);
	  
	  System.out.println(teamList.get(winnerTeam).getCarList().get(sort).getDriverName() + "(" + teamList.get(winnerTeam).getCarList().get(sort).getCarNo() + "):  "
			  +hours+ ":"+minute+":"+sec+"."+ ms );
	  
	  
	  
	  double prewiousTime = teamList.get(winnerTeam).getCarList().get(sort).getTotalTime();
	  */
	  int cars = 0;
	  for(int i = 0; i < teamList.size(); i++ )
	  {
		  cars += teamList.get(i).getCarList().size();
	  }
	  
	  
	  ArrayList<Car> AllCarList = new ArrayList<Car>(cars);
	  
	  
	  
	  for(int i = 0; i< teamList.size(); i++ )
	  {
		  for(int car = 0; car < teamList.get(i).getCarList().size(); car++)
		  {
			  AllCarList.add(teamList.get(i).getCarList().get(car));
		  }
	  }
		  
	  
	  
	  
	  for(int i = 0; i < cars ; i++)
	  {
		  double ShortTime = AllCarList.get(0).getTotalTime();
		  int sortOne = 0;
		  for(int car= 0; car <  AllCarList.size(); car++)
		  {
			  if(AllCarList.get(car).getTotalTime() < ShortTime)
			  {
				  ShortTime = AllCarList.get(car).getTotalTime();
				  sortOne = car;
			  }
		  }
		  
		  /*
		  int presort = sort;
		  sort = 0;
		  for(int car = 0; car < teamList.get(winnerTeam).getCarList().size(); car++)
		  {
			  
			  if(prewiousTime < teamList.get(winnerTeam).getCarList().get(car).getTotalTime())
			  {
				  
				  if(sort == presort)
				  {
					  sort = car;
				  }
				  
				  if(teamList.get(winnerTeam).getCarList().get(car).getTotalTime() < teamList.get(winnerTeam).getCarList().get(sort).getTotalTime())
				  {
					  sort = car;
				  }
			  }
			  
		  }
		  */
		  int tm = (int)(AllCarList.get(sortOne).getTotalTime()*1000);
		  int ms = tm%1000;
		  int sec =  (tm%(1000*60))/1000;
		  int minute = (tm%(1000*60*60))/(1000*60);
		  int hours = (tm)/(1000*60*60);
		  
		  System.out.printf(AllCarList.get(sortOne).getDriverName() + "(" + AllCarList.get(sortOne).getCarNo() + "):  "
				  +hours+ ":"+minute+":"+sec+"." );
		  if(ms>= 100 )
			  System.out.println(ms);
		  else if(ms >= 10)
		  {
			  System.out.println("0" + ms);
		  }
		  else
			  System.out.println("00" + ms);
		  AllCarList.remove(sortOne);
	  }
	  
	  
	  
	  
	return "ret";

  }
  
  
  
  
  
  
  
  private int findwinner()
  {
	  double mintime = teamList.get(0).getCarList().get(0).getTotalTime();
	  int winner = 0;
	  for(int team = 0; team < teamList.size(); team++)
	  {	  
		  for(int car = 0  ; car < teamList.get(team).getCarList().size(); car ++ )
		  {

			  if(teamList.get(team).getCarList().get(car).getTotalTime() < mintime)
			  {
				  mintime = teamList.get(team).getCarList().get(car).getTotalTime();
				  winner = team;
			  }
		  }
	  }
	  return winner;
  }
  
   
  
  
  
  
  
  
}