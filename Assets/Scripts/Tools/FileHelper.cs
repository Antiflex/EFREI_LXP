using System;
using System.IO;
using System.Text.RegularExpressions;
using UnityEngine;
#if UNITY_ANDROID && !UNITY_EDITOR
using System.Linq;
#endif

namespace Assets.Scripts.Tools
{
	/// <summary>
	/// Gestion fichiers
	/// </summary>
	public static class FileHelper
	{
		/// <summary>
		/// Obtenir tous les fichiers d'un répertoire
		/// Gestion avec Android
		/// </summary>
		/// <param name="directoryPath"></param>
		/// <param name="streamingAssetsRootPath">Détermine si on veut récupérer les fichiers listés dans StreamingAssets. Si oui, on gère pour Android</param>
		/// <param name="filterExtension"></param>
		/// <returns></returns>
		/// <exception cref="ArgumentNullException"></exception>
		public static string[] GetAllFiles(string directoryPath, bool streamingAssetsRootPath = false, string filterExtension = "")
		{
			if (string.IsNullOrWhiteSpace(directoryPath))
			{
				throw new ArgumentNullException(nameof(directoryPath));
			}

#if UNITY_ANDROID && !UNITY_EDITOR
			// Pour l'instant uniquement pour les fichiers se trouvant dans StreamingAssets
			if (streamingAssetsRootPath)
			{
				// On va utiliser le potentiel fichier de listing des StreamingAssets
				var filePaths = GetPathsFromStreaminAssetsListing();

				if (!filePaths.IsNullOrCountZero())
				{
					var filteredFilePaths = filePaths;

					if (filteredFilePaths.Any(f => f.StartsWith(directoryPath)))
					{
						filteredFilePaths = filteredFilePaths.Where(f => f.StartsWith(directoryPath)).ToArray();
					}

					if (!string.IsNullOrWhiteSpace(filterExtension))
					{
						filteredFilePaths =
							filteredFilePaths?.Where(f => Path.GetExtension(f).Equals(filterExtension, StringComparison.OrdinalIgnoreCase))?.ToArray();
					}

					return filteredFilePaths;
				}
			}

			return null;

#else
			return Directory.GetFiles(directoryPath);
#endif

		}
	}
}
