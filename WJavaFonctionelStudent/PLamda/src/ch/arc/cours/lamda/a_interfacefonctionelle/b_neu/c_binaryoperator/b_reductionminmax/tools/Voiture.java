
package ch.arc.cours.lamda.a_interfacefonctionelle.b_neu.c_binaryoperator.b_reductionminmax.tools;

public class Voiture
	{

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/

	public Voiture(int prix, int poids)
		{
		this.prix = prix;
		this.poids = poids;
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	@Override
	public String toString()
		{
		StringBuilder builder = new StringBuilder();
		builder.append("Voiture [prix=");
		builder.append(this.prix);
		builder.append(", poids=");
		builder.append(this.poids);
		builder.append("]");
		return builder.toString();
		}

	/*------------------------------*\
	|*				Get				*|
	\*------------------------------*/

	public int getPrix()
		{
		return this.prix;
		}

	public int getPoids()
		{
		return this.poids;
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	// Inputs/Outputs
	private int prix;
	private int poids;

	}
