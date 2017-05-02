
package ch.arc.cours.lamda.interfacefonctionelle.old.runnable;

public class UseRunnable
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
		version1();
		version2();
		version3();
		version4();

		// Version lamda
			{
			version5();
			version5Bis();
			version6();
			version6Bis();
			}
		}

	private static void version1()
		{
		Runnable runnable = new RunnableSeparer();

		Thread thread = new Thread(runnable);
		thread.start();
		}

	private static void version2()
		{
		Runnable runnable = new Runnable()
			{

			@Override public void run()
				{
				System.out.println("Hello2");
				}
			};

		Thread thread = new Thread(runnable);
		thread.start();
		}

	private static void version3()
		{
		Thread thread = new Thread(new Runnable()
			{

			@Override public void run()
				{
				System.out.println("Hello3");
				}
			});

		thread.start();
		}

	/**
	 * classe interne anonyme
	 * sans variable
	 */
	private static void version4()
		{
		// TODO
		}

	/*------------------------------*\
	|*		Version lamda			*|
	\*------------------------------*/

	/**
	 * Expression lamda, SYNTAXE FULL
	 */
	private static void version5()
		{
		// TODO
		}

	/**
	 * Expression lamda dans variable,SYNTAXE FULL
	 */
	private static void version5Bis()
		{
		// TODO
		}

	/**
	 * Expression lamda, SYNTAXE LIGHT
	 */
	private static void version6()
		{
		// TODO
		}

	/**
	 * Expression lamda dans variable,SYNTAXE LIGHT
	 */
	private static void version6Bis()
		{
		// TODO
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	}
