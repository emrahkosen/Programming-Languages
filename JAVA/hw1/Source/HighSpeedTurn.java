public class HighSpeedTurn extends TrackFeature {

  public HighSpeedTurn(int turnNo, TurnDirection direction, double distance, double roughness) {
    // Fill this method
	  featureNo = turnNo;
	  this.roughness = roughness;
	  turnDirection = direction;
	  this.distance = distance;
  }

@Override
public double typeFeature() {
	// TODO Auto-generated method stub
	return 1.55;
}
}