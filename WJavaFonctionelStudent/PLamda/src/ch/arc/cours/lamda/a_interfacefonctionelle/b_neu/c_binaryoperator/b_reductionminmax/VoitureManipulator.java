
package ch.arc.cours.lamda.a_interfacefonctionelle.b_neu.c_binaryoperator.b_reductionminmax;

import java.util.function.BinaryOperator;

import ch.arc.cours.lamda.a_interfacefonctionelle.b_neu.c_binaryoperator.b_reductionminmax.tools.Voiture;

public class VoitureManipulator
	{

/*------------------------------------------------------------------*\
|*							Methodes Public							*|
\*------------------------------------------------------------------*/


	/**
	 * see chapter stream to see beautiful flexible optimized code
	 */
	public static Voiture reduce(Iterable<Voiture> iterable,  BinaryOperator<Voiture> operator, Voiture initValue)
		{
		Voiture value = initValue;

		for(Voiture voiture:iterable)
			{
			// TODO
			}

		return value;
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/
	}



