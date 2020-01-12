public class HardTire extends Tire {

  public HardTire() {
    this.speed = 275;
    this.degradation = 0;
  }

@Override
public void tick(TrackFeature f) {
	// TODO Auto-generated method stub
	
	double featureMultiplier = f.typeFeature();
	double featurerought = f.getRoughness();	

	
	this.degradation +=  featureMultiplier*featurerought*1.0;
	if(this.speed > 100)
		this.speed -= Math.min(75, this.degradation)*0.25;	
	
}

@Override
public int type() {
	// TODO Auto-generated method stub
	return 2;
}
}