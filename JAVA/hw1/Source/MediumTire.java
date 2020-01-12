public class MediumTire extends Tire {

  public MediumTire() {
    this.speed = 310;
    this.degradation = 0;
  }

@Override
public void tick(TrackFeature f) {
	// TODO Auto-generated method stub
	double featureMultiplier = f.typeFeature();
	double featurerought = f.getRoughness();
	
	
	this.degradation +=  featureMultiplier*featurerought*1.1;
	if(this.speed > 100)
		this.speed -= Math.min(75, this.degradation)*0.25;	
	
}

@Override
public int type() {
	return 1;
}
}
