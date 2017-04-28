
package ch.arc.cours.lamda.interfacefonctionelle.neu.existant.binaryoperator.generic;

import java.util.Arrays;

import org.junit.Assert;

import ch.arc.cours.lamda.interfacefonctionelle.neu.existant.binaryoperator.NumberTools;

public class UseReduceAdd
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
		System.out.println("reduce : BinaryOperator<Integer> : add");
		reduceAdd();
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	private static void reduceAdd()
		{
		int n = 3;
		int[] tab = NumberTools.create(n);

		int sum1 = version1(tab);
		int sum2 = version2(tab);
		int sum3 = version3(tab);

		System.out.println(Arrays.toString(tab));
		System.out.println("sum = " + sum1);
		System.out.println("sum = " + sum2);
		System.out.println("sum = " + sum3);

		Assert.assertTrue(sum1 == n * (n + 1) / 2);
		Assert.assertTrue(sum2 == n * (n + 1) / 2);
		Assert.assertTrue(sum3 == n * (n + 1) / 2);
		}

	/*------------------------------*\
	|*				add				*|
	\*------------------------------*/

	/**
	 * classe interne anonyme
	 */
	private static int version1(int[] tab)
		{
		// TODO
		}

	/**
	 * lamda dans variable
	 */
	private static int version2(int[] tab)
		{
		// TODO
		}

	/**
	 * lamda
	 */
	private static int version3(int[] tab)
		{
		// TODO
		}

	}
