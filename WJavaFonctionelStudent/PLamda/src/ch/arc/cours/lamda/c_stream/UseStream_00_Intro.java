
package ch.arc.cours.lamda.c_stream;

import java.util.Arrays;
import java.util.List;
import java.util.stream.Stream;

import org.junit.Assert;

public class UseStream_00_Intro
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
		System.out.println("Stream : list array");

		// obtenir un stream
		useList1();
		useList2();

		useArray1();

		// see too
		//	UseIterable
		//	UseInfinite (advanced)
		// 	UseParallel
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	/*------------------------------*\
	|*				List			*|
	\*------------------------------*/

	/**
	 * fabrication stream et count
	 */
	private static void useList1()
		{
		List<Integer> list = Arrays.asList(1, 2, 3);

		// v1 (avec variable explicite stream)
			{
			Stream<Integer> stream = list.stream(); // stream: équivalant des | en Linux

			long count = stream.count();
			// count : terminal, impossible employer stream ensuite

			Assert.assertTrue(count == list.size());
			}

		// v2 (sans varaible explicite stream)
			{
			long count = list.stream().count();
			// count : terminal, impossible employer stream ensuite

			Assert.assertTrue(count == list.size());
			}
		}

	/**
	 * fabrication stream et count partielle
	 *
	 * Quoi: 		recuperation des m=2 premiers du stream, puis count
	 * Comment : 	limit, count
	 */
	private static void useList2()
		{
		List<Integer> list = Arrays.asList(1, 2, 3);

		int m = 2;

		long count = list.stream().limit(m).count();
		// limit : non terminal, stream-in -> stream-out
		// count : terminal, impossible employer stream ensuite

		Assert.assertTrue(count == m);
		}

	/*------------------------------*\
	|*				Array			*|
	\*------------------------------*/

	/**
	 * fabrication stream et count
	 */
	private static void useArray1()
		{
		Integer[] tab = { 1, 2, 3 };

		long count = Arrays.stream(tab).count();
		// count : terminal, impossible employer stream ensuite

		Assert.assertTrue(count == tab.length);
		}

	}
