public class Car {

  private int carNo;
  private String driverName;
  private double totalTime;
  private Tire tire;

  public Car() {
    // Fill this method
  }

  public Car(String driverName, int carNo, Tire tire) {
    // Fill this method
	  this.driverName = driverName;
	  this.carNo = carNo;
	  this.tire = tire;
	  totalTime = 0;
  }

  public Tire getTire() {
    return tire;
  }

  public void setTire(Tire tire) {
    this.tire = tire;
  }

  public String getDriverName() {
    return driverName;
  }

  public void setDriverName(String driverName) {
    this.driverName = driverName;
  }

  public int getCarNo() {
    return carNo;
  }

  public void setCarNo(int carNo) {
    this.carNo = carNo;
  }

  public double getTotalTime() {
    return totalTime;
  }

  public void tick(TrackFeature feature) {
	  double featuredistance = feature.getDistance();
	  double tirespeed = tire.getSpeed();
	  double random = Math.random();
	  totalTime += featuredistance/tirespeed + random;
	//  System.out.println(getCarNo() + "  tire " + tirespeed + "  rand " + random);
	  
  }
  
  
  public void newTire() // degradation value goes over 70
	{
	  if(tire.type() == 0)
		  setTire( new MediumTire());
		  
	  else
		  setTire( new SoftTire());
	  
	  totalTime += 25;
	  
	 }
  
  
  
  
  
  

}
