
package ch.arc.cours.lamda.c_stream;

import java.util.Arrays;
import java.util.List;
import java.util.stream.Stream;
import java.util.stream.StreamSupport;

import org.junit.Assert;

public class UseStream_03_Iterable
	{
	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	public static void main(String[] args)
		{
		main();
		}

	public static void main()
		{
		System.out.println("Stream from Iterable");

		// obtenir un stream
		useIterable();

		// see too UseInfinite (advanced)
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	/**
	 * recuperation et count
	 */
	private static void useIterable()
		{
		List<Integer> list = Arrays.asList(1, 2, 3);

		work1(list);
		work2(list);
		}

	private static void work1(Iterable<Integer> iterable)
		{
		boolean isParallel = false;

		Stream<Integer> stream = StreamSupport.stream(iterable.spliterator(), isParallel);

		Assert.assertTrue(stream.isParallel() == isParallel);
		Assert.assertTrue(stream.count() == 3);

		// Interdit : stream déja close, avec count terminal!
			{
			//Assert.assertTrue(stream.count() == 3);
			}
		}

	/**
	 * somme des elements
	 */
	private static void work2(Iterable<Integer> iterable)
		{
		boolean isParallel = true;

		Stream<Integer> stream = StreamSupport.stream(iterable.spliterator(), isParallel);
		Integer sum = stream.reduce(0, Integer::sum);

		Assert.assertTrue(sum == 1 + 2 + 3);
		}

	}
