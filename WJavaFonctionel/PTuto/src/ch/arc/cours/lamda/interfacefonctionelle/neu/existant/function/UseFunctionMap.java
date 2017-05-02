
package ch.arc.cours.lamda.interfacefonctionelle.neu.existant.function;

import java.util.function.Function;

import ch.arc.cours.lamda.interfacefonctionelle.neu.existant.function.tools.Maison;

public class UseFunctionMap
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
		System.out.println("map : Function");

		mapping();
		}

	private static void mapping()
		{
		int prix = 1;
		int nbPiece = 2;
		int surface = 3;
		Maison maison = new Maison(prix, nbPiece, surface);

		printSurface(maison);
		printPrix(maison);
		printPiece(maison);
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	private static void mapPrint(Maison maison, Function<Maison, Integer> function)
		{
		int attribut = function.apply(maison);
		System.out.println(attribut);
		}

	/*------------------------------*\
	|*				lamda			*|
	\*------------------------------*/

	private static void printSurface(Maison maison)
		{
		// version : classe interne anonyme
			{
			Function<Maison, Integer> function = new Function<Maison, Integer>()
				{

				@Override
				public Integer apply(Maison maison)
					{
					return maison.getSurface();
					}
				};
			mapPrint(maison, function);
			}

		// Version : lambda dans variable
			{
			Function<Maison, Integer> function = casa -> casa.getSurface();
			mapPrint(maison, function);
			}

		// Version : lambda
			{
			mapPrint(maison, casa -> casa.getSurface());
			}
		}

	private static void printPiece(Maison maison)
		{
		// Version : lambda
			{
			mapPrint(maison, casa -> casa.getNbPiece());
			}
		}

	private static void printPrix(Maison maison)
		{
		// Version : lambda
			{
			mapPrint(maison, casa -> casa.getPrix());
			}
		}

	}
