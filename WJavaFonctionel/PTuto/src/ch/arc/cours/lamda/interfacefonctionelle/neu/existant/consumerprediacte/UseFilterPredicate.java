
package ch.arc.cours.lamda.interfacefonctionelle.neu.existant.consumerprediacte;

import java.util.function.Predicate;

import ch.arc.cours.lamda.interfacefonctionelle.neu.existant.consumerprediacte.tools.Homme;
import ch.arc.cours.lamda.interfacefonctionelle.neu.existant.consumerprediacte.tools.HommeTools;

public class UseFilterPredicate
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
		System.out.println("filter : Predicate");

		filter();
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	private static void filter()
		{
		int n = 10;

		version1(n);

		// lamda
			{
			version2(n);
			version3(n);
			}
		}

	private static void version1(int n)
		{
		Iterable<Homme> iterable = HommeTools.create(n);

		System.out.println(iterable);

		Predicate<Homme> predicate = new Predicate<Homme>()
			{

			@Override
			public boolean test(Homme homme)
				{
				return homme.getHauteur() > 25;
				}
			};

		Iterable<Homme> iterableFiltrer = HommeManipulator.filter(iterable, predicate);

		System.out.println(iterableFiltrer);
		}

	/*------------------------------*\
	|*				lamda			*|
	\*------------------------------*/

	/**
	 * lamda dans variable
	 */
	private static void version2(int n)
		{
		Iterable<Homme> iterable = HommeTools.create(n);

		Predicate<Homme> hauteurBigger20 = homme -> homme.getHauteur() > 20;

		Iterable<Homme> iterableFiltrer = HommeManipulator.filter(iterable, hauteurBigger20);

		System.out.println(iterableFiltrer);
		}

	/**
	 * lamda
	 */
	private static void version3(int n)
		{
		Iterable<Homme> iterable = HommeTools.create(n);

		Iterable<Homme> iterableFiltrer = HommeManipulator.filter(iterable, homme -> homme.getHauteur() > 20);

		System.out.println(iterableFiltrer);
		}

	}
