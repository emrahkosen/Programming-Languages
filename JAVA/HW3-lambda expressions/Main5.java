public class Main5 {
  public static void main(String[] args) {
    // Tested with args = ["512"]
    try{
    PartsStore a =new PartsStore();
    int cap = Integer.parseInt(args[0]);
    a.FindFastestCPU();
    a.FindCheapestMemory(cap);
    a.UpdateStock();
    a.FindFastestCPU();
    a.FindCheapestMemory(cap);
    } catch(Exception e){
      System.out.println(e);
    }
  }
}
