import java.util.ArrayList;

public class Track {

  private String trackName;
  private ArrayList<TrackFeature> featureList;
  private boolean isClockwise;
  private int next;     /*ben ekledim getNextFeature için*/
  
  
  
  
  public Track() {
    // Fill this method
	  this.next = 0;
  }

  
  
  public Track(String trackName, ArrayList<TrackFeature> featureList, boolean isClockwise) {
    // Fill this method
	  this.trackName = trackName;
	  this.isClockwise = isClockwise;
	  this.featureList = new ArrayList<TrackFeature>(featureList.size());
	  for(TrackFeature tf : featureList )
	  {
		  this.featureList.add(tf);
	  }
	  
	  this.next = 0;
	  
  }

  public String getTrackName() {
    return trackName;
  }

  public void setTrackName(String trackName) {
    this.trackName = trackName;
  }

  public ArrayList<TrackFeature> getFeatureList() {
    return featureList;
  }

  public void setFeatureList(ArrayList<TrackFeature> featureList) {
    this.featureList = featureList;
  }

  public boolean isClockwise() {
    return isClockwise;
  }

  public void setClockwise(boolean clockwise) {
    isClockwise = clockwise;
  }
  
  
  

  public int getTrackLength() {
	return featureList.size();
  }

  public TrackFeature getNextFeature() {
	  
	  next = (next + 1)%getTrackLength();
	  
	  int featureNO ;
	  if(next == 0)
		  featureNO = getTrackLength()-1;
	  else
		  featureNO = next-1;
	  
	  return featureList.get(featureNO);
    // Fill this method
  }

  public void addFeature(TrackFeature feature) {
    // Fill this method
	  this.featureList.add(feature);
  }

  /***************yapılacak**********************/
  
  public boolean isValidTrack() 
  {
	// Fill this method
	  int len = featureList.size();
	  if(featureList.get(0).getTurnDirection() == TurnDirection.STRAIGHT)
	  {
		  if(featureList.get(len-1).getTurnDirection() == TurnDirection.STRAIGHT)
		  {
			  int four = 0;
			  for(int i = 0 ; i< len; i++)
			  {
				  if(featureList.get(i).getTurnDirection() == TurnDirection.LEFT)
				  {
					  four--;
				  }
				  if(featureList.get(i).getTurnDirection() == TurnDirection.RIGHT)
				  {
					  four++;
				  }
			  }
			  if(four == 4)
				  return true;
		  }
	  }
	  
	  
	return false;
    
  }
  
  /****************************************/
}
