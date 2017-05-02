
package ch.arc.cours.lamda.a_interfacefonctionelle.b_neu.b_consumer;

import ch.arc.cours.lamda.a_interfacefonctionelle.b_neu.a_predicate.tools.Homme;
import ch.arc.cours.lamda.a_interfacefonctionelle.b_neu.a_predicate.tools.HommeTools;

public class UseConsumer
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
		System.out.println("foreach : Consumer");

		foreach();
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	private static void foreach()
		{
		int n = 5;

		version1(n);

		// lamda
			{
			version2(n);
			version3(n);
			}
		}

	/*------------------------------*\
	|*			Consumer<T>			*|
	\*------------------------------*/

	/**
	 * Quoi 	: 	Opposer le poids de l'homme
	 * Exemple  :	7 -> -7
	 * Comment	: 	use methode opposePoids
	 *
	 * Essayer aussi provisoirement : afficher le poids de l'homme!
	 *
	 * classe interne anonyme
	 */
	private static void version1(int n)
		{
		Iterable<Homme> iterable = HommeTools.create(n);

		System.out.println("Before  : " + iterable + "\n");

		// TODO

		System.out.println("After 1 : " + iterable);
		}

	/**
	 * Opposer le poids de l'homme
	 *
	 * lamda dans variable
	 */
	private static void version2(int n)
		{
		Iterable<Homme> iterable = HommeTools.create(n);

		// TODO

		System.out.println("After 2 : " + iterable);
		}

	/**
	 * Opposer le poids de l'homme
	 *
	 * lamda
	 */
	private static void version3(int n)
		{
		Iterable<Homme> iterable = HommeTools.create(n);

		// TODO

		System.out.println("After 3 : " + iterable);
		}

	}
