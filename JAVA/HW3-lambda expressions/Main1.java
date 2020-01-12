public class Main1 {
  public static void main(String[] args) {
    // Tested with args = ["GPU", "Zotac", "GeForce RTX 2080"]
    try{
    PartsStore a =new PartsStore();
    String type = args[0].equals("null")?null:args[0];
    String brand = args[1].equals("null")?null:args[1];
    String model = args[2].equals("null")?null:args[2];
    a.TotalPrice(type, brand, model);
    } catch(Exception e){
      System.out.println(e);
    }
  }
}
