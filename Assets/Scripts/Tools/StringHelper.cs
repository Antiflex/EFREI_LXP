namespace Assets.Scripts.Tools
{
	public static class StringHelper
	{
		/// <summary>
		/// TrimEnd avec un string
		/// </summary>
		/// <param name="source"></param>
		/// <param name="value"></param>
		/// <returns></returns>
		public static string TrimEnd(this string source, string value)
		{
			// Contr�le que la valeur � trouver ne soit pas vide ou que la source se termine bien par la valeur � chercher
			if (string.IsNullOrEmpty(source) || string.IsNullOrEmpty(value) || !source.EndsWith(value))
			{
				return source;
			}

			return source.Remove(source.LastIndexOf(value, System.StringComparison.OrdinalIgnoreCase));
		}

		/// <summary>
		/// Supprimer la derni�re partie d'un texte source � partir d'un string pass� en param�tre
		/// </summary>
		/// <param name="source"></param>
		/// <param name="value"></param>
		/// <returns></returns>
		public static string TrimEndStartsWith(this string source, string value)
		{
			if (string.IsNullOrEmpty(source) || string.IsNullOrEmpty(value) || !source.Contains(value))
			{
				return source;
			}

			int lastPosition = source.LastIndexOf(value, System.StringComparison.OrdinalIgnoreCase);

			if (lastPosition >= 0)
			{
				return source.Substring(0, lastPosition);
			}

			return source;
		}
	}
}