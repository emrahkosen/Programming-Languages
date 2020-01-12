public class Main0 {
  // FindPartsWithBrand
  public static void main(String[] args) {
    // Tested with args = ["GPU", "Zotac"]
    try{
    PartsStore a =new PartsStore();
    String type = args[0].equals("null")?null:args[0];
    String brand = args[1];
    a.FindPartsWithBrand(type, brand);
    } catch(Exception e){
      System.out.println(e);
    }
  }
}
