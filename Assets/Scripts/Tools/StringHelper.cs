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
			// Contrôle que la valeur à trouver ne soit pas vide ou que la source se termine bien par la valeur à chercher
			if (string.IsNullOrEmpty(source) || string.IsNullOrEmpty(value) || !source.EndsWith(value))
			{
				return source;
			}

			return source.Remove(source.LastIndexOf(value, System.StringComparison.OrdinalIgnoreCase));
		}

		/// <summary>
		/// Supprimer la dernière partie d'un texte source à partir d'un string passé en paramètre
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