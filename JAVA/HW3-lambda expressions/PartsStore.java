

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class PartsStore
{
	  String txtFileName = "pcparts.csv";
	  List<List<String>> list;

	  public PartsStore()
	  {
		  list = new ArrayList<>();
		  try (Stream<String> stream = Files.lines(Paths.get(txtFileName)))
			{


				list = stream.map(line ->
				{
					List<String> str = Arrays.asList(line.split(","));
					return str;
				}).collect(Collectors.toList());

			} catch (IOException ioe) {
				ioe.printStackTrace();
			}
	  }



	  public void FindPartsWithBrand(String type, String brand)
		{
			if(type == null)
				type = "";
			final String type2 = type;
			if(brand == null)
				brand = "";
			final String brand2 = brand;



				//List<List<String>> list2 = list.stream().filter(line -> line.contains(type2) && line.contains(brand2) ).collect(Collectors.toList());
	 /*


				List<String> list3 = list.stream().
						map(line ->
						{
							return line.stream()
							           .map(Object::toString)
							           .collect(Collectors.joining(", "));

						}).filter(line -> line.contains(type2) && line.contains(brand2) ).collect(Collectors.toList());
				        //.collect(Collectors.joining("\n")).toString();
						//System.out.println(list3);//for string of list3
				list3.forEach(System.out::println);


				*/
				list.stream()
							.map(line ->
							{
								return line.stream()
								           .map(Object::toString)
								           .collect(Collectors.joining(","));

							})
							.filter(line -> line.contains(type2) && line.contains(brand2) )
							.collect(Collectors.toList())
							.forEach(System.out::println);






		}

	  public void TotalPrice(String type, String brand, String model)
	  {
		  if(type == null)
				type = "";
			final String type2 = type;
		  if(brand == null)
				brand = "";
		  final String brand2 = brand;
		  if(model == null)
			  model = "";
		  final String model2 = model;

		  double sum;
		/*
			  	List<String> list3 = list.stream()
						.map(line ->
						{
							return line.stream()
							           .map(Object::toString)
							           .collect(Collectors.joining(", "));

						}).filter(line -> line.contains(type2) && line.contains(brand2) && line.contains(model2) )
						  .collect(Collectors.toList());


				sum = list3.stream().mapToDouble(str -> {
					                                        List<String> l = Arrays.asList(str.split(","));
															String price = l.get(l.size()-1);
															price = price.substring(0, price.length() - 4);
															return Double.parseDouble(price);
														}).sum();
				//list.forEach(System.out::println);
				System.out.println(sum + " USD");
		*/
				sum = list.stream()
									.map(line ->
									{
										return line.stream()
										           .map(Object::toString)
										           .collect(Collectors.joining(","));

									})
									.filter(line -> line.contains(type2) && line.contains(brand2) && line.contains(model2+",") )
									.mapToDouble(str ->
									{
			                            List<String> l = Arrays.asList(str.split(","));
										String price = l.get(l.size()-1);
										price = price.substring(0, price.length() - 4);
										return Double.parseDouble(price);
									})
									.sum();
				System.out.println(sum + " USD");



	  }



	  public void UpdateStock()
	  {

				List<List<String>> list2 = list.stream()
				.filter(l -> {
					String price = l.get(l.size() - 1);
					double cpi = Double.parseDouble(price.substring(0, price.length() - 4));
					return cpi != 0;
				}).collect(Collectors.toList());


				int remove = list.size() - list2.size();
				System.out.println(remove + " items removed.");
				list = list2;

	  }

	  public void FindCheapestMemory(int capacity)
	  {

/*

				 List<List<String>> list1 = list.stream().filter(line -> line.contains("Memory") )
						 								 .collect(Collectors.toList());


				Optional<List<String>> list2 = list1.stream().filter(l -> {
					String cp = l.get(4);
					int cpi = Integer.parseInt(cp.substring(0, cp.length() - 2));
					return cpi == capacity;
				}).min(( l1, l2 ) ->  {
										double price1 = Double.parseDouble(l1.get(6).substring(0, l1.get(6).length() - 4));
										double price2 = Double.parseDouble(l2.get(6).substring(0, l2.get(6).length() - 4));
										return Double.compare(price1, price2);
									  });


				list2.ifPresent(name -> System.out.println(name.stream()
							.map(Object::toString)
				            .collect(Collectors.joining(", "))));
*/
				list.stream().filter(line -> line.contains("Memory") )
				 			 .filter(l ->
				 			 {
										String cp = l.get(4);
										int cpi = Integer.parseInt(cp.substring(0, cp.length() - 2));
										return cpi >= capacity;
							 })
				 			 .min(( l1, l2 ) ->
				 			 {
										double price1 = Double.parseDouble(l1.get(6).substring(0, l1.get(6).length() - 4));
										double price2 = Double.parseDouble(l2.get(6).substring(0, l2.get(6).length() - 4));
										return Double.compare(price1, price2);
							})
				 			 .ifPresent(name -> System.out.println(name.stream()
																			.map(Object::toString)
																            .collect(
																            			Collectors.joining(",")
																            		)
																  )
				 					   );


	  }

	  public void FindFastestCPU()
	  {
/*
				List<List<String>> list1 = list.stream().filter(line -> line.contains("CPU") ).collect(Collectors.toList());



				Optional<List<String>> line = list1.stream().max(( l1, l2 ) ->  //l1.get(4).compareTo(l2.get(4)
				  {
					double ghz1 = Double.parseDouble(l1.get(4).substring(0, l1.get(4).length() - 3));
					double ghz2 = Double.parseDouble(l2.get(4).substring(0, l2.get(4).length() - 3));
					return Double.compare(ghz1, ghz2);
				  });

				line.ifPresent(name -> System.out.println(name.stream()
							.map(Object::toString)
				            .collect(Collectors.joining(", "))));

*/
			list.stream().filter(l -> l.contains("CPU") )
						 .max(( l1, l2 ) ->
										  {
											double ghz1 = Double.parseDouble(l1.get(4).substring(0, l1.get(4).length() - 3))* Double.parseDouble(l1.get(3));
											double ghz2 = Double.parseDouble(l2.get(4).substring(0, l2.get(4).length() - 3))* Double.parseDouble(l2.get(3));
											return Double.compare(ghz1, ghz2);
										  })
						 .ifPresent(name -> System.out.println(name.stream()
								 										.map(Object::toString)
								 										.collect(Collectors.joining(","))
								 							  )
								   );





		}

}
